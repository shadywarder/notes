**2025-02-25 11:31**
**Tags:** [go](../3%20-%20indexes/go.md) [[../2 - tags/redis]]

## Getting Started with Redis and Go
### Why Redis?
Redis is a fantastic open-source in-memory data structure store which can be used for various purposes such a database for your app, or a caching service or even a message broker.

It supports a wide variety of different data structures and is incredibly versatile and fast. If you are concerned with things like resiliency then you'll pleased to hear that it has built-in replication and can be run in a cluster setup to ensure that your applications are not reliant on a single instance.

### Running Redis With Docker Locally
Let's get started with this tutorial and download the `redis` docker image and run it using the following 2 docker commands:

```bash
docker pull redis
docker run --name redis-test-instance -p 6379:6379 -d redis
```

The first `pull` command does the job of retrieving the `redis` image from DockerHub so that we can then run it as a container using the second command. In the second command we specify the name of our redis container and we also map our local port 6379 to the port that redis is running against within the container using the `-p` flag.

### Connecting to our Redis Instance
We'll start off by importing the widely used `github.com/go-redis/redis` package.

Now that we have imported the necessary package, we can start by defining a `client` which takes in various options such as the address of the redis instance we want to connect to, the password and the database we wish to use in that instance.

In this case, we don't have any password set for our particular locally running instance so we can leave that blank and we'll be using the default database for now which is denoted by the value `0`.

After we define this new redis client, we then want to try and `Ping` our instance to ensure that everything has been set up correctly and print out the results:

```go
package main

import (
	"fmt"
	"github.com/go-redis/redis/v8"
)

func main() {
	fmt.Println("Go Redis Tutorial")

	client := redis.NewClient(&redis.Options{
		Addr: "localhost:6379",
		Password: "",
		DB: 0,
	})

	pong, err := client.Ping().Result()
	fmt.Println(pong, err)
}
```

When we go run this new, we will see that our incredibly simple Go application has been able to successfully `ping` the redis instance that we have spun up and returned a successful `PONG` response:

```bash
Go Redis Tutorial
PONG <nil>
```

### Adding Values to Redis
#### Setting Values
We'll start off by looking at setting values using the `client.Set` method. This method takes in a `key` and a `value` as well as an `expiration`. Setting the `expiration` to 0 effectively sets the key to have no expiration time.

```go
// we can call set with a `Key` and a `Value`. 
err = client.Set("name", "Elliot", 0).Err()
// if there has been an error setting the value
// handle the error
if err != nil {
    fmt.Println(err)
}
```

#### Getting Values
The `Get` method simply takes in the `key` that you wish to retrieve from your redis instance and we can use the `Result()` method chained on the end to convert the response to a value, as well as a potential error:

```go
val, err := client.Get("name").Result()
if err != nil {
	slog.Error(err.Error())
}

log.Println(val)
```

### Storing Composite Values
In this case, we tend to Marshal the composite data structure into JSON and subsequently store these JSON strings in the database using the same `Set` method we used earlier.

We can update our code to first marshal a new `Author` struct and the `Set` this in our redis instance against the key `id1234` and passing in our newly marshalled JSON like so:

```go
entry, err := json.Marshal(Author{
	Name: "Elliot",
	Age:  25,
})
if err != nil {
	slog.Error(err.Error())
}

if err := client.Set("id1234", entry, 0); err != nil {
	slog.Error(err.Name())
}

val, err := client.Get("id1234").Result()
if err != nil {
	slog.Error(err.Error())
}

log.Println(val)
```

## References 
[Getting Started with Redis and Go - Tutorial](https://tutorialedge.net/golang/go-redis-tutorial/)