**2025-01-17 19:59**
**Tags:** [[sql]]

## SQL Arithmetic
In addition to querying raw data with SQL, you can also use math expressions to transform column values. Here's an example:

```sql
SELECT particle_speed / 10.0 + speed_offset
FROM particle_sensor_data
WHERE (particle_position ^ 2) * 10.0 > 500
AND sensor_type = 'photon'
AND measurement_day % 7 = 0;
```

Let's dive into each arithmetic operator, one by one.

### SQL Arithmetic Operators
#### SQL Addition +
The `+` operator adds two numbers.

```sql
SELECT salary + bonus AS total_compensation FROM employees;
```

#### SQL Subtraction -
The `-` operator subtracts one column value from another.

```sql
SELECT revenue - expenses AS profit FROM product_sales;
```

#### SQL Multiplication *
The `*` operator multiplies two numbers.

```sql
SELECT units_sold * price AS revenue FROM ecomm_orders;
```

#### SQL Division /
The `/` operator divides the first column value by the number in the 2nd column.

```sql
SELECT country_gdp / population AS gdp_per_capita FROM econ_stats;
```

Always ensure you're not dividing by zero, as it will cause an error. 

#### SQL Modulus %
The `%` operator, also known as the modulus or remainder function, returns the remainder of a division operation.

```sql
SELECT 23 % 6; -- Returns 5
```

##### Odd and Even with Modulus %
The modulus (`%`) operator is often used to find odd and even values.

```sql
SELECT *
FROM measurements
WHERE measurements_sum % 2 = 1
```

The above SQL query looks at the `measurements_num` and looks at the remainder when divided by 2.

Odd numbers like 1, 3, 5, when divided by 2, have a remainder of 1, which is why `WHERE measurement_num % 2 = 1` gets us all odd numbered measurements.

#### SQL Exponentiation (^)
The `^` operator, also known as the power operator, raises a number to the power of another number.

```sql
SELECT 10 ^ 2; -- Returns 100
```

### SQL Arithmetic Order of Operations
Just like in standard arithmetic, SQL follows the order of operations of PEMDAS:
- P: Parenthesis first
- E: Exponents (i.e. `^`)
- MD: Multiplication and Division (left-to-right)
- AS: Addition and Subtraction (left-to-right)
## References
[DataLemur SQL Arithmetic With Practice SQL Exercises](https://datalemur.com/sql-tutorial/sql-arithmetic)