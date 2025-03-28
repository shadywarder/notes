**2025-03-22 16:51**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Keys and Dependencies

### Keys

A **key** is an attribute or a set of attributes used to uniquely identify each row in a table. Understanding different types of keys is crucial for maintaining data integrity and efficiently organizing and accessing data.

### Why Are Keys Important?

Consider an Employee table:

![](../attachments/Pasted%20image%2020250322171851.png)

Suppose you need to update Bob's salary. Without a unique key, you can't accurately identify which Bob you're referring to. This is there keys come into play.

### Types of Keys

#### Candidate Key

A **candidate key** is a column, or set of columns, that can uniquely identify any row in the table. 

**Example**: `EmpID` is a candidate key because it uniquely identifies each employee and remains unique over time.

#### Primary Key

A **primary key** is a candidate key chosen to uniquely identify each row in a table. It must be unique and not null.

**Example**: In the Employee table, `EmpID` is selected as the primary key. Primary keys help maintain the uniqueness and integrity 

#### Super Key

A **super key** is a set of one or more columns (attributes) that can uniquely identify a row in a table. Super keys include primary keys, candidate keys, and any other combination that can uniquely identify rows.

**Example**: `EmpID`, `EmpID, Name`, `EmpID, Name, Email` are all super keys. However, we prefer minimal keys (like `EmpID`) to avoid redundancy.

#### Alternative Key

All candidate keys that are not chosen as primary keys are known as **alternative keys**.

#### Unique Key

A **unique key** is a column (or set of columns) with a constant that ensures all values are unique. Unlike primary keys, unique keys can have null values.

#### Foreign Key

A **foreign key** is a field (or set of fields) in one table that uniquely identifies a row of another table. This key establishes a relationship between the two tables.

**Example**: In a `Student` table, `CourseID` could be a foreign key that references the `CourseID` in a `Course` table.

![](../attachments/Pasted%20image%2020250322173005.png)

#### Composite Key

A **composite key** is a key that consists of two or more columns to uniquely a row.

**Example**: `Firstname, Lastname, Email` collectively can serve as a composite key.

#### Compound Key

A **compound key** is a composite key where each column is a foreign key. It is commonly used in junction tables to represent many-to-many relationships.

**Example**: A `Junction Table` might used `StudentID, CourseID` as a compound key to link `Student` and `Course`.

Junction Table:

![](../attachments/Pasted%20image%2020250322173353.png)

### Dependencies

#### Functional Dependency

- **Definition**: A functional dependency exists when one attribute uniquely determines another attribute

- **Example**: If `StudentID -> StudentName`, then `StudentName` is functionally dependent on `StudentID`

#### Partial Dependency

- **Definition**: A partial dependency occurs when a non-prime attribute depends only on a part of composite primary key.

- **Example**: In a table where the primary key is `StudentID, CourseID`, if `StudentName` depends only on `StudentID`, it's partial dependency.

#### Transitive Dependency

- **Definition**: A transitive dependency is when a non-prime attribute depends on another non-prime attribute, which in turn depends on the primary key.

- **Example**: If `InstructorName` depends on `CourseID` and `CourseID` depends on `StudentID`, then `InstructorName` is transitively dependent on `StudentID`.

## References
[Keys and Dependencies](https://nailyourinterview.org/interview-resources/dbms/keys-and-dependencies)