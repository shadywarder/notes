**2025-03-22 15:31**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Indexing

Indexing is a technique used in databases to speed up data retrieval. It acts like a roadmap, allowing the database to quickly find the data you are looking for, without having to scan every row. Let's explore how indexing works using the following Employee table example:

![](../attachments/Pasted%20image%2020250322153346.png)

### Why Use Indexing?

- **Query Efficiency**: Suppose we want to find the salary of an employee by their ID or name:

	```sql
	SELECT salary from employee WHERE id = 3;
	```
	
	The above query can efficiently return the salary of Alice, as it only needs to check one row.
	
	```sql
	SELECT salary FROM employee WHERE name = 'Jerry';
	```
	
	This query, however, might need to scan multiple rows if there's no indexing on the 'name' column.

- **Data Storage Optimization**: Each row's data occupies space, and efficient storage and retrieval mechanisms are essential for performance, especially with large tables.

### Clustered Indexing

A clustered index defines the physical order of data in a table. If stores data rows sorted according to the index key, usually using a B+ Tree structure for quick access.

#### How Does Clustered Indexing Work?

![](../attachments/Pasted%20image%2020250322154012.png)

1. **Primary Key as Clustered Index**: By default, a primary key is often the clustered index. It organizes the data in the table by this key, allowing quick retrieval.
2. **B+ Tree Structure**: 
	- Root and Non-Leaf Nodes: They store keys to guide the search process.
	- Leaf Nodes: These contain actual data rows or pointers to data rows stores in data pages. The entire row, including columns like ID, Name, and Salary, is present in the leaf nodes.
3. **Query Efficiency**: For a query like `SELECT salary FROM employee WHERE id = 3`, the B+ Tree allows the database to navigate directly to the leaf node that contains the ID 3, reducing the number of disk accesses needed.

> [!NOTE]
> A clustered index improves data retrieval speed by storing data in sorted order according to the index key.

#### Efficiency of B+ Tree

- Height and Breadth: A B+ Tree's efficiency is determined by the balance between the number of keys in each node and the tree's height. A well-balanced B+ Tree can handle millions or rows efficiently.
- Disk Access: The height of the tree directly influences the number of disk accesses. More keys per node mean fewer levels and fewer disk accesses.

### Non-Clustered Indexing

A non-clustered index creates a separate index that references the clustered index or primary key. It is used for columns that are frequently queried.

![](../attachments/Pasted%20image%2020250322160014.png)

1. Separate from Data Storage: Unlike clustered indexes, non-clustered indexes do not change the physical order of data. They create a sorted list of index keys (like names) and pointers to actual data rows.
2. How It Works:
	- The B+ Tree for a non-clustered index sorts the 'name' column and includes pointers to the corresponding rows in the clustered index.
	- For example, searching for 'Jerry' navigates the B+ Tree, finds a pointer to ID 6, and then retrieves the full row.

> [!NOTE]
> A table can have multiple non-clustered indexes for different columns, enhancing query performance for various seraches.

#### SQL Example

```sql
CREATE TABLE employee (
    id INT PRIMARY KEY,
    name VARCHAR(100),
    salary DECIMAL(10, 2)
);

CREATE INDEX idx_employee_name ON employee(name);
```

## References
[Indexing](https://nailyourinterview.org/interview-resources/dbms/indexing)