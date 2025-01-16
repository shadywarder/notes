**2025-01-11 00:27**
Tags:

## Arrays, Slices and Maps in Go
### Container Value Literals
There are several variants for array and slice composite literals:

```go
// The followings slice composite literals
// are equivalent to each other.
[]string{"break", "continue", "fallthrough"}
[]string{0: "break", 1: "continue", 2: "fallthrough"}
[]string{2: "fallthrough", 1: "continue", 0: "break"}
[]string{2: "fallthrough", 0: "break", "continue"}
```

### Composite Literals are Unaddressable but Can Be Taken Address
We have learned that *struct composite literals can be taken addresses directly* before. Container composite literals have no exceptions here.

Example:

```go
package main

import "fmt"

func main() {
	pm := &map[string]int{"C": 1972, "Go": 2009}
	ps := &[]string{"break", "continue"}
	pa := &[...]bool{false, true, true, false}
	fmt.Printf("%T\n", pm) // *map[string]int
	fmt.Printf("%T\n", ps) // *[]string
	fmt.Printf("%T\n", pa) // *[4]bool
}
```

### Nested Composite Literals Can Be Simplified
If a composite literal nested many other composite many other composite literals, then those nested composited literals can simplified to the form `{...}`.

For example, the slice value literal

```go
// A slice value of a type whose element type is
// *[4]byte. The element type is a pointer type
// whose base type is [4]byte. The base type is
// an array type whose element type is "byte".
var heads = []*[4]byte{
	&[4]byte{'P', 'N', 'G', ' '},
	&[4]byte{'G', 'I', 'F', ' '},
	&[4]byte{'J', 'P', 'E', 'G'},
}
```

can be simplified to

```go
var heads = []*[4]byte{
	{'P', 'N', 'G', ' '},
	{'G', 'I', 'F', ' '},
	{'J', 'P', 'E', 'G'},
}
```

### Recall the Internal Definition of Slice Types
To understand slice types and values better and explain slices easier, we need to have an impression on the internal structure of slice types. The internal structure of slice types defined by the standard Go compiler/runtime is like 

```go
type _slice struct {
	elements unsafe.Pointer // referencing underlying elements
	len      int            // length
	cap      int            // capacity
}
```

![](../attachments/Pasted%20image%2020250111012614.png)

Although the underlying memory segment which hosts the element of a slice may be very large, the slice may be only aware of a sub-segment of the memory segment. For example, in the above picture, the slice is only aware of middle grey sub-segment of the whole memory segment.

For the slice depicted in the above picture, the elements from index `len` to index `cap` (exclusive) don't belong to the elements of the slice. They are just some redundant element slots for the depicted slice, but they may effective elements of other slices or another array.

### Container Assignments
If a map is assigned to another map, then the two maps will share all (underlying) elements. Appending elements into (or deleting elements from) one map will on the other map.

Like map assignments, if a slice is assigned to another slice, they will share all (underlying) elements. Their respective lengths and capacities equal to each other. However, if the length/capacity of one slice changes later, the change will not reflect on the other slice.

When an array is assigned to another array, all the elements are copied from the source one to the destination one. The two array don't share any elements.

Example:

```go
package main

import "fmt"

func main() {
	m0 := map[int]int{0:7, 1:8, 2:9}
	m1 := m0
	m1[0] = 2
	fmt.Println(m0, m1) // map[0:2 1:8 2:9] map[0:2 1:8 2:9]

	s0 := []int{7, 8, 9}
	s1 := s0
	s1[0] = 2
	fmt.Println(s0, s1) // [2 8 9] [2 8 9]

	a0 := [...]int{7, 8, 9}
	a1 := a0
	a1[0] = 2
	fmt.Println(a0, a1) // [7 8 9] [2 8 9]
}
```

### Append and Delete Container Elements
An example showing how to use the `append` function:

