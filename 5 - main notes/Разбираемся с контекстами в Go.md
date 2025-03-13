**2025-02-15 11:42**
**Tags:** [[go]]

## Разбираемся с контекстами в Go
### Что такое контекст?
*Контекст* - это объект, который предназначен в первую очередь для того, чтобы иметь возможность отменить извне выполнение потенциально долгой операции. Кроме того, с помощью контекста можно хранить и передавать информацию между функциями и методами внутри нашей программы.

Отменять долгие операции с помощью контекста можно несколькими способами:

- По явному сигналу отмены (`context.WithCancel`)
- По истечению промежутка времени (`context.WithTimeout`)
- По наступлению временной отметки или дедлайна (`context.WithDeadline`)

### Пример. Столик в ресторане
Вы хотите забронировать столик в ресторане. Для этого вы набираете ресторан, и ждете, пока на той стороне возьмут трубку. Далее происходит одно из двух:
1. Сотрудник ресторана берет трубку. В таком случае вы начинаете диалог - все хорошо;
2. На той стороне никто не берет трубку в течение минуты, двух, трех...

Во втором случае вы не будете ждать вечно, и положите трубку, когда вам надоест ждать, либо вы поймете, что это не имеет смысла.

Похожим образом работает контекст с таймаутом: как только проходит определенный промежуток времени, исполнение операции останавливается.

#### `context.WithTimeout()`

Ваше приложение отправляет запрос во внешнюю систему, например, в API другого сервиса, который владеет интересующими вас данными. Так как мы не контролируем внешние системы, мы не может быть на 100% уверены, что API ответит за приемлимое время, или вообще ответит когда-либо. Чтобы не зависнуть навечно в ожиданн ответа от API, в запрос можно передать контекст:

```go
ctx, cancel := context.WithTimeout(context.Background(), 15 * time.Second)
defer cancel()

req, err := http.NewRequestWithContext(ctx, http.MethodGet, "https://example.com")
if err != nil {
	return nil, fmt.Errorf("failed to create request with ctx: %w", err)
}

res, err := http.DefaultClient.Do(req)
if err != nil {
	return nil, fmt.Errorf("failed to perform http request: %w", err)
}

return res, nil
```

Давайте разбираться, что здесь написано.

```go
ctx, cancel := context.WithTimeout(context.Background, 15 * time.Second)
defer cancel()
```

Первым делом происходит инициализация контекста с таймаутом в 15 секунд. Конструкция `defer cancel()` гарантирует, что после выхода из функции или горутины контекст будет отменен, и таким образом вы избежите утекания горутины - явления, когда горутина продолжает выполняться и существовать в памяти, но результат ее работы больше никого не интересует.

### Дерево контекстов
Вы можете спросить: а что за `context.Background()` ?

Дело в том, что любой контекст должен наследоваться от какого-то другого родительского контекста. Исключения: `Background` и `TODO`. `Background` - это контекст-заглушка, используемый как правило как самый верхний родитель для всех дочерних контекстов в иерархии. `TODO` - это тоже заглушка, но используется в тех случаях, когда мы еще не определились, какой тип контекста мы хотим использовать. Эти два типа контекста по сути одно и тоже, и разница исключительно семантическая.

Схема с родительскими и дочерними контекстами нужна для того, чтобы внутри функции, куда был проброшен контекст, не было возможности повлиять на условия отмены сверху. Таким образом мы имеем гарантию (с некоторыми оговорками), что контекст с дедлайнов отменится не позже данного дедлайна. 

Для наглядность рассмотрим еще один пример. Если мы запустим программу ниже, мы увидим: несмотря на то, что внутри функции `doWork` таймаут переопределяется на больший, отмена контекста все равно наступит через 10 секунд:

