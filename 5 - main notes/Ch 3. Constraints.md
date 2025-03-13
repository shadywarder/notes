**2025-01-18 23:42**
**Tags:** [sql](../2%20-%20tags/sql.md)

## Ch 3. Constraints
### Null Values
In SQL, a cell with a `NULL` value indicates that the value is *missing*. A `NULL` value is *very* different from a *zero* value.

#### Constraints
When creating a table we can define whether or not a filed *can* or *cannot* be `NULL`, and that's a kind of `constraint`.
We will cover constraints in more detail soon, for now, let's focus on `NULL` values.

### Constraints
A `constraint` is a rule we create on a database that *enforces* some specific behavior. For example, setting a `NOT NULL` constraint on a column ensures that the column will not accept `NULL` values.

If we try to insert a `NULL` into a column with the `NOT NULL` constraint, the insert will fail with an error message. Constraints are extremely useful we need to ensure that certain kinds of data exist within our database.

#### Defining a NOT NULL Constraint
The `NOT NULL` constraint can be added directly to the `CREATE TABLE` statement. 

```sql
CREATE TABLE employees(
	id INTEGER PRIMARY KEY,
	name TEXT UNIQUE,
	title TEXT NOT NULL
);
```

#### SQLite Limitation
In other dialects of SQL you can `ADD CONSTRAINT` within `ALTER TABLE` statement. SQLite does *not* support this feature so when we create our tables we need to make sure we specify all the constraints we want!

### Primary Keys
A *key* defines and protects relationships between tables. A `primary key` is a special column that uniquely identifies records within a table. Each table can have one, and only one primary key.

#### Your Primary Key Will Almost Be the "id" Column
I's *very* common to have a column named `id` on each table in a database, and that `id` is the primary key for that table. No two rows in that table can share an `id`.

A `PRIMARY KEY` constraint can be explicitly specified on a column to ensure uniqueness, rejecting any inserts where you attempt to create a duplicate ID.

### Foreign Keys
Foreign keys are what makes relational databases relational! Foreign keys define the relationships *between* tables. Simply put, a `FOREIGN KEY` is a field in one table that references another table's `PRIMARY KEY`.

#### Creating a Foreign Key in SQLite
Creating a `FOREIGN KEY` in SQLite happens at table creation! After we define the table fields and constraints we add a named `CONSTRAINT` where we define the `FOREIGN KEY` column and its `REFERENCES`.

Here's an example:

```sql
CREATE TABLE departmens (
	id INTEGER PRIMARY KEY,
	department_name TEXT NOT NULL
);

CREATE TABLE employees (
	id INTEGER PRIMARY KEY,
	name TEXT NOT NULL,
	department_id INTEGER,
	CONSTRAINT fk_departments
	FOREIGN KEY (department_id)
	REFERENCES departments(id)
)
```

In this example, an `employee` has a `departmend_id`. The `department_id`
 must be the same as the `id` field of a record from the `departments` table. `fk_departments` is the specified name of the *constraint*.
1. `CONSTRAINT fk_departments`: create a constraint called `fk_departments`
2. `FOREIGN KEY (department_id)`: make this constraint a foreign key assigned to the `department_id` field
3. `REFERENCES departments(id)`: link the foreign field `id` from the `departments` table

### Schema
We've used the word *schema* a few times now, let's talk about what that word means. A database's *schema* describes how data is organized within it.

Data types, table names, field names, constraints, and the relationships between all of those entities are part of a database's *schema*.

#### There Is NO Perfect Way to Architect a Database Schema
When designing a database schema there typically isn't a "correct" solution. We do our best to choose a sane set of tables, fields, constraints, etc that will accomplish our project's goals. Like many things in programming, different schema designs come with different tradeoffs.

#### How Do We Decide on a Sane Schema Architecture?
Let's use *CashPal* as an example. One very important decision that needs to be mane is to decide which table will store a user's balance! As you can imagine, ensuring our data is accurate when dealing with money is *super* important. We want to be able to:
- Keep track of a user's current balance
- See the historical balance at any point in the past 
- See a log of which transactions changed the balance over time

There are many ways to approach this problem. For our first attempt, let's try the *simplest schema that fulfills our project's needs*.

### Relational Databases
We have been using the term *relational* quite a bit, it's time we actually go over what that means! A *relational* database is a type of database that stores data so that it can be easily related to other data. For example, a `user` can have many `tweets`. There's a relationship between a `user` and their `tweet`.

In a relational database:
1. Data is typically represented in "tables".
2. Each table has "columns" or "fields" that hold attributes related to the record.
3. Each row or entry in the table is called a *record*.
4. Typically, each record has a unique `Id` called the *primary key*.

#### Example Relational Database

![](../attachments/Pasted%20image%2020250119005353.png)

Here is an example of a small relational database. This database has 3 tables, `Students`, `Courses`, and `StudentCourses`. The `StudentCourses` table manages the relationship between the `Students` and the `Courses` tables.

**Example 1: Sam**
- Sam has an `Id` of `1`
- We can find Sam's courses by looking in the `StudentCourses` for the records that match his `StudentId`

**Example 2: ASP.NET MVC**
- `ASP.NET MVC` has an `Id` of 2
- We can find all the students enrolled in the ASP.NET MVC course by checking the `StudentCourses` table

### Relational vs. Non-Relational Databases
The big difference between relational and non-relational databases is that non-relational databases *nest* their data. Instead of keeping records on separate tables, they store records *within other records*.

To over-simplify it, you can think of non-relational databases as giant JSON blobs. If a user can have multiple courses, you might just add all the courses to the user record.

```json
{
    "users": [
        {
            "id": 0,
            "name": "Elon",
            "courses": [
                {
                    "name": "Biology",
                    "id": 0
                },
                {
                    "name": "Biology",
                    "id": 0
                }
            ]
        }
    ]
}
```

This often results in *duplicate data* within the database. That's obviously less than ideal, but it does have some benefits that we'll talk about later in the course.

#### Relational Database

![](../attachments/Pasted%20image%2020250119010143.png)

#### Non-Relational Database

![](../attachments/Pasted%20image%2020250119010200.png)

## References
[Boot.dev SQL Course Ch. 3](https://www.boot.dev/lessons/186e59db-4344-4994-903e-71dc5e84331c)