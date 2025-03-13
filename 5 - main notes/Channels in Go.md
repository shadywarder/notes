**2025-02-13 16:01**
**Tags:** [[go]] [go101](../2%20-%20tags/go101.md) [concurrency](../2%20-%20tags/concurrency.md)

## Channels in Go
### Detailed Explanations for Channel Operations

| Operation              | A Nil Channel | A Closed Channel | A Not-Closed Non-Nil Channel |
| ---------------------- | ------------- | ---------------- | ---------------------------- |
| **Close**              | panic         | panic            | succeed to close             |
| **Send Value To**      | block forever | panic            | block or succeed to send     |
| **Receive Value From** | block forever | never block      | block or succeed to receive  |
We can think of each channel consisting of three queues internally:
1. the receiving queue. The queue is linked list without size limitation. Goroutines in this queue are all in blocking state and waiting to receive values from that channel.
2. the sending goroutine queue. The queue is also a linked list without size limitation. Goroutines in this queue are all in blocking state and waiting to send values to that channel. The value (or the address of the value, depending on compiler implementation) each goroutine is trying to send is also stored in the queue along with that goroutine.
3. the value buffer queue. This is a circular queue. Its size is equal to the capacity of the channel. The types of the values stored in this buffer are all element type of that channel. If the current number of values stored in the value buffer queue of the channel reaches the capacity of the channel, the channel is called in full status. If no values are stored in the value buffer queue currently, the channel is called in empty status. For a zero-capacity (unbuffered) channel, it is always in both full and empty status.

Each channel internally holds a mutex lock which is used to avoid data races in all kinds of operations.

**Channel operations case A:** when a goroutine `R` tries to receive a value from a not-closed non-nil channel, the goroutine `R` will acquire the lock associated with the channel firstly, then do the following steps until one condition is satisfied.
1. If the value buffer queue of the channel is not empty, in which case the receiving goroutine queue must be empty, the goroutine `R` will receive (by shifting) a value from the value buffer queue. If the sending goroutine queue of the channel is also not empty, a sending goroutine will be shifted out of the sending goroutine queue and resumed to running state again. The value that the just shifted sending goroutine is trying to send will be pushed into the value buffer queue of the channel. The receiving goroutine `R` continues running. For this scenario, the channel receive operation is called a **non-blocking operation**.
2. Otherwise (the value buffer queue of the channel is empty), if the sending goroutine queue of the channel is not empty, in which case the channel must be an unbuffered channel, the receiving goroutine `R` will shift a sending goroutine from the sending goroutine queue of the channel and receive the value that the just shifted sending goroutine is trying to send. The just shifted sending goroutine will get unblocked and resumed to running state again. The receiving goroutine `R` continues running. For this scenario, the channel receive operation is called a **non-blocking operation**.
3. If value buffer queue and the sending goroutine queue are both empty, the goroutine `R` will be pushed into the receiving goroutine queue lof the channel and enter (and stay in) blocking state. It may resumed to running state when another goroutine sends a value to the channel later. For this scenario, the channel receive operation is called a **blocking operation**.

**Channel rule case B:** when a goroutine `S` tries to send a value to a non-closed non-nil channel, the goroutine `S` will acquire the lock associated with the channel firstly, then do the following steps until one step condition is satisfied.
1. If the receiving goroutine queue of the channel is not empty, in which case the value buffer queue of the channel must be empty, the sending goroutine `S` will shift a receiving goroutine from the receiving goroutine queue of the channel and send the value to the just shifted receiving goroutine. The just shifted receiving goroutine will get unblocked and resumed to running state again. The sending goroutine `S` continues running. For this scenario, the channel send operation is called a **non-blocking operation**.
2. Otherwise (the receiving queue is empty), if the value buffer queue of the channel is not full, in which case the sending goroutine queue must be also empty, the value the sending goroutine `S` trying to send will be pushed into the value buffer queue, and the sending goroutine `S` continues running. For this scenario, the channel send operation is called a **non-blocking operation**.
3. If the receiving goroutine queue is empty and the value buffer queue of the channel is already full, the sending goroutine `S` will be pushed into the sending goroutine queue of the channel and enter (and stay in) blocking state. It may resumed to running state when another goroutine receives a value from the channel later. For this scenario, the channel send operation is called **blocking operation**.