```go
package main 

import (
	"context"
	"log"
	"time"
)

func main() {
	ctx, cancel := context.WithTimeout(context.Background(), 10 * time.Second)
	defer cancel()

	doWork(ctx)
}

func doWork(ctx context.Context) {
	newCtx, cancel := context.WithTimeout(ctx, 30 * time.Second)
	defer cancel()

	log.Println("starting working...")

	for {
		select {
		case <-newCtx.Done():
			log.Printf("ctx done: %v", ctx.Err())
			return
		default:
			log.Println("working...")
			time.Sleep(1 * time.Second)
		}
	}
}
```

#### `context.WithDeadline()`

Контекст с таймаутом по сути является удобной оберткой над контекстом с дедлайном. 

```go
ctx, cancel := with.Deadline(context.Background(), time.Now().Add(1))
defer cancel()
```

`time.Now().Add(10 * time.Second)` - это ровно то, что делает функция `context.WithTimeout()`, вызывая внутри себя `context.WithDeadline()`.

#### `context.WithCancel()`

Представьте, что вы очень торопитесь на важную встречу. Чтобы добраться побыстрее, вы решаете вызвать такси. Где быстрее найдется машина, вы не знаете, поэтому решаете начать поиск в нескольких сервисах одновременно. Когда в одном из них найдется машина, вы отмените поиск в остальных. Для похожих и других задач можно использовать контекст с функцией отмены.

Давайте представим, как описанная ситуация могла бы выглядеть в коде.

```go
package main

import (
	"context"
	"log"
	"math/rand"
	"sync"
	"time"
)

func main() {
	var (
		resultCh    = make(chan string)
		ctx, cancel = context.WithCancel(context.Background())
		services    = []string{"Yandex Taxi", "Uber", "Maxim"}
		wg          sync.WaitGroup
		winner      string
	)

	defer cancel()

	for _, svc := range services {
		wg.Add(1)
		go func() {
			requestRide(ctx, svc, resultCh)
			wg.Done()
		}()
	}

	go func() {
		winner = <-resultCh
		cancel()
	}()

	wg.Wait()
	log.Printf("found car in %q", winner)
}

func requestRide(ctx context.Context, svc string, resultCh chan string) {
	time.Sleep(3 * time.Second)

	for {
		select {
		case <-ctx.Done():
			log.Printf("stopped the search in %q (%v)", svc, ctx.Err())
			return
		default:
			if rand.Float64() > 0.75 {
				resultCh <- svc
				return
			}

			continue
		}
	}
}
```

#### `context.WithValue()`

Окей, а что насчет передачи значений через контекст? Для этого в пакете существует функция `WithValue`. Давайте взглянем, как это работает:

```go
package main

import (
	"context"
	"log"
)

func main() {
	ctx := context.WithValue(context.Background(), "name", "Joe")

	log.Printf("name = %v", ctx.Value("name"))
	log.Printf("age = %v", ctx.Value("age"))
}
```

Обратите внимание, что метод `Value` возвращает значение типа `interface{}`, поэтому скорее всего вам будет необходимо привести его к нужному типу. Кроме того, если ключ не представлен в контексте, метод вернет `nil`.

#### Когда стоит передавать данные через контекст?
Короткий ответ - никогда. Передача данных через контекст является антипаттерном, посколько это порождает неявный контракт между компонентами вашего приложения, к тому еще и ненадежный. Исключение составляют случаи, когда вам нужно предоставить компоненту из внешней библиотеки ваш реализацию интерфейса, который вы не можете менять. Например, middleware в HTPP сервере.

Пример middleware с присвоением id запросу.

```go
package main

import (
	"context"
	"fmt"
	"net/http"
)

type key string

const port = ":8080"
const requestIDKey key = "requestID"

// Middleware to add a request ID to the context.
func requestIDMiddleware(handler http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		requestID := "12345"

		// Add the request ID to the context.
		ctx := context.WithValue(r.Context(), requestIDKey, requestID)

		// Create a new request with the updated context.
		r = r.WithContext(ctx)

		handler(w, r)
	}
}

// Handler that retrieves the request ID from the context.
func handler(w http.ResponseWriter, r *http.Request) {
	// Retrieve the request ID from the context.
	requestID := r.Context().Value(requestIDKey).(string)

	fmt.Fprintf(w, "Request ID: %s\n", requestID)
}

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", requestIDMiddleware(handler))

	http.ListenAndServe(port, mux)
}

```

