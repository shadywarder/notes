## Backend Academy Homework Reflection

### Сигнатуры Хэндлеров с Path Variable 
При кодогенерации со спецификации свагера `oapi-generate` генерирует следующией интерфейс:

```go
// ServerInterface represents all server handlers.
type ServerInterface interface {
	// Убрать отслеживание ссылки
	// (DELETE /links)
	DeleteLinks(w http.ResponseWriter, r *http.Request, params DeleteLinksParams)
	// Получить все отслеживаемые ссылки
	// (GET /links)
	GetLinks(w http.ResponseWriter, r *http.Request, params GetLinksParams)
	// Добавить отслеживание ссылки
	// (POST /links)
	PostLinks(w http.ResponseWriter, r *http.Request, params PostLinksParams)
	// Удалить чат
	// (DELETE /tg-chat/{id})
	DeleteTgChatId(w http.ResponseWriter, r *http.Request, id int64)
	// Зарегистрировать чат
	// (POST /tg-chat/{id})
	PostTgChatId(w http.ResponseWriter, r *http.Request, id int64)
}
```

Является ли это хорошей практикой? Просто я у себя в проекте делал следующее:

```go
func (api *APIConfig) HandlerDeleteChirp(w http.ResponseWriter, r *http.Request) {
	chirpID, err := uuid.Parse(r.PathValue("chirpID"))
	if err != nil {
		respondWithError(w, http.StatusBadRequest, ErrParseChirpID.Error())
		return
	}

	...
}
```

Есть ли среди этих подходов победитель? 
