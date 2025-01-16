**2024-12-03 00:52**
Tags: [[ai]] [[university]]

## ITAI 10. PDDL

- Actually stands for the Planning Domain Definition Language.
- A framework for formulating and solving planning problems.

> [!NOTE] 
> Planning is the process of *choosing and scheduling actions* that lead towards a *goal*, based on a *high-level description* of the world.

**Domain specific planning**
- Methods and representations are specific to a problem:
	- Path and motion planning
	- Manipulation planning
**Domain independent planning**
- Applicable across very different domains
- Many different flavours
	- Offline/online
	- Discrete/continuous
	- Deterministic/non-deterministic
	- Fully/partially observable
	- Sequential/temporal

**We need to formally describe:**
- The environment in which we operate: the initial state, and the goal
- The actions that our robot can do, and how these affect the environment

**The classical (simplest) PDDL planning problem is described by a tuple:**
$$<F, A,I,G>$$
**where:**
- $F$ is a set of boolean propositions (facts)
- $A$ is a set of deterministic actions (with preconditions and effects)
- $I \in S$ is the initial state
- $G$ is the goal state
- $S = 2^F$ is the set of states

**The classical PDDL assumes:**
- Deterministic and instantaneous actions
- Boolean propositions to describe the world
- The world only changes according to the actions we apply (no external events)
- The system is fully observable (i.e. $I$ is known)

Even though classical PDDL might appear unrealistic for real use-cases, it is so popular actually:
- It provides idealised settings to develop automated planners
- In many cases it is enough - simplified robotics task in controlled environments

**PDDL Structure**
Planning tasks in classical PDDL relies on two separate files:
**Domain file** `domain.pddl`:
- **Predicates:** properties of the world
- **Operators**: the way in which the state can change
- First order logic (FOL): derive $F$ and $A$
**Problem file** `problem.pddl`:
- **Objects:** the things in the world
- **Initial state**
- **Goal**

**How to find a plan to achieve a goal?**
- Solvers take as input a `domain.pddl` and `problem.pddl`, and generate a plan
- The planning problem can be seen as *network of states*, where actions represent transitions
- It is a search problem: MCTS, A*

**PDDL - Syntax**
Domain file `domain.pddl`

```pddl
(define (domain <domain-name>)
	(:requirements
		<requirements-list>)
	(:types
		<types-list>)
	(:predicates
		<predicate-list>)
	(:action
		<action-details>)
)
```

- `<domain-name>` is the name of the world
- `:requirements` - which features of PDDL are being used
- `:types` - optional, type of objects
- `:predicates` - list of model's state, true or false facts
- `:action` - list of possible state transitions

Problem file `problem.pddl`

```pddl
(define (problem <title>)
	(:domain <domain-name>)
	(:objects
		<object-list>)
	(:init
		<predicates>)
	(:goal
		<predicates>)
)
```

- `<title>` is the name you give to the problem
- `<domain-name>` refers to the relative `domain.pddl`
- `:objects` - things in the world you want to manipulate
- `:init` - the initial state of your objects
- `:goal` - final state(s) to be achieved

**Example**
`domain.pddl`

```pddl
(define (domain simple_switches)
	(:requirements :typing)
	(:types switch)
	(:predicates (off ?s - switch)
				(on ?s - switch))
	(:action switch_on
		:parameters (?s - switch)
		:precondition (off ?s)
		:effect (and (not (off ?s))
			(on ?s)))
	(:action switch_off
		:parameters (?s - switch))
		:precondition (on ?s)
		:effect (and (not (on ?s)) 
		(off ?s))))
```

`problem.pddl`

```pddl
(define (problem switches_problem)
	(:domain simple_switches)
	(:objects s1 s2 s3 - switch)
	(:init (off s1) (off s2) (on s3))
	(:goal (and (on s1) (on s2) (on s3)))
)
```

An action has:
- $par(a) \subseteq F$ : parameters
- $pre(a) \subseteq F$ : simple conditions
- $add(a) \subseteq F$ : add effects
- $del(a) \subseteq F$ : delete effects
The order of expressions is prefix.

## References
 