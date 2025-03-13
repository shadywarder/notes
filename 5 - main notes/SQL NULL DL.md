**2025-01-18 21:09**
**Tags:** [sql](../2%20-%20tags/sql.md)

## SQL NULL
In SQL, `NULL` indicates the **absence of a value**. Unlike an empty string or zero, `NULL` doesn't represent a specific value, but rather, a missing or unknown piece of information.

Here's an overview of what you'll learn in this tutorial:
- `IS NULL` and `IS NOT NULL`: Used to identify null and non-null values.
- `COALESCE()`: Returns the first non-null value from a list of arguments.
- `IFNULL()`: Substitutes null value with a specified value.

### Why Is It Important to Handle NULL Values?
Handling `NULL` values is a common task in various real-world scenarios where data may be incomplete or missing. It the realm of databases, `NULL` values serve as placeholders for uncertain or absent data.

Here are a few examples of real-world scenarios:
1. **Employee Records:** In a human resources database, some employees might not have entered their emergency contact information yet, result in `NULL` values in that column.
2. **Survey Responses:** When collecting survey responses, participants might choose not to answer certain questions, leading to `NULL` values in those fields.
3. **Student Grades:** In an educational database, some students might not have received for certain assignments, leading to `NULL`values in the grade column.
4. **Health Records:** In a patient's medical history, some test results might not be available yet, resulting in `NULL` values in the test result columns.

In essence, `NULL` values in SQL are like flexible placeholders that cater to the uncertainties and variations in real-world data. They allow databases to accommodate missing or pending information without resorting to assumptions or default values.

### Identifying NULL Values with IS NULL and IS NOT NULL
Imagine you're data analyst at Goodreads and you're identifying records where the book titles are null to ensure data completeness and integrity.

```sql
SELECT * FROM goodreads
WHERE book_title = NULL:
```

The expected result would be an empty result set because there are no records in the `goodreads` table where the `book_title` column is explicitly set to `NULL`.

While it might seem like the query is looking for records where the `book_title` is blank, SQL doesn't work that way with blank values. The word `NULL` in SQL doesn't mean empty like it does in everyday language. Instead, it means "unknown" or "missing". So, when SQL tries to compare something to `NULL` using `=`, it doesn't work like you might expect. If fact, it doesn't work at all! It's like trying to compare apples and oranges - they're just not the same thing.

#### IS NULL
Now, to correctly identify `NULL` values, we can utilize the `IS NULL` condition:

```sql
SELECT * FROM goodreads
WHERE book_title IS NULL;
```

This query retrieves all records all records where the `book_title` column is indeed `NULL`.

#### IS NOT NULL
And, to retrieve rows with actual values (not `NULL`) in a column, utilize `IS NOT NULL`:

```sql
SELECT * FROM goodreads
WHERE book_title IS NOT NULL;
```

This query delivers rows where the `book_title` column isn't `NULL`.

#### Refining Data with SQL COALESCE()
The `COALESCE()` function takes multiple inputs and returns the first non-null value.

```sql
COALESCE(column_name, 'expression')
```

If `column_name` is NULL, it returns the specified 'expression'. Otherwise, it returns the value of `column_name`.

#### Handling Gaps with SQL IFNULL()
Suppose some of the book ratings are `NULL`, we can use the `IFNULL()` function to fill in the gaps with default values.

```sql
IFNULL(column_name, value_if_null)
```

#### Difference between COALESCE() and IFNULL()
While both the `COALESCE()` and `IFNULL()` functions serve a similar purpose of handling `NULL` values, there is a key difference between them.

`COALESCE()` **function:** Versatile for multiple arguments, it returns the first non-null value among them.

`IFNULL()` **function:** Handles two arguments, returning the second if the first is null; else, it returns the first.

**Example**
Suppose you have these values:
- `arg1` is `NULL`
- `arg2` is 5
- `arg3` is 10

With `COALESCE(arg1, arg2, arg3)`, the result would be 5 (the first non-null value). However, if `arg2` is `NULL`, then the result would be 10 (the first non-null value).

With `IFNULL(arg1, arg2)`, the result would be 5 (since `arg1` is `NULL`, it returns the second argument, which is 5). 

So, while they both can serve similar purposes,
- `COALESCE()` offers more flexibility when dealing with multiple values,
- Whereas `IFNULL()` is a more concise option when you have two values to work with.
## References
[DataLemur SQL NULL Tutorial With Practice Exericeses](https://datalemur.com/sql-tutorial/sql-null)