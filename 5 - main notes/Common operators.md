**2025-01-14 13:11**
Tags: [go](../3%20-%20indexes/go.md)

## Common operators
### Arithmetic Operators
**About overflows**
Overflows are not allowed for typed constant values but are allowed for non-constant and untyped constant values, either the values are intermediate or final results. Overflows will be truncated (or wrapped around) for non-constant values, but overflows (for default types) on untyped constant value will not be truncated (or wrapped around).

Example:

```go
// Results are non-constants.
var a, b uint8 = 255, 1
// Compiles ok, higher overflowed bits are truncated.
var c = a + b  // c == 0
// Compiles ok, higher overflowed bits are truncated.
var d = a << b // d == 254

// Results are untyped constants.
const X = 0x1FFFFFFFF * 0x1FFFFFFFF // overflows int
const R = 'a' + 0x7FFFFFFF          // overflows rune
// The above two lines both compile ok, though the
// two untyped value X and R both overflow their
// respective default types.

// Operation results or conversion results are
// typed values. These lines all fail to compile.
var e = X // error: untyped constant X overflows int
var h = R // error: constant 2147483744 overflows rune
const Y = 128 - int8(1)  // error: 128 overflows int8
const Z = uint8(255) + 1 // error: 256 overflow uint8
```

**About the results of arithmetic operator operations**
Except bitwise shift operations, the results of a binary arithmetic operator operation
- is a typed value of the same type of the two operands if the two operands are both typed value of the same type.
- is a type value of the same type of the typed operand on only one of the two operands is a typed value. In the computation, the other (untyped) value will be deduced as a value of the type of type operand. In other words, the untyped operand will be implicitly converted to the type of the typed operand.
- is still an untyped value if both of the two operands are untyped. The default type of the result value is one of the two default types and it is one the one appears latter in this list: `int`, `rune`, `float64`, `complex128`. For example, if the default type of one untyped operand is `int`, and the other one is `rune`, then the default type of the result untyped value is `rune`.
The rules for the result of a bitwise shift operator is a little complicated. Firstly, the result  value is always an integer value. Whether it is type or untyped depends on specific scenarios.
- If the left operand is a typed value (an integer value), then the type of the result is the same as the type of the left operand.
- If the left operand is an untyped value and the right operand is a constant, the the leftf operand will be always treated as an integer value, if its default type is not an integer type, it must be representable as an untyped integer and its default type will be viewed as `int`. For such cases, the result is also an untyped value and the default type of the result is the same as the left operand.
- If the left operand is an untyped value and the right operand is a non-constant integer, the the left operand will be first converted to the type it would assume if the bitwise shift operator operation were replaced by its left operand alone. The result is a typed value whose type is the assumed type.

Example:

```go
func main() {
	// Three untyped values. Their default
	// types are: int, rune(int32), complex64.
	const X, Y, Z = 2, 'A', 3i

	var a, b int = X, Y // two typed values.

	// The type of d is the default type of Y: rune.
	d := X + Y
	// The type of e is the type of a: int.
	e := Y - a
	// The type of f is the types of a and b: int.
	f := a * b
	// The type of g is Z's default type: complex64.
	g := Z * Y

	// Output: 2 65 (+0.000000e+000+3.000000e+000i)
	println(X, Y, Z)
	// Output: 67 63 130 (+0.000000e+000+1.950000e+002i)
	println(d, e, f, g)
}
```

Another example (bitwise shift operations):

```go
const N = 2
// A is an untyped value (default type as int).
const A = 3.0 << N // A == 12
// B is typed value (type is int8).
const B = int8(3.0) << N // B == 12

var m = uint(32)
// The following three lines are equivalent to
// each other. In the following two lines, the
// types of the two "1" are both deduced as
// int64, instead of int.
var x int64 = 1 << m
var y = int64(1 << m)
var z = int64(1) << m

// The following line fails to compile.
/*
var _ = 1.23 << m // error: shift of type float64
*/
```

The last rule for bitwise shift operation is to avoid the cases that some bitwise shift operations return different results on different architectures but differences will not be detected in time. For example, if the operand `1` is deduced as `int` instead of `int64`, the bitwise operation at line *13* (or line *12*) will return different results between 32-bit architectures (`0`) and 64-bit architectures (`0x100000000`), which may produce some bugs hard do detect.


## References
[Go 101 Article](https://go101.org/articles/oprators.html)