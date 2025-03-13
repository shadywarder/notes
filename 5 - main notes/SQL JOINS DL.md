**2025-01-21 15:27**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL JOINS
So far in the SQL tutorial we've only been analyzing data from one table at a time. In the real world, companies have databases containing thousands of tables though. Here where the `JOIN` comes in.

### Spotify SQL JOIN Cast Study

![](../attachments/Pasted%20image%2020250121153408.png)

As a Data Analyst or Data Scientist, you'll almost always be pulling data from multiple tables, which is why the SQL `JOIN` is crucial.

For example, at Spotify you might analyze Drake by writing queries that combine two tables like:
- `JOIN` the `artists` and `concerts` table to analyze upcoming Drake concerts.
- `JOIN` the `user_likes` and `playlists` table to count the # of likes on the *This Is Drake* playlist.
- `JOIN` the `artists` and `songs` table to rank Drake's top songs by play count.

![](../attachments/Pasted%20image%2020250121153754.png)

### SQL JOIN Example
Suppose you work at Spotify and want to join information in the `artists` table with information in the `songs` table. Here's the schema for the two tables:

**`artists` Example Input:**

|**artist_id**|**artist_name**|**label_owner**|
|---|---|---|
|101|Ed Sheeran|Warner Music Group|
|120|Drake|Warner Music Group|
|125|Bad Bunny|Rimas Entertainment|

**`songs` Example Input:**

|**song_id**|**artist_id**|**name**|
|---|---|---|
|55511|101|Perfect|
|45202|101|Shape of You|
|22222|120|One Dance|
|19960|120|Hotline Bling|
Notice how the two tables have the `artist_id` column in common:
- In the  `artists` table, you have information about each `artist_id`, like their artist name and what music label they work with.
- In the `songs` table, you have information about each song, which includes which `artist_id` made that particular song.

#### How to Write a SQL JOIN
There are three key parts to get right when writing `JOIN` in SQL. First, you need to specify what columns to show. For our `artists` x `songs` example, we'll just use `SELECT *` for that.

Secondly, you need to specify the names of the two tables we are joining. Since we are joining the `artists` with `songs` table, our query so far is as follows:

 ```sql
SELECT *
FROM artists
JOIN songs;
```

The third and final in a SQL `JOIN` query is the `ON` clause, which explains to the RDBMS (Relational Database Management System) how the two tables relate to each other.

We need to explicitly write in the SQL query that the `artists_id` column in the `artists` table matches up against the `artists_id` column in the `songs` table with this clause:

```sql
ON artists.artist_id = songs.artist_id
```

Putting these three parts together, we get the following SQL `JOIN` query:

```sql
SELECT *
FROM artists
JOIN songs
	ON artists.artist_id = songs.artist_id;
```

The about query combines info from the `artists` and `songs` table into the result below:

| **artist_id** | **artist_name** | **label_owner**     | **song_id** | **artist_id** | **name**      |
| ------------- | --------------- | ------------------- | ----------- | ------------- | ------------- |
| 101           | Ed Sheeran      | Warner Music Group  | 55511       | 101           | Perfect       |
| 101           | Ed Sheeran      | Warner Music Group  | 45202       | 101           | Shape of You  |
| 120           | Drake           | Warner Music Group  | 22222       | 120           | One Dance     |
| 120           | Drake           | Warner Music Group  | 19960       | 120           | Hotline Bling |
| 125           | Bad Bunny       | Rimas Entertainment | 12636       | 125           | Mia           |

### 4 Types of SQL Joins
So far in this tutorial, we've simply use the `JOIN` keyword, which is short for an `INNER JOIN`. There are actually 4 different types of `JOIN`s in SQL.

|Type of Joins|Description|
|---|---|
|INNER JOIN|Returns only the **rows with matching values** from both tables.|
|LEFT JOIN|Returns **all the rows from the left table** and the **matching rows from the right table**.|
|RIGHT JOIN|Returns **all the rows from the right table** and the **matching rows from the left table**.|
|FULL OUTER JOIN|Returns all rows when there is a **match in either the left or the right table**. If there is no match, `NULL` values are returned for columns from the table without a match.|

#### SQL INNER JOIN
An `INNER JOIN` returns only the **rows with matching values** from both tables.

```sql
SELECT
	orders.order_id,
	orders.customer_id,
	goodreads.book_title,
	orders.quantity
FROM goodreads
INNER JOIN orders
	ON goodreads.book_id = orders.book_id -- Columns with dame data type (integer)
WHERE goodreads.price >= 20;
```

