**2025-03-22 10:00**
**Tags:** [dbms](../2%20-%20tags/dbms.md)

## Understanding How Databases Store Data on Disk

### What is a Database?

A database in a systematically organized collection of related data, typically stored electronically within a computer sysitem.

Databases are structured into tables, with each table defined by columns (fields) specifying data types and rows (records) containing the actual data.

![](../attachments/Pasted%20image%2020250322100525.png)

In non-relational databases, data is stored in collections and documents rather than traditional tables and rows. 

### How Does a Database Store Data on Disk?

When working with a database management system (DBMS), it's important to understand how data is physically stored on disk. While we interact with data in a structured, tabular format, the underlying storage mechanism involves multiple layers and components.

#### Disk Structure: Tracks, Sectors, and Blocks

![](../attachments/Pasted%20image%2020250322100829.png)

A disk, whether it's a Hard Disk Drive (HDD) or a Solid-State Drive (SSD), server as secondary memory. Here's how it's organized:

- **Tracks**: Concentric circular paths on the disk surface.
- **Sectors**: Pie-shaped divisions within each track.
- **Blocks**: The smallest units of storage, defined at the intersection of tracks and sectors. Blocks are the basic units of data transfer to and from the disk.

### Storing Table Rows in Disk Blocks

Let's consider a simplified scenario of storing a row's data:
- **Integer Field**: 4 bytes
- **String Field**: Assume 60 bytes.
- **Another Integer Field**: 4 bytes.

Each row might occupy around 68 bytes in total.

If a disk block can store 258 bytes, approximately 3 rows could fit into a single block. When more rows are added to the table, they are stored in additional blocks, ideally placed contiguously to enhance read and write performance.

> [!NOTE]
> Typically, a disk block can store around 4kB of data.

### Data Operations and Memory Management

When an operation is performed on a specific row (e.g., row 2) the entire block containing rows 1, 2 and 3 is loaded into RAM for processing. This approach ensures efficient data retrieval and manipulation by minimizing disk I/O operations.

> [!NOTE]
> Databases typically store data in a structured manner, with entire rows stored consecutively to optimize access.

## References
[Understanding How Databases Store Data on Disk](https://nailyourinterview.org/interview-resources/dbms/database-internals)