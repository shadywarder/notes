## JSON Syntax
<u>JSON</u>  (JavaScript Object Notations), is a standard for representing *structured* data based on JavaScript's object syntax. It is commonly used to transmit data in web apps via HTTP. For example, the HTTP requests we have been making in this course have been returning *Fantasy Quest* items as JSON.

JSON supports the following primitive data types:
- Strings, e.g. `"Hello, world!"`
- Numbers, e.g. `42` or `3.14`
- Booleans, e.g. `true`
- Null, e.g. `null`

And the following collection types:
- Arrays, e.g. `[1, 2, 3]`
- Object literals, e.g. `{"key": "value"}`

JSON is similar to JavaScript objects and Python dictionaries. Keys are always strings, and the values can be any data type, including other objects.

The following is valid JSON data:

```json
{
    "movies": [
        {
            "id": 1,
            "title": "Iron Man",
            "director": "Jon Favreau",
            "favorite": true
        },
        {
            "id": 2,
            "title": "The Avengers",
            "director": "Joss Whedon",
            "favorite": false
        }
    ]
}
```

## Decoding JSON
When we receive JSON data in the body of an HTTP response, it comes as a stream of bytes. As we saw before, we can just convert the bytes to a string... but in Go there's a better way. It's typically best to decode the JSON data into a *struct*.

Take this example JSON data:

```json
[
  {
    "id": "001-a",
    "name": "Stick of Truth",
    "item_level": 9001
  }
]
```

To decode this JSON into a slice of `Item` structs, we need to know the JSON fields and their types. The standard <u>encoding/json</u> package user tags to map JSON fields to struct fields. 

*Note: Struct fields must be exported (capitalized( to decode JSON.*

```go
type Item struct {
	Id        string `json:"id"`
	Name      string `json:"name"`
	ItemLevel int    `json:"item_level"`
}
```

After receiving the response, we can decode it into a slice of `Item`s with the "address of" operator `&`.

```go
// res is a successful `http.Response`

var items []Item
decoder := json.NewDecoder(res.Body)
if err := decoder.Decode(&items); err != nil {
    fmt.Println("error decoding response body")
    return
}
```

If no error occurs, we can use the slice of items in our program.

```go
for _, item := range items {
    fmt.Printf("Item – id: %v, name: %v, item level: %v\n", item.Id, item.Name, item.ItemLevel)
    // Item – id: 001-a, name: Stick of Truth, item level: 9001
}
```

## JSON Review
JSON is *stringified representation* of a <u>JavaScript object</u>, which makes it perfect for saving to a file or sending in an HTTP request. Remember, an actual JavaScript object is something that exists only within your program's variables. If we want to send an object outside our program, for example, across the internet in an HTTP request, we need to convert it to JSON first.

### JSON isn't just for JavaScript
Just because JSON is called *JavaScript* Object Notation doesn't mean it's only used by JavaScript code! JSON is a common standard that is recognized and supported by every major programming language. For example, even though Boot.dev's backend is written in Go, we still use JSON as the communication format between front-end and backend.

### Common use-cases
- In HTTP request and response bodies
- As formats for text files `.json` files are often used as configuration files.
- In NoSQL databases like MongoDB, ElasticSearch and FileStore

## Unmarshal JSON
We can decode JSON bytes (or strings) into a Go struct using `json.Unmarshal` or a `json.Decoder`. 

The `Decode` method of `json.Decoder` streams data from an `io.Reader` into a Go struct, while `json.Unmarshal` works with data that's already in `[]byte` format. Using a `json.Decoder` can be more memory-efficient because it doesn't load all the data into memory at once. `json.Unmarshal` is ideal for small JSON data you already have in memory. When dealing with HTTP requests and responses, you will likely use `json.Decoder` since works directly with an `io.Reader`.

```go
// res is an http.Response
defer res.Body.Close()

data, err := io.ReadAll(res.Body)
if err != nil {
	return nil, err
}

var items []Item
if err = json.Unmarshal(data, &items); err != nil {
    return nil, err
}
```

### Marshal JSON 
If there is a way to <u>unmarshal</u> JSON data, there must be a way to marshal it as well. The `json.Marshal` function converts a Go struct into a slice of bytes representing JSON data.

```go
type Artifact struct {
    Id        string `json:"id"`
    Name      string `json:"name"`
    Level     int    `json:"level"`
}

scroll := Artifact{
    Id:        "001-a",
    Name:      "Scroll of Truth",
    Level:     9001,
}

data, err := json.Marshal(scroll)
if err != nil {
    log.Fatal(err)
}
fmt.Println(string(data))
// {"id":"001-a","name":"Scroll of Truth","level":9001}
```

## XML
We can't talk about JSON without mentioning <u>XML</u>. `XML`, or "Extensible Markup Language" is a text based format for representing structured information, like JSON - but different (and a bit more verbose).

### XML syntax
XML is a markup language like <u>HTML</u>, but it's more generalized in that it does *not* use predefined tags. Just like how in a JSON object keys can be called anything, XML tags can also have any name.

XML representing a movie:

```xml
<root>
  <id>1</id>
  <genre>Action</genre>
  <title>Iron Man</title>
  <director>Jon Favreau</director>
</root>
```

The same data in JSON:

```json
{
  "id": "1",
  "genre": "Action",
  "title": "Iron Man",
  "director": "Jon Favreau"
}
```

## Why use XML?
XML and JSON both accomplish similar tasks, so which should you use? 

XML used to be used for the same things that today JSON is primarily used for. Configuration files, HTTP bodies, and other data-transfer can work with either JSON or XML. Personally, I believe that if JSON works, you should favor it over XML. JSON is:
- Lighter-weight
- Easier to read
- Has better support in most programming languages
There are cases where XML might still be better, or maybe even *necessary*, but that tends to be the excepting rather than the rule.

## `map[string]interface{}`

Sometimes you have to deal with JSON data of unknown or varying structure in Go. In those instances `map[string]interface{}` offers a flexible way to handle it without predefined structs.

```go
var data map[string]interface{}
jsonString := `{"name": "Alice", "age": 30, "address": {"city": "Wonderland"}}`
json.Unmarshal([]byte(jsonString), &data)
fmt.Println(data["name"])  // Output: Alice
fmt.Println(data["address"].(map[string]interface{})["city"])  // Output: Wonderland
```

Example of `json.Decoder` usage:

```go
func getResources(url string) ([]map[string]any, error) {
	var resources []map[string]any

	res, err := http.Get(url)
	if err != nil {
		return resources, err
	}

	defer res.Body.Close()

	decoder := json.NewDecoder(res.Body)
	err := decoder.Decode(&resources)
	if err != nil {
		return resources, err
	}

	return resources, nil
}
```