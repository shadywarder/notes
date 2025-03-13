**2025-01-26 21:28**
**Tags:** [go](../3%20-%20indexes/go.md) [go101](../2%20-%20tags/go101.md)

## Interfaces in Go
### Interface Types and Type Sets
An interface type defines some (type) requirements. All non-interface types satisfying these requirements form a type set, which is called the type set of the interface type.

For example, the predeclared `error` interface type, which definition is shown below, embeds a method specification `Error() string`. In the definition, `interface{...}` is called an interface type literal and the word `interface` are a keyword in Go.

```go
type error interface {
	Error() string
}
```

The following are some other interface type definitions and alias declarations.

```go
// This interface directly specifies two methods and
// embeds two other interface types, one of which
// is a type name and the other is a type literal.
type ReadWriteCloser = interface {
	Read(buf []byte) (n int, err error)
	Write(buf []byte) (n int, err error)
	error                      // a type name
	interface{ Close() error } // a type literal
}

// This interface embeds an approximation type. Its type
// set includes all types whose underlying type is []byte.
type AnyByteSlice = interface {
	~[]byte
}

// This interface embeds a type union. Its type set includes
// 6 types: uint, uint8, uint16, uint32, uint64 and uintptr.
type Unsigned interface {
	uint | uint8 | uint16 | uint32 | uint64 | uintptr
}
```

Embedding an interface type (denoted by either a type name or a type literal)
in another one is equivalent to (recursively) expanding the elements in the former into the latter. For example, the interface type denoted by the type alias `ReadWriteCloser` is equivalent to the interface type denoted the the following literal, which directly specifies four methods:

```go
interface {
	Read(buf []byte) (n int, err error)
	Write(buf []byte) (n int, err error)
	Error() string
	Close() error
}
```

### Value Boxing
If a type `T` implements a (basis) interface type `I`, then any value of type `T` can be implicitly converted to type `I`. In other words, any value of type `T` is assignable to (modifiable) value of type `I`. When a `T` value is converted (assigned) to an `I` value,
- if type `T` is non-interface type, then a copy of the `T` value is boxed (or encapsulated) into the result (or destination) `I` value. The time complexity of the copy is $O(n)$, where $n$ is the size of copied `T` value.
- if type is also an interface type, then a copy of the value boxed in the `T` value is boxed (or encapsulated) into the result (or destination) `I` value. The standard go compiler makes an optimization here, so the time complexity of the copy is $O(1)$ instead of $O(n)$.

Let's view an example which demonstrates some assignments with interface values as the destinations.

```go
package main

import "fmt"

type Aboutable interface {
	About() string
}

// Type *Book implements Aboutable.
type Book struct {
	name string
}
func (book *Book) About() string {
	return "Book: " + book.name
}

func main() {
	// A *Book value is boxed into an
	// interface value of type Aboutable.
	var a Aboutable = &Book{"Go 101"}
	fmt.Println(a) // &{Go 101}

	// i is a blank interface value.
	var i interface{} = &Book{"Rust 101"}
	fmt.Println(i) // &{Rust 101}

	// Aboutable implements interface{}.
	i = a
	fmt.Println(i) // &{Go 101}
}
```

The following is another example which shows how a blank interface value is used to box values of any non-interface type.

```go
package main

import "fmt"

func main() {
	var i interface{}
	i = []int{1, 2, 3}
	fmt.Println(i) // [1 2 3]
	i = map[string]int{"Go": 2012}
	fmt.Println(i) // map[Go:2012]
	i = true
	fmt.Println(i) // true
	i = 1
	fmt.Println(i) // 1
	i = "abc"
	fmt.Println(i) // abc

	// Clear the boxed value in interface value i.
	i = nil
	fmt.Println(i) // <nil>
}
```

Go compilers will build a global table which contains the information of each type at compile time. The information includes what kind a type is, what methods and fields a type owns, what the element type of a container type is, type sizes, etc. The global table will be loaded into memory when a program starts.

At run time, when a non-interface value is boxed into an interface value, the Go runtime (at least for the standard Go runtime) will analyze and build the implementation information for the type pair of the two values, and store the implementation information in the interface value. The implementation information for each non-interface type and interface type pair will only built one and cached in a global map for execution efficiency consideration The number of entries of he global map never decreases. In fact, a non-nil interface value just uses an internal pointer field which references a cached implementation information entry.

The implementation information for each (interface type, dynamic type) pair includes two pieces of information:
1. the information of the dynamic type (a non-interface type)
2. and a method table (a slice) which stores all the corresponding methods specified by the interface type and declared for the non-interface type (the dynamic type).

These two pieces of information are essential for implementing two important features in Go:
1. The dynamic type information is the key to implement reflection in Go.
2. The method table information is the key to implement polymorphism.

### Polymorphism
When a non-interface value `t` of a type `T` is boxed in an interface value `i` of type `I` calling a method specified by the interface type `I` on the interface value `i` will call the corresponding method declared for the non-interface type `T` on the non-interface value `t` actually. On other words, **calling the method of an interface value will actually call the corresponding method of the dynamic value of the interface value**. For example, calling method `i.m` will call method `t.m` actually. With different dynamic values of different dynamic types boxed into the interface value, the interface value behaves differently. This is called polymorphism. 

