**2025-02-04 10:54**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md) [course](../2%20-%20tags/course.md)

## Ch 4. JSON
So far, you have *probably* been using a browser to test your server. That works fine with simple `GET` requests (the kind of request a browser sends when you type a URL into the address bar), but it's not very useful for any other HTTP methods or requests with custom headers and bodies.

#### Debugging Your Endpoints 
Servers are build to be used by clients. As you develop your code, you should be using a tool that makes sending one-off requests to your server easy! 

### JSON
#### Decode JSON Request Body
It's *very* common for `POST` requests to send JSON data in the request body. Here's how you can handle that incoming data: 

```json
{
	"name": "John",
	"age": 30
}
```

```go
func handler(w http.ResponseWriter, r *http.Request){
    type parameters struct {
        // these tags indicate how the keys in the JSON should be mapped to the struct fields
        // the struct fields must be exported (start with a capital letter) if you want them parsed
        Name string `json:"name"`
        Age int `json:"age"`
    }

    decoder := json.NewDecoder(r.Body)
    params := parameters{}
    err := decoder.Decode(&params)
    if err != nil {
        // an error will be thrown if the JSON is invalid or has the wrong types
        // any missing fields will simply have their values in the struct set to their zero value
		log.Printf("Error decoding parameters: %s", err)
		w.WriteHeader(500)
		return
    }
    // params is a struct with data populated successfully
    // ...
}
```

#### Encode JSON Response Body

```go
func handler(w http.ResponseWriter, r *http.Request){
    // ...

    type returnVals struct {
        // the key will be the name of struct field unless you give it an explicit JSON tag
        CreatedAt time.Time `json:"created_at"`
        ID int `json:"id"`
    }
    respBody := returnVals{
        CreatedAt: time.Now(),
        ID: 123,
    }
    dat, err := json.Marshal(respBody)
	if err != nil {
			log.Printf("Error marshalling JSON: %s", err)
			w.WriteHeader(500)
			return
	}
    k
    w.WriteHeader(200)
    w.Write(dat)
}
```

## References
[Learn HTTP Servers in Go Ch 4.](https://www.boot.dev/lessons/eb030acc-ef30-4bf9-89ae-7b16ba09691c)