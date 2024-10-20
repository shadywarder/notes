### Your Car is Lost in a Carpark
- How would you find it?
- Walk at random
	- No guarantee you will find it
	- Could be lost forever
- Walk down each row
	- Guarantee you will find it
	- Might take a long time
- Walk to the place you think it was last, the expand your search
	- Guarantee you will find it
	- As long as your memory is good - on average it will be less then every row, worst case just as good
- Walk to the place you think it was last, hit the alarm button, then expand search 
	- Guarantee you will find it
	- Alarm can be heard from a long way away, and if you press it to no effect the car in not local to you (radius of activation)

### Search Space
- Many problems define a set of actions on an environment which can be seen as a search space of states
	- We are at one point in the environment with a destination, there is a list of action states which will bring us to the destination
- Each search type is a method of navigation of the space
- We will rarely want to go to the same point in the search space
	- Represents a cycle in the search, which are not useful in terms of state spaces
- Solutions - most searches will avoid this by using tree structures
	- Each node in the tree is a state within the search
	- Search Trees, Game Trees


### Types of Searches
**Uniformed Search**
- Have no sense of the problem domain
- Generally applicable in all cases

**Informed Search**
- Use a heuristic function developed for the domain
- Applicable in their own domain

### Minimax with Alpha-Beta Pruning
https://www.youtube.com/watch?v=zp3VMe0Jpf8

### Alpha-Beta Pruning Problems
- The effectiveness of alpha-beta pruning is highly dependent of the order in which the states are examined
- Even with alpha-beta pruning and clever move ordering, minimax won't work for games like Chess and Go, because there are still too many states to explore in the time available
	- Too high branching factor

### Hill-Climbing Algorithm
It continuously moves towards a solution that improves the objective function (e.g., maximizing profit or minimizing cost), but it can get stuck at **local optima** because it doesn't backtrack or consider distant options.

https://www.youtube.com/watch?v=kOFBnKDGtJM

### Issues and Work About
- Local Maxima
	- Stuck in suboptimal places if our value is on a localized hill
		- Change the mutation
		- Change the representation
		- Random restart
- Plateaus
	- A flat area of the state-space landscape. It can be a flat local maximum, from which on uphill exit exists
- Ridges
	- Because hill climbers only adjust one element in the vector at a time, each step will move in an axis-aligned direction

- Multiple Optima
	- Multiple Good Solutions
		- Random Restart
	- Large areas of equal solutions
		- Change the mutation
		- Random restart
	- Jumping over areas of the space
		- Selected Mutation hops over the space