**Channel operation case C:** when a goroutine tries to close a not-closed non-nil channel, once the goroutine has acquired the lock of the channel, both of the following two steps will be performed by the following order.
1. If the receiving goroutine queue of the channel is not empty, in which case the value buffer of the channel must be empty, all the goroutines in the receiving goroutine queue of the channel will be shifted one by one, each of them will receive a zero value of the element type of the channel and be resumed to running state.
2. If the sending goroutine queue of the channel is not empty, all the goroutines in the sending goroutine queue of the channel will be shifted one by one and each of them will produce a panic for sending on a closed channel. This is the reason why we should avoid concurrent send and close operations on the same channel. In fact, when the go command's data race detector option (`-race`) is enabled, concurrent send and close operation cases might be detected at run time and a runtime panic will be thrown.
Note: after a channel is closed , the value which have been already pushed into the value buffer of the channel are still there.  Please read the closely following explanations for case D for details.

**Channel operation case D:** after a non-nil channel is closed, channel receive operations will never block. The values in the value buffer channel can still be received. The accompanying second optional bool return values are still `true`. Once all the values in the value buffer are taken out and received, infinite zero values of the element type of the channel will be received by any of the following receive operations on the channel. As mentioned above, the optional second return result of a channel receive operation is an untyped boolean value which indicates whether or not the first result (the received value) is sent before the channel is closed. If the second return result if `false`, then the first return result (the received value) must be a zero value of the element type of the channel.

According to the explanations listed above, we can get some facts about the internal queues of a channel.
- If the channel is closed, both its sending goroutine queue and receiving goroutine queue must be empty, but its value buffer queue may not be empty.
- At any time, if the value buffer is not empty, then its receiving goroutine queue must be empty.
- At any time, if the value buffer is not full, then its sending goroutine queue must be empty.
- If the channel is buffered, then at any time, at least one of the channel's goroutines queues must be empty (sending, receiving, or both).
- If the channel in unbuffered, most of the time one of its sending goroutine queue and the receiving goroutine queue must be empty, with one exception. The exception is that a goroutine may be pushed into both of the two queues when executing a `select` control flow block.

### Some Channel Use Examples

A simple request/response example. The two goroutines in this example talk to each other through an unbuffered channel.

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	c := make(chan int) // an unbuffered channel
	go func(ch chan<- int, x int) {
		time.Sleep(time.Second)
		// <-ch    // fails to compile
		// Send the value and block until the result is received.
		ch <- x*x // 9 is sent
	}(c, 3)
	done := make(chan struct{})
	go func(ch <-chan int) {
		// Block until 9 is received.
		n := <-ch
		fmt.Println(n) // 9
		// ch <- 123   // fails to compile
		time.Sleep(time.Second)
		done <- struct{}{}
	}(c)
	// Block here until a value is received by
	// the channel "done".
	<-done
	fmt.Println("bye")
}
```

A demo of using a buffered channel. This program is not a concurrent one, it just shows how to use buffered channels.

```go
package main

import "fmt"

func main() {
	c := make(chan int, 2) // a buffered channel
	c <- 3
	c <- 5
	close(c)
	fmt.Println(len(c), cap(c)) // 2 2
	x, ok := <-c
	fmt.Println(x, ok) // 3 true
	fmt.Println(len(c), cap(c)) // 1 2
	x, ok = <-c
	fmt.Println(x, ok) // 5 true
	fmt.Println(len(c), cap(c)) // 0 2
	x, ok = <-c
	fmt.Println(x, ok) // 0 false
	x, ok = <-c
	fmt.Println(x, ok) // 0 false
	fmt.Println(len(c), cap(c)) // 0 2
	close(c) // panic!
	// The send will also panic if the above
	// close call is removed.
	c <- 7
}
```

A never-ending football game.

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	var ball = make(chan string)
	kickBall := func(playerName string) {
		for {
			fmt.Println(<-ball, "kicked the ball.")
			time.Sleep(time.Second)
			ball <- playerName
		}
	}
	go kickBall("John")
	go kickBall("Alice")
	go kickBall("Bob")
	go kickBall("Emily")
	ball <- "referee" // kick off
	var c chan bool   // nil
	<-c               // blocking here for ever
}
```