### Пример. HTTP Middleware
Представьте, что вы хотите, чтобы ваш API принимал запросы только от аутентифицированных клиентов. Однако вызывать методы для аутентификации в каждом обработчике не кажется удачной идеей. Но вы можете сделать так, чтобы перед тем как вызовется обработчик запроса, вызвался метод, который проведет аутентификацию, и либо вызовет следующий номер в цепочке (в данном случае обработчик), либо вернет HTTP с ошибкой аутентификации. Это и есть пример классического middleware.

Вот как это может выглядеть:

```go
package main

import (
	"context"
	"fmt"
	"io"
	"log"
	"net/http"
)

type ctxKey string

const keyUserID ctxKey = "user_id"

func main() {
	mux := http.NewServeMux()

	mux.Handle("/restricted", authMiddleware(handleRestricted()))

	if err := http.ListenAndServe(":8080", mux); err != nil {
		log.Fatal(err)
	}
}

func authMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		token := r.Header.Get("Token")

		if token != "very-secret-token" {
			w.WriteHeader(http.StatusUnauthorized)
			io.WriteString(w, "invalid token")
			return
		}

		ctx := context.WithValue(r.Context(), keyUserID, 52)
		next.ServeHTTP(w, r.WithContext(ctx))
	})
}

func handleRestricted() http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		userID, ok := r.Context().Value(keyUserID).(int)
		if !ok {
			w.WriteHeader(http.StatusInternalServerError)
			io.WriteString(w, "internal error, try again later please")
			return
		}

		io.WriteString(w, fmt.Sprintf("hello, user #%d", userID))
	})
}
```

```bash
curl -H "Token: very-secret-token" -X GET http://localhost:8080/restricted
hello, user #52  
```

### Когда использовать контекст?
- Метод ходит куда-то по сети;
- Горутина исполняется потенциально "долго".

Если у вас есть сомнения насчет того, соответсвует ли функция одному из этих критериев, то лучше все-таки добавить контекст. Это не усложнет вам жизнь, но потенциально упростит ее в будущем. Особенно это касается объявляемых вами интерфейсов - внутри реализации может происходить все что угодно, в том числе сетевые вызовы и долгие операции.

### Советы и лучшие практики
- **Передавайте контекст всегда первым аргументом** - это общепринятое соглашение.
- **Передавайте контекст только в функции и методы**, не храните в состоянии (внутри структуры). Контексты спроектированы так, чтобы их использовали как одноразовые и неизменяемые объекты. Например, если вы сохраните контекст с таймаутом 15 секунд в поле структуры, а спустя 15 секунд попробуете выполнить операцию с данным контекстом, у вас ничего не получится. Обнулить счетчик таймаута вы тоже не сможете;
- **Используйте `context.WithValue` только в крайних случаях.** В 99,(9)% случаев вы сможете передать данные через аргументы функции;
- **`context.Background` должен использоваться только как самый верхний родительский контекст**, посколько он является заглушкой и не предоставляет средств контроля;
- **Используйте `context.TODO`, если пока не уверены**, какой контекст нужно использовать;
- **Не забывайте вызывать функцию отмены контекста**, т.к. функции, принимающей контекст может потребоваться время на завершение перед выходом;
- **Передавайте только контекст, без функции отмены.** Котроль за завершеним контекста должен оставаться на вызывающей стороне, иначе логика приложения может стать очень запутанной.

## References
[Разбираемся с контекстами в Go](https://blog.ildarkarymov.ru/posts/context-guide/)