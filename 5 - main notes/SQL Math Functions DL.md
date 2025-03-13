**2025-01-18 16:42**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL Math Functions
### ABS(): Calculating Absolute Differences 
Imagine you're tasked with preparing a dashboard showcasing the historical performance of Google's stock (ticker:'GOOG') throughout 2023. The finance team specifically requests the absolute difference between the opening and closing prices for each trading day.

We can utilize the `ABS()` function which calculates the absolute value of a number, irrespective of its sign.

```sql
SELECT 
date,
ticker,
(close-open) AS difference,
ABS(close-open) AS abs_difference
FROM stock_prices
WHERE EXTRACT(YEAR FROM date) = 2023 
AND ticker = 'GOOG';
```

### ROUND(): Rounding Numbers
Consider a scenario where you're compiling a report displaying the average closing prices of Apple's stock (ticker:'APPL') throughout 2022. To ensure the report's readability, you decide to round the average prices to 2 decimal places.

The `ROUND()` function is handy here; it rounds a number to a specified number of decimal places.

```sql
SELECT
ticker,
AVG(close) AS avg_close,
ROUND(AVG(close), 2) AS rounded_avg_close
FROM stock_prices
WHERE EXTRACT(YEAR FROM date) = 2022
GROUP BY ticker;
```

In the initial `AVG(close)` calculation, the output displays with 10 decimal places which honestly just looks unpleasant. However, by using `ROUND(AVG(close), 2)`, your specify the number of decimals you prefer , resulting in a neatly rounded up price.

### CEIL() and FLOOR(): Rounding Up and Down
Now, imagine you're analyzing Facebook's stork performance (ticker:'META') to identify potential trading ranges.

We can utilize the `CEIL()` function to round up and the `FLOOR()` function to round down to the lowest and highest prices.

```sql
SELECT
date,
ticker,
high,
CEIL(high) AS resistance_level,
low,
FLOOR(low) AS support_level
FROM stock_prices
WHERE ticker = 'META'
ORDER BY date;
```

By employing `FLOOR()` on the low column, we highlight potential support levels by rounding down the lowest prices. Conversely, with `CEIL()` on the high column, we identify potential resistance levels by rounding up the highest prices.

### POWER(): Calculating Squared Values
In this scenario, we'll explore the concept of squared values by focusing on the 3 popular tech stocks: Apple ('APPL'), Google ('GOOG'), and Microsoft ('MSFT'). Although this scenario is simplified for illustrative purposes, it offers a straightforward way to introduce the usage of the `POWEWR` function.

The `POWER()` function raises a number to a specified power, allowing us to perform exponential calculations.

```sql
SELECT
	date,
	ticker,
	close,
	ROUND(POWER(close, 2), 2) AS squared_close
FROM stock_prices
WHERE ticker IN ('APPL', 'GOOG', 'MSFT')
ORDER BY date;
```

For shorthand, in PostgreSQL, we can also just use the `^` operator too!

### MOD() or %
Imagine you're intrigued by stocks that exhibit a consistent price behavior divisible by 5.

The `MOD()` function or `%` modulo operator calculates the remainder of division between two numbers.

```sql
SELECT
	ticker,
	close,
	MOD(close, 5) AS price_remainder_mod,
	close%5 AS price_remainder_modulo
FROM stock_prices
WHERE ticker = 'GOOG';
```

In this example, `MOD()` calculates the remainder when the closing prices are divided by 5. The `%` operator achieves the same result. Both approaches help in identifying stocks with price behaviors divisible by 5.

## References
[DataLemur SQL Math Functions: ABS, CEIL, FLOOR, ROUND Examples](https://datalemur.com/sql-tutorial/sql-tutorial-mathematical-functions)