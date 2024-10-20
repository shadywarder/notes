## Functional Programming Concepts
- declarative 
- pure functions
- data immutability
- first class and high-order functions

## Declarative
Imperative paradigm - "How to do"
Declarative paradigm - "What to do"

## Pure functions
```
function double(x) {
	return x * 2
}
```

Properties:
- Same input - same output
- Function doesn't depend from an external state
- Function doesn't affect to an external state or context

## Data immutability
```
images = [{
	location: &{addr, 'X'}, 
	created_at: 1725512345,
	awesomness: 10
},
{
	location: &{addr, 'Y'},
	created_at: 1725504321,
	awesomness: 7
}]

imagesCopy = copy(images) - shallow copy (неглубокая копия, ссылка на location будет одна)
```

### Why mutating data is bad
- Inconsistent data;
- Possible side effects;
- It is more difficult to localize the problem and track the life cycle of the object.

### Why is it good not to do that
- Non-mutable data is thread-safe;
- Non-mutable data is easier to test and debug because of their modularity.

## First class and high-order function
First class function properties:
- We can pass such function as argument to another function
- We can return such function from another function
- We can assign such function to some variable
- We can store such function in data structure

Function, that takes other function as an argument or return other function is called **high-order function**;

There are many places in code where we want to call bunch of functions in certain order. For example, like that:

```
func1(func2(func3(func4(data))))
```

We take out such call to separate function for convenience:

```
function composeFunc(data) {
	return func1(func2(func3(func4(data))))
}
```

Actually, we can rewrite it"

```
function composeFunc(data) {
	res4 = func4(data)
	res3 = func3(res4)
	res2 = func2(res3)
	return func1(res2)
}
```

```
doublePrimeSortedInts = compose(doubleArr, sortArr, keepPrime)
```


## Currying and partial application
Intentionally reducing the arguments in the original functions is called **partial application**.

For each function call, a new function with 1 less argument is returned (**currying**).

```
sum(1, 2, 3, 4, 5)
sum(1) (2) (3) (4) (5)
sum(1) (2) (3, 4, 5)
```

```
function carry(func) {
	return function curried(...args) {
		if size(args) >= size(func) {
			return func(args...)
		} else {
			return function(...args2) {
				return curried(args..., args2...)
			}
		}
	}
}
```

```
function userHasAccessright(user, accessRight) {
	return user.accessRight.find(accessRight)
}

curried = curry(userHasAccessRight)

readerHasAccessRights = curried(reader)
if readerHasAccessRights('w') { ... }

canReaderWrite = curried(reader)('w')
if canReaderWrite() { ... }
```
## Chaining
The chain of function calls.

