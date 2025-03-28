**2025-03-20 15:41**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Lab Week 7 Questions

<details>
<summary>What Layer of TCP/IP Reference model was covered during the lecture?</summary>
Transport, Network.
</details>
<details>
<summary>What protocols of this layer do you know?</summary>
Transport - TCP, UDP.
Network - RIP, IP, BGP.
</details>
<details>
<summary>What is the difference between those protocols?</summary>
Congestion control. Reliable data transfer. Flow control. Transmission control. Sequence number for packets. Timeout control.
</details>
<details>
<summary>For what type of services would you use TCP?</summary>
Web page retrieval, large files download, email exchange.
</details>
<details>
<summary>For what type of services would you use UDP?</summary>
DNS resolution, video streaming and audio applications.
</details>
<details>
<summary>What are the possible ways of Error Detection?</summary>
checksum, Simple parity check, Two-dimensional parity check, Cyclic redundancy check.
</details>
<details>
<summary>What is a checksum?</summary>
A value that represents the number of bits in a transmission message.
</details>
<details>
<summary>Which TCP/IP layer is concerned with reliable end to end delivery of data?</summary>
Transport.
</details>
<details>
<summary>How does reliability of Transport Layer can be achieved?</summary>
Using Reliable Data Transfer protocol.
</details>
<details>
<summary>Do exist reliable channels or they can only make an illusion of the reliability?</summary>
The reliable channels are just illusion provided by transport layer. The reality is, communication channel on the network layer are not reliable.
</details>
<details>
<summary>What is RDT?</summary>
Reliable Data Transfer. Theoretical abstraction for illustrating reliable communication concepts. Its aim to provide an illusion of a 100% reliable communication channel.
</details>
<details>
<summary>What ACK control message means?</summary>
Receiver's feedback to Sender. ACK - positive acknowledgment. Data is received. Data is not corrupted.
</details>
<details>
<summary>What NAK control message means?</summary>
Data is received, but data is corrupted.
</details>
<details>
<summary>What is the main problem being solved at the Network layer of the TCP/IP reference model?</summary>
Host-to-host communication, package forwarding and routing.
</details>
<details>
<summary>What is routing in a Computer Network?</summary>
The determination of the most efficient path for data transferring from source host to destination host.
</details>
<details>
<summary>Up to which layer of TCP/IP reference model does router work?</summary>
Network layer.
</details>
<details>
<summary>What is Router functionality?</summary>
Forwarding and routing of data packets.
</details>
<details>
<summary>What is forwarding in Computer Networks?</summary>
The transmission of data packets from incoming link to the outgoing link.
</details>
<details>
<summary>Up to which layer of TCP/IP reference model does switch work?</summary>
Data Link Layer.
</details>
<details>
<summary>What is Switch functionality?</summary>
The packets forwarding.
</details>
<details>
<summary>What is the key purpose of Forwarding Table?</summary>
The packets forwarding.
</details>
<details>
<summary>What optimisation techniques are applied to optimise the structure of the Forwarding Table? (2 opt. techniques)</summary>
Address ranges, address prefix.
</details>
<details>
<summary>What is the address prefix?</summary>
The beginning of IP address.
</details>
<details>
<summary>What is TTL in terms of Network Packet?</summary>
Time-to-Live. The maximum number of routers, or hops, allowed to pass through.
</details>
<details>
<summary>What is the Control Plane and Forwarding Data Plane in Router architecture?</summary>
Control Plane determines the route data will take over a network. 
Forwarding Data Plane propagate packets table from input link to output link based on information from control plane.
</details>
<details>
<summary>What are Input Link functions in Router Architecture?</summary>
Store data from packets into its local buffer. De-encapsulation. 
</details>
