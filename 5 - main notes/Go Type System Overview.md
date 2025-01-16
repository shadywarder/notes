**2025-01-10 16:19**
Tags: [[go]] [[go101]]

## Go Type System Overview
### Concept: Basic Types
- Built-in string type: `string`.
- Built-in boolean type: `bool`.
- Build-in numeric types:
	- `int8`, `uint8` (`byte`), `int16`, `uint16`, `int32` (`rune`), `uint32`, `int64`, `uint64`, `int`, `uint`, `uintptr`.
	- `float32`, `float64`.
	- `complex64`, `complex128`.

Note, `byte` is a built-in alias of `uint8`, and `rune` is a built-in alias of `int32`. 

### Concept: Composite Types
Go supports the following composite types:
- pointer types - C point alike.
- struct types - C struct alike.
- function types - function are first-class types in Go.
- container types:
	- array types - fixed-length container types.
	- slice type - dynamic-length and dynamic capacity container types.
	- map types - maps are associative arrays (or dictionaries). The standard Go compiler implements maps as hashtables.
- channel types - channels are used to synchronize data among goroutines.
- interface types - interfaces play a key role in reflection and polymorphism.

## Syntax: Type Definitions
In Go we can define new types by using the following form. In the syntax, `type` is a keyword.
Note,
- a new defined type and its respective source type in type definitions are two distinct types.
- two types defined in two type definitions are always two distinct types.
- the new defined type and the source type will share the same underlying type, and their values can be converted to each other
- types can be defined within function bodies.

Some type definition examples: 

```go
// The following new defined and source types are all
// basic types. The source types are all predeclared.
type (
	MyInt int
	Age   int
	Text  string
)

// The following new defined and source types are all
// composite types. The source types are all unnamed.
type IntPtr *int
type Book struct{author, title string; pages int}
type Convert func(in0 int, in1 bool)(out0 int, out1 string)
type StringArray [5]string
type StringSlice []string

func f() {
	// The names of the three defined types
	// can be only used within the function.
	type PersonAge map[string]int
	type MessageQueue chan string
	type Reader interface{Read([]byte) int}
}
```

Please note that, from Go 1.9 to Go 1.17, the Go specification ever thought predeclared built-in types are defined types. But since Go 1.18, the Go specification clarifies built-in types are not defined types.

### Concept: Named Types vs. Unnamed Types
Before Go 1.9, the terminology **named type** is defined accurately in Go specification. A named type was defined as a type that is represented by an identifier. Along with the custom type alias feature introduced in Go 1.9, the **named type** was ever removed from Go specification and it was replaced by the **defined type** terminology. Since Go 1.18, along with the introduction of custom generics, the **named type** terminology has been added back to Go specification.

A named type may be
- a predeclared type (not including type alias);
- a defined (non-custom-generic) type;
- an instantiated type (of a generic type);
- a type parameter type (used in custom generics).

Other value types are called unnamed types. An unnamed type must be a composite type (not vice versa).

### Concept: Underlying Types
In Go, each type has an underlying type. Rules:
- for built-in types, the respective underlying types are themselves.
- for the `Pointer` type defined in the `unsafe` standard code package, its underlying type is itself. `unsafe.Pointer` is also viewed as a built-in type.
- the underlying type of an unnamed type, which must be a composite type, is itself.
- in a type declaration, the newly declared type and the source type have the same underlying type.

Examples:

```go
// The underlying types of the following ones are both int.
type (
	MyInt int
	Age   MyInt
)

// The following new types have different underlying types.
type (
	IntSlice   []int   // underlying type is []int
	MyIntSlice []MyInt // underlying type is []MyInt
	AgeSlice   []Age   // underlying type is []Age
)

// The underlying types of []Age, Ages, and AgeSlice
// are all the unnamed type []Age.
type Ages AgeSlice
```

How can an underlying type be traced given a user declared type? The rule is, when a built-in basic type or an unnamed type is met, the tracing should be stopped. Take the type declaration shown above as examples, let's trace their underlying types.

MyInt → int
Age → MyInt → int
IntSlice → []int
MyIntSlice → []MyInt → ~~[]int~~
AgeSlice → []Age → ~~[]MyInt → []int~~
Ages → AgeSlice → []Age → ~~[]MyInt → []int~~

### Concept: Values
An instance of a type is called a 'value' of the type. Values of the same type share some common properties. A type may have many values. One of them is the zero value of the type.

Each type has a zero value, which can be viewed as the default value of the type. The predeclared `nil` identifier can used to represent zero values of slices, maps, functions, channels, pointers (including type-unsafe pointer) and interfaces.

There are several kinds of value representation forms in code, including literals, named constants, variables and expressions, though the former three can be viewed as special cases of the latter one.

A value can be typed or untyped (more details in [[Typed and Untyped Constants in Go]])

### Concept: Directions of Channel Types
Channel values can be viewed as synchronized first-in-first-out (FIFO) queues. Channel types and values have directions.
- A channel value which is both sendable and receivable is called a bidirectional channel. Its type is called a bidirectional channel type. The underlying types of bidirectional channel types are denoted by the `chan T` literal.
- A channel value which is only sendable is called a send-only channel. Its type is called a send-only channel type. Send-only channel types are denoted by the `chat<- T` literal.
- A channel value which is only receivable is called a receive-only channel. Its type is called a receive-only channel type. Receive-only channel types are denoted by the `<-chan T` literal.

## References
[Go 101 Article](https://go101.org/article/type-system-overview.html)
