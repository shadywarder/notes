**2025-03-04 14:24**
**Tags:** [university](../3%20-%20indexes/university.md) [s25](../3%20-%20indexes/s25.md) [dbms](../2%20-%20tags/dbms.md)

## Lab 03 Relational Algebra

### Schema

![](../attachments/Pasted%20image%2020250304142439.png)

### Example 1
Find the name of suppliers who have produced at least one product produced by supplier 4.

```
pi Supplier.Name ((pi Catalogue.SID (pi Catalogue.PID (sigma SID = 4 (Catalogue)) ⨝ Catalogue)) ⨝ Supplier)
```

![](../attachments/Pasted%20image%2020250304162429.png)

> [!NOTE] 
> In relational algebra, the **natural join** (⨝) operation automatically matches columns with the **same attribute names** from the two relations. In your example:
> - **Supplier** and **Catalogue** both have the attribute `SID`.
> - When you perform `Supplier ⨝ Catalogue`, the natural join implicitly uses `SID` as the join key because it is the only common attribute.

### Example 2
Find the name of the suppliers who did not produce any product produced by Kazan suppliers.

```
pi Name ((pi SID Supplier - pi SID ((pi Catalogue.PID (sigma City = 'Kazan' (Supplier ⨝ Catalogue))) ⨝ Catalogue)) ⨝ Supplier)
```

### Example 3
Find the item and color of the products supplied by all the Moscow suppliers.

```
pi Item, Color ((pi PID, SID Catalogue ÷ pi SID (sigma City = 'Moscow' Supplier)) ⨝ Product)
```

Solution without using the division operator.

```
MoscowPIDs = sigma City = 'Moscow' Supplier

pi Item, Color (((pi PID Product - pi PID ((pi SID (MoscowPIDs)) ⨯ pi PID Product - pi SID, PID ((pi SID (MoscowPIDs)) ⨝ Catalogue))) ⨝ Product))
```

1. **Find all Moscow Suppliers' SIDs;**
2. **Compute all possible (SID, PID) pairs;**
3. **Subtract Actual Supplied PIDs by Moscow Suppliers;**
4. **Find PIDs with No Missing Pairsж**
5. **Join with Product to Get Item and Color**

## References
