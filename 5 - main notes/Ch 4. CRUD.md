**2025-01-19 01:03**
**Tags:** [sql](../2%20-%20tags/sql.md)

## Ch 4. CRUD
### CRUD
CRUD is an acronym that stands for `CREATE`, `READ`, `UPDATE`, and `DELETE`. These four operations are the bread and butter of nearly every database you will create.

#### HTTP and CRUD
The CRUD operations correlate nicely with the HTTP methods we learned in the *Learn HTTP Clients* course.
- `HTTP POST` - `CREATE`
- `HTTP GET` - `READ`
- `HTTP PUT` - `UPDATE`
- `HTTP DELETE` - `DELETE`

### Insert Statement
Tables are pretty useless without data in them! In SQL we can add records to a table using an `INSERT INTO` statement. When using an `INSERT` statement we must first specify the `table` we are inserting the record into, followed by the `fields` within that table we want to add `VALUES` to.

Example `INSERT INTO` statement:

```sql
INSERT INTO employees(id, name, title)
VALUES (1, 'Allan', 'Engineer');
```

### HTTP CRUD Database Lifecycle
It's important to understant how data *flows* through a typical web application.

![](../attachments/Pasted%20image%2020250119011129.png)

1. The front-end processes some data from user input - maybe a form is submitted.
2. The front-end sends that data to the server through an HTTP request - maybe a `POST`.
3. The server makes a SQL query to its database to create an associated record - Probably using an `INSERT` statement.
4. Once the server has processed that the database query was successful, it responds to the front-end with a status code! Hopefully a 200-level code (success)!

### Auto Increment 
Many dialects of SQL support an `AUTO INCREMENT` feature. When inserting records into a table with `AUTO INCREMENT` enabled, the database will assign the next value *automatically*. In SQLite an integer `id` field that the `PRIMARY KEY` constraint will auto increment by default!

#### Id's 
Depending on how your database is set up, you may be using traditional `id`s or you may be using *UUIDs*. SQL doesn't support auto incrementing a `uuid` so if your database is using them your server will have to handle the changing uuid's for each record.

#### Using AUTO INCREMENT in SQLite
We are using traditional `id`s in our database, so we can take advantage of the auto increment feature. Different dialects of SQL will implement this feature differently, but in SQLite any column that has the `INTEGER PRIMARY KEY` constraint will auto increment! So we can omit the `id` field within the `INSERT` statement and allow the database to automatically add that field for us!

### Manual Entry
Manually `INSERT`ing every single record in a database would be an *extremely* time-consuming task! Working with raw SQL as we are not is *not* super common when designing backend systems.

When working with SQL within a software system, like a backend web application, you'll typically have access to a programming language such as Go or Python. For example, a backend server written in Go can use string concatenation to dynamically create SQL statements, and that's usually how it's done!

```sql
sqlQuery := fmt.Sprintf(`
INSERT INTO users(name, age, country_code)
VALUES ('%s', %v, '%s');
`, user.Name, user.Age, user.CountrySide)
```

#### SQL Injection
This example above is an oversimplification of what *really* happens when you access a database using Go code. In essence, it's correct. String interpolation is how production systems access databases. That said, it must be done *carefully* to not be a *security vulnerability*.

### HTPP CRUD Database Lifecycle
We talked about how a "create" operation flows through a web application. Let's talk about a "read".

![](../attachments/Pasted%20image%2020250119012820.png)

Let's talk through an example using the CashPal app. Our product manager wants to show profile data on a user's settings page. Here's how we could engineer that feature request:
1. First, the front-end webpage loads.
2. The front-end sends an HTTP `GET` request to a `/users` endpoint on the back-end server.
3. The server receives the request.
4. The server uses a `SELECT` statement to retrieve the user's record from the `users` table in the database.
5. The server converts the row of SQL data into a `JSON` object and sends to the front-end.

### DELETE 
When a user deletes their account on Twitter, or deletes a comment on a YouTube video, that data needs to be removed from its respective database.

