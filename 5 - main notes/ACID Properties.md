**2025-03-22 14:12**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## ACID Properties

ACID properties ensure that database transactions are processed reliably and help maintain the integrity of the data in the face of failures or attacks. Let's dive into each property:

### Atomicity

#### What is a Transaction?

![](../attachments/Pasted%20image%2020250322141409.png)

Imagine a scenario where Shubh wants to but a book online. He finds one last copy available and adds it to his cart. During checkout, the payment fails. Now, Shubh hasn't received the book, but the store shows one less book in stock. This results in an inconsistent state of the database.

**Atomicity** ensures that every transaction is treated as a single unit. This means either all the operations withing the transaction are executed, or none are. If any part of transaction fails, the entire transaction is rolled back, restoring the database to its previous state. 

> [!NOTE]
> A transaction is a sequence of operations performed as a single unit of work.

### Consistency 

![](../attachments/Pasted%20image%2020250322142052.png)

Consistency ensures that the database remains in a valid state before and after a transaction. For example, if a customer decides to delete their account, their orders should also be removed to maintain consistency.

- **Foreign Key Constraints**: Ensure that the referenced records exists.

- **Check Constraints**: Validate data before allowing it into the database.

Without these checks, the database could enter an inconsistent data, leading to errors in operations and analysis.


### Isolation

#### What is Isolation?

When multiple transactions occur simultaneously, isolation ensures that the execution of one transaction is independent of others. This prevents data from being read or modified in an inconsistent state.

#### Real-World Example: BookMyShow

![](../attachments/Pasted%20image%2020250322142504.png)

Consider a scenario where two users try to book the last available seat for a movie simultaneously. Proper isolation ensures that only one user can book the seat, maintaining consistency.

### Types of Read Violations

1. **Dirty Read**: Reading uncommitted data from another transaction.

	![](../attachments/Pasted%20image%2020250322150956.png)

2. **Non-Repeatable Read**: A transaction reads the same data twice but gets different results due to another transaction modifying the data.

	![](../attachments/Pasted%20image%2020250323115251.png)

3. **Phantom Read**: A transaction reads a set of records that meet certain criteria, but another transaction inserts or deletes records, causing different results in subsequent reads.

	![](../attachments/Pasted%20image%2020250322151354.png)

#### Non-Repeatable Read vs. Phantom Read

A non-repeatable read occurs, when during the course of a transaction, a row is retrieved twice and the values within the row differ between reads.

A phantom read occurs when, in the course of a transaction, two identical queries are executed, and the collection of rows returned by the second query is different from the first.

### Isolation Levels

1. **Read Uncommitted**: Allows dirty reads. Least strict but highest performance.

```sql
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
```

2. **Read Committed**: Prevents dirty reads but allows non-repeatable reads.

```sql
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
```

3. **Repeatable Read**: Prevents dirty and non-repeatable reads but allows phantom reads.

```sql
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
```

4. **Serializable**: Most strict isolation level, ensuring complete isolation. No read violations are possible.

```sql
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
```

### Durability

Durability ensures that once a transaction is committed, it will remain so, even in the case of a system crash. This is achieved through logging and recovery mechanisms:

1. **In-memory Logging**: Changes made by transactions are logged in memory.
2. **Disk Persistence**: Logs are periodically written to disk to ensure durability.
3. **Recovery Process**: In case of failure, the DBMS uses the logs to recover to a consistent state.
4. **Transaction Replay**: Committed transactions that were not written to the database at the time of failure are replayed to ensure consistency.
5. **Rollback of Uncommitted Transactions**: Any uncommitted transactions at the time of failure are rolled back.

These ACID properties are fundamental to maintaining the integrity and reliability of databases, ensuring that transactions are handled in a robust and error-free manner.

## References
[ACID Properties](https://nailyourinterview.org/interview-resources/dbms/acid-properties)