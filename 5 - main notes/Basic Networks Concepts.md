**2025-01-24 23:28**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)
 
## Basic Networks Concepts

### Communication Channel Characteristics

![](../attachments/Pasted%20image%2020250124234015.png)

**Channel characteristics:**
- Transfers data;
- Wired or wireless;
- Emposes transfer delay;
- Bounded throughput;
- Can corrupt and lose data.

### Network Interface Controller (NIC)

![](../attachments/Pasted%20image%2020250124234228.png)

**Network Interface Card (NIC) characteristics:**
- To transmit (put) data (of a binary format) into a network channel;
- To take data from a network channel;
- Emposes a "transmission delay", when transmitting or receiving data (it is different from a "transfer delay")

### Data Transfer Principles
**There are several basic principles for a data transfer:**
- Data is divided into small blocks - "packets";
- Every packet is transferred independently;
- The bitsize of a packet depends on a specific protocol.

**Communication Protocol** - the agreement ("protocol") on technical communication details between network nodes.
**Examples: HTTP, SMTP, IMAPS, VoIP, etc.**

**Communication Protocol purpose:** 
- To schedule nodes for data sending;
- To define an exchanged data format;
- Other technical details.

### Communication Protocols

![](../attachments/Pasted%20image%2020250124235053.png)

![](../attachments/Pasted%20image%2020250124235112.png)

![](../attachments/Pasted%20image%2020250124235131.png)

![](../attachments/Pasted%20image%2020250124235218.png)

![](../attachments/Pasted%20image%2020250124235254.png)

### TDM Communication Protocol (Time Division Multiplexing)

![](../attachments/Pasted%20image%2020250124235424.png)

A **Point-to-Point Network** is a private data connection securely connecting two or more locations for private data services. A Point-to-Point Network is a closed network data transport service which does not traverse the public Internet and is inherently secure with no data encryption needed.

### Point-to-Point and Multi-Point Communication

![](../attachments/Pasted%20image%2020250125014131.png)

**Broadcast communication:**
1. Message from one host is sent all others;
2. Each host, when receiving a message, checks its destination address;
	1. It reads a message, if it destinated to it;
	2. Otherwise, it discards a message.

**Multiple problems are raised in case of Multi-Point case, including:**
- Packet routing algorithms;
- Network security;
- Others.

### Terminology List

![](../attachments/Pasted%20image%2020250125014730.png)

### Key Network Components
**Hosts:** end devices exchanging data.
**Link:** device to transmit data between adjacent nodes.
**Router:** device to forward/route data.
**Source Host:** sends data.
**Destination Host:** receives data.
**Packet:** A block of data of predefined size.
**Routing/Forwarding:** packets across a network.
**Router Interface:** it helps to connect to several host systems.
**Routing/Forwarding packets:** Forwards packet between interfaces.
**Router-like Devices:**
- Switch
- Bridge
- Hub
- WiFi Access Point
- Repeater
**Network Address:** Unique identifier for a hosts.
**Address Types:**
- **Media Access Control (MAC) address (e.g. `00:1b:63:84:45:e6`)** 
	Burned-in into a network interface card.
- **Internet Protocol (IP) address (e.g. `192.158.1.38`)**
	Assigned dynamically, change over time.
	- **IP version 4 (IPv4)**, e.g. `192.0.2.146` (Lack of these addresses)
	- **IP version 6 (IPv6)**, e.g. `2001:0db8:85a3:0000:0000:8a2e:0370:7334` (A new standard, but not widely adopted)

![](../attachments/Pasted%20image%2020250125020139.png)

### Network Organization
**Network  Core:** Intermediate routers and other network devices, providing communication between hosts.
**Network Edge:** Network hosts, initiating data exchange over a network.