#### DELETE Statement
A `DELETE` statement removes all records from a table that match the `WHERE` clause. As an example:

```sql
DELETE FROM employees
	WHERE id = 251;
```

This `DELETE` statement removes all records from the `employees` table that have an id of `251`

### The Danger of Deleting Data
Deleting data can be a dangerous operation. Once removed, data can be really hard if not *impossible* to restore! Let's talk about a couple of common ways back-end engineers protect against losing valuable customer data.

#### Strategy 1 - Backups
If you're using a cloud-service like GCP's *Cloud SQL* or AWS's *RDS* you should *always* turn on automated backups. They take an automatic snapshot of your entire database on some interval, and keep it around for some length of time.

For example, the Boot.dev database has a backup snapshot taken daily and we retain those backups for 30 days. If I ever accidentally run a query deletes valuable data, I can restore it from backup.

**You should have a backup strategy for production databases.**
#### Strategy 2 - Soft Deletes
A "soft delete" is when you don't *actually* delete your data from database, but instead just "mark" the data as deleted. For example, you might set a `deleted_at` date on the row you want to delete. Then, in your queries you ignore anything that has a `deleted_at` date set. The idea is that this allows your application to behave as if it's deleting data, but you can always go back and restore any data that's been removed.

You should probably only soft-delete if you have a specific reason to to so. Automated backups should be "good enough" for most applications that are just interested in protecting against developer mistakes.

### Update Query in SQL
Whenever you update your profile picture or change your password online, you are changing the data in a field on a table in a database! Imagine if every time you accidentally messed up a Tweet on Twitter you had to delete the entire tweet and post a new one instead of just editing it...

...Well, that's a bad example.

#### Update Statement
The `UPDATE` statement in SQL allows us to update the fields of a record. We can even update many records depending on how we write the statement.

An `UPDATE` statement specifies the table that needs to be updated, followed by the fields and their new values by using the `SET` keyword. Lastly a `WHERE` clause indicates the records(s) to update.

```sql
UPDATE employees
SET job_title = 'Backend Engineer', salary = 15000
```

### Object-Relational Mapping (ORMs)
An *Object-Relational Mapping* or an *ORM* for short, is a tool that allows you to perform CRUD operations on a database using a traditional programming language. These typically come in the form of a library or framework that you would use in your backend code. 

The primary benefit an ORM provides is that it maps your database records to in-memory objects. For example, in Go we might have a struct what we use in our code: 

```go
type User struct {
	ID int
	Name string
	IsAdmin bool
}
```

This struct definition conveniently represents a database table called `users`, and an *instance* of the struct represents a row in the table.

#### Example: Using an ORM
Using an ORM we might be able to write simple code like this:

```go
user := User{
	ID: 10,
	Name: "Lane",
	IsAdmin: false,
}

// generates a SQL statement and runs i,
// creating a new record in the users table
db.Create(user)
```

#### Example: Using Straight SQL
Using straight SQL we might have to do something a bit more manual:

```go
user := User{
	ID: 10,
	Name: "Lane",
	IsAdmin: false,
}

db.Exec("INSERT INTO users (id, name, is_admin) VALUES (?, ?, ?);",
		user.ID, user.Name, user.IsAdmin)
```

#### Should You Use an ORM?
That depends! An ORM typically *trades simplicity for control.*

Using straight SQL you can take full advantage of the power of the SQL language. Using an ORM, you're limited by whatever functionality the ORM has. If you run into issues with a specific query , it can be harder to debug with an ORM because you have to dig through the framework's code and documentation to figure out how the underlying queries are being generated.

I recommend doing projects *both ways* so that you can learn about the tradeoffs. At the end of the day, when you're working on a team of developers it will be a team decision.
## References
[Boot.dev SQL Course Ch. 4](https://www.boot.dev/lessons/1c8a7ea3-4fd6-442b-94a4-5ddeb2fa000f)