**2025-01-10 17:48**
Tags: [[go]]

## Typed and Untyped Constants in Go

In Go constant are treated in a different way that any other language. Go has a very strong type system that doesn't allow implicit conversion between any of the types. Even with the same numeric types no operation is allowed without explicit conversion. For example you cannot add a `int32` and `int64` value. To add those either `int32` has to be explicitly converted to `int64` or vice versa. However untyped constant have the flexibility or temporary escape from the Go's type system.

### Typed Constant

A const declared specifying the type in the declaration is a type constant. For example below we are declaring a const of type `int32`

```go
const a int32 = 8
```

This `const a` can only be assigned to a variable of type `int32`. If you assign it to a variable of any other type it will raise an error. 

```go
package main

func main() {
    const a int32 = 8

    var i1 int32
    var i2 int64

    i1 = a
    i2 = a
}
```

**Output:**

```go
cannot use a (type int32) as type int64 in assignment
```

### Untyped Constant 

An untyped constant is a constant whose type has not been specified. An untyped constant in Go can be either named or unnamed. In both cases it doesn't have any type associated with it.

Examples of unnamed untyped constant.

```go
123        // Default hidden type is int
"circle"   // Default hidden type is string
5.6.       // Default hidden type is float64
true       // Default hidden type is bool
'a'        // Default hidden type is rune
3+5i       // Default hidden type is complex128
```

Examples of named untyped constant.

```go
const a = 123        // Default hidden type is int
const b = "circle"   // Default hidden type is string
const c = 5.6        // Default hidden type is float64
const d = true       // Default hidden type is bool
const e = 'a'        // Default hidden type is rune
const f = 3+5i       // Default hidden type is complex128
```

Default hidden type for constants.

| Value           | Hidden type   |
| --------------- | ------------- |
| Integers        | int           |
| Floats          | float64       |
| Complex Numbers | complex128    |
| Strings         | string        |
| Booleans        | bool          |
| Characters      | int32 or rune |

The default type of a named constant type will become the type of variable they are assigned to. For example, in the below code variable a will get its type from the default type of unnamed constant `123` which is `int`.

```go
var a = 123
```

The use of untyped constants is that the type of the constant will be decided dependeing upon the type of variable they are being assigned to. 

`Pi` constant value in `math` package is declared as below.

```go
const Pi = 3.14159265358979323846264338327950288419716939937510582097494459
```

Notice that the type is not specified in only has a hidden default type (which is `float64` here). Let's see a code

```go
package main
import (
    "fmt"
    "math"
)
func main() {
    var f1 float32
    var f2 float64
    f1 = math.Pi
    f2 = math.Pi

    fmt.Printf("Type: %T Value: %v\n", math.Pi, math.Pi)
    fmt.Printf("Type: %T Value: %v\n", f1, f1)
    fmt.Printf("Type: %T Value: %v\n", f2, f2)
}
```

**Output:**

```go
Type: float64 Value: 3.141592653589793
Type: float32 Value: 3.1415927
Type: float64 Value: 3.141592653589793
```

Notice above program.
- Due to untyped nature of `math.Pi` constant it can be assigned to a variable of type `float32` as well as `float64`. This is otherwise is not possible in Go after type is fixed.
- Then we print the type of `math.Pi`, it prints the default type which is `float64`.

Depending upon use case an untyped constant can be assigned to a low precision type (`float32`) or a high precision type (`float64`)


## References
https://golangbyexample.com/typed-untyped-constant-golang/