**2024-12-03 00:10**

Tags: [[ai]] [[university]]

## ITAI 09. GA, GP, EA, EP

### Comparison table

| Aspect             | GA                         | GP                         | ES                                                                 | EP                                                                 |
| ------------------ | -------------------------- | -------------------------- | ------------------------------------------------------------------ | ------------------------------------------------------------------ |
| Representation     | Fixed-length chromosomes   | Tree structures (programs) | Real-valued vectors                                                | Finite state machines/vectors                                      |
| Primary Operation  | Crossover                  | Crossover                  | Mutation (No crossover)                                            | Mutation (No crossover)                                            |
| Application Focus  | Combinatorial optimization | Program/model evolution    | Real-valued optimization                                           | Dynamic systems                                                    |
| Selection Approach | Proportional/tournament    | Proportional/tournament    | Replace with a member of a sample of mutants is better that parent | Replace with a member of a sample of mutants is better that parent |
|                    |                            |                            |                                                                    |                                                                    |

*GA Crossover*: the exchange of parts of strings between parents
*GA Mutation*: small character changes in the string

*GP Crossover*: the exchange of the branches
*GP Mutation:* changing the value of a node or function

*ES Crossover*: absent
*ES Mutation*: add small normally distributed parameter to a value

*EP Crossover*: absent
*EP Mutation*: adding/deleting of a nodes; changing the transitions, initial node or exit

### EA Pseudocode

```md
Initialize population P with random individuals
Evaluate fitness for each individual in P

WHILE stopping criteria is not met DO
	Select parent individuals from P (using selection method)
	Apply crossover to generate children
	Apply mutation to children
	Evaluate fitness of children
	Select indivduals for the next generation (using replacement strategy)
END WHILE

Return the best individual(s) from P
```

### Direct vs. Indirect Representation

| Direct                                                       | Indirect                                                                        |
| ------------------------------------------------------------ | ------------------------------------------------------------------------------- |
| When the genotype and phenotype are the same                 | When the evolved values allow for the construction of a solution to the problem |
| Settings on a machine, creation of a FSM or other controller | Evolving a program for the solution                                             |


## References

https://moodle.innopolis.university/pluginfile.php/214200/mod_resource/content/1/Lecture%209%20%281%29.pdf
https://moodle.innopolis.university/pluginfile.php/214260/mod_resource/content/1/Week%209%20Lecture%202.pdf