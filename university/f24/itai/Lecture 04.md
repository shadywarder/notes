### Expert System
- **Expert Systems** are computer programs that utilize knowledge and inference mechanisms to provide advice, solutions, or recommendations in specialized domains.
- They are designed to capture and emulate the expertise of human specialists to solve complex problems and make informed decisions
- Were formally introduced around 1965 by the Stanford Heuristic Programming Project led by Edward Feigenbaum

### Prolog 
- **Prolog** is a general-purpose logic programming language associated with artificial intelligence and computational linguistics
- Prolog stands for **Pro**gramminc in **Log**ic
- Prolog has its roots in first-order logic, a format logic, and unlike many other programming languages, Prolog is declarative: the program logic is expressed in terms of relations, represented as facts and rules. A computation is initiated by running a *query* other these relations
- The language was first conceived by a group around Alain Colmerauer in Marsielle, France, in the early 1970s and the first Prolog system was develped in 1972 by Colmerauer with Philippe Roussel

### Prolog Semantics
- `Head :- Body`
- Clauses with empty bodies are called *facts* `cat(tom).`
- Clauses with bodies are called *rules*. Rules describe new rules based on facts and/or other rules `animal(X) :- cat(X).`
- Queries are needed to show outputs. They are also called *goals* `?- cat(X). Answer: X = tom`

### Data Types
Prolog's single data type ins the term. There are 4 terms types:
- Atoms
- Numbers (integers and floats)
- Variables
- Compound terms

![](../../../attachments/Pasted%20image%2020241016022907.png)


```prolog
% facts

male(nick).
male(dan).
male(brad).
female(kate).
female(mary).
female(alice).
female(jane).

parent(dan, nick).
parent(dan, kate).
parent(mary, nick).
parent(mary, kate).
parent(brad, dan).
parent(brad, alice).
parent(jane, dan).
parent(jane, alice).

% rules

father(X,Y) :- parent(X,Y), male(X).
mother(X,Y) :- parent(X,Y), female(X).
grandfather(X,Y) :- father(X,Z), parent(Z,Y).
grandmother(X,Y) :- mother(X,Z), parent(Z,Y).
siblings(X,Y) :- father(F,X), father(F,Y), mother(M,X), mother(M,Y), X\=Y.
brother(X,Y) :- siblings(X,Y), male(X), X\=Y.
sister(X,Y) :- siblings(X,Y), female(X), X\=Y.
aunt(X,Y) :- parent(Z,Y), sister(Z,X).
uncle(X,Y) :- parent(Z,Y), brother(Z,X).
```

![](../../../attachments/Pasted%20image%2020241016023327.png)

