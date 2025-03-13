**2025-03-04 12:10**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Relational Algebra
Relational database systems are expected to be equipped with a query language that can assist its users to query the database instances. There are two kinds of query languages - relational algebra and relational calculus.

### Relational Algebra
Relational algebra is a procedural query language, which takes instances of relations as input and yields instances of relations as output. It uses operators to perform queries. An operator can be either **unary** or **binary**. The accept relations as their input and yield relations as their output. Relational algebra is performed recursively on a relation and intermediate results are also considered relations.

The fundamental operations of relational algebra are as follows:
- Select
- Project
- Union
- Set difference
- Cartesian product
- Rename

### Select Operation (σ)
It selects tuples that satisfy the given predicate from a relation.
**Notation** - $\sigma_p(r)$ 
Where $\sigma$ stands for selection predicate and $r$ stands for relation. $p$ is prepositional logic formula which may use connectors like **and, or,** and **not**.

**For example**
$$\sigma_{\text{subject}=\text{"database"}}\text{Books}$$
**Output** - selects tuples from books where subject is "database".

$$\sigma_{\text{subject}=\text{"database"}\text{ and price = "450" or year } > \text{ "2010"}}\text{Books}$$
**Output** - selects tuples from books where subject is "database" and "price" is 450 or those books published after 2010.

### Project Operation (∏)
It projects column(s) that satisfy a given predicate.
**Notation** - $\Pi_{A_{1},A_{2}, A_{n}}(r)$
Where ${A_{1},A_{2}, A_{n}}$ are attribute names of relation $r$.
Duplicate rows are automatically eliminated, as relation is a set.

**For example**
$$\Pi_{\text{subject, author}}\text{Books}$$
Selects and projects columns named as subject and author from the relation Books.

## References
[DBMS - Relational Algebra](https://www.tutorialspoint.com/dbms/relational_algebra.htm)