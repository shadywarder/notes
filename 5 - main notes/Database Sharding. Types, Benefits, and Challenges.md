**2025-03-24 11:48**
**Tags:** [system design](../2%20-%20tags/system%20design.md)

## Database Sharding. Types, Benefits, and Challenges

![](../attachments/Pasted%20image%2020250324115858.png)

Database sharding is a technique used to distribute data across multiple database servers to improve performance, manageability, and availability. It is a key strategy for scaling databases to handle large volumes of data.l

### Sharding vs. Partitioning 

Although the terms `sharding` and `partioning` are often used interchangeably, they have subtle differences:

- **Partitioning**: Involves dividing data into smaller chunks (partitions) and keeping those chunks on the same server. This technique aims to enhance query performance by reducing the amount of data scanned during a query.

- **Sharding**: Involves splitting data into smaller chunks (shards) and distribution each across different servers. This approach is used to handle potentially limitless amounts of data, improve availability, and boost performance by scaling horizontally.

### Why Use Sharding?

1. **Scalability**: A single database server can store only a limited amount of data due to hardware (RAM, CPU, SSD) limitations. Sharding allows you to store potentially unlimited amounts of data by adding more database servers.

2. **Reduced Response Time**: By distributing data across multiple database servers, sharding reduces the load on any single server, leading to faster query response time. When parts of the requested data are in different shards, they can be processes simultaneously.

3. **Availability**: If one shard fails, its replica shard can continue to operate, improving overall system availability and reliability.

### How Sharding Works?

![](../attachments/Pasted%20image%2020250324120832.png)

1. **Data Distribution**: Data is distributed across multiple database servers (physical shards) based on a shard key. Each physical shard holds a portion of the data, known as a logical shard.

> [!NOTE]
> Database sharding operates on a `shared-nothing` architecture, meaning each physical shard operates independently and is unaware of other shards.


2. **Shard Key**: The shard key is a column used to distribute data across physical shards. In the diagram above, `name` column is used as the shard key.

3. **Query Routing**: Queries are routed to the appropriate shards based on the shard key. A coordinator intercepts the query and sends it to the appropriate shards, using one of the sharding methods described below.

> [!NOTE]
> Some databases have a built-in coordinator for managing sharding, while others may require third-party libraries. For example, in Postgres, you can use `Citus`, a third-party library that implements a master-slave setup with a coordinator and shards.

### Types of Sharding

#### Fixed Partitioning 

- **Definition**: Shards are predefined with specific boundaries. For example, users whose names start with `A - I` are assigned to shard 1. These boundaries are fixed by can be manually adjusted if needed.

#### Dynamic Partitioning

- **Definition**: Shards are adjusted automatically based on real-time metrics. For example, if shard 1 has too much data, the system can automatically rebalance by narrowing the range (e.g., `A - D` for shard 1). This approach reduces manual intervention and optimized data distribution.

### Sharding Methods

#### Range-Based Sharding

Data is divided into ranges based on shard key values.

**Example**: In the diagram above, range-based sharding is used on `name`. Users whose names start with `A - I` go to shard 1, those starting with `J - R` go to shard 2, and the remaining users go to shard 3.

**Advantages**:

- Simple to implement and understand.

- Efficient for range queries.

**Disadvantages**:

- Uneven data distribution if the data is not uniformly distributed. For instance, shard 3 might have significantly fewer records.

- Hot spots can occur if most queries target a specific range of data.

#### Hashed Sharding

A hash function is applied to the shard key, and data is distributed based on the hash value.

**Example**: A hash function like `(hash(userID) % number_of_shards)` determines the shard. `userID` is the shard key, `hash(userID)` generates a number, and this value is modded by the number of shards to device the shard number.

**Advantages**:

- Provides a more uniform data distribution.

- Reduces the likelihood of hot spots.

**Disadvantages**:

- Changes in the hash function or the number of shards require rehashing and redistributing data, which is complex.

#### Directory-Based Sharding

Directory sharding uses a lookup table to redirect queries to specific shards.

**Example**: For an e-commerce platform, you could shard the `products` table based on product categories using a lookup table:


| Category       | Shard Number |
| -------------- | ------------ |
| Electronics    | 1            |
| Clothing       | 2            |
| Home & Kitchen | 3            |

**Advantages**: 

- Precise control over data placement.

- Can optimize queries by grouping related data.

**Disadvantages**:

- The application must first query the lookup table, adding latency.

- If the server with the lookup table crashes, the entire system can by disrupted.

> [!NOTE]
> Geo sharding is a type of directory-based sharding where users are divided based on geographical regions. To be effective, your entire application should be sharded geographically, not just the database.

### Selecting a Shard Key

Choosing an appropriate shard key is critical for effective sharding. Consider these factors:

- **Cardinality**: High cardinality (many unique values) helps distribute data more evenly. For example, using `gender` as a shard key provides limited distribution (typically only two options).

- **Query Patterns**: The shard key should align with common query patterns to minimize cross-shard queries. For example, in a dating app like Tinder, where users are often filtered by city, using `city` as a shard key makes sense. 

- **Uniform Distribution**: The shard key should ensure an even distribution of data across shards to avoid hot spots. For instance, if 90% of your customers are from one country, using `country` as shark key could lead to uneven load.

- **Growth and Scalability**: Choose a shard key that will accommodate future growth. If most users are from one region, geographic sharding may lead to scalability issues.

### Disadvantages of Sharding

1. **Increased Latency**: Queries that require data from multiple shards involve network communication, increasing latency.

2. **Joins and Transactions**: Performing joins across shards is inefficient because data must be fetched from multiple shards and joined at the application layer. Managing transactions across shards can be complex and impact data consistency.

3. **Potential for Hot Spots**: Poor shard key choices or uneven data distribution can lead to hot spots, where specific shards receive a disproportionate amount of traffic, reducing performance.

4. **Data Rebalancing**: When a shard becomes too large or too small, rebalancing data among shards is necessary, which can be complex and resource-intensice.

5. **Operational Overheads**: Managing multiple database servers increases operational complexity. Regular monitoring, backups, and updates become more challenging with sharding.

## References
[Database Sharding: Types, Benefits, and Challenges](https://nailyourinterview.org/interview-resources/system-design/database-sharding)