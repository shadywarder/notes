**2025-01-10 21:07**
Tags: [[go]] [[go101]]

## Pointers in Go
### Restrictions on Pointers in Go
For safety reasons, Go makes some restrictions to pointers (comparing to pointers in C language). By applying these restrictions, Go keeps the benefits of pointers, and avoids the dangerousness of pointers at the same time.

**Go pointers values don't support arithmetic operations**
In Go, pointers can't do arithmetic operations. For a pointer `p`, `p++` and `p-2` are both illegal. If `p` is a pointer to a numeric value, compilers will view `*p++` is a legal statement and treat it as `(*p)++`. In other words, the precedence of pointer dereference operator `*` is higher that the increment operator `++` and decrement operator `--`.

**A pointer value can't be converted to an arbitrary pointer type**
In Go, a pointer value of pointer type `T1` can be directly and explicitly converted to another pointer type `T2` only if either of the following two conditions is get satisfied.
1. The underlying types of type `T1` and `T2` are identical (ignoring struct tags), in particular if either `T1` and `T2` is a *unnamed* type and their underlying types are identical (considering struct tags), then the conversion can be implicit. 
2. Type `T1` and `T2` are both unnamed pointer types and the underlying types of their base are identical (ignoring struct tags).

For example, for the below shown pointer types:

```go
type MyInt int64
type Ta    *int64
type Tb    *MyInt
```

the following facts exist:
1. values of type `*int64` can be implicitly converted to type `Ta`, and vice versa, for their underlying types are both `*int64`.
2. values of type `*MyInt` can be implicitly converted to type `Tb` , and vice versa, for their underlying types are both `*MyInt`
3. values of type `*MyInt` can be explicitly converted to type `*int64`, and vice versa, for they are both unnamed and the underlying types of their base types are both `int64`.
4. values of type `Ta` can't be directly converted to type `Tb`, even if explicitly. However, by the just listed first three facts, a value `pa` of type `Ta` can be indirectly converted to type `Tb` by nesting three explicit conversions, `Tb((*MyInt)((*int64)(pa)))`.
None values of these pointer types can be converted to type `*uint64`, in any safe ways.

**A pointer value can't be compared with values of an arbitrary pointer type**
In Go, pointers can be compared with `==` and `!=` operators. Two Go pointer values can only be compared if either of the following three conditions are satisfied.
1. The types of the two Go pointers are identical.
2. One pointer value can be implicitly converted to the pointer type of the other. In other words, the underlying types of the two types must by identical and either of the two types of the two Go pointers is an unnamed type.
3. One and only one of two pointers is represented with the bare (untyped) `nil` identifier.

```go
package main

func main() {
	type MyInt int64
	type Ta    *int64
	type Tb    *MyInt

	// 4 nil pointers of different types.
	var pa0 Ta
	var pa1 *int64
	var pb0 Tb
	var pb1 *MyInt

	// The following 6 lines all compile okay.
	// The comparison results are all true.
	_ = pa0 == pa1
	_ = pb0 == pb1 // Because pb1 is unnamed type (pointer to named)
	_ = pa0 == nil
	_ = pa1 == nil
	_ = pb0 == nil
	_ = pb1 == nil

	// None of the following 3 lines compile ok.
	/*
	_ = pa0 == pb0
	_ = pa1 == pb1
	_ = pa0 == Tb(nil)
	*/
}
```

**A pointer value can't be assigned to pointer values of other pointer types**
The conditions to assign a pointer value to another pointer value are the same as the conditions to compare a pointer value to another pointer value, which are listed above.


## References
[Go 101 Article](https://go101.org/article/pointer.html)