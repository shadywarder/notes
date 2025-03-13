**2025-02-25 19:43**
**Tags:** [go](../3%20-%20indexes/go.md)

## Mocking
The tests still pass and the software works as intended but we have some problems:
- Our tests take 3 seconds to run.
	- Every forward-thinking post about software development emphasises the importance of quick feedback loops.
	- **Slow tests ruin developer productivity.**
	- Imagine if the requirements get more sophisticated warranting more tests. Are we happy with 3s added to the test for us for every new test of `Countdown`?
- We have not tested an important property of our function.

We have a dependency on `Sleep`ing which we need to extract so we can then control it in our tests.

If we can *mock* `time.Sleep` we can use *dependency injection* to use it instead of a "real" `time.Sleep` and then we can **spy on the calls** to make assertions on them.

### But isn't mocking evil?
You may have heard mocking is evil. Just like anything in software development it can be used for evil, just like DRY.

People normally get in to a bad state when they don't *listen to their tests* and are *not respecting the refactoring stage*.

If your mocking code is becoming complicated or you are having to mock out lots of things to test something, you should *listed* to that bad feeling and think about your code. Usually it is a sign of
- The thing you are testing is have to do many things (because it has too many dependencies to mock)
	- Break the module apart so it does less
- Its dependencies are too find-grained
	- Think about how you consolidate some of these dependencies into one meaningful module
- Your test too concerned with implementation details
	- Favour testing expected behavior rather than implementation

Normally a lot of mocking points to *bad abstraction* in your code.

**What people see here is a weakness in TDD but it is actually a strength**, more often than not poor test code is a result of bad design or put more nicely, well-designed code is easy to test.

### But mocks and tests are still my life hard!
Ever run into this situation?
- You want to do some refactoring
- To do this you end up changing lots of tests
- You question TDD and make a post on Medium titled "Mocking considered harmful"

This is usually a sign of you testing too much *implementation detail*. Try to make it so your tests are testing *useful behavior* unless the implementation is really important to how the system runs.

It is sometimes hard to know *what level* to test exactly but here are some thought processes and rules I try to follow:
- **The definition of refactoring is that the code changes but the behavior stays the same.** If you have decided to do some refactoring in theory you should be able to make the commit without any test changes. So when writing a test ask yourself
	- Am I testing the behavior I want, or the implementation details?
	- If I were to refactor this code, would I have to make lots of changes to the tests?
- Although Go lest you test private functions, I would avoid it as private functions are implementation detail to support public behavior. Test the public behaviour. Sandi Metz describes private function as being "less stable" and you don't want to couple your tests to them.
- I feel like if a test is working with **more than 3 mocks then it is a red flag** - time for a rethink on the design.
- Use spies with caution. Spies let you see the insides of the algorithm you writing which can be very useful but that means a tighter coupling between your test code and the implementation. **Be sure you actually care about these details if you're doing to spy on them**.

### Bonus - Example of iterators from go 1.23
In Go 1.23 iterators were introduced. We can use iterators in various ways, in this instance we can make a `countDownFrom` iterator, which will return the numbers to countdown in reverse ordder.

Before we get into how we write custom iterators, let's see how we use them. Rather that writing a fairly imperative looking loop to count down from a number, we can make this code look more expressive by `range`-ing over our custom `countdDownFrom` iterator.

```go
func Countdown(out io.Writer, sleeper Sleeper) {
	for i := range countDownFrom(3) {
		fmt.Fprintln(out, i)
		sleeper.Sleep()
	}

	fmt.Fprint(out, finalWord)
}
```

To write an iterator like `countDownFrom`, you need to write a function in a particular way. From the docs:

```md
The “range” clause in a “for-range” loop now accepts iterator functions of the following types
    func(func() bool)
    func(func(K) bool)
    func(func(K, V) bool)
```

Go also provides a convenience type `iter.Seq[T]` which is a type alias from `func(func(T) bool).`



## References
[Mocking](https://quii.gitbook.io/learn-go-with-tests/go-fundamentals/mocking)