**2025-02-15 16:40**
**Tags:** [go](../3%20-%20indexes/go.md) [concurrency](../2%20-%20tags/concurrency.md)

## Select. Graceful shutdown
`select` различает три вида операции:
1. blocking;
2. non-blocking;
3. `default` branch.

```go
func baseSelect() {
	buffchan := make(chan string, 1)
	buffchan <- "first"

	select {
	case str := <-buffchan:
		log.Println("read", str)
	case buffchan <- "second":
		log.Println("write", <-buffchan, <-buffchan)
	}
}
```

Output:

```bash
2025/02/15 16:43:54 read first
```

В первую очередь ищет non-blocking operations (send/receive).
Если мы не хотим, чтобы `select` завис навечно или на какое-то время, то нам стоит использовать `default` branch.

Если есть несколько non-blocking operations, то `select` не гарантирует выбор какой-то определенной из них, то есть какая-то из non-blocking operations будет выбрана случайно.

Например:

```go
func baseSelect() {
	buffchan := make(chan string, 2)
	buffchan <- "first"

	select {
	case str := <-buffchan:
		log.Println("read", str)
	case buffchan <- "second":
		log.Println("write", <-buffchan, <-buffchan)
	}
}
```

```go
func baseSelect() {
	unbuffchan := make(chan int)

	go func() {
		time.Sleep(time.Second)
		unbuffchan <- 1
	}()

	select {
	case val := <-unbuffchan:
		log.Println("blocking reading")
	}
}
```

Зависаем на секунду, потому что больше нет никаких веток.

```go
func baseSelect() {
	unbuffchan := make(chan int)

	go func() {
		time.Sleep(time.Second)
		unbuffchan <- 1
	}()

	select {
	case val := <-unbuffchan:
		log.Println("blocking reading")
	default:
		log.Println("default case")
	}
}
```

Output:

```bash
2025/02/15 16:59:49 default case
```

Мы должны выносить канал из цикла `for`, иначе на каждой итерации цикла таймер будет инициализироваться заново.

```go
func baseSelect() {
	timer := time.After(time.Second)
	resultChan := make(chan int)

	go func() {
		defer close(resultChan)

		for i := 0; i < 1000; i++ {
			select {
			case <-timer:
				log.Println("time's up")
				return
			default:
				time.Sleep(time.Millisecond)
				resultChan <- i
			}
		}
	}()

	for v := range resultChan {
		fmt.Println(v)
	}
}
```


## References
[Concurrency. Select. Graceful shutdown](https://www.youtube.com/watch?v=kSfR5LWKUrM&list=PLc2Vkg57qmuRNHp6NNvYRVgg3OP-b5E_v&index=22)