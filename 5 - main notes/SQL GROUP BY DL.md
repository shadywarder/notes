**2025-01-17 15:19**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL GROUP BY
The SQL Aggregate Function like `AVG`, `MIN`, and `SUM` from the previous lesson process an entire column to come up with an answer. But what if you want to aggregate only *part* of a table?

For example, instead of finding the average price all Amazon products orders, what if you want to find the average spent by category (i.e. average spend on appliances vs. electronics?)

`GROUP BY` command tells the database to separate your data into groups, which can then be aggregated independently.

```sql
SELECT category, SUM(spend)
FROM product_spend
GROUP BY category;
```

The output of that `GROUP BY` query yields this results:

|category|sum|
|---|---|
|electronics|1007.54|
|appliance|1135.22|
### GROUP BY Two Columns
You can GROUP BY two columns, even multiple columns, in SQL. To group by multiple categories, just separate column names with commas.

For an example of grouping by multiple columns, here's the average stock open price grouped by each ticker symbol and group by each year:

```sql
SELECT
	ticker,
	EXTRACT(YEAR FROM data) AS year,
	ROUND(AVG(open), 2) AS avg_open
FROM stock_prices
GROUP BY ticker, year
ORDER BY year DESC;
```

And again, just like with `ORDER BY` syntax for multiple columns, for shorthand, you can use numbers instead of typing out the full column names, to make your query mode concise. Here's the exact same query in the `GROUP BY 1, 2` format:

```sql
SELECT
	ticker,
	EXTRACT(YEAR FROM date) AS year,
	ROUND(AVG(open), 2) AS avg_open
FROM stock_prices
GROUP BY 1, 2
ORDER BY year DESC;
```

#### Can GROUP BY be used to remove duplicates?
While `GROUP BY` isn't exactly used for the purpose of finding duplicates, the command does allow you to collapse multiple rows with the same values into a single row. So, in a way, it *could* be considered as a way to get rid of duplicates for certain columns.

To demonstrate this, imagine you were analyzing this website traffic data from a Google Analytics report:

|browser|visits|
|---|---|
|Chrome|6|
|Safari|2|
|Safari|4|
|Edge|3|
|Safari|5|
|Chrome|3|
|Chrome|4|
To get rid of duplicate browser data, and aggregate the visits information, you could use the following `GROUP BY` query:

```sql
SELECT
	browser,
	SUM(visits)
FROM google_analytics_sata
GROUP BY browser;
```

This would eliminate the duplicate browser information, and output the following results:

|browser|visits|
|---|---|
|Chrome|13|
|Safari|11|
|Edge|3|
#### What's the difference between GROUP BY and ORDER BY?
People sometimes get confused between `GROUP BY` and `ORDER BY` because both commands have `BY` in them, but their actual function is quite different!

`ORDER BY` helps you output your rows in a specific order, such as alphabetically on some text column, or from smallest to biggest, for some text column.

`GROUP BY`, as you saw earlier, is all about grouping your data into categories! Because they are quite different commands, it's absolutely possible for a query to have both `GROUP BY` and `ORDER BY`, with `GROUP BY` coming first!

Here's query that uses both `GROUP BY` and `ORDER BY`:

```sql
SELECT
	ticker,
	AVG(open) AS avg
FROM stock_prices
GROUP BY ticker
ORDER BY avg DESC;
```

It takes the FAANG stack data, and finds the average stock open price for each ticker symbol. Then, the `ORDER BY` clause orders the average stock open price, from highest to lowest.

## References
[SQL HAVING Tutorial With Examples](https://datalemur.com/sql-tutorial/sql-group-by)