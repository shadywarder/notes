## HTTP Methods - GET
HTTP defines a set of <u>methods</u>. We must choose one to use each time we make an HTTP request. The most common ones include: 
- `GET`
- `POST`
- `PUT`
- `DELETE`

The <u>GET method</u> is used to "get" a *representation* of a specified resource. It doesn't *take* (remove) the data from the server but rather *gets* a representation, or copy, of the resource in its current state. A GET request is considered a <u>safe</u> method to call multiple times because it shouldn't alter the state of the server.

### Making a GET request in Go
There are two basic ways to make a Get request in Go.
1. The simple but less powerful way: `http.Get`
2. The verbose but more powerful way: `http.Client`, `http.NewRequest` and `http.Client.Do`

If all you need to is make a simple `GET` request to a URL, `http.Get` will work:

```go
resp, err := http.Get("https://jsonplaceholder.typicode.com/users")
```

If you need to customize things like headers, cookies, or timeouts, you'll want to create a custom `http.Client`, an `http.NewRequest`, then use the client's `Do` method to execute it.

```go
client := &http.Client{
	Timeout: time.Second * 10,
}

req, err := http.NewRequst("GET", "https://jsonplaceholder.typicode.com/users", nil)
if err != nil {
	log.Fatal(err)
}

resp, err := client.Do(req)
```

## Why use HTTP methods?
The primary purpose of HTTP methods is to indicate to the server what we want to do with the resource we're trying to interact with. At the end of day, an HTTP method is just a string, like `GET`, `POST`, `PUT`, or `DELETE`, but by *convention*, backend developers write their server code so that the methods correspond with different "CRUD" actions.

The "CRUD" actions are:
- Create
- Read
- Update
- Delete
 
The bulk of the logic is most web applications is "CRUD" logic. Even a complex social media site is *mostly* just CRUD. Users create, read, update, and delete their accounts. They create, read, update, and delete their posts. It's *CRUD all the down*.

The 4 most common HTTP methods map nicely to the CRUD actions:

| HTTP Method | CRUD Action |
| ----------- | ----------- |
| GET         | Read        |
| POST        | Create      |
| PUT         | Update      |
| DELETE      | Delete      |

## POST Request
An <u>HTTP POST request</u> *sends* data to a server, typically to *create* a new resource.

### Adding a body
The `body` of the request is the *payload* sent to the server. The special `Content-type` header is used to tell the server the format of the body: `application/json` for JSON data in our case. `POST` requests are generally *not* safe methods to call multiple times because that would create duplicate records. For example, you wouldn't want to accidentally send a tweet twice.

Like `http.Get`, the standard library's `http.Post` function can be used to send simple `POST` requests. The trouble is, it's a bit limited. And because we need to add an `X-API-Key` header, the simple `http.Post` function won't work for use. Instead, we need to use `http.NewRequest`:

```go
type Comment struct {
	Id      string `json:"id"`
	UserId  string `json:"user_id"`
	Comment string `json:"comment"`
}

func createComment(url, apiKey string, commentStruct Comment) (Comment, error) {
    // encode our comment as json
	jsonData, err := json.Marshal(commentStruct)
	if err != nil {
		return Comment{}, err
	}

    // create a new request
	req, err := http.NewRequest("POST", url, bytes.NewBuffer(jsonData))
	if err != nil {
		return Comment{}, err
	}

    // set request headers
	req.Header.Set("Content-Type", "application/json")
    req.Header.Set("X-API-Key", apiKey)

    // create a new client and make the request
	client := &http.Client{}
	res, err := client.Do(req)
	if err != nil {
		return Comment{}, err
	}
	defer res.Body.Close()

    // decode the json data from the response
	// into a new Comment struct
	var comment Comment
	decoder := json.NewDecoder(res.Body)
	err = decoder.Decode(&comment)
	if err != nil {
		return Comment{}, err
	}

	return comment, nil
}
```

## Status Codes
The `Status Code` of an HTTP *response* tells the client whether or not the server was able to to fulfill the request. Status codes are 3-digit numbers that are grouped into categories:
- `100-199`: Informational responses. There are very rare.
- `200-299`: Successful responses. Hopefully, most responses are 200's!
- `300-399`: Redirection messages. These are typically invisible because the browser or HTTP client will automatically do the redirect.
- `400-499`: Client errors. You'll see these often, especially when trying to debug a client application.
- `500-599`: Server errors. You'll see these sometimes, usually only if there is a bug on the server.

Here are some of the most common status codes:
- `200` - OK. This is by far the most common code, it just means that everything worked as expected.
- `201` - Created. This means that a resource was creates successfully. Typically in response to a `POST` request.
- `301` - Moved permanently. This means the resource was moved to a new place, and the response will include where that new place is. Websites often use `301` redirects when they change their domain names, for example.
- `400` - Bad request. A general error indicating the client made a mistake in their request.
- `401` - Unauthorized. This means the client doesn't have the correct permissions. Maybe they didn't include a required authorization header, for example.
- `404` - Not found. You'll see this on websites quite often. It just means the resource doesn't exist.
- `500` - Internal server error. This means something went wrong on the server, likely a bug on their end.

### Don't memorize
It's good to know the basics by heart, like "2XX is good", "4XX is a client error", and "5XX is a server error". But don't memorize all the status codes... 

## Status Code Property
The `http.Response` struct has a `.StatusCode` property that contains the status code of the response.

## HTTP PUT
The HTTP <u>PUT</u> method creates *or more commonly, updates* the target resource with the contents of the request's `body`. Unlike `GET` and `POST`, there is not `http.Put` function. You will have to create a raw `http.Request` what an `http.Client` can <u>Do</u>. 

### POST vs PUT
While `POST` and `PUT` are both used for creating resources, `PUT` is more common for updates and is `idempotent`, meaning it's safe to make the request multiple times without changing the server state. For example:

```shell
POST /users/bob (create bob user)
POST /users/bob (create duplicate bob user)
POST /users/bob (create duplicate bob user)
```

```Shell
PUT /users/bob (create bob user if it doesn't exist)
PUT /users/bob (update bob user with the same data)
PUT /users/bob (update bob user with the same data)
```

## Patch vs PUT
You may encounter the <u>PATCH</u> method from time to time. It's frankly not used very often. It's meant to *partially* modify a resource, whereas `PUT` is meant to *completely replace* a resource.

`PATCH` is not as popular as `PUT`, and many servers, even if they allow partial updates, just use `PUT`.

## Delete
The `DELETE` method does exactly what you expect: it deletes a specified resource.

```go
// This deletes the location with ID: 52fdfc07-2182-454f-963f-5f0f9a621d72
url := "https://api.boot.dev/v1/courses_rest_api/learn-http/locations/52fdfc07-2182-454f-963f-5f0f9a621d72"
req, err := http.NewRequest("DELETE", url, nil)
if err != nil {
	fmt.Println(err)
    return
}

client := &http.Client{}
res, err := client.Do(req)
if err != nil {
	fmt.Println(err)
    return
}
res.Body.Close()

if res.StatusCode > 299 {
    fmt.Println("request to delete location unsuccessful")
    return
}
fmt.Println("request to delete location successful")
```

