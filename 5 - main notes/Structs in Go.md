**2025-01-10 21:49**
Tags: [[go]] [[go101]]

## Structs in Go
### Struct Types and Struct Type Literals
The field tags and the order of the field declarations in a struct type matter for the identity of the struct type. Two unnamed struct types are identical only if they have the same sequence of field declarations. Two field declarations are identical only if their respective names, their respective types and their respective tags are all identical. Please note, **two non-exported struct field names from different packages are always viewed as two different names**.

A struct type can't have a field of the struct type itself, neither directly nor recursively.

### About Struct Value Assignments
Two struct values can be assigned to each other only if their types are identical or the types of the two struct values have an identical underlying type (considering field tags) and at least one of the two types is an unnamed type.

### Struct Field Addressability
The fields of an addressable struct are also addressable. The fields of an unaddressable struct are also unaddressable. The fields of unaddressable structs can't be modified. All composite literals, including struct composite literals are unaddressable.

Example:

```go
package main

import "fmt"

func main() {
	type Book struct {
		Pages int
	}
	var book = Book{} // book is addressable
	p := &book.Pages
	*p = 123
	fmt.Println(book) // {123}

	// The following two lines fail to compile, for
	// Book{} is unaddressable, so is Book{}.Pages.
	/*
	Book{}.Pages = 123
	p = &(Book{}.Pages) // <=> p = &Book{}.Pages
	*/
}
```

Note that the precedence of the property selection operator `.` in a selector is higher than the address-taking operator `&`.

### Composite Literals Are Unaddressable But Can Take Address
Generally, only addressable values can take addresses. But there is a syntactic sugar in Go, which allows us to take addresses on composite literals. A syntactic sugar is an exception to make programming convenient.

For example,
```go
package main

func main() {
	type Book struct {
		Pages int
	}
	// Book{100} is unaddressable but can
	// be taken address.
	p := &Book{100} // <=> tmp := Book{100}; p := &tmp
	p.Pages = 200
}
```

### About Struct Value Comparisons 
A struct type is comparable only if none of the types of its fields (including the fields with names as the blank identifier `_`) are *incomparable*.

Two struct values are comparable only if they can be assigned to each other and their types are both comparable. In other words, two struct values can be compared with each other only if the (comparable) types of the two struct values are identical or their underlying types are identical (considering field tags) and at least one of the types is unnamed.

When comparing two struct values of the same type, each par of their corresponding fields will be compared (in the order shown in source code). The two struct values are equal only if all of their corresponding fields are equal. The comparison stops in advance when a pair of fields is found unequal or *a panic occurs*. In comparisons, fields with names as the blank identifier `_` will be ignored.

### About Struct Value Conversions
Values of two struct types `S1` and `S2` can be converted to each other's types, if `S1` and `S2` share the identical underlying type (by ignoring field tags). In particular if either `S1` or `S2` is an unnamed type and their underlying types are identical (considering field tags), then the conversions between the values of them can be implicit.

Given struct types `S0`, `S1`, `S2`, `S3` and `S4` in the following code snippet,
- values of type `S0` can't be converted to the other four types, and vice versa, because the corresponding field names are different.
- two values of two different types among `S1`, `S2`, `S3` and `S4` can be converted to each other's type.

In particular,
- values of the type denoted by `S2` can be implicitly converted to type `S3`, and vice versa.
- values of the type denoted by `S2` can be implicitly converted to type `S4`, and vice versa.

But,
- values of the type denoted by `S2` must be explicitly converted to type `S1`, and vice versa.
- values of type `S3` must be explicitly converted to type `S4`, and vice versa.

### Anonymous Struct Types Can Be Used in Field Declarations
Anonymous struct types are allowed to be used as the types of the fields of another struct type. Anonymous struct type literals are also allowed to be used in composite literals.

An example:

```go
var aBook = struct {
	// The type of the author field is
	// an anonymous struct type.
	author struct {
		firstName, lastName string
		gender              bool
	}
	title string
	pages int
}{
	author: struct { // an anonymous struct type
		firstName, lastName string
		gender              bool
	}{
		firstName: "Mark",
		lastName: "Twain",
	},
	title: "The Million Pound Note",
	pages: 96,
}
```

## References
[Go 101 Article](https://go101.org/article/struct.html)