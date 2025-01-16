**2024-12-26 16:58**
Tags: [[go]] [[web]]

## JSON Encoding & Decoding in Go
In this note I want to consider some fundamentals of working with JSONs in Go. In particular, decoding and encoding process. We will be working with the following endpoint:

```sh
{
  "userId": 1,
  "id": 1,
  "title": "delectus aut autem",
  "completed": false
}          
```

In order to decode this JSON response we need to match its fields in struct using struct tags.

```go
type Todo struct {
	UserId    int    `json:"userId"`
	Id        int    `json:"id"`
	Title     string `json:"title"`
	Completed bool   `json:"completed"`
}
```

The whole procedure of decoding can be implement as follows: 

```go
package main

import (
	"encoding/json"
	"fmt"
	"log/slog"
	"net/http"
)

type Todo struct {
	UserId    int    `json:"userId"`
	Id        int    `json:"id"`
	Title     string `json:"title"`
	Completed bool   `json:"completed"`
}

func main() {
	url := "https://jsonplaceholder.typicode.com/todos/1"

	resp, err := http.Get(url)
	if err != nil {
		slog.Error(err.Error())
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		slog.Error("unsuccessful request!")
	}

	var todo Todo

	dec := json.NewDecoder(resp.Body)
	if err := dec.Decode(&todo); err != nil {
		slog.Error("unsuccessful decoding!")
	}

	fmt.Printf("%+v", todo)
}
```

We can continue this program with meaningless encoding of just decoded todo object into, let's say, `todo.json`. 

```go
f, err := os.Create("todo.json")
if err != nil {
	slog.Error(err.Error())
}

data, err := json.MarshalIndent(todo, "", "\t")
if err != nil {
	slog.Error(err.Error())
}

if _, err := f.Write(data); err != nil {
	slog.Error(err.Error())
}
```

 As a result we'll have encoded json file filled with the content of response.
## References
https://www.youtube.com/watch?v=Vr63uGL7NrU