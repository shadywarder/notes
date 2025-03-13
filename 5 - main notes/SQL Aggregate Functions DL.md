**2025-01-17 14:43**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL Aggregate Functions DL
Here's the 5 SQL Aggregate Functions:
- `SUM` adds together all the values in a particular column.
- `MIN` returns the lowest value in a particular column.
- `MAX` returns the highest value in a particular column
- `AVG` calculates the average of a group of selected values.
- `COUNT` counts how many rows are in a particular column.

Think of aggregate functions as your data detectives 🕵🏻‍♀️, helping you extract precious insights from your database, whether you're counting customers, summing up sales, or analyzing real estate property trends. 

### Analyzing Amazon Customer Transaction Data
To bring these concepts to life, we'll be working with the `product_spend` dataset which contains data on what products Amazon products customers are buying, and how much they are buying them for.

|category|product|user_id|spend|transaction_date|
|---|---|---|---|---|
|appliance|washing machine|123|219.80|03/02/2022 11:00:00|
|electronics|vacuum|178|152.00|04/05/2022 10:00:00|
|electronics|wireless headset|156|249.90|07/08/2022 10:00:00|
|electronics|vacuum|145|189.00|07/15/2022 10:00:00|
|electronics|computer mouse|195|45.00|07/01/2022 11:00:00|
|appliance|refrigerator|165|246.00|12/26/2021 12:00:00|
|appliance|refrigerator|123|299.99|03/02/2022 11:00:00|
|...|...|...|...|...|

### Counting Number of Orders with SQL COUNT()
The `COUNT()` function enables you to count the total number of rows. We can use the `COUNT()` function on the `user_id` column as follows:

```sql
SELECT COUNT(user_id) FROM product_spend;
```

Frequently, one of the first things we do after `SELECT *`'ing the data to explore it is then count how big the dataset is. WE do this with the following query:

```sql
SELECT COUNT(*) FROM table_name;
```

### Calculating Total Sales with SQL SUM()
The `SUM()` function calculates the sum of numeric values in a column. To calculate the total amount of money spend on Amazon products, we can use the `SUM()` function to sum the `spend` column.

```sql
SELECT SUM(spend) FROM product_spend;
```

### Finding the Average Price with SQL AVG()
The `AVG()` function computes the average value of numeric data in a column. To find the average price of an Amazon order, we can use the `AVG()` function on the `spend` column.

```sql
SELECT AVG(spend) FROM product_spend;
```

### Finding the Minimum with SQL MIN()
The `MIN()` function identifies the smallest value in a column. To find the lowest priced Amazon product order, we can use the `MIN()` function on the `spend` column.

```sql
SELECT MIN(spend) FROM product_spend;
```

### Discovering the Maximum Price with SQL MAX()
The `MAX()` function retrieves the largest value in a column. To find the highest priced Amazon product order, we can use the `MAX()` function on the `spend` column.

```sql
SELECT MAX(spend) FROM product_spend;
```

### Real-World Scenarios: Utilizing SQL Aggregate Functions for Practical Insights
1. **Calculating Total Sales for Financial Analysis 👩🏻‍💻**
	 - **Scenario:** A business wants to analyze its total sales over a specific period to access its financial performance.
	 - **Use case:** The `SUM()` function can be used to calculated the total revenue generated from sales during the chosen time frame, aiding in financial planning and analysis.
2. **Average Ratings for Product Reviews 🛍️**
	- **Scenario:** An e-commerce platform wants to showcase the average rating of products based on customer reviews.
	- **Use case:** The `AVG()` function can calculate the average rating of products, helping customers make informed purchasing decisions.
3. **Identifying Most Active Users📱**
	- **Scenario:** A social networking site wants to recognize its most active users based on the number of posts they've made.
	- **Use Case:** The `COUNT()` function can tally the number of posts for each user, highlighting the most prolific contributors.
4. **Finding Lowest and Highest Prices ✈️**
	- **Scenario:** A travel website wants to display the cheapest and most expensive flight options for users.
	- **Use case:** The `MIN()` and `MAX()` functions can identify the lowest and highest prices for flights, allowing users to quickly compare options.
5. **Tracking Student Performance in Education 📚**
	- **Scenario:** An educational institution wants to track student performance by calculating average scopes and identifying top performers.
	- **Use Case:** The `AVG()` function can compute the average scores of students, while the `MAX()` function can help find the highest scores.

## References
[SQL Aggregate Functions Tutorial With Practice Exercises](https://datalemur.com/sql-tutorial/sql-aggregate-functions)