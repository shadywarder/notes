**2025-01-20 16:44**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL CASE
The `CASE` statement in SQL allows you to shape, transform, manipulate, and filter data based on specified conditions. It's a conditional expression tool that lets you customize query results, create new categories, and apply conditional logic.

Here's what we'll be covering:
- Using `CASE` statement in `SELECT` statement
- Using `CASE` statement in `WHERE` clause
- Counting results using SQL `COUNT()` in `CASE` statement
- Adding results using SQL `SUM()` in `CASE` statement
- Averaging results using SQL `AVG()` in `CASE` statement

#### Using CASE Statement in SELECT Statement
The `CASE` statement in the `SELECT` allows us to control flow based on specified conditions. 

```sql
SELECT
	column_1,
	column_2
	CASE
		WHEN condition_1 THEN result_1
		WHEN condition_2 THEN result_2
		WHEN ... THEN ...
		ELSE result_3 -- default case
	END AS column_3_name -- give you new column a name
FROM table_1;
```

#### Using CASE Statement in Where Clause
The `CASE` statement in the `WHERE` clause is used to **filter rows based on specified conditions**.

```sql
SELECT
	column_1,
	column_2
FROM table_1
WHERE CASE
	WHEN condition_1 THEN result_1
	WHEN condition_2 THEN result_2
	WHEN ... THEN ...
	ELSE result_3;
END;
```

#### Assigning Categories with CASE Statement in SELECT Statement
Here's an example that determines the popularity category of each Marvel character based on their number of followers ("Popular" if they have 500,000 or more followers).

```sql
SELECT
	character,
	superhero_alias,
	platform,
	CASE
		WHEN followers >= 500000 THEN 'Popular'
	END AS popularity_category
FROM marvel_avengers;
```

Here's the output:

|character|superhero_alias|platform|popularity_category|
|---|---|---|---|
|Tony Stark|Iron Man|Instagram|Popular|
|Steve Rogers|Captain America|Twitter|NULL|
|Natasha Romanoff|Black Widow|Instagram|Popular|
|Thor|Thor|YouTube|NULL|
|Bruce Banner|Hulk|Twitter|NULL|

#### Counting Results using SQL COUNT() in CASE Statement
The `COUNT()` aggregate function within a `CASE` statement is used to **count occurrences based on various conditions** within the dataset.

Assume we're given the following conditions:
- Assign to `popular_actor_count` if number of actors with followers greater than or equal to 500,000 followers.
- Assign to `less_popular_actor_count` if number of actors with followers than 500,000 followers.

```sql
SELECT
	platform,
	COUNT(CASE
		WHEN followers >= 500000 THEN 1
		ELSE NULL
	END) AS popular_actor_count,
	COUNT(CASE
		WHEN followers < 500000 THEN 1
		ELSE NULL
	END) AS less_popular_actor_count
FROM marvel_avengers
GROUP BY platform;
```

Results shown:

| platform  | popular_count | less_popular_count |
| --------- | ------------- | ------------------ |
| Instagram | 2             | 0                  |
| Twitter   | 0             | 2                  |
| YouTube   | 1             | 0                  |

#### Adding Results using SQL SUM() in CASE Statement
The `SUM()` aggregate function within a `CASE` statement allows to **add values based on specific conditions**.

```sql
SELECT
	platform,
	SUM(CASE
		WHEN engagement_rate >= 8.0 THEN followers
		ELSE 0
	END) AS high_engagement_followers_sum,
	SUM(CASE
		WHEN engagement_rate < 8.0 THEN followers
		ELSE 0
	END) AS low_engagement_followers_sum
FRUM marvel_avengers
GROUP BY platform;
```

Here's the results:

| platform  | high_engagement_followers_sum | low_engagement_followers_sum |
| --------- | ----------------------------- | ---------------------------- |
| Instagram | 1200000                       | 0                            |
| Twitter   | 0                             | 500000                       |
| YouTube   | 400000                        | 0                            |
#### Averaging results using SQL AVG() in CASE statement
The `AVG()` aggregate function within a `CASE` statement **calculates averages based on specific conditions** within the dataset, providing an average value.

Let's say we're calculating the average number of followers of actors based on their engagement rates. If the engagement rates. If the engagement rate is 8.0 or higher, assign "high_engagement_followers", otherwise, assign to "log_engagement_followers" for each platform.

```sql
SELECT 
	platform,
	AVG(CASE
		WHEN engagement_rate >= 8.0 THEN followers ELSE NULL
	END) AS avg_high_engagement_followers,
	AVG(CASE
		WHEN engagement_rate < 8.0 THEN followers ELSE NULL
	END) AS avg_low_engagement_followers
FROM marvel_avengers
GROUP BY platform;
```

Output shown:

|platform|avg_high_engagement_followers|avg_low_engagement_followers|
|---|---|---|
|Instagram|600000|NULL|
|Twitter|NULL|250000|
|YouTube|400000|NULL|
## References
[DataLemur SQL CASE Tutorial With Examples](https://datalemur.com/sql-tutorial/sql-case-statement)