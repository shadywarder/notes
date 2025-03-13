**2025-03-05 09:46**
**Tags:** [university](../3%20-%20indexes/university.md) [s25](../3%20-%20indexes/s25.md) [dbms](../2%20-%20tags/dbms.md)

## DBMS. Database design. ER model
**Data** is collection of facts in a raw or unorganized form (e.g., number or characters).
**Database** is a collection of related data.

### Database management system
**Database management system (DBMS)** is a computer system that helps to create and maintain a database with large amount of data. DBMS is used for defining, constructing, manipulating, and sharing databases among various users and applications. The primary goal of DBMS is to provide a way to store and retrieve database information that is both convenient and efficient.

#### DBMS Advantages over file-processing system:
- **Data redundancy and inconsistency**
	- different files have different structures;
	- programs are written in different programming languages;
	- files can be duplicated.
- **Difficulty in accessing data**
	- in file systems, it is inconvenient and inefficient to work with data.
- **Data isolation**
	- In file systems, it is difficult to combine data of different formats.
- **Integrity problems**
	- In file systems, it is difficult to ensure that integrity constraints are respected (for example, that a numeric field necessarily contains only a number).
- **Atomicity problem**
	- Data operations must be performed either completely or not at all. In file systems, if the system crashes in the middle of an operating, the data may end up in a partially updated state, leading to errors.
- **Concurrent-access**
	- In file systems, simultaneous access to data by multiple users may lead to errors.
- **Security issues**
	- In file systems, it is difficult to implement security restrictions (for example, access rights).


#### Minimum requirements for DBMS:
1. Structured Data Storage
2. Data Manipulation Capabilities
3. Querying Support
4. Data Integrity Enforcement (uniqueness of primary keys, link integrity, specified limitations (e.g. age >= 0))
5. Concurrency Control
6. Security Features
7. Backup and Recovery Mechanisms
8. Scalability

### Database Design
**Data model** is an abstract representation that describes how data is organized, how it relates to each other, and how it corresponds to the features of real-world objects.
**Database model** is a specific type of data model that defines the logical structure of a database and specifies that way data is organized (for example, **tables** in relational model or **objects** in object-based model).
#### Requirements Engineering
- defining data that needs to be stored
- understanding what applications will run on that data
- analyzing the frequency of operations to design a productive system
- clarifying the needs of the users

#### Data Abstraction
- **Conceptual Level**
	- describes entities and connections between them;
	- creating Entity-Relationship model (ER model);
	- representation is easy to understand for developers and regular user alike.
- **Logical Level**
	- choosing a specific DBMS, columns, more restrictions.
- **Physical Level**
	- consider the expected workloads that the database must be able to handle;
	- **indexes:** create indexes to speed up data searching;
	- **clustering:** grouping tables for quick access;
	- **schema redesign:** changes to data structure to improve performance.

### Entity-Relationship model
#### Main components
**Entity:** corresponds to some object.
**Relationship:** corresponds to a link between entities.
**Attribute:** a property that describes an entity.

![](../attachments/Pasted%20image%2020250305101106.png)

#### Attributes
Attributes can be:
- **atomic** (name) or **composite** (address)
- **stored** (Roll_no) or **derived** (age, can be derived from DOB)
- **multivalued** (Phone_No, can be many)

![](../attachments/Pasted%20image%2020250305101258.png)

> [!NOTE]
> If some attribute exists in multiple entity types, you can make it independent entity type to avoid redundancy and improve normalization.

#### Key
Each entity has a **key** - a set of attributes uniquely identifying an entity.
In ER diagrams, keys are indicated by an underscore (for example, <u>Stu_ID</u>) 

![](../attachments/Pasted%20image%2020250305101535.png)

**Superkey** is any set of attributes that uniquely identifies an entity. A superkey may include unnecessary attributes.
**Candidate Key** is a minimal superkey that doesn't contain unnecessary information.
**Primary Key** is one of the candidate keys that is selected by the database designer to be used as the main key of the table.

![](../attachments/Pasted%20image%2020250305101720.png)

### Relationships
#### Participation
The **participation constraint** specifies whether the existence of an entity depends on its being related to another entity via the relationship type:
- **Total Participation** indicated by two lines and means that entity cannot exist without the relationship (student can't exist without professor)
- **Partial Participation** indicated by one line and means that entity can exist without relationship (professor can exist without students)

![](../attachments/Pasted%20image%2020250305102322.png)

#### Cardinality Rations
There are 4 type of cardinality ratios:
- one-to-one (1:1)
- one-to-many (1:N)
- many-to-one (N:1)
- many-to-many (N:M)

#### Strong and Weak Entities
- **Strong Entity** is an entity that has its own unique key
- **Weak Entity** does not have its own key and identified through a relationship with another entity

#### Higher-Degree Relationships
Sometimes it's convenient to use ternary relationships instead of binary ones.

![](../attachments/Pasted%20image%2020250305103032.png)

![](../attachments/Pasted%20image%2020250305103037.png)

#### Formatting Principles
- **Entity names** are in singular form and in uppercase letters, usually noun
- **Relationship names** are in uppercase letters, usually verb
- **Attribute names** have their initial letter capitalized and usually noun
- ER diagram should be readable from the left to right and from top to bottom, which is especially useful for representing relationships.

![](../attachments/Pasted%20image%2020250305103307.png)

## References