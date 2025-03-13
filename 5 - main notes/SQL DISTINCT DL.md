**2025-01-17 19:23**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL DISTINCT
The `DISTINCT` SQL command is used in conjunction with the `SELECT` statement to return only distinct (different) values. Here's an example `DISTINCT` SQL query used to find only unique names of pharmaceutical manufactures:

```sql
SELECT DISTINCT manufacturer
FROM pharmacy_sales;
```

#### DISTINCT For Data Exploration
`DISTINCT` can be particularly helpful when exploring a new data set. In many real-world scenarios, you will generally end up writing several exploratory `SELECT DISTINCT` queries in order to figure out what data you have access too, and how you might want to group or filter the data.

### DISTINCT With Two Columns
If you include two (or more) columns in `SELECT DISTINCT` clause, your results will contain all of the unique pairs of those two columns.

For example, imagine you worked at stock trading app Robinhood and had access to their trades dataset. Here's a SQL query that uses `DISTINCT` on two columns - `user_id`'s and trade statuses:

```sql
SELECT DISTINCT user_id, status
FROM trades 
ORDER BY user_id;
```

Note: You only need to include `DISTINCT` once in your `SELECT` clause - you do not need to add it for each column name.

#### COUNT DISTINCT Example
You can use `DISTINCT` with aggregate functions - the most common one being `COUNT`. Here's an example that finds the number of unique user's who made trades:

```sql
SELECT COUNT(DISTINCT used_id)
FROM trades;
```

Notice that `DISTINCT` goes inside the `COUNT()` aggregate function, rather at the beginning of the `SELECT` statement.

While you could use `DISTINCT` with `SUM` or `AVG`, in practice it's rare to want to just sum or average just unique values. When it comes to `MAX` and `MIN`, they aren't affected by `DISTINCT` - whether there are duplicates or not, the lowest/highest value in the dataset will be the same.

## References
[SQL DISTINCT Tutorial with Examples](https://datalemur.com/sql-tutorial/sql-distinct)