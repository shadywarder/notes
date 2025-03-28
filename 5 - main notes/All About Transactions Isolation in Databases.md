**2025-03-23 11:23**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## All About Transactions Isolation in Databases

### Transaction

Each transaction is treated as a single unit of work. Either all queries succeeded entirely (commit - all changes applied) or they failed entirely (rollback - like it never happened).

![](../attachments/Pasted%20image%2020250323112448.png)

### Isolation

The database ensures and controls how transactions can affect each other. And how it can affect data consistency.

![](../attachments/Pasted%20image%2020250323113108.png)

### Why several levels?

Their purpose is to choose the right balance between data consistency and system performance.

![](../attachments/Pasted%20image%2020250323113340.png)

### Phenomenon

It's a specific types of several issues which arise when different transactions interfere will each other in concurrent execution (data corruption, inconsistency, logical errors).,

![](../attachments/Pasted%20image%2020250323113552.png)

#### Lost Update (Write-Write Conflict)

![](../attachments/Pasted%20image%2020250323113634.png)

#### Missing or Double Read

A reading transaction is reading a range of rows in an index scan operation locking only one row at the time. During the read a rows is updated by a second transaction, changing the index key column(s) and thus its position in the scan.

![](../attachments/Pasted%20image%2020250323114211.png)

#### Dirty Read (write-read conflict)

![](../attachments/Pasted%20image%2020250323114502.png)

There is no read uncommitted isolation level (allows dirty read) in Postgres.

#### Non-Repeatable Read (read-write conflict)

![](../attachments/Pasted%20image%2020250323114844.png)

We fixed dirty read by always reading only committed changes.

#### Phantom Read

![](../attachments/Pasted%20image%2020250323115430.png)

#### Serialization Anomalies. Write-Skew #0 anomaly

![](../attachments/Pasted%20image%2020250323120705.png)

#### Write-Skew #1 anomaly

![](../attachments/Pasted%20image%2020250323121232.png)

#### Write-Skew #2 anomaly

![](../attachments/Pasted%20image%2020250323121750.png)

#### Read-Skew anomaly

![](../attachments/Pasted%20image%2020250323122242.png)

Should be `batch <= x - 1`.

### Isolation Level Types

![](../attachments/Pasted%20image%2020250323123131.png)

#### Read Uncommitted

Transactions may read changes made by other transactions before those changes are committed (dirty reads). This level offers the highest concurrency but very low data consistency.


| Anomalies             | Prevents |
| --------------------- | -------- |
| Dirty Reads           | None     |
| Non-repeatable Reads  |          |
| Phantom Reads         |          |
| Serialization Anomaly |          |

#### Read Committed

Can only read data that has been committed by other transactions. The `SELECT` clause will return the latest committed version. After the `SELECT` records can be updated, deleted, inserted or locked by another transaction.

It is fast and simple to use for many applications which do not require some complex queries and updates.


| Anomalies             | Prevents    |
| --------------------- | ----------- |
| Phantom Reads         | Dirty Reads |
| Serialization Anomaly |             |
| Non-Repeatable Reads  |             |
| Lost Update           |             |

#### Repeatable Read

It only sees data committed at the beginning of transaction only; it never sees either uncommitted data or changes committed by concurrent transactions during the transaction's execution (in pg; by the standard in can see phantom anomalies).

Some nuances related to Postgres:

1. Does not allow Phantom Read anomaly.
2. Is implemented as Snapshot Isolation using optimistic locking (MVCC - multiversion concurrency control) and applications should be prepared to retry the whole transaction on serialization failures from scratch will all operations.


| Anomalies                 | Prevents             |
| ------------------------- | -------------------- |
| Phantom Reads (non in pg) | Dirty Reads          |
| Serialization Anomaly     | Non-Repeatable Reads |
|                           | Lost Update          |

#### Serializable

Transactions are serialized and executed in a form of sequential consistency, which guarantees they will be performed one after another, serially.

This level offers the lowest concurrency but very high data consistency, because it should add protection and monitoring for the conditions which could cause a Serialization Anomaly.

It can be achieved by using pessimistic locking of all the required rows (or a table) by the current transactions (all other transactions will wait) or optimistic locking by using rows version control (if rows have the old versions the transaction will instantly fail).


| Anomalies | Prevents                |
| --------- | ----------------------- |
| None      | Dirty Reads             |
|           | Non-Repeatable Reads    |
|           | Phantom Reads           |
|           | Serialization Anomalies |
|           | Lost Update             |

#### Advantages and Disadvantages

Lower isolation levels allow higher concurrency and performance, but at the risk of getting some of the anomalies (lower data consistency).

Higher levels provide lower concurrency and performance, but higher data consistency (by removing anomalies and increasing locking). 

#### How to choose the right isolation level?

Read Committed (default by most apps) -> performance and high concurrency, but slightly compromised consistency.

Repeatable Read -> remove unrepeatable reads and phantoms (pg).

Serializable -> anomalies can't be tolerated and strict data integrity is required.

Isolation level should be selected based on correctness, not performance.

#### Nuances with Read Committed

1. Compare with atomic variables in multithreading app.
	1. We read some snapshot of the current state and it can be changed right after our read operation by another thread.
	2. We do not read data ins some intermediate state - only committed data
2. We can read some rows and our program logic will be based on them. But, by the fact these rows could be already changed by a parallel transaction.

#### Nuances with Serializable

1. Serializable transactions are implemented using Serializable Snapshot Isolation (SSI).
2. There are researches that say that serializable mode provides performance similar to snapshot isolation and considerably strict two-phase locking on read-intensive workloads.
3. With high contention workloads being more likely to experience reduced throughput and increased latency.
4. In PostgresSQL predicate locks used to detect sync errors do not cause any blocking and therefore cannot play any part in causing a deadlock
5. SSI does not affect any transaction which has a lower isolation level.
6. In Serializable transactions we doe even need `SELECT FOR UPDATE` locks.
7. Performance can be significantly improved if transactions which do not modify tables are declared as `READ ONLY`.
8. Performance will degrade more rapidly with a large number of active connections that under less strict isolation levels. So, we should use a connection pool if possible.
9. Do not use long-running transactions.
10. Transaction rollback and retrieves in highly concurrent environments can impact performance and introduce additional complexity and overhead in application logic.
11. There are researchers which show that using modern concurrency protocols like PWV can significantly increase performance of the Serializable level and in some cases make it closely fast to Read Committed.

#### SSI Performance

![](../attachments/Pasted%20image%2020250323130913.png)

#### Types of Concurrency Control

![](../attachments/Pasted%20image%2020250323131736.png)

#### Isolation Levels Are Not Always an Answer

Transaction isolation levels do not rescue us from concurrency issues when we are accessing shared critical value. RMW operations which operations which are distributed in time.

Higher level transaction levels reduce concurrency in a database. Storm of retries.

Try to choose the right options for your problem. Right isolation level, row lock, table lock, atomic updates, optimistic and pessimistic locking, RMW problems, etc.

It is better to have a DBA in your company to additionally check out and optimize our queries :)

## References
[Всё про изоляции транзакций БД](https://www.youtube.com/watch?v=SMv5_-uVwRo)