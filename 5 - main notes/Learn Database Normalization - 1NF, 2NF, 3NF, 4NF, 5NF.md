**2025-03-05 00:18**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Learn Database Normalization - 1NF, 2NF, 3NF, 4NF, 5NF

![](../attachments/Pasted%20image%2020250305002107.png)

Normalized tables are:
- Easier to understand
- Easier to enhance and extend
- Protected from:
	- insertion anomalies
	- update anomalies
	- deletion anomalies

![](../attachments/Pasted%20image%2020250305002351.png)

### 1NF
Where were the members of the Beatles?
- John, Paul, George, and Ringo
- Paul, John, Ringo, and George
These answers are equivalent, despite different order.

```sql
SELECT Member_name
FROM Members_Of_The_Beatles
```

Using row order to convey information violates 1NF.
Mixing data types within a single column also violates 1NF.

![](../attachments/Pasted%20image%2020250305002810.png)

A table without a primary key violates 1NF.

![](../attachments/Pasted%20image%2020250305003056.png)

Storing a repeating group of data items on a single row violates 1NF.

![](../attachments/Pasted%20image%2020250305003236.png)

**1NF Rules:**
1. Using row order to convey information is not permitted;
2. Mixing data types within the same column is not permitted;
3. Having a table without a primary key is not permitted;
4. Repeating groups are not permitted.

### 2NF

![](../attachments/Pasted%20image%2020250305003706.png)

Non-key attributes: Item_Quantity, Player_Rating
Primary key: Player_ID, Item_Type

2NF: Each non-key attribute must depend on the entire primary key.

`{Player_ID, Item_Type} -> {Item_Quantity}` 
`{Player_ID} -> {Player_Rating}` violates condition about dependency on the entire primary key.

![](../attachments/Pasted%20image%2020250305004517.png)

### 3NF

![](../attachments/Pasted%20image%2020250305005053.png)

`{Player_ID} -> {Player_Skill_Level}`
`{Player_ID} -> {Player_Skill_Level} -> {Player_Rating}` - transitive dependency.

The 3NF forbids the exactly this type of dependency: the dependency of a non-key attribute on another non-key attribute.

![](../attachments/Pasted%20image%2020250305005707.png)

3NF: Every non-key attribute in a table should depend on the key, the whole key, and nothing but the key.

Boyce-Codd Normal Form: 
Every attribute in a table should depend on the key, the whole key, and nothing but the key.

### 4NF

![](../attachments/Pasted%20image%2020250305010919.png)

4NF: Multivalued dependencies in a table must be multivalued dependencies on the key.

![](../attachments/Pasted%20image%2020250305011059.png)

### 5NF

![](../attachments/Pasted%20image%2020250305011359.png)

5NF: The table (which must be in 4NF) cannot be describable as the logical result of joining some other tables together.

### Summary and review
#### First Normal (1NF)
1. Using row order to convey information is not permitted;
2. Mixing data types within same column is not permitted;
3. Having a table without a primary key is not permitted;
4. Repeating groups are not permitted.
#### Second Normal Form (2NF)
Each non-key attribute in the table must be dependent on the entire primary key.
#### Third Normal Form (3NF)
Each non-key attribute in the table must depend on the key, the whole key, and nothing but the key.
#### Boyce-Codd Normal Form (BCNF)
Each attribute in the table must depend on the key, the whole key, and nothing but the key.
#### Fourth Normal Form (4NF)
The only kinds of multivalued dependency allowed in a table are multivalued dependencies on the key.
#### Fifth Normal Form (5NF)
It must not be possible to describe the table as being the logical result of joining some other tables together.

## References
[Learn Database Normalization - 1NF, 2NF, 3NF, 4NF, 5NF](https://www.youtube.com/watch?v=GFQaEYEc8_8&t=493s)