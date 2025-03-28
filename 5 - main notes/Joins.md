**2025-03-22 17:43**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Joins

Joins are used in SQL to combine rows from two or more tables based on a related column between them. This allows you to retrieve data stored in different tables with a single query.

### Why Are Joins Important?

Imagine you have two tables: one for employees and one for departments. If you want to know which department an employee works in, you need to combine data from both tables. Joins help you do this seamlessly by connecting related information.

`Employee Table`

![](../attachments/Pasted%20image%2020250322174629.png)

`Department Table`

![](../attachments/Pasted%20image%2020250322174700.png)

To find out which department Shubh works in, we can use SQL joins to combine the Employee and Department tables based on the `DepartmentID` column, which acts as a foreign key.

```sql
SELECT Department.DepartmentName
FROM Employee
JOIN Department ON Employee.DepartmentID = Department.DepartmentID
WHERE Employee.Name = 'Shubh';
```

### Types of Joins

#### Inner Join 

An inner join returns only the rows where there is a match in both tables.

In our example, an inner join between Employee and Department tables will return only those employees who have a matching `DepartmentID` in both tables.

Here's how to write SQL query for performing an inner join, which displays the `Name` from the Employee table and the `DepartmentName` from the Department table.

```sql
SELECT Employee.Name, Department.DepartmentName
FROM Employee
INNER JOIN Department ON Employee.DepartmentID = Department.DepartmentID;
```

Result:

![](../attachments/Pasted%20image%2020250322175126.png)

#### Left Join

A left join returns all rows from the left table and the matched rows from the right table. If there's no match, the result in NULL on the right side.

In a left join, all the rows from the left table (Employee) will be show, regardless of whether there is a match in the right table (Department). If a matching `DepartmentID` is found in the Department table, the corresponding `DepartmentName` will be displayed. However, if the `DepartmentID` from the left table does not have a match in the right table, the result will display `NULL` for the `DepartmentName` on the right side.

Here's an example SQL query for performing a left join:

```sql
SELECT Employee.Name, Department.DepartmentName
FROM Employee
LEFT JOIN Department ON Employee.DepartmentID = Department.DepartmentID;
```

Result:

![](../attachments/Pasted%20image%2020250322175722.png)

#### Right Join

A right join returns all rows from the right table and the matched rows from the left table. If there's no match, the result is `NULL` on the left side. 

In a right join, all rows from the right table (Department) will be included in the result set, regardless of whether there is a matching `DepartmentID` in the left table (Employee).

For the `DepartmentID` values: 10 and 20, which exists in both tables, the corresponding `DepartmentName` from Department table will be displayed alongside the employee's name from the Employee table.

However, for the `DepartmentID` values 30 and 40, which are present in the Department table but not in the Employee table, `NULL` values will be filled in the result set for the employee's name at the appropriate places.

Here's an example SQL query for performing a right join:

```sql
SELECT Employee.Name, Department.DepartmentName
FROM Employee
RIGHT JOIN Department ON Employee.DepartmentID = Department.DepartmentID;
```

Result:

![](../attachments/Pasted%20image%2020250322180212.png)

Above, all the `DepartmentID` from Department Table will be selected and if they are not present in Employee Table, `NULL` will be returned.

#### Full Outer Join

A full join returns all rows when there is a match in either the left or right table. If there's no match, the result in `NULL` for that table.

A full outer join combines the result of both left and right joins.

Here's an example SQL query for performing a full outer join:

```sql
SELECT Employee.Name, Department.DepartmentName
FROM Employee
FULL OUTER JOIN Department ON Employee.DepartmentID = Department.DepartmentID;
```

Result:

![](../attachments/Pasted%20image%2020250322180502.png)

### Drawbacks

#### Performance Issues

**Complexity and Speed**: Joins, especially complex ones involving multiple tables, can be slow and resource-intensive. The database engine has to perform significant work to combine rows from different tables. 

**Large Datasets**: Joins on large tables can result in substantial processing time and memory usage. This can lead to slow query performance and can impact the overall performance of the database.

**Index Usage**: Proper indexing can improve join performance, but poor indexing or lack of indexes can lead to inefficient execution plans and slow joins.

#### Complexity

**Query Complexity and Readability**: Writing queries with multiple joins can be complex and hard to understand. This increases the likelihood of errors and makes maintenance more challenging.

#### Scalability

**Horizontal Scalability**: Joins can be challenging to scale horizontally (across multiple servers) because they often require data to be located on the same server or involve expensive cross-node data transfer.

**Sharding**: In sharded databases, joins across shards are complex to implement and often inefficient, requiring data to be brought together from multiple locations.

## References
[Joins](https://nailyourinterview.org/interview-resources/dbms/joins)