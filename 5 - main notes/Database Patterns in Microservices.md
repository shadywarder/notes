**2025-03-24 09:32**
**Tags:** [[dbms]]

## Database Patterns in Microservices

### Transaction Is Not Always a Solution

![](../attachments/Pasted%20image%2020250324093317.png)

### Common Techniques

- Optimistic and pessimistic locking
- Atomic updates
- Rows blocking

### Pessimistic Locking

After a user performs an action that causes a lock to be applied, other users cannot perform actions on that data until the owner releases the lock. It is mainly used in environment where there is high contention for data.

![](../attachments/Pasted%20image%2020250324093922.png)

![](../attachments/Pasted%20image%2020250324093900.png)

![](../attachments/Pasted%20image%2020250324094239.png)

### Optimistic Locking

A system does not lock data when users use it. When a user updates data, the system checks to see if another user changed the data after it was read. If another user updated the data, an error is raised. Typically, the user receiving the error rolls back the transaction and starts over.

It is mainly used in environments where there is low contention for data, and where the cost of occasionally rolling back a transaction is lower than the cost of locking data when read.

![](../attachments/Pasted%20image%2020250324094555.png)

![](../attachments/Pasted%20image%2020250324100638.png)

### Pessimistic or Optimistic?

#### Pessimistic

![](../attachments/Pasted%20image%2020250324100934.png)

If there are lots of competing requests to our service which are trying to modify the same resource.

#### Pessimistic Downsides

Using it will remove parallel access to the resource. Only one transaction can work with the resource at the time. It can decrease performance and concurrency.

#### Optimistic

![](../attachments/Pasted%20image%2020250324101010.png)

When we have pretty spare modification access to the shared resource, when conflicts are rare (low data contention). We can retry and succeed.

To return an error or some type of unsucceeded operation status.

It can be used on several levels of software development (API, atomics, db, file transfers).

Can prevent Race conditions, Lost Update, Move logic from a db to the app level, user lower isolation level and decrease load from the db.

#### Optimistic Downsides

In some cases it will lead to a requests storm to the database and will increase load on the database and on the network significantly.

### Read-Modify-Write and Logical Race Conditions

It is used in many domains, such as multi-threading, IPC (inter-process communication), inter-service communication and without careful thinking about synchronization can lead to logical errors and race conditions.

![](../attachments/Pasted%20image%2020250324101826.png)

#### Two threads

Two threads modify non-atomic variables in the main memory.

![](../attachments/Pasted%20image%2020250324102232.png)

#### Lost Update

![](../attachments/Pasted%20image%2020250324102355.png)

#### Transactions do not help

![](../attachments/Pasted%20image%2020250324102559.png)

1. Not always there is a possibility to use it.
2. It can reduce performance of the system and complicate vacuum.
3. You still need to implement failover logic and retries.

### Atomic Update or Delete

The special simple case where we only need to update a column with a specific difference (+value or -value).

## References
[Паттерны работы с бд в микросервисах](https://www.youtube.com/watch?v=WgXw_GN0xko)