```go
package main

import "fmt"

func main() {
	s0 := []int{2, 3, 5}
	fmt.Println(s0, cap(s0)) // [2 3 5] 3
	s1 := append(s0, 7)      // append one element
	fmt.Println(s1, cap(s1)) // [2 3 5 7] 6
	s2 := append(s1, 11, 13) // append two elements
	fmt.Println(s2, cap(s2)) // [2 3 5 7 11 13] 6
	s3 := append(s0)         // <=> s3 := s0
	fmt.Println(s3, cap(s3)) // [2 3 5] 3
	s4 := append(s0, s0...)  // double s0 as s4
	fmt.Println(s4, cap(s4)) // [2 3 5 2 3 5] 6

	s0[0], s1[0] = 99, 789
	fmt.Println(s2[0], s3[0], s4[0]) // 789 99 2
}
```

In the above program, 
- the `append` call at line 8 will allocate a new underlying memory segment for slice `s1`, for slice `s0` doesn't have enough redundant element slots to store the new appended element. The same situation is for the `append` call at line 14.
- the `append` call at line 10 will not allocate a new underlying memory segment for slice `s2`, for slice `s1` has enough redundant element slots to store the new appended elements.

So, `s1` and `s2` share some elements, `s0` and `s3` share all elements, and `s4` doesn't share elements with others. The following picture depicted the statuses of these slices at the end of the above program.

![](../attachments/Pasted%20image%2020250111014008.png)

### Create Slices and Maps With the Built-in `make` Function
Assume `M` is a map type and `n` is an integer, we can use the following two forms to create new maps of type `M`.

```go
make(M, n)
make(M)
```

The first form creates a new empty map which is allocated with enough space to hold at least `n` entries without reallocating memory again. The second form only takes one argument, in which case a new empty map with enough space to hold a small number of entries without reallocation memory again. The small number is compiler dependent.

### Allocate Containers With the Build-in `new` Function
We can also call the built-in `new` function to allocate a value of any type and get a pointer which references the allocated value. The allocated value is a zero value of its type. For this reason, it is a nonsense to use `new` function to create map and slice values. 

It is not totally a nonsense to allocate a zero value of an array type with the built-in `new` function. However, it is seldom to do this in practice, for it is more convenient to use composite literals to allocate arrays.

Example: 

```go
package main

import "fmt"

func main() {
	m := *new(map[string]int)   // <=> var m map[string]int
	fmt.Println(m == nil)       // true
	s := *new([]int)            // <=> var s []int
	fmt.Println(s == nil)       // true
	a := *new([5]bool)          // <=> var a [5]bool
	fmt.Println(a == [5]bool{}) // true
}
```

### Addressability of Container Elements
Following are some facts about the addressabilities of container elements.
- Elements of addressable array values are also addressable. Elements of unaddressable array values are also unaddressable. The reason is each array value consists only of one direct part.
- Elements of any slice are always addressable, whether or not that slice value is addressable. This is because the elements of a slice of a slice are stored in the underlying (indirect) value part of the slice and the underlying part is always hosted on an allocated segment.
- Elements of map values are always unaddressable.

For example:

```go
package main

import "fmt"

func main() {
	a := [5]int{2, 3, 5, 7}
	s := make([]bool, 2)
	pa2, ps1 := &a[2], &s[1]
	fmt.Println(*pa2, *ps1) // 5 false
	a[2], s[1] = 99, true
	fmt.Println(*pa2, *ps1) // 99 true
	ps0 := &[]string{"Go", "C"}[0]
	fmt.Println(*ps0) // Go

	m := map[int]bool{1: true}
	_ = m
	// The following lines fail to compile.
	/*
	_ = &[3]int{2, 3, 5}[0]
	_ = &map[int]bool{1: true}[1]
	_ = &m[1]
	*/
}
```

Unlike most other unaddressable values, which direct parts can not be modified, the direct part of a map element values can be modified, but can only be modified (overwritten) as a whole. For most kinds of elements types, this is not a big issue. However, if the element of map type is an array type or struct type, things become some counter-intuitive.

So
- if the element type of a map is a struct type, we can not modify each field of an element (which is a struct) of the map.
- if the element type of a map is an array type, we can not individually modify each element of an element (which is an array) of the map.

Example:

```go
package main

import "fmt"

func main() {
	type T struct{age int}
	mt := map[string]T{}
	mt["John"] = T{age: 29} // modify it as a whole
	ma := map[int][5]int{}
	ma[1] = [5]int{1: 789} // modify it as a whole

	// The following two lines fail to compile,
	// for map elements can be modified partially.
	/*
	ma[1][1] = 123      // error
	mt["John"].age = 30 // error
	*/

	// Accesses are okay.
	fmt.Println(ma[1][1])       // 789
	fmt.Println(mt["John"].age) // 29
}
```

