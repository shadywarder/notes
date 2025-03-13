**2024-12-31 01:22**
Tags: [[sql]] [dbms](../2%20-%20tags/dbms.md) [[stp]]

## Table Creation
An SQL query is used to create the table. It indicated which table is being created, which attributes it consists of and which data type each field has, field description (primary key etc.) specifies if necessary. Example:
 
```sql
CREATE TABLE genre(
	genre_id INT PRIMARY KEY AUTO_INCREMENT,
	name_genre VARCHAR(30)
);
```

***Recommendations for the SQL query***
- Key-words: SQL is not case sensitive (i.e. `CREATE == create`).
- SQL key-words and data types recommended to be written in uppercase.
- Tables and fields names - in lowercase.
- SQL-query can be written in multiple lines.
- SQL-query should be ended with semicolon.



## References
https://stepik.org/lesson/297508/step/8?unit=279268