The `INNER JOIN` returns only the rows where there is a matching book ID in both the `goodreads` and `orders` tables, focusing on books priced $20 and above.

#### SQL LEFT JOIN
Next, let's explore how the `LEFT JOIN` works using `orders` and `deliveries` tables.

Suppose we want to retrieve all the orders along with their corresponding deliveries information. Here's the query:

```sql
SELECT
	orders.order_id,
	deliveries.delivery_id,
	deliveries.dedlivery_date,
	deliveries.delivery_status
FROM orders
LEFT JOIN deliveries
	ON orders.order_id = deliveries.order_id;
```

With `LEFT JOIN`, **all rows from the left table (`orders`)** are fetched, along with **matching rows from the right table (`deliveries`)**. If there is no matching data in the right table, the result will still include the left table's data with `NULL` values in the columns from the right table. 

But what if we flip the tables? By swapping the positions of the tables in the `LEFT JOIN`, the same result can be achieved"

```sql
SELECT
	orders.order_id,
	deliveries.delivery_id,
	deliveries.delivery_date,
	deliveries.delivery_status
FROM deliveries
LEFT JOIN orders
	ON deliveries.order_id = order.order_id;
```

#### SQL RIGHT JOIN
A `RIGHT JOIN` is the opposite of a `LEFT JOIN`. IT **returns all rows from the right table** and pairs them with **matching rows from the left table**. If there is no match, the columns from the left table have `NULL` values.

We can also swap the positions of the tables, and you'll get the exact same results as a `LEFT JOIN`.

> [!TIP]
> In the real world, `RIGHT JOIN` is rarely used. Most people naturally think from left to right, making `LEFT JOIN` easier to understand and implement. So, if you find yourself in a situation where you might consider a `RIGHT JOIN`, simply switch positions of the tables and use a `LEFT JOIN` instead!

#### SQL FULL OUTER JOIN
Now, let's explore the `FULL OUTER JOIN` which allows you to bring unmatched rows into the results.

Ever wondered what happens when both tables have something to offer, but they're not a perfect match?

A `FULL OUTER JOIN` returns all rows when there is a **match in either the left or the right table**. If there is no match, `NULL` values are returned for columns from the table without a match.

```sql
SELECT
	orders.order_id,
	deliveries.delivery_id,
	deliveries.delivery_date,
	deliveries.deilvery_status
FROM orders
FULL OUTER JOIN deliveries
	ON orders.order_id = deliveries.order_id;
```

Running this query is like uniting two tables: `orders` and `deliveries`. Each row represents an attempt at a match. If there's no match, you'll see `NULL` values in the columns

> [!TIP]
> Be careful with `FULL OUTER JOIN` as it can introduce duplicate rows to your results without you realizing!

#### Conditional SQL JOINS
Conditional joins involve using single or multiple conditions using logical operations like `AND` and `OR`, or incorporating complex logical expressions such as ranges, pattern matching, or subqueries. 

**Example 1: Joining `goodreads` and `orders` table with a condition on quantity**
Retrieve the list of book titles and their quantities ordered where the quantity ordered ins more than 2.

```sql
SELECT
	g.book_title,
	o.quantity
FROM goodreads AS g
INNER JOIN orders AS o
	ON g.book_id = o.book_id
		AND o.quantity > 2;
```

What happens is:
- This query applies the `o.quantity > 2` condition as part of the join condition itself. The join only includes rows there both `g.book_id = o.book_id` and `o.quantity > 2` are `true`.
- Since the filter condition is part of the join, no additional filtering is required after the join is performed.

**Example 2: Joining all three tables with a condition on `book_rating` and `delivery_status`**
Retrieve the book titles, their average ratings, order dates, and delivery statuses for books with a rating higher than 4.0 that have been delivered.

```sql
SELECT
	g.book_title,
	g.book_rating,
	o.order_rate,
	d.delivery_status
FROM goodreads g
JOIN orders o
	ON g.book_id = o.book_id
		AND g.book_rating > 4.0
INNER JOIN deliveries d
	ON o.order_id = d.order_id
		AND d.delivery_status = 'Delivered';
```


## References
[DataLemur SQL JOINS Tutorial With Practice Exercises](https://datalemur.com/sql-tutorial/sql-joins-inner-outer-left-right)