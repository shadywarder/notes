**2024-12-31 20:44**
Tags: [[go]]

## Defer in Go
### Defer Statement with an Anonymous Function

```go
for i := 0; i < 5; i++ {
	defer func() {
		fmt.Printf("i = %d\n", i)
	}()
}

// output:
// i = 5
// i = 5
// i = 5
// i = 5
// i = 5
```

The reason for this is, as the anonymous function has no parameters, so the defer calls are as the following:

```go
func() { fmt.Printf("i = %d\n", i) }()
func() { fmt.Printf("i = %d\n", i) }()
...
```

So, by the end of the loop, the value of `i` that made the loop end is `5`, therefore it printed `5` 5 times.

### Defer Will Not Be Called

```go
defer fmt.Println("a message will never be called")
os.Exit(3)

// output:
// exit status 3
```

`defer` will not be run when using `os.Exit`, so the `fmt.Println` will never be called.
## References