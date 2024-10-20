### What is an Agent?
An agent is anything which:
- Lives in an environment
- Can perceive the environment via its sensors
- Can act upon the environment via its actuators

Agents also have memory of the current and past perceptions of the environment
- Percept - the current state
- Percept Sequence - the complete history of Percepts

### Humans as Agents
Environments 
- Home
- School
- Work

Sensors
- Eyes
- Ears
- Mouth
- Nose
- Skin

Actuators
- Hands
- Feet
- Speech

### Rationality
For each possible percept sequence, a rational agent should select an action that is expected to maximize its performance measure.

### PEAS - Performance Measure, Environment, Actuators, Sensors
Agent Type 
- Jester

Performance measure
- The King is Happy

Environment
- The Court

Actuators
- Tumbling
- Juggling 
- Joke Telling

Sensors
- Hearing Laughter
- Seeing Smiles

### Properties of the Environment
**Fully Observable vs. Partially Observable**
- Can the agent see everything in the world via its sensors?
- Does it miss elements which are relevant to the decision making progress?
- Unobservable for agent without sensors
Examples:
- Chess (f. o.)
- Driving (p. o.)

**Single-agent vs. Multiagent**
- Is there only one agent within the space?
- Does there need to be some form of *competitive* or cooperation between agents?
- How do the agents communicate?
Example:
- The game of football is multi-agent as it involves 11 players in each team.

**Deterministic vs. Stochastic**
- Can we determine the next state of the environment given the previous state and the action we are applying into it?
- We can be certain in environments which are fully observable in deterministic.
Examples:
- Chess (d.)
- Self-Driving Cars (s.)

**Episodic vs. Sequential**
- Episodic environments allow for atomic actions not dependent upon those previous
- Sequential actions are those which the current decision has consequences on future actions
Examples:
- Pick and Place robot (e.)
- Checkers (s.)

**Static vs. Dynamic**
- Does the environment change as the agent is thinking about actions?
- Semi-dynamic if the environment does not change as the time passes by but the agent's performance score does
Examples:
- Empty House (s.)
- Roller Coaster (d.)

**Discrete vs. Continuous**
- Are there states in the environment, or does the environment smoothly act over time.
Examples:
- Chess (s.)
- Jenga (d.)

**Known vs. Unknown**
- Does the designer of the agent have full knowledge of the rules of the environment?
Examples:
- Chess (k.)
- Self-Driving Cars (u.)

### The Worst Case
An environment which is partially observable, multiagent, stochastic, sequential, dynamic, continuous, and unknown

### Types of Agents
**Simple Reflex Agents**

![](../../../attachments/Pasted%20image%2020241016005024.png)

- Only current percept matters
- Work only in fully observable environment
- Too many condition-action rules may be required

**Model-based Reflex Agents**

![](../../../attachments/Pasted%20image%2020241016005137.png)

- Work better in partially observable environment because of keeping track of the world
- Internal state exists
- In partially observable environment not always possible to answer "What the world is like now?". Sometimes agent tries to guess
- Still, too many condition-action rules may be required
- Not flexible enough

**Goal-based agents**

![](../../../attachments/Pasted%20image%2020241016005337.png)

- More flexible than previous agent types.
- Goal replacement does not entail rewriting of all the rules
- May be hard to choose between multiple goals

**Utility-based Agents**

![](../../../attachments/Pasted%20image%2020241016005504.png)

- Allows to maximize the "happiness" of the agent
- Allows to find the tradeoff between the conflicting goals
- More difficult to implement

**Learning Agents**

![](../../../attachments/Pasted%20image%2020241016011617.png)

- Any type of agent (model-based, goal-based, utility-based etc.) can be built as a learning agent (or not)
- **Performance element** is what we previously considered as entire agent
- **Learning element** is responsible for making improvements
- The learning element receives a feedback from the **Critic**
- **Problem generator** is responsible for suggesting actions that will lead to new and informative experiences