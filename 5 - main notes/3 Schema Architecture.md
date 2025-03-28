**2025-03-22 13:46**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## 3 Schema Architecture

![](../attachments/Pasted%20image%2020250322134638.png)

The three-schema architecture forms the backbone of how Database Management Systems (DBMS) organize, manage, and present data. This model is crucial for understanding the different layers at which data is handled, from its raw storage on disk to its presentation in a user-friendly format.

### Physical Level

At the most basic level, data has to be stored somewhere. The physical level of the DBMS is responsible for how this data is stored on the disk in a structured, efficient format.

- **Data Storage**: This level deals with the actual storage of data on physical storage devices (e.g., hard drives, SSDs). It involves organizing data in blocks, using data structures like B+ Trees for indexing to enable fast retrieval.

- **Binary Representation**: Data is stored in binary form (0s and 1s). This raw data representation is essential for efficient storage and access.

- **Access Methods**: Efficient algorithms and data structures (such as hashing, B+ trees) are used to access and manage the data.

The physical level is all about answering the question: "How the data is stored?"

### Logical Level

Moving up from the physical storage, the logical level provides a more abstract view of the data, hiding the complexities of the physical layer.

#### Integrity Constraints

The logical level is responsible for maintaining the integrity of data through various constraints:

1. **Primary Key Constraint**: Ensures each record in a table is unique.
2. **Unique Constraint**: Prevents duplicate record in a table is unique.
3. **Foreign Key Constraint**: Maintains referential integrity between tables by linking a column in one table to a primary key in another table.
4. **Check Constraint**: Ensures that values in a column meet specific criteria.
5. **Not Null Constraint**: Guarantees that a column cannot have a null value.

#### Table 

The logical level defines how data is organized in tables:

- **Table Name**: Each table has a unique name to identify it.

- **Column Names and Data Types**: Each column is names and has a specified data type (e.g., integer, varchar).

- **Constraints**: As mentioned, constraints are applied at this level to ensure data integrity.

#### Relationships 

Defines how tables relate to each other, usually through primary and foreign keys. This is crucial for maintaining consistency and establishing relationships within the database.

#### Data Dictionary 

A centralized repository that holds metadata about the database schema, tables, columns, and relationships. This dictionary acts as a reference for DBMS operations.

> [!NOTE]
> The logical level enables the representation of data in tabular form, ensuring data integrity and managing complex relationships within the database.

### View Level

The topmost layer in the three-schema architecture is the view level. This is what end-users typically interact with, presenting a tailored view of the database without exposing all details. 

![](../attachments/Pasted%20image%2020250322140813.png)

- **User-Specific Views**: Different users or user groups can have customized views, showing only relevant data. For example, a sales may see customer and order data, while the finance team might only see invoice and payment information.

- **Security**: By restricting views, sensitive data is protected, minimizing exposure and potential misuse.

- **Simplicity**: Provides simplified access to complex databases, ensuring users can interact with, the data they need without having to understand underlying complexities.

```sql
CREATE VIEW CustomerView AS
SELECT id, name
FROM customer;

GRANT SELECT ON CustomerView TO analytics_team;

-- Only id, name columns are shown to analytics_team
SELECT * FROM CustomerView;
```

In this example, the CustomerView restricts access to sensitive customer details, showing only the id and name columns to the analytics team.

## References
[3 Schema Architecture](https://nailyourinterview.org/interview-resources/dbms/three-schema-architecture)