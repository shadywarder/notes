**2025-01-19 16:14**
**Tags:** [sql](../2%20-%20tags/sql.md)

## Ch 8. Subqueries
### Subqueries
Sometimes a single query is not enough to retrieve the specific we need.

It is possible to run a query on the *result set* of another query - a query within a query! This is called a "subquery".

Subqueries can very useful in a number of situations when trying to retrieve specific data that wouldn't be accessible by simple querying a single table.

#### Retrieving Data from Multiple Tables
Here is an example of a subquery:

```sql
SELECT id, song_name, artist_id
FROM songs
WHERE artist_id IN (
	SELECT id
	FROM artists
	WHERE artists_name LIKE 'Rick%'
);
```

In this hypothetical database, the query above selects all of the `id`s, `song_name`s, and `artists_id`s from the `songs` table that are written by artists whose name starts with "Rick". Notice that the subquery allows us to use information from a different table - in this case the `artists` table.

#### Subquery Syntax
The only syntax unique to a subquery is the parentheses surrounding the nested query. The `IN` operator could be different, for example, we could use the `=` operator if we expect a single value to be returned.

### No Tables
When working on a back-end application, this doesn't come up often, but it's important to remember that **SQL is a full programming language**. We usually use it to interact with data stored in tables, but it's quite flexible and powerful.

For example, you can `SELECT` information that's simply calculated, with no tables necessary.

```sql
SELECT 5 + 10 as sum;
```

## References
[Boot.dev SQL Course Ch. 8](https://www.boot.dev/lessons/8df8034e-3032-4f31-b0e7-58f55c5bce51)