### Derive Slices From Arrays and Slices
There are two subslices syntax forms (`baseContainer` is an array of slice):

```go
baseContainer[low : high]       // two-index form
baseContainer[low : high : max] // three-index form
```

Please note that, subslice operations may cause kind-of memory leaking. For example, half of the memory allocated for the return slice of a call to the following function will be wasted unless the returned slice becomes unreachable (if no other slices share the underlying element memory segment with the returned slice).

```go
func f() []int {
	s := make([]int, 10, 100)
	return s[50:60]
}
```

### Convert Slice to Array Pointer
Since Go 1.17, a slice may be converted to an array pointer. In such a conversion, if the length of the base array type of the pointer type is larger than the length of the slice, a panic occurs.

An example:

```go
package main

type S []int
type A [2]int
type P *A

func main() {
	var x []int
	var y = make([]int, 0)
	var x0 = (*[0]int)(x) // okay, x0 == nil
	var y0 = (*[0]int)(y) // okay, y0 != nil
	_, _ = x0, y0

	var z = make([]int, 3, 5)
	var _ = (*[3]int)(z) // okay
	var _ = (*[2]int)(z) // okay
	var _ = (*A)(z)      // okay
	var _ = P(z)         // okay

	var w = S(z)
	var _ = (*[3]int)(w) // okay
	var _ = (*[2]int)(w) // okay
	var _ = (*A)(w)      // okay
	var _ = P(w)         // okay

	var _ = (*[4]int)(z) // will panic
}
```

### Convert Slice to Array
Since Go 1.20, a slice may be converted to an array. In such a conversion, if the length of the array type is larger than the length of the slice, a panic occurs. The slice and the result array don't share any element.

```go
package main

import "fmt"

func main() {
	var s = []int{0, 1, 2, 3}
	var a = [3]int(s[1:])
	s[2] = 9
	fmt.Println(s) // [0 1 9 3]
	fmt.Println(a) // [1 2 3]
	
	_ = [3]int(s[:2]) // panic
}
```

### Copy Slice Elements With the Built-in `copy` Function
We can use the built-in `copy` function to copy elements from one slice to another, the types of the two slices are not required to be identical, but their element types must be identical. In other words, the two argument slices must share the same underlying type.

An example:

```go
package main

import "fmt"

func main() {
	type Ta []int
	type Tb []int
	dest := Ta{1, 2, 3}
	src := Tb{5, 6, 7, 8, 9}
	n := copy(dest, src)
	fmt.Println(n, dest) // 3 [5 6 7]
	n = copy(dest[1:], dest)
	fmt.Println(n, dest) // 2 [5 5 6]

	a := [4]int{} // an array
	n = copy(a[:], src)
	fmt.Println(n, a) // 4 [5 6 7 8]
	n = copy(a[:], a[2:])
	fmt.Println(n, a) // 2 [7 8 7 8]
}
```

### Container Element Iterations
If it is promised that there are no other goroutines manipulating a map `m`, then the following code is guaranteed to clear all entries (but the ones with keys as `NaN`) stored in the map `m`:

```go
for key := range m {
	delete(m, key)
}
```

For a `for-range` loop block (whether `=` or `:=` before `range`)

```go
for key, element = range aContainer {...}
```

there are two important facts.
1. The ranged container is **a copy** of `aContainer`. Please note, *only the direct part of* `aContainer` *is copied*. The container copy is anonymous, so there are no ways to modify it.
	- If the `aContainter` is an array, then the modification made on the array elements during the iteration will not be reflected to the iteration variables. The reason is that the copy of the array doesn't share elements with the array.
	- If the `aContainer` is a slice or map, the the modifications made on the slice or map elements during the iteration will be reflected to the iteration variables. The reason is that the clone of the slice (or map) shares all elements (entries) with the slice (or map).
2. A key-element part of the copy of `aContainer` will be assigned (copied) to the iteration variable part at each iteration step, so the modifications made on **the direct parts** of the iteration variables will not be reflected to the elements (and keys for maps) stored in `aContainer`. (For this fact, and as using `for-range` loop blocks is the only way to iterate map keys and elements, it is recommended not to use large-size types as map key and element types, to avoid large copy burdens.)

