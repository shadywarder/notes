**2025-03-19 11:01**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Client-Server and Peer-to-Peer Applications. Network Calculus

### Network Server Characteristics

![](../attachments/Pasted%20image%2020250319110346.png)

**Two types of network nodes:**
Servers (passive) - to provide services (e.g. an HTTP server uploads a web page content);
Clients (active) - to request those services (e.g. an HTTP browser downloads and demonstrates a web page).

**Some types of servers:**
- Web Servers: to provide web pages;
- Mail Servers: to store/exchange emails between clients;
- FTP Servers (or simply File Servers): to support operations with files;
- Database Servers: to fulfill database queries;
- DHCP (Dynamic Host Configuration Protocol) servers: to allocate IP addresses to hosts;
- DNS servers: to determine IP addresses of URLs.

Network server - a (remote) computer providing services to network clients:
- Provides a high speed data upload;
- Has high requirements to hardware;
- Runs a specific operating system (Linux or Windows Server, other choice - more rarely);
- Reliable and resistant to failures/attacks;
- Supports simultaneous connections to multiple clients;
- Consumes a lot of power leading to high operat. costs.

### Client-Server Architecture: Some Performance Metrics

![](../attachments/Pasted%20image%2020250319111356.png)

![](../attachments/Pasted%20image%2020250319112613.png)

![](../attachments/Pasted%20image%2020250319112630.png)

![](../attachments/Pasted%20image%2020250319112639.png)

![](../attachments/Pasted%20image%2020250319112701.png)

### Sample Use Case: the distribution of a file over a network

![](../attachments/Pasted%20image%2020250319112850.png)

**Network server (e.g. FTP server):** 
- Provides high upload and download speed;
- Upload and download capacities are however limited.

![](../attachments/Pasted%20image%2020250319113003.png)

![](../attachments/Pasted%20image%2020250319113213.png)

1. File is divided into parts;
2. Each part is downloaded independently by different peers, over different communication channels;
3. Peers exchange parts of the file, by using communication channels between them, until all peers get all file parts.

### Client-Server Architecture: Lower Bound for a File Distribution Time

![](../attachments/Pasted%20image%2020250319113439.png)

### Peer-to-Peer Architecture: Lower Bound for a File Distribution Time

![](../attachments/Pasted%20image%2020250319114912.png)

![](../attachments/Pasted%20image%2020250319115111.png)

### File Distribution Time Trends: Peer-to-Peer vs. Client-Server Models

![](../attachments/Pasted%20image%2020250319115148.png)

###  Comparison: Client-Server vs. Peer-to-Peer Architecture for Network Applications

![](../attachments/Pasted%20image%2020250319115434.png)

![](../attachments/Pasted%20image%2020250319115453.png)

### Achievable Lower Bound for a File Distribution Time: Client-Server Case

![](../attachments/Pasted%20image%2020250319115822.png)