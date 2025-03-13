**2025-02-24 10:41**
**Tags:** [go](../3%20-%20indexes/go.md)

## Don't defer Close() on writable files

It's an idiom that quickly becomes rote to Go programmers: whenever you conjure up a value that implements the `io.Closer` interface, after checking for errors you immediately `defer` its `Close()` method. You see this most often when making HTTP requests:

```go
resp, err := http.Get("https://joeshaw.org")
if err != nil {
    return err
}
defer resp.Body.Close()
```

or opening files:

```go
f, err := os.Open("/home/joeshaw/notes.txt")
if err != nil {
    return err
}
defer f.Close()
```

But this idiom is actually harmful for writable files because deferring a function call ignores its return value, and the `Close()` methods can return errors. **For writable files, Go programmers should avoid the `defer` idiom or very infrequent, maddening bugs will occur.**

Why would you get an error from `Close()` but not an earlier `Write()` call? To answer that we need to take a brief, high-level detour into the area of computer architecture.

Generally speaking, as you move outside and away from your CPU, actions get orders or magnitude slower. Writing to a CPU register is very fast. Accessing system RAM is quite slow in comparison. Doing I/O on disks or networks is an eternity.

In every `Write()` call committed the data to the disk synchronously, the performance of our systems would unusably slow. While synchronous writes are very important for certain type of software (like databases), most of the time it's overkill.

The pathological case is writing to a file one byte at a time. Hard drives - brutish, mechanical devices - need to physically move a magnetic head to the position on the platter and possibly wait for a full platter revolution before the data could be persisted. SSDs, which store data in blocks and have a finite number of write cycles for each block, would quickly burn out as blocks are repeatedly written and overwritten.

Fortunately this doesn't happen because multiple layers within hardware and software implement caching and write buffering. When you call `Write()`, your data is not immediately being written to media. The operating system, storage controllers and the media are all buffering the data in order to batch smaller writes together, organizing the data optimally for storage on the medium, and deciding when best to commit it. This turns our writes from slow, blocking synchronous operations to quick, asynchronous operations that don't directly touch the much slower I/O device. Writing a byte at a time is never the most efficient thing to do, but at least we are not wearing out our hardware if we do it.

Of course, the bytes do have to be committed to disk at some point. The operating system knows that when we close a file, we are finished with it and no subsequent write operations are going to happen. It also knows that closing the file is its last chance to tell us something went wrong.

On POSIX systems like Linux and macOS, closing a file is handled by the `close` system call. The BSD man page for `close(2)` talks about the errors it can return:

```
ERRORS
     The close() system call will fail if:

     [EBADF]            fildes is not a valid, active file descriptor.

     [EINTR]            Its execution was interrupted by a signal.

     [EIO]              A previously-uncommitted write(2) encountered an input/output
                        error.
```

`EIO` is exactly the error we are worried about. It means that we've lost data trying to save it to disk, and our Go programs should absolutely not return a `nil` error in that case. 

The simplest way to solve this is simply not to use `defer` when writing files:

```go
func helloNotes() error {
    f, err := os.Create("/home/joeshaw/notes.txt")
    if err != nil {
        return err
    }

    if err = io.WriteString(f, "hello world"); err != nil {
        f.Close()
        return err
    }

    return f.Close()
}
```

This does mean additional bookkeeping of the file in the case of errors: we must explicitly close it in the case where `io.WriteString()` fails (and ignore its error, because the write error takes precedence). But it's clear, straightforward, and properly checks the error from the `f.Close()` call.

There *is* a way to handle this case with `defer` by using names return values and a closure:

```go
func helloNotes() (err error) {
	var f *os.File
	f, err := os.Create("/home/joeshaw/notes.txt")
	if err != nil {
		return
	}

	defer func() {
		cerr := f.Close()
		if err == nil {
			err = cerr
		}
	}()

	err = io.WriteString(f, "hello world")
	return
}
```

The main benefit of this pattern is that it's not possible to forget to close the file because the deferred closure always executes. In longer functions with more if `if err != nil` conditional branches, this pattern can also result in fewer lines of code and less repetition.

### Update 2
Closing the file is the last chance the OS has to tell us about problems, but the buffers are not necessarily going to be flushed when you close the file. It's entirely possible that flushing the write buffer to disk will happen *after* you close the file, and a failure there cannot be caught. If this happens, it usually means you have something seriously wrong, like a failing disk.

However, you can force the write to disk with the `Sync()` method on `*os.File`, which calls the `fsync` system call. You should check for errors from that call, but then I think it's safe to ignore an error from `Close()`. Calling `fsync` has serious implications on performance: it's flushing write buffers out to slow disks. But if you really, really want the data on disk, the best pattern to follow is probably:

```go
func helloNotes() error {
    f, err := os.Create("/home/joeshaw/notes.txt")
    if err != nil {
        return err
    }
    defer f.Close()

    if err = io.WriteString(f, "hello world"); err != nil {
        return err
    }

    return f.Sync()
}
```

## References
[Don't defer Close() on writable files](https://www.joeshaw.org/dont-defer-close-on-writable-files/)