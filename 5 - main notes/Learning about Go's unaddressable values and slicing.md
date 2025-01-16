**2025-01-13 21:52**
Tags: [go](../3%20-%20indexes/go.md)

## Learning about Go's unaddressable values and slicing

```go
#golang pop quiz: what does this program print?

package main

import (
    "crypto/sha1"
    "fmt"
)

func main() {
    input := []byte("Hello, playground")
    hash := sha1.Sum(input)[:5]
    fmt.Println(hash)
}
```

Output:

```go
./test.go:10:28: invalid operation sha1.Sum(input)[:5] (slice of unaddressable value)
```

That leaves us with the concept of unaddressable values, which are the opposite of *addressable values*. The hand waving summary version is that most anonymous values are not addressable (one big exception is composite literals). Here the return value of `sha1.Sum()` is anonymous, because we're immediately slicing it. Had we stored it in a variable and thus made it non-anonymous, the code would have worked:

```go
tmp := sha1.Sum(input)
hast := tmp[:5]
```

The final piece of the puzzle is why slicing was an error. That's because slicing an array specifically requires that the array be addressable (this is covered at the end of Slice expressions). The anonymous array that is the return value of `sha1.Sum()` is not addressable, so slicing it is rejected by the compiler.


## References
[Learning about Go's unaddressable values and slicing](https://utcc.utoronto.ca/~cks/space/blog/programming/GoUnaddressableSlice)