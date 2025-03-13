**2025-02-19 13:29**
**Tags:** [go](../3%20-%20indexes/go.md) [go101](../2%20-%20tags/go101.md)
 
## Reflections in Go
### Overview of Go Reflections
- We can inspect Go values through the values of `Type` and `Value` types defined in the `reflect` package.
- One of the Go reflection design goals is any non-reflection operations should be also possible to be applied through the reflection ways.

### The `reflect.Type` Type and Values

- We can create a `reflect.Type` values from an arbitrary non-interface value by calling the `reflect.TypeOf` function.
- Since Go 1.22, we can also use the `reflect.TypeFor` function to get a `reflect.Type` value which represents a type which is known at compile time. The compile-time known type may be either non-interface or interface.
- The `reflect.Type` type is interface type. It specifies several methods. We can call these methods to inspect the information of the type represented by a `reflect.Type` receiver value.
- Calling one of the methods through an improper `reflect.Type` receiver value will produce a panic.

We can use the `Elem` method to get the base type of a pointer type. For example,

```go
type T []interface{ m() }

func (T) m() {}

func main() {
	tt := reflect.TypeOf(T{})
	fmt.Println(tt.Kind()) // slice

	tim := tt.Elem()
	fmt.Println(tim.Kind()) // interface

	fmt.Println(tt.Implements(tim)) // true

	// All types implement any blank interface type.
	tp := reflect.TypeOf(new(interface{})).Elem()
	fmt.Println(tim.Implements(tp))
}
```

- We can get all of the field types (of a struct type) and the method information of a type through reflection. 
- We can get the parameter and result type information of a function type through reflection.

```go
type F func(string, int) bool
func (f F) m(s string) bool {
	return f(s, 32)
}
func (f F) M() {}

type I interface{m(s string) bool; M()}

func main() {
	var x struct {
		F F
		i I
	}
	tx := reflect.TypeOf(x)
	fmt.Println(tx.Kind())        // struct
	fmt.Println(tx.NumField())    // 2
	fmt.Println(tx.Field(1).Name) // i
	// Package path is an intrinsic property of
	// non-exported selectors (fields or methods).
	fmt.Println(tx.Field(0).PkgPath) // 
	fmt.Println(tx.Field(1).PkgPath) // main

	tf, ti := tx.Field(0).Type, tx.Field(1).Type
	fmt.Println(tf.Kind())               // func
	fmt.Println(tf.IsVariadic())         // false
	fmt.Println(tf.NumIn(), tf.NumOut()) // 2 1
	t0, t1, t2 := tf.In(0), tf.In(1), tf.Out(0)
	// The next line prints: string int bool
	fmt.Println(t0.Kind(), t1.Kind(), t2.Kind())

	fmt.Println(tf.NumMethod(), ti.NumMethod()) // 1 2
	fmt.Println(tf.Method(0).Name)              // M
	fmt.Println(ti.Method(1).Name)              // m
	_, ok1 := tf.MethodByName("m")
	_, ok2 := ti.MethodByName("m")
	fmt.Println(ok1, ok2) // false true
}
```







## References