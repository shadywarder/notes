**2025-02-28 18:08**
**Tags:** [go](../3%20-%20indexes/go.md) [go101](../2%20-%20tags/go101.md)

## Methods in Go
### Each Method Corresponds to an Implicit Function
For each method declaration, compiler will declare a corresponding implicit function for it. For example, for the following piece of code:

```go
type Book struct {
	pages int
}

func (b Book) Pages() int {
	return b.pages
}

func (b *Book) SetPages(pages int) {
	b.pages = pages
}
```

Two following functions are implicitly declared by compiler:

```go
func Book.Pages(b Book) int {
	// The body is the same as the Pages method.
	return b.pages
}

func (*Book).SetPages(b *Book, pages int) {
	// The body is the same as the SetPages method.
	b.pages = pages
}
```

The implicit function names, `Book.Pages` and `(*Book).SetPages`, are both of the form `TypeDenotation.MethodName`. As identifiers in Go can't contain the period special characters, the two implicit function names are not legal identifiers, so the two functions can't be declared explicitly. They can only be declared by compilers directly, but they can be called in user code:

```go
package main

import "fmt"

type Book struct {
	pages int
}

func (b Book) Pages() int {
	return b.pages
}

func (b *Book) SetPages(pages int) {
	b.pages = pages
}

func main() {
	var book Book
	// Call the two implicit declared functions.
	(*Book).SetPages(&book, 123)
	fmt.Println(Book.Pages(book)) // 123
}
```

In fact, compilers not only declare the two implicit functions, they also rewrite the two corresponding explicit declared methods to let the two methods call the two implicit functions in the method bodies (at least, we can think this happens), just like the following code shows:

```go
func (b Book) Pages() int {
	return Book.Pages(b)
}

func (b *Book) SetPages(pages int) {
	(*Book).SetPages(b, pages)
}
```

### Implicit Methods With Pointer Receivers
For each method declared for value receiver type `T`, a corresponding method with same name will be implicitly declared by compiler for type `*T`. By the example above, the `Pages` method is declared for type `Book`, so a method with the same name `Pages` is implicitly declared for type:

```go
// Note: this is not a legal Go syntax.
// It is shown here just for explanation purpose.
// It indicates that the expression (&aBook).Pages
// is evaluated as aBook.Pages (see below sections).
func (b *Book) Pages = (*b).Pages
```

This is why I don't reject the use of the value receiver terminology (as the opposite of the pointer receiver terminology). After all, when we explicitly declare a method for a non-pointer type, if fact two methods are declared, the explicit one is for the non-pointer type and the implicit one is for the corresponding pointer type.

As mentioned at the last section, for each declared method, compilers will also declare a corresponding implicit function for it. So for the implicitly declared method, the following implicit function is declared by compiler:

```go
func (*Book).Pages(b *Book) int {
	return Book.Pages(*b)
}
```

In other words, for each explicitly declared method with a value receiver, two implicit functions and one implicit method will also declared at the same time.

### Receiver Arguments Are Passed by Copy
Same as general function arguments, the receiver arguments are also passed by copy. So, the modifications on the direct part of a receiver argument in method call will not be reflected to the outside of the method.

An example:

```go
package main

import "fmt"

type Book struct {
	pages int
}

type Books []Book

func (books Books) Modify() {
	// Modifications on the underlying part of
	// the receiver will be reflected to outside
	// of the method.
	books[0].pages = 500
	// Modifications on the direct part of the
	// receiver will not be reflected to outside
	// of the method.
	books = append(books, Book{789})
}

func main() {
	var books = Books{{123}, {456}}
	books.Modify()
	fmt.Println(books) // [{500} {456}]
}
```

Some off topic, if the two lines in the orders of the above `Modify` method are exchanged, then both of the modifications will not be reflected to outside of the method body.

```go
func (books Books) Modify() {
	books = append(books, Book{789})
	books[0].pages = 500
}

func main() {
	var books = Books{{123}, {456}}
	books.Modify()
	fmt.Println(books) // [{123} {456}]
}
```

### Method Value Normalization
At compile time, compilers will normalize each method value expression, by changing implicit address taking and pointer dereference operations into explicit ones in that method value expression.

Assume `v` is a value of type `T` and `v.m` is a legal method value expressions,
- if `m` is s method explicitly declared for type `*T`, then compilers will normalize it as `(&v).m`;
- if `m` is a method explicitly declared for type `T`, then the method value expressions `v.m` is already normalized.

Assume `p` is a value of type `*T` and `p.m` is a legal method value expression,
- if `m` is a method explicitly declared for type `T`, then compilers will normalize it as `(*p).m`
- If `m` is a method explicitly declared for type `*T`, then the method value expression `p.m` is already normalized.

### Method Value Evaluation
Assume `v.m` is a normalized method value expression, at run time, when the method value `v.m` is evaluated, the receiver argument `v` is evaluated and a copy of the evaluation result is saved and user in later calls to the method value.

```go
package main

import "fmt"

type Book struct {
	pages int
}

func (b Book) Pages() int {
	return b.pages
}

func (b *Book) Pages2() int {
	return (*b).Pages()
}

func main() {
	var b = Book{pages: 123}
	var p = &b
	var f1 = b.Pages
	var f2 = p.Pages
	var g1 = p.Pages2
	var g2 = b.Pages2
	b.pages = 789
	fmt.Println(f1()) // 123
	fmt.Println(f2()) // 123
	fmt.Println(g1()) // 789
	fmt.Println(g2()) // 789
}
```

### A Defined Type Doesn't Obtain the Methods Declared Explicitly for the Source Type Used in Its Definition
For example, in the following code, unlike the defined type `MyInt`, the defined type `Age` has not an `IdOdd` method.

```go
package main

type MyInt int
func (mi MyInt) IsOdd() bool {
	return mi%2 == 1
}

type Age MyInt

func main() {
	var x MyInt = 3
	_ = x.IsOdd() // okay
	
	var y Age = 36
	// _ = y.IsOdd() // error: y.IsOdd undefined
	_ = y
}
```

### Should a Method Be Declared With Pointer Receiver or Value Receiver?
Firstly, from the last section, we know that sometimes we must declare methods with pointer receivers.

If fact, we can always declared method with pointer receivers without any logic problems. It is just a matter of program performance that sometimes it is better to declared methods with value receivers.

For the cases value receivers and pointer receivers are both acceptable, here are some factors needed to be considered to make decisions.
- Too many pointer copies may cause workload for garbage collector.
- If the size of a value receiver type is large, then the receiver argument copy cost may be not negligible. Pointer types are all small-size types.
- Declaring methods of both value receivers and pointer receivers for the same base type is more likely to cause data races if the declared methods are called concurrently in multiple goroutines.
- Values of the types in the `sync` standard package should not be copied, so declaring methods with value receivers for struct types which embedding the types in the `sync` standard package is problematic.

If it is hard to make a decision whether a method should use a pointer receiver or a value receiver, then just choose the pointer receiver way.

## References
[Methods in Go](https://go101.org/article/method.html)