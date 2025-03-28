**2025-03-22 10:49**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## ER Model

> The ER Model is a fundamental framework for designing and visualizing databases using entities, attributes, and relationships. It helps simplify the understanding of complex databases. The graphical representation of the ER Model is known as an **ER Diagram**.


### What is an Entity?

> An entity is a real-world object that exists independently and possesses a unique identity.

In ER modeling, entities are depicted as rectangles. For example, in a database, entities could include `Student`, `Employee`, `Customer`, etc.

![](../attachments/Pasted%20image%2020250322105339.png)

 This circular paths attached to the rectangle represent attributes, which are properties or characteristics of the entity.

### Types of Entities

#### Strong Entity

A strong entity is one that exists independently. For example, a "Customer" can exist on its own in a database, having attributes like CustomerID, Name, and Address. These attributes uniquely each customer, making it a strong entity.

#### Weak Entity

A weak entity cannot exist independently and relies on a strong entity for its existence. For instance, an "Order" entity typically depends on a "Customer" entity. Without a customer, the order wouldn't make sense. Weak entities often have a partial key that, when combined with the key of a strong entity, uniquely identifies each instance.

### Entity Set

An entity set is a collection of similar types of entities. For instance, the `Customer` entity set would include all customers within a database. Each row in the entity set represents an individual entity.

![](../attachments/Pasted%20image%2020250322122626.png)

> [!NOTE]
> Though entity set refers to the table, in practical terms, both "entity set" and "entity" are often user interchangeably to refer to the table itself.


### Attributes

Attributes define the properties of characteristics of an entity. They are represented as oval connected to their respective entity rectangles.

![](../attachments/Pasted%20image%2020250322122805.png)

### Common Types of Attributes
- **Simple**: These attributes cannot be divided further. For example, `Age` is a simple attribute.
- **Composite**: Attributes that can be broken down into smallerparts. For instance, a `Name` attribute can be split into `First Name` and `Last Name`. 
- **Single-Valued**: Attributes that can hold only one value for each entity. For example, `StudentID` is single-value.
- **Multi-Valued**: Attributes that can have multiple values for each entity, such as `Phone Numbers` of a student.
- **Derived**: Attributes whose values can be derived from other attributes, like calculating `Age` from `Date of Birth`.
- **NULL**: Represents missing or unknown information for an attribute.









## References
[ER Model](https://nailyourinterview.org/interview-resources/dbms/er-model)