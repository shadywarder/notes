**2025-02-03 15:16**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md) [course](../2%20-%20tags/course.md)

## Ch 2. Routing
It's frequently useful to have a way to store and access state in our handlers. For example, we might have want to keep track of the number of requests we've received, or we may want to pass around an open connection to a database, or credentials to an API.

### Middleware
Middleware is a way to wrap a handler with additional functionality. It is a common pattern in web applications that allows us to write DRY code. For example, we can write a middleware that logs every request to the server. We can then wrap our handler with this middleware and every request will be logged without us having to write the logging code in every handler.

Here are examples of the middleware that we've written so far.

#### Keeping Track of the Number of Times a Handler Has Been Called

```go
func (cfg *apiConfig) middlewareMetricsInc(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request){
		cfg.fileserverHits.Add(1)
		next.ServeHTTP(w, r)
	})
}
```

#### Logging Every Request
We haven't written this one yet, but it would look something like this:

```go
func middlewareLog(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		log.Printf("%s %s", r.Method, r.URL.Path)
		next.ServeHTTP(w, r)
	})
}
```

### Routing 
The Go standard library has a lot of powerful HTTP features and, as of version 1.22, comes equipped with method-based pattern matching for routing.

Note that there are other powerful routing libraries like *Gorilla Mux* and *Chi*, however, the instructions for this course will assume you are using Go's standard library. Just know that it isn't your only option!

In this lesson, we are going to limit which endpoints are available via which HTTP methods. In our current implementation, we can use any HTTP method to access any endpoint. *This is not ideal*.

#### Try It!
Run this command to send an empty `POST` request to your running server:

```shell
curl -X POST http://localhost:8080/healthz
```

You should get an `OK` response - but we want this endpoint to only be available via `GET` requests!

#### Method Specific Routing
Using the Go standard library, you can specify a method like this `[METHOD ][HOST]/[PATH]`. For example:

```go
mux.HandleFunc("POST /articles", handlerArticlesCreate)
mux.HandleFunc("DELETE /articles", handlerArticlesDelete)
```

### Patterns
A pattern is a string that specifies the set of URL paths that should be matched to handle HTTP requests. Go's `ServeMix` router uses these patterns to dispatch requests to the appropriate handler functions based on the URL path of the request. As we saw in the previous lesson, pattern help organize the handling of different routes efficiently. 

As previously mentioned, patterns generally look like this: `[METHOD ][HOST]/[PATH]`. Note that all three parts are optional.

#### Rules and Definitions
##### Fixed URL Paths
A pattern that exactly matches the URL path. For example, if you have a pattern `/about`, it will match the URL path `/about` and no other paths.

##### Subtree Paths
If a pattern ends with a slash `/`, it matches all URL paths that have the same prefix. For example, a pattern `/images/` matches `/images/`, `/images/logo.png`, and `/images/css/style.css`. As we saw with our `/app/` path, this is useful for serving a directory of static files or for structuring your application into subsections.

##### Longest Match Wins
If more that one pattern matches a request path, the longest match is chosen. This allows more specific handlers to override more general ones. For example, if you have pattern `/` (root) and `/images/`, and the request path is `/images/logo.png`, the `/images/` handler will be used because it's the longest match.

##### Host-Specific Patterns
We won't be using this but be aware that patterns can also start with a hostname (e.g., `www.example.com/`). This allows you to serve different content based on the Host header of the request. If bot host-specific and non-host-specific patterns match, the host-specific pattern takes precedence.
If you're interested, you can read more in the *ServeMux docs*.




## References
[Learn HTTP Servers in Go Ch 2.](https://www.boot.dev/lessons/a13ffa72-18b9-49f7-81a9-c5a17d007b3a)