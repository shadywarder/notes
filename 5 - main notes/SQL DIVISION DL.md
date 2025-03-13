**2025-01-18 17:39**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL DIVISION
Division in SQL looks deceptively easy. Here's the syntax:

```sql
SELECT expression_1 / expression_2
FROM table;
```

It gets tricky though, because depending on the values of `expression_1` and `expression_2`, you'll get unexpected results.

### How to Divide Integers and Return Decimal/Float Output?
You can still make SQL achieve decimal output with a few tricks such as:
- `CAST()` function
- multiplying by `1.0`
- being explicit with types `::`

### Divide Integers using CAST()
The `CAST()` function converts one or both operands into decimal or floating-point data types (aka not whole number integers). By casting the operands, you explicitly instruct SQL to consider the division with a different type, resulting in the desired output.

```sql
SELECT
	CAST(10 AS DECIMAL)/4, 
	CAST(10 AS FLOAT)/4,
	10/CAST(6 AS DECIMAL),
	10/CAST(6 AS FLOAT);
```

|output|output|output|output|
|---|---|---|---|
|2.5000000000000000|2.5|1.6666666666666667|1.6666666666666667|
### Divide Integers Using Multiplication by 1.0
Another ingenious technique involves multiplying one of the operands by 1.0. This straightforward action converts an integer into a decimal or floating-point data type, allowing for the inclusion of decimal places in the result.

```sql
SELECT
	10/6,
	10*1.0/6,
	10/6*1.0.
	10/(6*1.0);
```

|output|output|output|output|
|---|---|---|---|
|1|1.6666666666666667|1.0|1.6666666666666667|
### Divide Integers using ::DECIMAL/::FLOAT
The `::` notation is a versatile tool to cast data types explicitly. When used for division, it signifies that you want the division to be executed with the specified data type, effectively achieving decimal or floating-point output.

```sql
SELECT
	10::DECIMAL/4,
	10::FLOAT/4,
	10/4::DECIMAL,
	10/4::FLOAT,
	10::DECIMAL/6,
	10::FLOAT/6;
```

|output|output|output|output|output|output|
|---|---|---|---|---|---|
|2.5000000000000000|2.5|2.5000000000000000|2.5|1.6666666666666667|1.6666666666666667|

### Calculate Percentages
The basic formula to calculate a percentage is `(part/total) * 100`. In SQL, you can apply this formula using the following syntax:

```sql
SELECT 
	(part_column / total_column) * 100 AS percentage
FROM table;
```
## References
[DataLemur SQL DIVISION With Examples](https://datalemur.com/sql-tutorial/sql-division)