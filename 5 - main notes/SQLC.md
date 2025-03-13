**2025-01-26 17:26**
**Tags:** [go](../3%20-%20indexes/go.md) [sql](../2%20-%20tags/sql.md)

## SQLC
*SQLC* is an *amazing* Go program that generates Go code from SQL queries. It's not exactly an *ORM*, but rather a tool that makes working with raw SQL easy and type-safe.

SQLC is just a command line tool, it's not a package that we need to import. I recommend installing it using `go install`. Installing Go CLI tools with `go install` is easy and ensures compatibility with your Go environment.

- Configure *SQLC*. You'll always run the `sqlc` command from the root of your project. Create a file called `sqlc.yaml` in the root of your project. Here is mine:

```yaml
version: "2"
sql:
	- schema: "sql/schema"
	queries: "sql/queries"
	engine: "postgresql"
	gen:
		go:
			out: "internal/database"
```

We're telling SQLC to look in the `sql/schema` directory for our schema structure (which is the same set of files that Goose uses, but `sqlc` automatically ignores "down" migrations), and in the `sql/queries` directory for queries. We're also telling it to generate Go code in the `internal/database` directory.

- Write a query to create a user. Inside the `sql/queries` directory, create a file called `users.sql`. Here's the format:

```sql
-- name: CreateUser :one
INSERT INTO users (id, created_at, updated_at, name)
VALUES (
	$1,
	$2,
	$3,
	$4
)
RETURNING *;
```

`$1`, `$2`, `$3`, and `$4` are parameters that we'll be able to pass into the query in our Go code. The `:one` at the end of the query name tells SQLC that we expect to get back a single row (the created user).

Keep the *SQLC postgres docs* handy, you'll probably need to refer to them again later.

- Generate the Go code. Run `sqlc generate` from the root of your project. It should create a new package of go code in `internal/database`. You'll notice that the generated code relies on Google's `uuid` package, so you'll need to add that to your module.
- Write another query to get a user by name. I used the comment `-- name: GetUser :one` to tell SQLC that I expect to get back a single row. Again, generate the Go code to ensure that it works.

- Import a PostgreSQL driver.
	We need to add and import a *Postgres driver* so our program knows to talk to the database.  `go get github.com/lib/pq`
	Add this import to the top of your `main.go` file: `import _ "github.com/lib/pq"` 
## References