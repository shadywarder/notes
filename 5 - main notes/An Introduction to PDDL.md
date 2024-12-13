**2024-12-03 22:47**

Tags: [[ai]] [[university]]

## An Introduction to PDDL
**Domain Files**
Domain files look like this:

```pddl
(define (domain <domain name>)
	<PDDL code for predicates>
	<PDDL code for first action>
	[...]
	<PDDL> code for last action>
)
```

`<domain name>` is a string that identifies the planning domain, e.g. `gripper`

**Problem Files**
Problem files look like this

```pddl
(define (problem <problem name>)
	(:domain <domain name>)
	<PDDL code for objects>
	<PDDL code for initial state>
	<PDDL code for goal specification>
)
```

`<problem name>` is a string that identifies the planning task, e.g. `gripper-four-balls`
`<domain name>` must match the domain name in the corresponding domain file.

**Running Example**
**Gripper** task with four balls:
There is a robot that can move between two rooms and pick up or drop balls either of his two arms. Initially, all balls and the robot are in the first room. We want the balls to be in the second room.

- *Objects:* The two rooms, four balls and two robot arms.
- *Predicates:* Is $x$ a room? Is $x$ a ball? Is ball $x$ inside room $y$? Is robot arm $x$ empty?
- *Initial state:* All balls and the robot are in the first room. All robot arms are empty.
- *Goal specification:* All balls must be in the second room.
- *Actions/Operators:* The robot can move between rooms, pick up a ball or drop ball.

**Objects**
Rooms: `rooma, roomb`
Balls: `ball1`, `ball2`, `ball3`, `ball4`
Robot arms: `left`, `right`

```pddl
(:objects rooma roomb
          ball1 ball2 ball3 ball4
          left right)

```

**Predicates**
`ROOM(x)` - true iff $x$ is a room
`BALL(x)` - true iff $x$ is a ball
`GRIPPER(x)` - true iff $x$ is a gripper (robot arm)
`at-robby(x)` - true iff $x$ is a room and the robot is in $x$ 
`at-ball(x,y)` - true iff $x$ is ball, $y$ is a room, and $x$ is in $y$
`free(x)` - true iff $x$ is a gripper and $x$ does not hold a ball
`carry(x,y)` - true iff $x$ is as gripper, $y$ is a ball, and $x$ holds $y$

```pddl
(:predicates (ROOM ?x) (BALL ?x) (GRIPPER ?x)
             (at-robby ?x) (at-ball ?x ?y) 
             (free ?x) (carry ?x ?y))

```

**Initial State**
`ROOM(rooma)` and `ROOM(roomb)` are true.
`BALL(ball1), ..., BALL(ball4)` are true.
`GRIPPER(left), GRIPPER(right), free(left), free(right)` are true.
`at-robby(rooma), at-ball(ball1, rooma), ..., at-ball(ball4, rooma)` are true.
Everything else is false.

```ppdl
(:init (ROOM rooma) (ROOM roomb)
       (BALL ball1) (BALL ball2) (BALL ball3) (BALL ball4)
       (GRIPPER left) (GRIPPER right) (free left) (free right)
       (at-robby romma)
       (at-ball ball1 rooma) (at-ball ball2 rooma)
       (at-ball ball3 rooma) (at-ball ball4 rooma))

```

**Goal Specification**
`at-ball(ball1, roomb), ..., at-ball(ball4, roomb)` must be true.
Everything else should be false.

```pddl
(:goal (and (at-ball ball1 roomb) 
            (at-ball ball2 roomb)
            (at-ball ball3 roomb) 
            (at-ball ball4 roomb)))
```

**Movement Operator**
*Description:* The robot can move from $x$ to $y$.
*Precondition:* `ROOM(x)`, `ROOM(y)` and `at-robby(x)` are true.
*Effect:* `at-robby(y)` becomes true. `at-robby(x)` becomes false. 
Everything else doesn't change.

```pddl
(:action move :parameters (?x ?y)
    :precondition (and (ROOM ?x) (ROOM ?y) (at-robby ?x))
    :effect (and (at-robby ?y) (not (at-robby ?x))))
```

**Pick-up operator**
*Description:* The robot can pick up $x$ in $y$ with $z$.
*Precondition:* `BALL(x), ROOM(y), GRIPPER(z), at-ball(x,y), at-robby(y), free(z)` are true. 
*Effect:* `carry(z,x)` becomes true. `at-ball(x,y)` and `free(z)` becomes false. Everything else doesn't change.

```pddl
(:action drop : parameters (?x ?y ?z)
    :preconditions (and (BALL ?x) (ROOM ?y) 
            (GRIPPER ?z) (at-ball ?x ?y) (at-robby ?y) (carry ?z
    :effect (and (at-ball ?x ?y) (free ?z) (not (carry ?z ?x))))
```
## References
https://www.cs.toronto.edu/~sheila/2542/s14/A1/introtopddl2.pdf
[[ITAI 10. PDDL]]