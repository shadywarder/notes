**2025-02-25 12:14**
**Tags:** [go](../3%20-%20indexes/go.md)

## How Interfaces Work in Go
### The Internal Definition Of Interface Types
All interface types have the same internal definition:

```go
type _interface struct {
	dynaimicTypeInfo *_implementation
	dynamicValue unsafe.Pointer
}
```

The internal `_implementation` type is declared like

```go
type _implementation struct {
	itype *_type // the interface type.
	dtype *_type // the dynamic type, which must implement itype.
	methods []*_func // the methods which are defined on dtype and each of them implements a corresponding method declared in itype.
}
```

From the definitions, we know that each interface value contains two pointer fields. The `dynamicValue` field stores the dynamic value information, and the `dynamicTypeInfo` field stores the implementation information. `dynamicTypeInfo.itype` stores the type information of the interface value and `dynamicTypeInfo.dtype` stores the type information of the dynamic value.

The `dynamicTypeInfo` field of interface value may be `nil`, which means nothing is stored in the interface value. For this case, the `dynamicValue` field must also be nil. We can also say the dynamic value of the interface value is untyped `nil` for this case.

For the official Go compiler and runtime, a non-nil `dynamicValue` field value may store
- the address of the dynamic value if the dynamic type is not a pointer type, or
- the dynamic value itself if the dynamic type is a pointer type.

Surely, it is not essential to make the exception for pointer dynamic types. This is just a compiler optimization. 

Other involved internal type are declared like:

```go
type _func struct {
	name      string  
	methodSig uint // two methods with the same signature have
	               // the same signature id. Receiver parameter
	               // doesn't contribute to this signature.
	funcSig   uint // receiver parameter accounts to this signature.

	// other information ...
}

type _type struct {
	name       string   // type name
	id         uint32   // each type has unique id
	flags      uint32   // comparable? isPointer?
	size       uintptr  // value size in bytes
	kind       uint8    // 
	methods    []*_func // the methods are sorted 
	                    // by methodSig and name.
	// more information ...
}

const (
	// flags
	TypeFlag_Comparable = 1 << 0
	TypeFlag_IsPointer  = 1 << 1
	TypeFlag_IsString   = 1 << 2
)

func (t *_type) IsComparable() bool {
	return t.flags & TypeFlag_Comparable != 0
}

func (t *_type) IsPointer() bool {
	return t.flags & TypeFlag_IsPointer != 0
}

func (t *_type) IsString() bool {
	return t.flags & TypeFlag_IsString != 0
}
```

Here is the function to get an `_implementation` value from an interface type and a non-interface type:

```go
/ global table
var cachedImpls = map[uint64]*_implementation{}

// itype must be an interface type and
// dtype must be a non-interface type.
// Return nil if dtype doesn't implement itype.
// Must not return nil if dtype implements itype.
func getImpl (itype *_type, dtype *_type) *_implementation {
	var key = uint64(itype.id) << 32 | uint64(dtype.id)
	var impl = cachedImpls[key]
	if impl == nil {
		// for each (dtype, itype) pair, the implementation
		// method table is only calculated most once at
		// run time. The calculation result will be cached.
		
		var numMethods = len(itype.methods)
		var methods = make([]*_func, numMethods)
		
		// find every implemented methods.
		// The methods of itype and dtype are both sorted
		// by methodSig and name.
		var n = 0
		var i = 0
		for _, im := range itype.methods {
			for i < len(dtype.methods) {
				tm := dtype.methods[i]
				i++
				
				// Here, for simplicity, assume
				// all methods are exported.
				
				if tm.methodSig < im.methodSig {
					continue
				}
				if tm.methodSig > im.methodSig {
					// im method is not implemented
					return nil
				}
				if tm.name < im.name {
					continue
				}
				if tm.name > im.name {
					// im method is not implemented
					return nil
				}
				
				methods[n] = tm
				n++
				break
			}
		}
		
		// dtype doesn't implement all methods of itype
		if n < numMethods {
			return nil
		}
		
		// dtype implements itype.
		// create and cache the implementation.
		impl = &_implementation{
			dtype: dtype, 
			itype: itype, 
			methods: methods,
		}
		cachedImpls[key] = impl
	}
	
	return impl
}
```

This function will be called in the value conversions explained in following sections.
In any Go program, at run time, all `_implementation` values are cached and stored in a global map and all `_type` values are stored in a global immutable array.

As the blank interface type `interface{}` is used popular in Go programming, the official Go compiler uses a different and more efficient underlying definition for the blank interface than other interface types:

```go
// blank interface
struct {
	dynamicType     *_type         // the dynamic type
	dynamicValuePtr unsafe.Pointer // points to the dynamic value
}
```




## References