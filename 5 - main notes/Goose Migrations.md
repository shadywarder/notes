**2025-01-23 15:32**
**Tags:** [go](../3%20-%20indexes/go.md) [sql](../2%20-%20tags/sql.md)

## Goose Migrations
*Goose* is a database migration tool written in Go. It runs migrations from a set of SQL lines, making it perfect fit for this project (we wanna stay close to the raw SQL).

### What Is a Migration?
A migration is just a set of changes to your database table. You can have as many migrations as needed as your requirements change over time. For example, one migration create a new table, one might delete a column, and one might add 2 new columns.

And "up" migration moves the state of the database from its current schema to the schema that you want. So, to get a "blank" database to the state it needs to be ready to run your application, you run all the "up" migrations.

If something breaks, you can run one of the "down" migrations to revert the database to a previous state. "Down" migrations are also used if you need to reset a local testing database to a known state.

A "migration" in Goose is just a `.sql` file with some SQL queries and some special comments. Our first migration should just create a `users` table. The simplest form for these files is:

```sql
number_name.sql
```

For example, I created a file in `sql/schema` called `001_users.sql` with the following contents:

```sql
-- +goose Up
CREATE TABLE ___

-- +goose Down
DROP TABLE users;
```

Write out the `CREATE TABLE` statement. A `user` should have 4 fields:
- `id`: a `UUID` that will serve as the *primary key*
- `created_at`: a `TIMESTAMP` that can *not be null*
- `updated_at`: a `TIMESTAMP` that can *not be null*
- `name`: a *unique* string that can *not be null*

The `-- +goose Up` and `-- +goose Down` statement in full, I left it blank for you to fill in. They tell Goose how to run the migration in each direction.

Get your connection string. A connection string is just a URL with all of the information needed to connect to a database. The format is:

```shell
protocol://username:password@host:port/database
```

Here is example:

```sql
postgres://postgres:postgres@localhost:5432/gator
```

Add the connection to the `.gatorconfig.json` file instead of the example string we used earlier. When using it with `goose`, you'll use it in the format we just used. However, here in the config file it needs an additional`sslmode:disable` query string:

```shell
protocol://username:password@host:part/database?sslmode=disable
```

Your application code needs to know to not try to use SSL locally.
## References
[Boot.dev Blog Aggregator Tutorial](https://www.boot.dev/lessons/d049abb2-c733-4986-a33a-73f05e2ea06c)