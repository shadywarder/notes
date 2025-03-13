**2025-01-18 22:59**
**Tags:** [sql](../2%20-%20tags/sql.md)

## Ch 2. Tables
### Creating a Table
To create a new table in a database, use the `CREATE TABLE` statement followed by the name of the table and the fields you want in the table.

```sql
CREATE TABLE employees (
	id INTEGER,
	name TEXT,
	age INTEGER,
	is_manager BOOLEAN,
	salary INTEGER
);
```

- The `PRAGMA TABLE_INFO(TABLENAME);` command returns information about a table and its fields. You don't need to edit this line, I just thought you might be curious!
- `INTEGER` and `INT` are slightly *different data types*. The tests expect `INTEGER`, not `INT`.

### Create Table Practice
In most relational databases a single table isn't enough to hold all the data we need! We *usually* create a table-per-entity. For example, a social media application might have the following tables:
- `users`
- `posts`
- `comments`
- `likes`

### Altering Tables
We often need to alter out database schema without deleting it re-creating it. Imagine if Twitter deleted its database each time it needed to add a feature, that would be a *disaster*! Your account and all your tweets would be wiped out on a daily basis.

Instead, we can use the `ALTER TABLE` statement to make changes in place without deleting any data.

#### ALTER TABLE
With SQLite an `ALTER TABLE` statement allows you to:
1. **Rename a Table or Column**

```sql
ALTER TABLE employees
RENAME TO contractors;

ALTER TABLE contractors
RENAME COLUMN salary TO invoice;
```

2. **Add or DROP a Column**

```sql
ALTER TABLE contractors
ADD COLUMN job_title TEXT;

ALTER TABLE contractors
DROP COLUMN is_manager;
```

### Intro to Migrations
A database *migration* is a set of changes to a relational database. In fact, the `ALTER TABLE` statements we did in the last exercise were examples of migrations!

Migrations are helpful when transitioning from one state to another, fixing mistakes, or adapting a database to changes.

*Good* migrations are small, incremental and ideally *reversible* changes to a database. As you can imagine, when working with large databases, making changes can be scary! We have to be careful when writing database migrations so that we don't break any systems that depend on the old database schema.

| Add            | Delete         | Update                                                     |
| -------------- | -------------- | ---------------------------------------------------------- |
| Safe           | Safe           | Unsafe                                                     |
| 1. Update DB   | 1. Update code | Schedule downtime (kinda sucks)                            |
| 2. Update code | 2. Update DB   | "same time" deploy (there will be a bug for a few seconds) |
|                |                | Copy (requires more complex migration code)                |
|                |                | Aliasing                                                   |
Always try to avoid updates!


| UP                      | DOWN               |
| ----------------------- | ------------------ |
| 1. Create a table       | 1. Delete a table  |
| 2. Delete a column      | 2. Add a column    |
| 3. Create another table | 3. Delete a table  |
| 4. Renames a column     | 4. Rename a column |
| 5. Deletes a table      | 5. Add a table     |
#### Example of a Bad Migration
In the CashPal backend periodically runs a query like `SELECT * FROM people`, and we execute a database migration that alters the table name from `people` to `users` *without updating the code*, the application will break! It will try to grab data from a table than no longer exists.

A simple solution to this problem would be to deploy new code that uses a new query:

```sql
SELECT * FROM users;
```

And we would deploy that code to production *immediately* following the migration.

### SQL Data Types 
SQL an a language can support many different data types. However, the datatypes that *your database management system (DMBS)* supports will vary depending on the specific database you're using.

SQLite only supports the most *basic* types, and we're using SQLite in this course!

#### SQLite Data Types
Let's go over the *data types supported by SQLite*: and how they are stored.
1. `NULL` - Null value.
2. `INTEGER` - A signed integer stored in 0, 1, 2, 3, 4, 5, 6, or 8 bytes.
3. `REAL` - Floating point value stored as an 64-bit *IEEE floating point number*.
4. `TEXT` - Text string stores using database encoding such as *UTF-8*.
5. `BLOB` - Short for *Binary large object* and typically used for images, audio or other multimedia.
6. `BOOLEAN` - Boolean values are written in SQLite queries as `true` or `false`, but are recorded as `1` or `0`.
## References
[Boot.dev SQL Course Ch. 2](https://www.boot.dev/lessons/2d5263f8-f9ed-45e7-812a-c094506ac2e3)