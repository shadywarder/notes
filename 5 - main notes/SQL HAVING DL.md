**2025-01-17 16:24**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL HAVING
From the [previous note](SQL%20GROUP%20BY%20DL.md), you learned how to use the `GROUP BY` clause to aggregate state from the FAANG stocks dataset, like find the average price for each FAANG stock.

But suppose it's not enough to know the aggregated stats for each FAANG stock. Instead, say we wanted to display just the stocks whose average open price was greater then $200 per share.

In your head, you may think that the `WHERE` clause would help. Sadly, in this scenario, you'll get hit with the error message *"aggregate functions are not allowed in WHERE"*.

But, have no fear, the `HAVING` clause can come to our rescue! In SQL, `HAVING` allows you to filter data based on values from [aggregate functions](SQL%20Aggregate%20Functions%20DL.md).

Here's an example `HAVING` query that finds all FAANG stocks with an average share open price of more than $200:

```sql
SELECT ticker, AVG(open)
FROM stock_prices
GROUP BY ticker
HAVING AVG(open) > 200;
```

### WHERE vs. HAVING 
The difference between `WHERE` vs. `HAVING` is a common conceptual SQL interview question, so we figured we'd cover it a bit more explicitly: `WHERE` filters on values in individual rows, versus `HAVING` filters values aggregated from groups of rows.

Here's a summary table on the difference between `WHERE` & `HAVING`:

|                       | WHERE                                                                    | HAVING                                                                             |
| --------------------- | ------------------------------------------------------------------------ | ---------------------------------------------------------------------------------- |
| When It Filters       | Values BEFORE Grouping                                                   | Values AFTER Grouping                                                              |
| Operates On Data From | Individual Rows                                                          | Aggregated Values from Groups of Rows                                              |
| Example               | `SELECT username, followers FROM instagram_data WHERE followers > 1000;` | `SELECT country FROM instagram_data GROUP BY country HAVING AVG(followers) > 100;` |

### Can HAVING be used with multiple conditions?
In SQL, `HAVING` can be used to filter aggregated data using multiple conditions, just in the same way `WHERE` can filter data with multiple conditions.

Here's an example that finds all FAANG stocks where the average open price is greater that $200 per share, and the minimum price the stock opened at is greater than 100 per share:

```sql
SELECT 
	ticker, 
	AVG(open),
	MIN(open)
FROM stock_prices
GROUP BY ticker
HAVING AVG(open) > 200 AND MIN(open) > 100;
```

### Common SQL HAVING Questions 
#### Can HAVING be used without GROUP BY?
It's technically possible to have `HAVING` without `GROUP BY` in SQL, and in this case `HAVING` operates the same as `WHERE`. However, practically speaking, it's super weird to use `HAVING` in this context. For the most part, you should just use a `WHERE` clause if trying to filter on non-aggregated values.

#### Where should HAVING be placed in a query?
It's CRUCIAL to write clauses in the correct order, otherwise, your SQL query won't run!

Here's the order for the commands you've learned so far:
1. `SELECT`
2. `FROM`
3. `WHERE`
4. `GROUP BY`
5. `HAVING`
6. `ORDER BY`

## References
[SQL HAVING Tutorial With Examples](https://datalemur.com/sql-tutorial/sql-having)