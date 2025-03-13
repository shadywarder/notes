**2025-02-24 14:27**
**Tags:** [go](../3%20-%20indexes/go.md)

## Memory Leaks in Go
### What is a memory leak
Let's understand what memory leak is.

> A memory leak is a type of resource leak that occurs when a computer program incorrectly manages memory allocations in a way that memory which is no longer needed is not released.

Go has a garbage collector that does a very good job managing memory for us, tracking down memory that is no longer used and can be returned back to the system. Still there are some cases where we can end up with either memory leaks or our system needing excessive memory to work.

### Why are memory leaks bad
Let us discuss why it can be bad having memory leaks and why we need to be mindful:
- The system might behave unpredictably and crash from out of memory errors.
- Inefficient resource utilization.
- Performance degradation.
- Difficult to track down and debug.

### Common causes for memory leaks in Go
##### Unbounded resource creation
Resource creation without a limit can be seen as a type of memory leak.
For example if we have a cache that only ever grows our service eventually will crash with out of memory error.

```go
var cache = map[int]int{}

func main() {
  // keep allocating memory indifinitely
  for i:=0; ; i++ {
    cache[i] = i
  }
} 
```

##### Long lived references
Keeping references to objects that your service no longer needs can result to memory leaks as the garbage collector sees the references and cannot free the memory.

In our example we have a function `readDetails` that opens a big file and returns only portion of it, so we slice the data `[]byte` and return it. Since in Go slices share the same underlying memory block we will still keep the whole large file in memory even though we only need a small piece of it.

```go
func readFileDetails(name string) []byte{
  data, err := os.ReadFile(name)
  if err != nil {
    return err
  }
  
  return data[5:10]
}

// not holding reference to underlying memory anymore
func readFileDetails(name string) []byte{
  data, err := os.ReadFile(name)
  if err != nil {
    return err
  }
  
  return bytes.Clone(data[5:10]))
}
```

##### Goroutines
Go runtime is doing a great job in spawning and managing goroutines, a lightweight thread, but there is a limit oh how many goroutines you can have at any time, bounded to the underlying system your service is running on.

Let's see the example below. We have a function that creates a new goroutine every 10 seconds to execute a task, allocates a big data slice, does some processing and then hangs forever.

This code has two problems:
1. Creates an unbounded number of goroutines.
2. Due to absence of termination of those goroutines allocated resources are never going to be released.

```go
func runJobs(cancel <-chan struct{}) {
  for {
    go func() {
      // create a 1Gb slice
      bigSlice := make([]byte, 1_000_000_000)
      
      // do some work with the data
      _ = bigSlice
      
      // wait until a cancellation signal is received
      <-cancel
    }()
  
    time.Sleep(10 * time.Second)
  }
}
```

##### Deferring function calls
The most common mistake is when you call `defer` inside a loop but the `defer` calls are pushed onto a stack and only executed in LIFO order at the end of the calling function.

In the example below we are processing files in a `for` loop and calling `.Close` using `defer`. The problem here is that if we call `processManyFiles` with a lot of files we are only going to close all the files after we are done processing.

```go

func processManyFiles(files []string) error {
  for _, file := range files {
    f, err := os.Open(file)
    if err != nil {
      return err 
    }
    defer f.Close()
    
    process(f)
  }
  
  return nil
}

func process(f *os.File) {
  // do something with the file
}
```

The correct way to approach such task is to break opening and processing of the file to a separate functions so there will be always only one `defer` in stack at a time.

```go

func processManyFiles(files []string) error {
  for _, file := range files {
    err := process(file)
    if err != nil {
      return err 
    }
  }
  
  return nil
}

func process(name string) error {
  f, err := os.Open(name)
  if err != nil {
    return err
  }
  defer f.Close() 
  
  // do something with the file
  
  return nil
}
```

## References
[Memory Leaks in Go](https://dev.to/gkampitakis/memory-leaks-in-go-3pcn)