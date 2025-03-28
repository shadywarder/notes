**2025-03-19 14:56**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Lab Week 3 Questions

<details>
<summary>What is the difference between stateful and stateless connections?</summary>
Stateful: server maintains information about previous user requests.
Stateless: the opposite.
</details>
<details>
<summary>What is the difference between persistent and non-persistent connections?</summary>
Non-persistent: At most one object sent over TCP connection. Connection then closed. Multiple objects required multiple connections. Persistent: Multiple objects can be sent over single TCP connection.
</details>
<details>
<summary>What are two types of connections of FTP protocol?</summary>
Control (user authorization and authentication). Data (file transfer itself).
</details>
<details>
<summary>What is the difference between HTTP server and WEB server terms?</summary>
HTTP server - a software process running (at a specific port) on a server hardware machine, which understands and serves HTTP requests. WEB server - the hardware machine itself (server) with all its software, hard drives, databases, etc.
</details>
<details>
<summary>What is cookies mechanism and its primary purpose?</summary>
The cookie is just a small text file with client and server identifiers. It needs to be set using Set-Cookie header from the response at the first time and then specified in the Cookie header in the further requests. The server will perform a set of certain actions corresponding to this client.
</details>
<details>
<summary>Which header is used in a request to a server to transfer stored cookies?</summary>
Cookie
</details>
<details>
<summary>Which header is used in a response to a client to write cookies?</summary>
Set-Cookie
</details>
<details>
<summary>What is a Round Trip TIme?</summary>
RTT: round trip time for a small packet to travel from client to server and back.
</details>
<details>
<summary>Between servers and clients - who can initiate communication first?</summary>
Clients.
</details>
<details>
<summary>What is the difference between Client Server and Peer-to-Peer architectures?</summary>
CS - Nodes are divided into clients (active) and servers (passive). PTP - Every node acts as a client and a server simultaneously. CS - Dominant architecture. PTP - Less used. CS - Simpler (centralized algorithms). PTP - More complex (distributed algorithms). CS - Likely to decrease with the number of peers. PTP - Likely do increase with the number of peers. CS - A single point of a failure - a centralized server. PTP - No single point of failure. CS - More expensive. PTP - Cheaper (due to absence of a server). CS - Other, except large files distr. and hierarchical databases. PTP - Large files distribution and distributed databases.
</details>
