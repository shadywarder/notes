**2024-12-13 16:25**

Tags: [[go]] 

## Learning Go with Tests - Hello, World
### How to test
It is good to separate your "domain" code from the outside world (side-effects). The `fmt.Println` is a side effect (printing to stdout), and the string we send in is our domain.

```go
package main

import "fmt"

func Hello() string {
	return "Hello, world"
}

func main() {
	fmt.Println(Hello())
}
```

Now create a new file called `hello_test.go` where we are going to write a test for our `Hello` function.

```go
package main

import "testing"

func TestHello(t *testing.T) {
	got := Hello()
	want := "Hello, world"

	if got != want {
		t.Errorf("got %q want %q", got, want)
	}
}
```





## References