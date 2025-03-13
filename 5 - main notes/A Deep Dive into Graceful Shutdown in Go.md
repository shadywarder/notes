**2025-02-12 21:36**
**Tags:** [go](../3%20-%20indexes/go.md) [best practices](../2%20-%20tags/best%20practices.md)

## A Deep Dive into Graceful Shutdown in Go
When developing web services in Go, implementing proper shutdown handling is crucial for maintaining system reliability and data integrity. A graceful shutdown ensures that your service can terminate safely while completing existing operations, rather than abruptly stopping and potentially leaving tasks unfinished.

### The Core Concept
Graceful shutdown involves coordinating between incoming termination signals, ongoing operations, and resource cleanup. In Go, this is typically achieved using signal handling, goroutines, and context-based cancellation. Here's minimal implementation that demonstrates these concepts:

```go
package main

import (
	"context"
	"errors"
	"log"
	"net/http"
	"os"
	"os/signal"
	"syscall"
	"time"
)

const (
	Port = ":8080"
)

func main() {
	mux := http.NewServeMux()

	mux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Write([]byte("Hello, World!"))
	})

	srv := &http.Server{
		Addr:         Port,
		Handler:      mux,
		ReadTimeout:  15 * time.Second,
		WriteTimeout: 15 * time.Second,
		IdleTimeout:  time.Minute,
	}

	srvErr := make(chan error, 1)

	go func() {
		log.Printf("Server is running on http://localhost%s", srv.Addr)
		if err := srv.ListenAndServe(); !errors.Is(err, http.ErrServerClosed) {
			srvErr <- err
		}
	}()

	stop := make(chan os.Signal, 1)
	signal.Notify(stop, syscall.SIGINT, syscall.SIGTERM)

	select {
	case err := <-srvErr:
		log.Printf("Server error: %v", err)
	case sig := <-stop:
		log.Printf("Received shutdown signal: %v", sig)
	}

	log.Println("Server is shutting down...")

	ctx, cancel := context.WithTimeout(context.Background(), 15*time.Second)
	defer cancel()

	if err := srv.Shutdown(ctx); err != nil {
		log.Printf("Server shutdown error: %v", err)
		return
	}

	log.Println("Server exited properly")
}
```

### How It Works
The implementation starts by running the HTTP server in a separate goroutine. This allows the main goroutine to handle shutdown signals without blocking the server's operation. We create two channels: one for server errors and another for OS signals.

The signal handling channel (`stop`) is buffered to ensure we don't miss the shutdown signal even if we're not immediately ready to process it. We register this channel to receive both `SIGINT (Ctrl+C)` and `SIGTERM` signals, which are common ways to request server shutdown.

We use a `select` statement to wait for either a server error or a shutdown signal. This creates a blocking point where our program waits something to happen. When either occurs, we begin the shutdown process.

The shutdown itself uses a `context` with timeout to ensure we don't hang indefinitely. The `server.Shutdown` method stops accepting new connections immediately while allowing existing request to complete. If ongoing take longer than our timeout (15 seconds in this case), the shutdown will be forced.

### The Shutdown Sequence
When a shutdown signal is received, the following sequence occurs:

1. The server stops accepting new connections. This prevents new requests from starting while we're trying to shut down.
2. The server waits for all existing connections to complete their current requests. This is the "graceful" part of the shutdown - we're giving ongoing operations a chance to finish properly. 
3. If any requests are still running when the context timeout expires, they will be forcefully terminated. This prevents the server from hanging indefinitely if some request take too long.
4. Once all requests are complete or the timeout is reached, the server exits and the program can terminate cleanly.

The visual representation helps understand how different components interact during the shutdown process and how the program coordinates between normal operation and graceful termination.

![](../attachments/Pasted%20image%2020250212220300.png)

### Real-World Considerations
In production environments, you might need to handle additional cleanup tasks during shutdown. This could include closing database connections, saving state, or cleaning up temporary files. These operations should be added before the `server.Shutdown` call and should respect the same `context` timeout.

It's also worth noting that the 15-second timeout we've used is arbitrary. In practice, you should choose a timeout value that makes sense for your application's typical request duration and cleanup needs.

### Key Benefits of This Implementation
1. Non-blocking Operation
	- Server runs in a separate goroutine
	- Main goroutine remains responsive to signals
2. Controlled Shutdown 
	- Existing requests are allowed to complete
	- New request are rejected
	- Timeout prevents hanging
3. Error Handling
	- Captures both server errors and shutdown errors
	- Distinguishes between normal shutdown and errors

## References
[A Deep Dive into Graceful Shutdown in Go](https://dev.to/yanev/a-deep-dive-into-graceful-shutdown-in-go-484a#:~:text=When%20developing%20web%20services%20in,and%20potentially%20leaving%20tasks%20unfinished.)