An example which proves the first and second facts.

```go
package main

import "fmt"

func main() {
	type Person struct {
		name string
		age  int
	}
	persons := [2]Person {{"Alice", 28}, {"Bob", 25}}
	for i, p := range persons {
		fmt.Println(i, p)

		// This modification has no effects on
		// the iteration, for the ranged array
		// is a copy of the persons array.
		persons[1].name = "Jack"

		// This modification has not effects on
		// the persons array, for p is just a
		// copy of a copy of one persons element.
		p.age = 31
	}
	fmt.Println("persons:", &persons)
}
```

The output:

```
0 {Alice 28}
1 {Bob 25}
persons: &[{Alice 28} {Jack 25}]
```

If we change the array in the above to a slice, then the modification on the slice during the iteration has effects on the iteration, but the modification on the iteration variable still has no effects on the slice.

```go
...

	// A slice.
	persons := []Person {{"Alice", 28}, {"Bob", 25}}
	for i, p := range persons {
		fmt.Println(i, p)

		// Now this modification has effects
		// on the iteration.
		persons[1].name = "Jack"

		// This modification still has not
		// any real effects.
		p.age = 31
	}
	fmt.Println("persons:", &persons)
}
```

The output becomes to:

```
0 {Alice 28}
1 {Jack 25}
persons: &[{Alice 28} {Jack 25}]
```

The following example proves the second facts.

```go
package main

import "fmt"

func main() {
	m := map[int]struct{ dynamic, strong bool } {
		0: {true, false},
		1: {false, true},
		2: {false, false},
	}
	
	for _, v := range m {
		// This following line has no effects on the map m.
		v.dynamic, v.strong = true, true
	}
	
	fmt.Println(m[0]) // {true false}
	fmt.Println(m[1]) // {false true}
	fmt.Println(m[2]) // {false false}
}
```

The cost of a slice or map assignment is small, but the cost of an array assignment is large if the size of the array type is large. So, generally, it is not a good idea to range over a large array. We can range over a slice derived from the array, or range over a pointer to the array (see the next section for details).

For an array or slice, if the size of its element type is large, then, generally, it is also not a good idea to use the second iteration variable to store the iterated element at each loop step. For such arrays and slices, we should use the one-iteration-variable `for-range` loop variant or the traditional `for` loop to iterate their elements. In the following example, the loop in function `fa` is much less efficient than the loop in function `fb`.

```go
type Buffer struct {
	start, end int
	data       [1024]byte
}

func fa(buffers []Buffer) int {
	numUnreads := 0
	for _, buf := range buffers {
		numUnreads += buf.end - buf.start
	}
	return numUnreads
}

func fb(buffers []Buffer) int {
	numUnreads := 0
	for i := range buffers {
		numUnreads += buffers[i].end - buffers[i].start
	}
	return numUnreads
}
```

Prior to Go 1.22, when a `for-range` loop block (note the sign before before `range` is `:=`)

```go
for key, element := range aContainer {...}
```

is executed, all key-element pairs will be assigned to **the same** iteration variable instance pair. However, since Go 1.22, each key-element pair will be assigned to a **distinctive** iteration variable instance pair (a.k.a. a distinctive instance will be created for each iteration variable in each loop iteration).

The following example shows the behavior differences between 1.21- and 1.22+ Go versions.

```go
// forrange1.go
package main

import "fmt"

func main() {
	for i, n := range []int{0, 1, 2} {
		defer func() {
			fmt.Println(i, n)
		}()
	}
}
```

Use different Go Toolchain versions to run the code ([gotv](https://go101.org/apps-and-libs/gotv.html) is a tool used to manage and use multiple coexisting installations of official Go toolchain versions), we will get different outputs:

```go
$ gotv 1.21. run forrange1.go
[Run]: $HOME/.cache/gotv/tag_go1.21.8/bin/go run forrange1.go
2 2
2 2
2 2
$ gotv 1.22. run forrange1.go
[Run]: $HOME/.cache/gotv/tag_go1.22.1/bin/go run forrange1.go
2 2
1 1
0 0
```
## References
[Go 101 Article](https://go101.org/article/container.html)