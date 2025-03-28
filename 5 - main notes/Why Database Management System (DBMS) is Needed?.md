**2025-03-22 10:23**
**Tags:**

## Why Database Management System (DBMS) is Needed?

### The Importance of DBMS

![](../attachments/Pasted%20image%2020250322102514.png)

In the last chapter, we learned that rows of data are stored in disk blocks, and when a particular row is needed, the entire block containing that rows is loaded into RAM. This is a complex and tedious task to manage directly, which is where the Database Management System (DBMS) comes into play.

The DBMS acts as a bridge, simplifying data storage and retrieval. It handles storing data on the disk, managing memory when data is needed, and using data structures to local specific disk blocks where rows are stored. As users, we interact with the DBMS using SQL (Structured Query Language), which is human-readable and makes database interactions intuitive.

### Key Characteristics of DBMS

#### Minimizing Redundancy

One of the primary goals of a DBMS is to minimize data redundancy. Redundant data - storing the same information in multiple places - can lead to inconsistencies and unnecessary storage usage. DBMS uses techniques like normalization to ensure data is only stored and referenced where needed, maintaining consistency across the database.

#### Security 

DBMS provides robust security mechanisms to protect data from unauthorized access, ensure integrity, and maintain confidentiality. Here are some essential aspects of database security:

#### Access Control

![](../attachments/Pasted%20image%2020250322103255.png)

DBMS uses authentication and authorization to control access. Users must provide credentials (like usernames and passwords) to access the database. Once authenticated, authorization settings determine what actions users can perform and what data they can access, based on roles and privileges.

```sql
CREATE ROLE 'role_name';
GRANT SELECT, INSERT ON database.* TO 'role_name';
GRANT 'role_name' TO 'username'@'ip_address';
```

#### Encryption

Encryption is a critical feature for securing sensitive data. It can protect data at rest (stored in the database) and in transit (moving between client and server). For example, using SQL encryption functions can secure sensitive information like credit card numbers.

```sql
CREATE TABLE customer_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    encrypted_credit_card VARBINARY(255)
);

INSERT INTO customer_data (name, encrypted_credit_card) VALUES
    ('John Doe', AES_ENCRYPT('123456789', 'encryption_key'));

SELECT id, name, AES_DECRYPT(encrypted_credit_card, 'encryption_key') AS decrypted_credit_card
FROM customer_data;
```

For data in transit, similar to how web applications uses HTTPS for secure communication, MySQL can use SSL/TLS to secure the connection between the client and server.

#### Auditing and Logging 

![](../attachments/Pasted%20image%2020250322103824.png)

DBMS systems can maintain audit logs to track database activities like login attempts, data changes, and access control modifications. This helps detect security breaches, trace user activities, and meet compliance requirements.

#### Backup and Recovery

Regular database backups are essential for data recovery in case of accidental deletion, corruption, or security incidents. DBMSs support various backup strategies, such as full backups, incremental backups, and transaction log backups, ensuring data availability and integrity.

#### Concurrency Control

In environments where multiple users and applications access the database simultaneously, concurrency control are vital. These ensure that transactions are executed without interfering with each other, maintaining the ACID properties (Atomicity, Consistency, Isolation, Durability).

#### Data Consitency

Maintaining consistent and accurate data across the database is crucial. DBMS ensures data consistency using various methods like keys, locks, and adherence to ACID properties. 

#### Transaction Management

A transaction is a sequence of operations performed as a single logical unit of word. DBMS supports transaction management to ensure that all operations withing a transaction are completed successfully, or none at all, maintaining data integrity.
## References
[Why Database Management System (DBMS) is Needed](https://nailyourinterview.org/interview-resources/dbms/why-dbms-is-needed/)