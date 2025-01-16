**2025-01-10 23:50**
Tags: [[go]] [[go101]]

## Value Parts
### Two Categories of Go Types

| Types whose values each in only hosted on one single memory block                            | Types whose values each may be hosted on multiple memory blocks                      |
| -------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| ![](../attachments/Pasted%20image%2020250110235528.png)                                      | ![](../attachments/Pasted%20image%2020250110235517.png)                              |
| boolean types, numeric types, pointer types, unsafe pointer types, struct types, array types | slice types, map types, channel types, function types, interface types, string types |

### (Possible) Internal Definitions of the Types in the Second Category
**Internal definitions of map, channel and function types**
The internal definitions of map, channel and function types are similar:

```go
// map types
type _map *hashtableImpl

// channel types
type _channel *channelImpl

// function types
type _function *functionImpl
```

So, internally, types of the three kinds are just pointer types. In other words, the direct parts of values of these types are pointers internally. For each non-zero value of these types, its direct part (a pointer) reference its indirect implementation part.

**Internal definition of slice types**
The internal definition of slice types is like:

```go
type _slice struct {
	// referencing underlying elements
	elements unsafe.Pointer
	// number of elements and capacity
	len, cap int
}
```

**Internal definition of string types**
Below is the internal definition for string types:

```go
type _slice struct {
	// referencing underlying elements
	elements unsafe.Pointer
	// number of elements and capacity
	len, cap int
}
```

**Internal definition of interface types**
Below is the internal definition for general interface types:

```go
type _interface struct {
	dynamicType  *_type         // the dynamic type
	dynamicValue unsafe.Pointer // the dynamic value
}
```

In fact, for the standard Go compiler, the above definition is only used for blank interface types. Blank interface types are the interface types which doesn't specify any methods. For non-blank interface types, the definition like the following one is used.

```go
type _interface struct {
	dynamicTypeInfo *struct {
		dynamicType *_type       // the dynamic type
		methods     []*_function // method table
	}
	dynamicValue unsafe.Pointer // the dynamic value
}
```

The `methods` field of the `dynamicTypeInfo` field of an interface value stores the implemented methods of the dynamic type of the interface value for the (interface) type of the interface value.

### Underlying Value Parts Are Not Copied in Value Assignments
In Go, each value assignment (including parameter passing, etc.) is a shallow value copy if the involved destination and source values have the same type (if their types are different, we can think that the source value will be implicitly converted to the destination type before doing that assignment). In other words, only the direct part of the source value is copied to the destination value in a value assignment. If the source value has underlying value part(s), then the direct parts of the destination and source values will reference the same underlying value part(s).

![](../attachments/Pasted%20image%2020250111001619.png)


## References
[Go 101 Article](https://go101.org/article/value-part.html)