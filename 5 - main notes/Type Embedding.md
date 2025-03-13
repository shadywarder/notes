**2025-03-03 12:19**
**Tags:** [go](../3%20-%20indexes/go.md) [go101](../2%20-%20tags/go101.md)

## Type Embedding
### What Does Type Embedding Look Like?
Here is an example demonstrating type embedding:

```go
package main

import "net/http"

func main() {
	type P = *bool
	type M = map[int]int
	var x struct {
		string // a named non-pointer type
		error  // a named interface type
		*int   // an unnamed pointer type
		P      // an alias of an unnamed pointer type
		M      // an alias of an unnamed type

		http.Header // a named map type
	}
	x.string = "Go"
	x.error = nil
	x.int = new(int)
	x.P = new(bool)
	x.M = make(M)
	x.Header = http.Header{}
}
```

### Which Types Can be Embedded?










## References