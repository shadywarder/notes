**2025-02-27 21:37**
**Tags:** [s25](../3%20-%20indexes/s25.md) [networks](../2%20-%20tags/networks.md) [university](../3%20-%20indexes/university.md)

## Networks Characteristic
### Scale (geographical)
**PAN:** Personal Area Network - Connects electronic devices within a user's immediate area.
**LAN:** Local Area Network - One physical location, e.g. building, office, or home.
**CAN:** Campus area network - Spans a limited geographic area.
**MAN:** Metropolitan Area Network - Multiple buildings or entire city.
**WAN:** Wide Area Network - Interconnection of MANs.

![](../attachments/Pasted%20image%2020250227214127.png)

![](../attachments/Pasted%20image%2020250227214653.png)
 

| Criteria    | PAN                | LAN             | CAN      | MAN               | WAN                  |
| ----------- | ------------------ | --------------- | -------- | ----------------- | -------------------- |
| Technology  | Bluetooth, Zigbeen | Ethernet, Wi-Fi | Ethernet | DQDB,ATM          | Leased Line, Dial-Up |
| Range       | 1-100 m            | Up to 2 km      | 1-5 km   | 5-50 km           | Above 50 km          |
| Speed       | Very High          | Very High       | High     | Average           | Low                  |
| Ownership   | Private            | Private         | Private  | Private or Public | Private or Public    |
| Maintenance | Very Easy          | Easy            | Moderate | Difficult         | Very Difficult       |

### Transmission Medium
Optical, Coaxial, Radiowaves, Infrared

![](../attachments/Pasted%20image%2020250227214859.png)

### Protocols/Technologies
LAN: **Ethernet**
MAN: **Distributed Queue Dual Bus**
WAN: **Cable Mode, Digital Subscriber** or **Leased Line**
BAN, PAN: **Bluetooth, Wi-Fi**

### Network Topology

> The layout of computer cables and other network devices (e.g. hosts, routers, switches, bridges, etc.)

![](../attachments/Pasted%20image%2020250227220721.png)

**Ring Topology:** Every node is connected to two neighboring nodes.
**Star Topology:** Every node is connected to a switch or similar device, which supports message exchange between any two nodes.
**Full Mesh Topology:** Every node is connected to all other nodes directly.
**Bus Topology:** Data packets are exchanged via a shared communication bus.
**Tree Topology:** Data packets are exchanged via a shared communication bus.

#### Bus vs. Star
**Physical Structure & Data Transmission**
- **Bus:** All devices are connected to a single central cable (the "bus"). Data travels along this shared medium, and every device receives the signal. Only the intended recipient processes the data; others ignore it.
- **Star:** Devices connect to a central switch (or hub). The switch acts as a traffic controller, forwarding data **only** to the intended recipient. No shared medium exists - each connection is point-to-point.

**Security Implications**
- **Bus:** Less secure. Since all data is broadcast on the shared bus, any device can eavesdrop on traffic meant for others (e.g., via packet sniffing).
- **Star:** More secure. The switch isolates traffic between devices, reducing eavesdropping risks (unless the switch itself is compromised).

**Role of the Central Device**
- **Bus:** No central device - data flows directly over the shared cable.
- **Star:** The switch intelligently manages connections, enabling simultaneous communication and minimizing collisions.

#### Speed: Ring vs. Star
**Ring:**
- Devices from a closed loop. Data travels in one direction (unidirectional) or both (bidirectional), passing through each node until it reaches the destination.
- **Speed Limitations:** In token-based rings (e.g. Token Ring), devices wait for a "token" to transmit, causing latency in large networks. Bandwidth is shared, leading to congestion.

**Star:**
- A central switch enables full-duplex communication (devices can send/receive simultaneously). Modern switches support high-speed dedicated links (e.g., Gigabit Ethernet) and handle multiple connections at once.
- **Speed Advantage:** Star is generally faster and more scalable. Switches reduce collisions, prioritize traffic, and support higher bandwidth.

#### Encryption Needs in Ring vs. Star
**Ring:**
- Data passes through multiple intermediate nodes to reach the destination. Even "non-neighbor" devices can intercept traffic, making encryption critical to protect confidentiality.

**Star:** 
- The switch directs data only to the target device, reducing exposure. However, encryption is still essential because:
	- A compromised switch could traffic.
	- External attacks (e.g., ARP spoofing) can bypass the switch's isolation.

### Performance Metrics
**Bandwidth** (bits/sec) - max. transfer rate;
**Throughput** (bits/sec) - actual/average transfer rate;
**Packet Loss, Error bit late**

`ping` - command to check connection validity, ratio of lost packets, other.

### Proprietary Type
**Open systems:** OSI-compliant, standard protocols;
**Proprietary systems:** private technologies and protocols.


| Network Characteristic | Examples                                          |
| ---------------------- | ------------------------------------------------- |
| Scale (geographical)   | PAN, LAN, MAN, WAN                                |
| Transmission Medium    | Optical, Coaxial, Radiowaves, Infrared            |
| Protocols/Technologies | Ethernet, Wi-Fi, Bluetooth                        |
| Topology               | Bus, Ring, Star, Hierarchical, Mesh               |
| Performance Metrics    | Bandwidth, Throughput, Packet Loss and Error rate |
| Proprietary Type       | Open and Proprietary systems                      |

## References