**2025-01-13 19:31**
Tags: [[go]] 

## Addressable values in Go (and unaddressable ones too)

From the Go specification:

>[!NOTE]
>For an operand `x` of type `T`, the address operation `&x` generates a pointer type of `*T` to `x`. The operand must be *addressable*, that is, either a variable, pointer indirection, or slice indexing operation; or a field selector of an addressable struct operand; or an array indexing operation of an addressable array. As an exception to the addressability requirement, `x` may also be a (possibly parenthesized) composite literal.

There are number of important things that are not addressable. For example, values in a map and the return values from function and method calls are not addressable. The following are all errors:

```go
&m["key"]
&afunc()
&t.method()
```

The return value of a function only becomes addressable when we put into a variable:

```go
v := afunc()
&v
```

Since field selection and array indexing require and array indexing require their structure or array also be addressable, you also can't take the address of a field or an array element from a return value. The following are errors:

```go
&afunc().field
&afunc()[0]
```

In both cases, you must the return value in a variable first, as you need to do if you want to use `&` on the entire return value. However, the general rule about pointer dereferencing means that this works if the function returns a pointer to a structure or an array.

Functions themselves are not addressable, so this is an error:

```go
func ifunc() int { return 1 }
&ifunc
```

Functions points out the difference between Go and C, which is that Go has the concept of pointer-like things that are not pointers as the language sees them. You cannon apply `&` to functions, but you can assign them to variables; however, the resulting type is not formally a pointer:

```go
v := ifunc
fmt.Printf("%T\n", v)
```

The type printed here is `func() int`, not a pointer type. Of course you can now take the address of `v`, at which point you have the type `*func() int`.

**The most important place that addressability shows up in the specification is in Assignments**.

>[!IMPORTANT] 
>Each left-hand side operand must be addressable, a map index expression, or (for `=` assignments only), the blank identifier.

(Map index expression must be specially added here because there aren't addressable.)

Because structure fields and array indexes require their containing thing to be addressable, you cannot directly assign to fields or array elements in structures or arrays returned by functions. Both of these are errors:

```go
sfunc().field = ...
afunc()[0] = ...
```

Because all slice index expressions are addressable, if you have a function that returns a slice, you can directly assign to a portion of the returned slice without capturing the slice in a variable:

```go
slicefunc()[:5] = ...
```

Since map index expressions are a special exception to the addressability requirements, you can assign to an index in a map that's just been returned by a function:

```go
mfunc()["key"] = ...
```

Next, slice expressions sometimes require addressability:

> [!IMPORTANT]
> If the sliced operand is an array, it must be addressable and the result of the slice operation in a slice with the same element type as the array.

Taking slices of strings, existing slices, or pointers to arrays does not require that the value you are slicing be addressable; only actual arrays are special (more about it in [Learning about Go's unaddressable values and slicing](Learning%20about%20Go's%20unaddressable%20values%20and%20slicing.md)), because it means that if a function returns an actual array, you cannot immediately slice its return value; you must assign the return value to a variable first in order to make it addressable.

Given that you can take slices of unaddressable slices, just not of unaddressable arrays, it seems pretty likely that this decision is a deliberate pragmatic one to avoid requiring Go to silently materialize heap storage for cases like arrays that are return values. If you do this through variable, it is at least more explicit that you have a full return object sitting around and that the slice is not necessarily making most of it go away.


## References
[Addressable values in Go (and unaddressable ones to)](https://utcc.utoronto.ca/~cks/space/blog/programming/GoAddressableValues)
