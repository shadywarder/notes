**2025-02-25 18:07**
**Tags:** [go](../3%20-%20indexes/go.md)

## Dependency Injection
There are *a lot* of misunderstandings around dependency injection around the programming community. Hopefully, this guide will show you how.
- You don't need a framework
- It does not overcomplicate your design
- It facilitates testing
- It allows you to write great, general-purpose functions.

We want to write a function that greets someone, just like we did in the hello-world chapter but his time we are going to be testing the *actual printing*.

Just to recap, here is what that function could look like

```go
func Greet(name string) {
	fmt.Printf("Hello, %s", name)
}
```

But how can we test this? Calling `fmt.Printf` prints to `stdout`, which is pretty hard for us to capture using the testing framework.

What we need to do is be able to **inject** (which is just a fancy word for pass in) the dependency of printing.

**Our function doesn't need to care *where or how* the printing happens, so we should accept an *interface* rather that a concrete type.**

If we do that, we can then change the implementation to print something we control so that we can test it. In "real life" you would inject in something that writes to `stdout`.

If you look at the source code of `fmt.Printf` you can see a way for us to hook in

```go
// It returns the number of bytes written and any write error encountered.
func Printf(format string, a ...interface{}) (n int, err error) {
	return Fprintf(os.Stdout, format, a...)
}
```

Interesting! Under the hood `Printf` just calls `Fprintf` passing in `os.Stdout`.
What exactly *is* as `os.Stdout`? What does `Fprintf` expect to get passed to it for the 1st argument?

```go
func Fprintf(w io.Writer, format string, a ...interface{}) (n int, err error) {
	p := newPrinter()
	p.doPrintf(format, a)
	n, err = w.Write(p.buf)
	p.free()
	return
}
```

An `io.Writer`

```go
type Writer interface {
	Write(p []byte) (n int, err error)
}
```

From this we can infer that `os.Stdout` implements `io.Writer`; `Printf` passes `os.Stdout` to `Fprintf` which expects an `io.Writer`.

As you write more Go code you will find this interface popping up a lot because it's a great general purpose interface for "put this data somewhere".

So we know under the covers we're ultimately using `Writer` to send our greeting somewhere. Let's use this existing abstraction to make our code testable and more reusable.

### Wrapping up
Our first round of code was not easy to test because it wrote data to somewhere we couldn't control.

*Motivated by our tests* we refactored the code so we could control *where* the data was written by **injecting a dependency** which allowed us to:
- **Test our code** If you can't test a function *easily*, it's usually because of dependencies hard-wired into a function *or* global state. If you have a global database connection pool for instance that is used by some kind of service layer, it is likely going to be difficult to test and they will be slow to run. DI will motivate you to inject in a database dependency (via an interface) which you can then mock out with something you can control in you tests.
- **Separate our concerns**, decoupling *where the data goes* from *how to generate it*. If you ever feel like a method/function has too many responsibilities (generating data *and* writing to a db? handling HTTP requests *and* doing domain level logic?) DI is probably going to be the tool you need.
- **Allow our code to be re-used in different contexts** The first "new" context our code can be used in is inside tests. But further on if someone wants to try something new with your function they can inject their own dependencies.


## References
[Dependency Injection](https://quii.gitbook.io/learn-go-with-tests/go-fundamentals/dependency-injection)