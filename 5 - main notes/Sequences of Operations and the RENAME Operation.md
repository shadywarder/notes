**2025-03-04 12:32**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Sequences of Operations and the RENAME Operation
In general, for most queries, we need to apply several relational algebra operations one after the other. Either we can write the operations as a single **relational algebra expression** by nesting the operations, or we can apply one operation at a time and create intermediate result relations.

For example, to retrieve the first name, last name, and salary of all employees who work in department number 5, we must apply a `SELECT` and a `PROJECT` operation. We can write a single relational algebra expression, also known as an **in-line expression**, as follows:

![](../attachments/Pasted%20image%2020250304123530.png)

Alternatively, we can explicitly show the sequence of operations, giving a name to each intermediate relation, and using the **assignment operation**, denoted by <-, as follows:

![](../attachments/Pasted%20image%2020250304123635.png)

We can also use this technique to **rename** the attributes in the intermediate and result relations. To rename the attributes in a relation, we simply list the new attribute names in parentheses, as in the following example:

![](../attachments/Pasted%20image%2020250304123803.png)

We can also define a formal `RENAME` operation - which can rename either the relation name or the attribute names, or both - as a unary operator. The general `RENAME` operation when applied to relation `R` of degree $n$ is denoted by any of the following three forms:

![](../attachments/Pasted%20image%2020250304123949.png)

![](../attachments/Pasted%20image%2020250304124002.png)


## References
Fundamentals of Database Systems Seventh Edition, 8.1 Unary Relational Operations: SELECT and PROJECT