### Channel Element Values Are Transferred by Copy
When a value transferred from one goroutine to another goroutine, the value will be copied at least one time. If the transferred value ever stayed in the value buffer of a channel, then two copies will happen in transfer process. One copy happens when the value is copied from the sender goroutine into the value buffer, the other happens when the value is copied from the value buffer to the receiver goroutine. Like value assignments and function argument passing, when a value is transferred, only its direct part is copied.

### About Channel and Goroutine Garbage Collections
Note, a channel is referenced by all the goroutines in either the sending or the receiving goroutine queue of the channel, so if neither of the queues of the channel is empty, the channel cannot be garbage collected. On other hand, if a goroutine is blocked and stays in either the sending or the receiving goroutine queue of a channel, then the goroutine also cannot be garbage collected, even if the channel is referenced only by this goroutine. In fact, a goroutine can only be garbage collected when it has already exited.

### Channel Send and Receive Operations Are Simple Statements
Channel send operations and receive operations are simple statements. A channel receive operation can be always used as a single-value expression. Simple statements and expressions can be used at certain portions of basic control flow blocks.

An example in which channel send and receive operations appear as a simple statements in two `for` control flow blocks.

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	fibonacci := func() chan uint64 {
		c := make(chan uint64)
		go func() {
			var x, y uint64 = 0, 1
			for ; y < (1 << 63); c <- y { // here
				x, y = y, x+y
			}
			close(c)
		}()
		return c
	}
	c := fibonacci()
	for x, ok := <-c; ok; x, ok = <-c { // here
		time.Sleep(time.Second)
		fmt.Println(x)
	}
}
```

The second `for` loop block can be simplified to:

```go
for x := range c {
	time.Sleep(time.Second)
	fmt.Println(x)
}
```

`select-case` Control Flow Code Blocks
There is a `select-case` code block syntax which is specially designed for channels. The syntax is much like the `switch-case` block syntax. For example, there can be multitple `case` branches and at most one `default` branch in the `select-case` code block. But there are also some obvious differences between them.
- No expressions and statements are allowed to follow the `select` keyword (before `{`).
- No `fallthrough` statements are allowed to be used in `case` branches.
- Each statement following a `case` keyword in a `select-case` code block must be either a channel receive operation or a channel send operation statement. A channel receive operation can appear as the source value of a simple assignment statement. Later, a channel operation following a `case` keyword will be called a `case` operation.
- If there are one or more non-blocking `case` operations, Go runtime will **randomly select on these non-blocking operations to execute**, then continue to execute the corresponding `case` branch.
- If all the `case` operations in a `select-case` code block are blocking operations, the `default` branch will be selected to execute if the `default` branch in present. If the `default` branch is absent, the current goroutine will be pushed into the corresponding sending goroutine queue or receiving goroutine queue of every channel involved in all `case` operations, then enter blocking state.

By the rules, a `select-case` code block without any branches, `select{}`, will make the current goroutine stay in blocking state forever.

The following program will enter the `default` branch for sure.

```go
package main

import "fmt"

func main() {
	var c chan struct{} // nil
	select {
	case <-c:             // blocking operation
	case c <- struct{}{}: // blocking operation
	default:
		fmt.Println("Go here.")
	}
}
```

An example showing how to use try-send and try-receive:

```go
package main

import "fmt"

func main() {
	c := make(chan string, 2)
	trySend := func(v string) {
		select {
		case c <- v:
		default: // go here if c is full.
		}
	}
	tryReceive := func() string {
		select {
		case v := <-c: return v
		default: return "-" // go here if c is empty
		}
	}
	trySend("Hello!") // succeed to send
	trySend("Hi!")    // succeed to send
	// Fail to send, but will not block.
	trySend("Bye!")
	// The following two lines will
	// both succeed to receive.
	fmt.Println(tryReceive()) // Hello!
	fmt.Println(tryReceive()) // Hi!
	// The following line fails to receive.
	fmt.Println(tryReceive()) // -
}
```

The following example has 50% possibility to panic. Both of the two `case` operations are non-blocking in this example.

```go
package main

func main() {
	c := make(chan struct{})
	close(c)
	select {
	case c <- struct{}{}:
		// Panic if the first case is selected.
	case <-c:
	}
}
```

### The Implementation of the Select Mechanism
The select mechanism in Go is an important and unique feature. Here the steps of the select mechanism implementation by the official Go runtime are listed.

There are several steps to execute a `select-case` block:
1. evaluate all involved channel expressions and value expressions to be potentially sent in `case` operations, from top to bottom and left to right. Destination values for receive operations (as source values) in assignments needn't be evaluated at this time.
2. randomize the branch orders for polling in step *5*. The `default` branch is always put at the last position in the result order. Channels may be duplicate in the `case` operations.
3. sort all involved channels in the `case` operations to avoid deadlock (with other goroutines) in the next step. No duplicate channels stay in the first `N` channels of the sorted result, where `N` is the number of involved channels in the `case` operations. Below, the ***channel lock order*** is a concept for the first `N` channels in the sorted result.
4. lock (a.k.a., acquire the locks of) all involved channels by the channel lock order produced in last step.
5. poll each branch in the `select` block by the randomized order produced in step 2:
	1. if this is a `case` branch and the corresponding channel operation is a send-value-to-closed-channel operation, unlock all channels by the inverse channel lock order and make the current goroutine panic. Go to step *12*.
	2. if this is a `case` branch and the corresponding channel operation is non-blocking, perform the channel operation and unlock all channels by the inverse channel lock order, then execute the corresponding `case` branch body. The channel operation may wake up another goroutine in blocking state. Go to step *12*.
	3. if this is the `default` branch, then unlock all channels by the inverse channel lock order and execute the `default` branch body. Go to step *12*.

(Up to here, the `default` branch is absent and all `case` operations are blocking operations.)
6. push (enqueue) the current goroutine (along with the information of the corresponding `case` branch) into the receiving or sending goroutine queue of the involved channel in each `case` operation. The current goroutine may be pushed into the queues of a channel for a multiple times. for the involved channels in multiple cases may be the same one.
7. make the current goroutine enter blocking state and unblock all channels by the inverse channel lock order.
8. wait in blocking state until other channel operations wake up the current goroutine, ...
9. the current goroutine is waken up by another channel operation in another goroutine. The other operation bay be a channel close operation or a channel send/receive operation. If it is a channel send/receive operation, there must be a `case` channel receive/send operation cooperating with it. If the cooperation, the current goroutine will dequeued from the receiving/sending goroutine queue of the channel.
10. lock all involved channels by the channel lock order.
11. dequeue the current goroutine from the receiving goroutine queue or sending goroutine queue of the involved channel in each `case` operation,
	1. if the current goroutine is waken up by a channel close operation, go to step *5*.
	2. if the current goroutine is waken up by a channel send/receive operation, the corresponding `case` branch of the cooperating receive/send operation has already been found in the dequeuing process, so just unlock all channels by the inverse channel lock order and execute the corresponding `case` branch.
12. done.

From the implementation, we know that
- a goroutine may stay in the sending goroutine queues and the receiving goroutine queues of multiple channels at the same time. It can even stay in the sending goroutine queue and the receiving goroutine queue of the same channel at the same time.
- when a goroutine currenly being blocked at a `select-case` code block gets resumed later, it will be removed from all the sending goroutine queues and the receiving goroutine queues of all channels involved in the channel operations following `case` keywords in the `select-case` code block.


## References
[Go 101 Article](https://go101.org/article/channel.html)