Whenm method `i.m` is called, the method table in the implementation information stored in `i` will be looked up to find and call the corresponding method `t.m`. The method table is a slice and the lookup is just a slice element indexing, so this is quick.

*(Note, calling method on a nil interface value will panic at run time, for there are no available declared methods to be called.)*

An example:

```go
package main

import "fmt"

type Filter interface {
	About() string
	Process([]int) []int
}

// UniqueFilter is used to remove duplicate numbers.
type UniqueFilter struct{}
func (UniqueFilter) About() string {
	return "remove duplicate numbers"
}
func (UniqueFilter) Process(inputs []int) []int {
	outs := make([]int, 0, len(inputs))
	pusheds := make(map[int]bool)
	for _, n := range inputs {
		if !pusheds[n] {
			pusheds[n] = true
			outs = append(outs, n)
		}
	}
	return outs
}

// MultipleFilter is used to keep only
// the numbers which are multiples of
// the MultipleFilter as an int value.
type MultipleFilter int
func (mf MultipleFilter) About() string {
	return fmt.Sprintf("keep multiples of %v", mf)
}
func (mf MultipleFilter) Process(inputs []int) []int {
	var outs = make([]int, 0, len(inputs))
	for _, n := range inputs {
		if n % int(mf) == 0 {
			outs = append(outs, n)
		}
	}
	return outs
}

// With the help of polymorphism, only one
// "filterAndPrint" function is needed.
func filterAndPrint(fltr Filter, unfiltered []int) []int {
	// Calling the methods of "fltr" will call the
	// methods of the value boxed in "fltr" actually.
	filtered := fltr.Process(unfiltered)
	fmt.Println(fltr.About() + ":\n\t", filtered)
	return filtered
}

func main() {
	numbers := []int{12, 7, 21, 12, 12, 26, 25, 21, 30}
	fmt.Println("before filtering:\n\t", numbers)

	// Three non-interface values are boxed into
	// three Filter interface slice element values.
	filters := []Filter{
		UniqueFilter{},
		MultipleFilter(2),
		MultipleFilter(3),
	}

	// Each slice element will be assigned to the
	// local variable "fltr" (of interface type
	// Filter) one by one. The value boxed in each
	// element will also be copied into "fltr".
	for _, fltr := range filters {
		numbers = filterAndPrint(fltr, numbers)
	}
}
```

The output:

```bash
before filtering:
	 [12 7 21 12 12 26 25 21 30]
remove duplicate numbers:
	 [12 7 21 26 25 30]
keep multiples of 2:
	 [12 26 30]
keep multiples of 3:
	 [12 30]
```

In the above example, polymorphism makes it unnecessary to write one `filterAndPrint` function for each filter type.

Besides the above benefit, polymorphism also makes it possible for the developers of a library code package to declare an exported interface type and declare a function (or method) which has a parameter of the interface type, so that a user of the package can declare a type, which implements the interface type, in user code and pass arguments of the user type to calls to the function (or method). The developers of the code package don't need to care about how the user type is declared, as long as the user type satisfies the behaviors specified by the interface type declared in the library code package.

If fact, polymorphism is not essential feature for a language. There are alternative ways to achieve the same job, such as callback functions. But the polymorphism way is cleaner and more elegant.

### Type assertion
There are four kinds of interface-value-involving value conversions cases in Go:
1. convert a non-interface value to an interface, where the type of the non-interface value must implement the type of the interface value.
2. convert an interface value to an interface value, where the type of the source interface must implement the type of the destination interface value.
3. convert an interface value to a non-interface value, where the type of the non-interface value must implement the type of the interface value.
4. convert an interface value to an interface value, where the type of the source interface doesn't implement the destination interface type, but the dynamic type of the source interface value might implement the destination interface type.

An example which shows how to use type assertions (asserted types are non-interface types):

```go
package main

import "fmt"

func main() {
	// Compiler will deduce the type of 123 as int.
	var x interface{} = 123

	// Case 1:
	n, ok := x.(int)
	fmt.Println(n, ok) // 123 true
	n = x.(int)
	fmt.Println(n) // 123

	// Case 2:
	a, ok := x.(float64)
	fmt.Println(a, ok) // 0 false

	// Case 3:
	a = x.(float64) // will panic
}
```

Another example which shows how to use type assertions (asserted types are interface types):

```go
package main

import "fmt"

type Writer interface {
	Write(buf []byte) (int, error)
}

type DummyWriter struct{}
func (DummyWriter) Write(buf []byte) (int, error) {
	return len(buf), nil
}

func main() {
	var x interface{} = DummyWriter{}
	var y interface{} = "abc"
	// Now the dynamic type of y is "string".
	var w Writer
	var ok bool

	// Type DummyWriter implements both
	// Writer and interface{}.
	w, ok = x.(Writer)
	fmt.Println(w, ok) // {} true
	x, ok = w.(interface{})
	fmt.Println(x, ok) // {} true

	// The dynamic type of y is "string",
	// which doesn't implement Writer.
	w, ok = y.(Writer)
	fmt.Println(w, ok) // <nil> false
	w = y.(Writer)     // will panic
}
```

