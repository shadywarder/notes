**2025-02-03 11:00**
**Tags:** [go](../3%20-%20indexes/go.md) [web](../2%20-%20tags/web.md)

## Ch 1. Servers
### What Is a Server?
A web *server* is just a computer that serves data over a network, typically the Internet. Servers run software that listens for incoming requests from clients. When a request is received, the server responds with the requested data.

![](../attachments/Pasted%20image%2020250203110342.png)

Any server worth its salt can handle *many* requests at the same time. In Go, we use a new *goroutine* for each request to handle them concurrently. 

### Goroutines in Servers
In Go, *goroutines* are used to serve *many* requests at the same time, but not all servers are quite so performant.

Go was built by Google, and one of the purposes of its creation was to power Google's massive web infrastructure. Go's goroutines are a great fit for web servers because they're lighter weight than operating system threads, but still take advantage of multiple cores.

#### Node.js / Express.js
In JavaScript land, servers are typically single-threaded. A *Node.js* server (often using the *Express* framework) only uses one CPU core at a time. It can still handle many requests at one by using an *async event loop*. That just means whenever a request has to wait on I/O (like to a database), the server puts it on pause and does something else a bit.

![](../attachments/Pasted%20image%2020250203111317.png)

This might sound *horribly* inefficient, but it's not *too* bad. Node servers do just fine with the I/O workloads associated with most CRUD apps (Where processing is offloaded to the Database). You only start to run into trouble with this model when you need your server to do CPU-intensive work.

#### Python / Django / Flask
*Django* and *Flask* are two of the most popular back-end Python frameworks. They're both built on top of the *WSGI* standard, which is a specification for how web servers and web application should communicate.

Generally speaking, Python application code only processes a single request at a time. This means that if a request is being processed, the application won't do *anything else* until it's finished.

The only reason this isn't completely debilitating is there is a separate WSGI process (for example *uwsgi*) that handles the concurrency of the application code. It can spawn multiple processes of the Python application to handle different requests at once.

In other words, `uwsgi + Flask` or `uwsgi + Django` are both needed to handle the same things that a single Node.js or Go server does *alone*.
#### Takeaways
- Go servers are great for performance whether the workload is I/O _or_ CPU-bound
- Node.js and Express work well for I/O-bound tasks, but struggle with CPU-bound tasks
- Python and Django/Flask do just fine with I/O bound tasks, but frankly, no one picks Python for its performance

### Fileservers
A *fileserver* is a kind of simple web server that serves static files from the host machine. Fileservers are often used to serve static assets for a website, things like:
- HTML
- CSS
- JavaScript
- Images

### Serving Imgaes
You may be wondering how the fileserver knew to serve the `index.html` file to the root of the server. It's *such* a common convention on the web use a file called `index.html` to server the webpage for a given path, that the Go standard library's *FileServer* does it automatically.

When using a standard library fileserver, the path to a file on a disk is the same as its URL path. An exception is that `index.html` is served from `/` instead of `/index.html`.

#### Try It Out
Run you chirpy server again, and open `http://localhost:8080/index.html` in a new browser tab. You'll notice that you're redirected to `http://localhost:8080/`.

This works for all directories, not just the root!

For example:
- `/index.html` will be served from `/`
- `/pages/index.html` will be served from `/pages`
- `/pages/about/index.html` will be served from `/pages/about`

Alternatively, try opening a URL that doesn't exist, like `http://localhost:8080/doesntexist.html`. You'll see that the fileserver returns a 404 error.

### Workflow Tips
Servers are interesting because they're *always running*. A lot of the code we've written in Boot.dev up to this point has acted like a command line tool: it run, does its thing, and then exits.

Servers are different. They run forever, waiting for requests to come in, processing them, sending responses, and then waiting for the next request. If they didn't work this way, websites and apps would be down and unavailable *all the time*!

#### Debugging a Server
Debugging a CLI app is simple:
1. Write some code.
2. Build and run the code.
3. See if it did what you expected.
4. If it didn't, add some logging or fix the code, and go back to step 2.

Debugging a server is a little different. The *simplest* way (minimal tooling) is to:
1. Write some code.
2. Build and run the code.
3. *Send a request to the server using a browser or some other HTTP client*.
4. See if it did what you expected.
5. If it didn't, add some logging or fix the code, and go back to step 2.
*Make sure you're testing your server by hitting endpoints in the browser before submitting your answers.*

### Custom Handlers
In the previous exercise, we used the `http.FileServer` function, which simply returns a built-in `http.Handler`.
An `http.Handler` is just an interface:

```go
type Handler interface {
	ServerHTTP(ResponseWriter, *Request)
}
```

Any type with a `ServeHTTP` method that matches the `http.HandlerFunc` signature above is an `http.Handler`. Take a second to think about it: it makes a lot of sense! To handle an incoming HTTP request, all a function needs is a way to write a response and the request itself.

### Handler Review
#### Handler
An `http.Handler` is any *defined type* that implements the set of methods defined by the `Handler` *interface*, specifically the `ServeHTTP` method.

```go
type Handler interface {
	ServeHTTP(ResponseWriter, *Request)
}
```

The `ServeMux` you need in the previous exercise is an `http.Handler`.
You will typically use a `Handler` for more complex use cases, such as when you want to implement a custom router, middleware, or other custom logic.

#### HandlerFunc

```go
type HandlerFunc func(ResponseWriter, *Request)
```

You'll typically use a `HandlerFunc` when you want to implement a simple handler. The `HandlerFunc` type is just a function that matches the `ServeHTTP` signature above.

#### Why This Signature?
The `Request` argument is fairly obvious: it contains all the information about the incoming request, such as the HTTP methods, path, headers, and body.

The `ResponseWriter` is less intuitive in my opinion. The response is an *argument*, not a *return type*. Instead of returning a value all at once from the handler function, we *write* the response to the `ResponseWriter`.
## References
[Learn HTTP Servers in Go Ch 1.](https://www.boot.dev/lessons/50f37da8-72c0-4860-a7d1-17e4bda5c243)