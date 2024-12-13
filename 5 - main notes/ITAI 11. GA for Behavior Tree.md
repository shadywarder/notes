**2024-12-03 13:18**

Tags: [[ai]] [[university]]

## ITAI 11. GA for Behavior Tree

**Behavior Tree Architecture**
Mathematical Model of Plan Execution - describe switching between a finite set of behaviors in a *modular* fashion.
Properties:
- Expressiveness
- Accuracy
- one-way vs. two-way control transfer (BTs are more modular than FSMs is that they use a two-way control transfer)
- Implementation (memory-less vs. memory-full nodes)

The execution of a BT starts from the root which sends ticks with a certain frequency to its child.

![[Pasted image 20241203133113.png|600]]

**Selector**
![[Pasted image 20241203133548.png|300]]

**Sequence**
![[Pasted image 20241203133622.png|300]]

**Parallel**
![[Pasted image 20241203133647.png|300]]

**Decorator**
![[Pasted image 20241203133935.png|300]]

Decorators are special nodes that can have only a single child. The goal of the decorator is to change the behavior of the child by by manipulating the returning value or changing its ticking frequency.
- Repeater
- Inverter

**Execution Nodes**
The execution nodes are the primitive building blocks of the behavior tree. They perform some computation and return a state value (functional).
- **Condition node** checks whether a certain conditions has been meet and returns TRUE or FALSE to its parent
- **Action node** (behavior in our case) performs computations to change the agent state returns TRUE, FALSE or RUNNING to its parent.

![[Pasted image 20241203134221.png|500]]

**Benefits**
- **Maintainability:** transitions in BT are defined by the structure, not by conditions inside the states $\Rightarrow$ nodes can be designed independent for each other. Thus, when adding or removing new nodes/subtress in a small part of the tree, it is not necessary to change other parts of the tree.
- **Scalability:** when a BT have many nodes, it can be decomposed into small subtrees saving the readability of the graphical model.
- **Reusability:** due to the independence of nodes in BT, the subtrees are also independent. This allows the reuse of subtrees among other trees or projects.

**GA Pseudocode**

1. Randomly generate an initial population of $I$ individuals.
2. Calculate cost of each individual $i$ in the population.
3. Select individuals for next generation.
4. Change individual randomly.
5. Repeat 2-4 until criteria is achieved.

**BT crossover**
![[Pasted image 20241203141937.png|600]]

**BT mutations**
![[Pasted image 20241203200418.png|600]]

![[Pasted image 20241203200443.png]]

## References
https://moodle.innopolis.university/pluginfile.php/215279/mod_resource/content/1/Tutorial%2011.Genetic%20Algorithm%20for%20Behaviour%20Tree.pdf
https://youtu.be/NZbJawgZu4U?si=U6gM4YqI7R2XYcwN