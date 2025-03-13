**2025-02-27 15:22**
**Tags:** [go](../3%20-%20indexes/go.md)

## Why People are Angry over Go 1.23 Iterators
**TL;DR** It makes Go *feel* too "functional" rather than being an unabashed imperative language.

Here is the example from the original Tweet I found:

```go
func Backward[E any](s []E) func(func(int, E) bool) {
	return func(yield func(int, E) bool) {
		for i := len(s)-1; i >= 0; i-- {
			if !yield(i, s[i]) {
				// Where clean-up code goes
				return
			}
		}
	}
}

s := []string{"a", "b", "c"}
for _, el in range Backward(s) {
	fmt.Print(el, " ")
}
// c b a
```

This example is clear enough in *what* it does, but the entire design of it is a bit crazy to me for the general/majority use case.

From what I understand it appears that the code will be transformed into something like the following:

```go
Backward(s)(func(_ int, el string) bool {
	fmt.Print(el, " ")
	return true // `return false` would be the equivalent of an explicit `break`
})
```

This means that Go's iterators are much closer to what some languages have with a "for each" method (e.g. `.forEach()`) in JavaScript and passing a callback to it. And fun fact, this approach is already possible in Go < 1.23 but it does not have the syntactic sugar to use it within a `for range` statement.

I will try to summarize the rationale Go 1.23 iterators, but it seems that they ware wanting to minimize a few factors:

- Make the iterator look/act like a generator from other languages (thus the `yield`)
- Minimize the need for sharing too many stack frames
- Allow for clean-up with `defer`
- Reduce data being stored outside of the control flow

#### More Complex Example
**NOTE:** Do not worry what this actually does, I just wanted to show an example of the clean-up needed with something like `defer`.

An example from the original PR shows an example of a much more complex approach requiring clean-up where values which are *pulled* directly:

```go
// Pairs returns an iterator over successive pairs of values from seq.
func Pairs[V any](seq iter.Seq[V]) iter.Seq2[V, V] {
	return func(yield func(V, V) bool) bool {
		next, stop := iter.Pull(it)
		defer stop()
		v1, ok1 := next()
		v2, ok2 := next()
		for ok1 || ok2 {
			if !yield(v1, v2) {
				return false
			}
		}
		return true
	}
}
```

#### An Alternative Pseudo-Proposal (State Machine)
**NOTE:** I am not suggesting Go does this whatsoever.

When designing Odin, I wanted the ability for the user to design their own kind of "iterators", but have them be very simple; in fact, just normal procedures. I didn't want to add a special construct to the language just for this - this would complicated the language too much which is what I wanted to minimize in Odin.

One possible pseudo-proposal I could give for Go iterators would look like the following:

```go
func Backward[E any](s []E) func() (int, E, bool) {
	i := len(s)-1
	return func(onBreak bool) (idx int, elem E, ok bool) {
		if onBreak || !(i >= 0) {
			// Where clean-up code goes, if there is any
			return
		}
		idx, elem, ok = i, s[i], true
		i--
		return
	}
}
```

This pseudo-proposal would operator like this:

```go
for it := Backward(s);; {
	_, el, ok := it(false)
	if !ok {
		break // it(true) does not need to be called because the `false` was called
	}

	fmt.Print(el, " ")
}
```

## References
[Why People are Angry over Go 1.23 Iterators](https://www.gingerbill.org/article/2024/06/17/go-iterator-design/)