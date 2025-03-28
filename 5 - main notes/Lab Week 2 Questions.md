**2025-03-18 20:05**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Lab Week 2 Questions

<details>
<summary>What is the difference between LAN and WAN?</summary>
Range, speed, maintenance.
</details>
<details>
<summary>What is the physical network topology?</summary>
The layout of cables and other network devices.
</details>
<details>
<summary>What is the difference between physical and logical topologies?</summary>
Actual data flow. May differ from physical topology e.g. due to the admin rights.
</details>
<details>
<summary>What types of topologies do you know?</summary>
Ring, Star, Mesh, Full-Mesh, Bus, Tree, Hybrid.
</details>
<details>
<summary>Describe Ring topology</summary>
Two adjacent nodes connected to each other.
</details>
<details>
<summary>Describe Star topology</summary>
Every node is connected to the switch or similar device, which supports messages exchange between any two nodes.
</details>
<details>
<summary>Describe Bus topology</summary>
Data packets are exchanged via shared communication bus.
</details>
<details>
<summary>Describe Tree topology</summary>
Data packets are exchanged via shared communication bus.
</details>
<details>
<summary>What is the difference between bandwidth and throughput?</summary>
Bandwidth - max. transfer rate. Throughput - actual transfer rate.
</details>
<details>
<summary>What are the purposes of Internet Service Provider?</summary>
The allocation of IP addresses, domain names registration, web-hosting. Connection to Internet.
</details>
<details>
<summary>Why Download and Upload speeds are different?</summary>
Since most users spend much more time downloading than they do uploading, high speed Internet providers have designed their systems to give priority to downloading.
</details>
<details>
<summary>Which Application Layer protocols do you know?</summary>
DHCP, DNS, HTTP, SMTP, POP, IMAP, FTP.
</details>
<details>
<summary>What is the purpose of HTTP protocol?</summary>
Web pages access.
</details>
<details>
<summary>What is the purpose of FTP protocol?</summary>
Files download/upload (large).
</details>
<details>
<summary>How many connection types there are in FTP protocol?</summary>
Control (exchange commands and replies) and Data (file transfer itself).
</details>
<details>
<summary>How many connection types there are in HTTP protocol?</summary>
Request and response.
</details>
<details>
<summary>What are the steps of conversation flow in HTTP protocol?</summary>
Request to establish connection -> Agreement (or denial) -> Sending the request (e.g. GET file location) -> Fulfilling a client request or returning an error code -> Analyzing the response, closing the connection -> Closing the connection
</details>
<details>
<summary>What are the steps of conversation flow in FTP protocol?</summary>
Control: Request to establish FTP connection -> Welcome message/request for identity -> Username identification -> Request for password -> Password transfer -> Authentication confirmation -> Request for file to download/upload -> Confirmation of file existence, access rights, etc. -> Starting file transfer through a newly created Data Connection -> Opening a data connection
Data: Specification of file to download (name, location, etc.) -> Opening data connection, starting to upload file to a client -> Close data connection after transfer -> Closing control connection
</details>
<details>
<summary>What is the difference between persistent and non-persistent connections?</summary>
Non-persistent HTTP: At most one object sent over TCP connection. Connection then closed. Downloading multiple objects required multiple connections
Persistent HTTP: Multiple objects can be sent over a single TCP connection between the client and the server.
</details>
<details>
<summary>What is the difference between stateful and stateless connections?</summary>
Stateful: server maintains information about past client requests.
</details>
<details>
<summary>What is the difference between URL and URI?</summary>
Actually, URL is a subset of URI.
</details>
