**2025-02-26 12:59**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md)

## How I write HTTP services in Go after 13 years

### The `NewServer` constructor

Let's start by looking at the backbone of any Go service: the server. The `NewServer` function makes the main `http.Handler`. Usually I have one per service, and I rely on HTTP routes to divert traffic to the right handlers within each service because:
- `NewServer` is a big constructor that takes in all dependencies as arguments
- It returns an `http.Handler` if possible, which can be a dedicated type for more complex situations
- It usually configures its own muxer and calls out to `routes.go`
For example, you code might look similar to this:

```go
func NewServer(
	logger *Logger
	config *Config
	commentStore *commentStore
	anotherStore *anotherStore
) http.Handler {
	mux := http.NewServeMux()
	addRoutes(
		mux,
		Logger,
		Config,
		commentStore,
		anotherStore
	)
	var handler http.Handler = mux
	handler = someMiddleware(handler)
	handler = someMiddleware2(handler)
	handler = someMiddleware3(handler)
	return handler
}
```

In test cases that don't need all of the dependencies, I pass in `nil` as a signal it won't be used.

The `NewServer` constructor is responsible for all the top-level HTTP stuff that applies to all endpoints, like CORS, auth middleware, and logging:

```go
var handler http.Handler = mux
handler = logging.NewLoggingMiddleware(logger, handler)
handler = logging.NewGoogleTraceIDMiddleware(logger, handler)
handler = checkAuthHeaders(handler)
return handler
```

Setting up the server is usually a case of exposing it using Go's built-in `http` package:

```go
srv := NewServer(
	logger, 
	config, 
	tenantsStore,
	slackLinkStore,
	msteamsLinkStore,
)
```





## References