Here is an example in which a `type-switch` control flow code block is used.

```go
package main

import "fmt"

func main() {
	values := []interface{}{
		456, "abc", true, 0.33, int32(789),
		[]int{1, 2, 3}, map[int]bool{}, nil,
	}
	for _, x := range values {
		// Here, v is declared once, but it denotes
		// different variables in different branches.
		switch v := x.(type) {
		case []int: // a type literal
			// The type of v is "[]int" in this branch.
			fmt.Println("int slice:", v)
		case string: // one type name
			// The type of v is "string" in this branch.
			fmt.Println("string:", v)
		case int, float64, int32: // multiple type names
			// The type of v is "interface{}",
			// the same as x in this branch.
			fmt.Println("number:", v)
		case nil:
			// The type of v is "interface{}",
			// the same as x in this branch.
			fmt.Println(v)
		default:
			// The type of v is "interface{}",
			// the same as x in this branch.
			fmt.Println("others:", v)
		}
		// Note, each variable denoted by v in the
		// last three branches is a copy of x.
	}
}
```

The output:

```bash
number: 456
string: abc
others: true
number: 0.33
number: 789
int slice: [1 2 3]
others: map[]
<nil>
```

### More About Interface in Go
#### Comparisons involving interface values
There are two cases of comparisons involving interface values:
1. comparison between a non-interface value and an interface value.
2. comparisons between two interface values.

For the first case, the type of the non-interface value must implement the type (assume it is `I`) of the interface value, so the non-interface value can be converted to (boxed into) an interface value of `I`. This means a comparison between a non-interface value and an interface value can be translated to a comparison between two interface values.

Comparing two interface values is comparing their respective dynamic types and dynamic values actually.

The steps of comparing two interface values (with the `==` operator):
1. if one of the two interface values is a nil interface value, then the comparison result is whether or not the other interface value is also a nil interface value.
2. if the dynamic types of the two interface values are two different types, then the comparison result is `false`.
3. in the case where the dynamic types of the two interface values are the same type,
	- if the same dynamic type is an incomparable type, a panic will occur.
	- otherwise, the comparison result in the result of comparing the dynamic values of the two interface values.

In short, two interface values are equal only if one of the following conditions are satisfied.
1. They are both nil interface values.
2. Their dynamic types are identical and comparable, and their dynamic values are equal to each other.

An example:

```go
package main

import "fmt"

func main() {
	var a, b, c interface{} = "abc", 123, "a"+"b"+"c"
	// A case of step 2.
	fmt.Println(a == b) // false
	// A case of step 3.
	fmt.Println(a == c) // true

	var x *int = nil
	var y *bool = nil
	var ix, iy interface{} = x, y
	var i interface{} = nil
	// A case of step 2.
	fmt.Println(ix == iy) // false
	// A case of step 1.
	fmt.Println(ix == i) // false
	// A case of step 1.
	fmt.Println(iy == i) // false

	// []int is an incomparable type
	var s []int = nil
	i = s
	// A case of step 1.
	fmt.Println(i == nil) // false
	// A case of step 3.
	fmt.Println(i == i) // will panic
}
```

#### Values of `[]T` can't be directly converted to `[]I`, even if type `T` implements interface type `I`.

For example, sometimes, we may need to convert a `[]string` value to `[]interface{}` type. Unlike some other languages, there is no direct way to make the conversion. We must take the conversion manually in a loop:

```go
package main

import "fmt"

func main() {
	words := []string{
		"Go", "is", "a", "high",
		"efficient", "language.",
	}

	// The prototype of fmt.Println function is
	// func Println(a ...interface{}) (n int, err error).
	// So words... can't be passed to it as the argument.

	// fmt.Println(words...) // not compile

	// Convert the []string value to []interface{}.
	iw := make([]interface{}, 0, len(words))
	for _, w := range words {
		iw = append(iw, w)
	}
	fmt.Println(iw...) // compiles okay
}
```

#### Each method specified in an interface type corresponds to an implicit function
For each method with name `m` in the method set defined by an interface type `I`, compilers will implicitly declare a function named `I.m`, which has one more input parameter, of type `I`, than method `m`. The extra parameters is the first input parameter of function `I.m`. Assume `i` is an interface value of `I`, then the method call `i.m(...)` is equivalent to the function call `I.m(i, ...)`.

An example:

```go
package main

import "fmt"

type I interface {
	m(int)bool
}

type T string
func (t T) m(n int) bool {
	return len(t) > n
}

func main() {
	var i I = T("gopher")
	fmt.Println(i.m(5))                        // true
	fmt.Println(I.m(i, 5))                     // true
	fmt.Println(interface{m(int)bool}.m(i, 5)) // true

	// The following lines compile okay,
	// but will panic at run time.
	I(nil).m(5)
	I.m(nil, 5)
	interface {m(int) bool}.m(nil, 5)
}
```

## References
[Go 101 Article](https://go101.org/article/interface.html)