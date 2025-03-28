**2025-03-22 20:46**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Database Transaction Models

It is a set of rules which determines how a database organizes, stores, and manipulates data.

The most popular transaction models are:
- ACID - for SQL databases
- BASE - for NoSQL databases

### ACID 

![](../attachments/Pasted%20image%2020250322204909.png)

ACID properties are essential for ensuring that database transactions are executed reliable and that the database remains ins a consistent state.

Financial institutions - money transfers and other operations require the atomic nature of ACID and strict environment.

#### Atomicity

Each transaction is treated as a single unit of work. Either all queries succeeded entirely (commit - all changes applied) or they failed entirely (rollback - like it never happened).

![](../attachments/Pasted%20image%2020250322205212.png)

Example: money transfer from one account to another. We subtract money from the first account and add to the second one. In case of the second operation failure, the money will just disappear. We want to such transactions be atomic.

#### Consistency

In databases, consistency ensures that all the data follows some set of rules. If something doesn't follow the rules, it's not allowed to stay in the database.

![](../attachments/Pasted%20image%2020250322205711.png)

#### Isolation

The database ensures and controls what changes different concurrent transactions can see of each other. That everything in a database doesn't interfere with other things happening at the same time.

![](../attachments/Pasted%20image%2020250322205948.png)

Levels of isolation:

- Read uncommitted

- Read committed 

- Repeatable read

- Serializable

#### Durability

All committed transactions are persisted on disk and safe even in the event of a power loss, crash, and error.

![](../attachments/Pasted%20image%2020250322210510.png)

### BASE

![](../attachments/Pasted%20image%2020250322211308.png)

It is often used in distributes systems like NoSQL databases which provide more flexibility, scalability and availability over strict consistency in ACID. 

High-performance and distributed systems with eventual consistency.

#### Basically Available

The system is available for operations, even in the face of failures (network, crashed).

![](../attachments/Pasted%20image%2020250322211747.png)

#### Soft State

The state of the system might change over time, even without input. E.g. it can be in the process of updating and replicating data.

![](../attachments/Pasted%20image%2020250322211946.png)

The state might be changed, e.g., due to the records in other nodes (data actualizing).

#### Eventually Consistent

The system will become consistent but over time. After some time, all replicas of the data will have the same state of data.

![](../attachments/Pasted%20image%2020250322212200.png)

## References
[Все про ACID & BASE](https://www.youtube.com/watch?v=gxCIZCDnBlY)