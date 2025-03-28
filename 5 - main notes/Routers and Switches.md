**2025-03-20 13:15**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Routers and Switches

### Routing in a Computer Network

![](../attachments/Pasted%20image%2020250320131746.png)

**Routing** - the determination of an efficient path for transferring data packets from a source to a destination host.

### Forwarding in a Computer Network

![](../attachments/Pasted%20image%2020250320131813.png)

**Forwarding** - the process of transferring data packets from an incoming to an outgoing link withing a single router.

![](../attachments/Pasted%20image%2020250320131852.png)

### Forwarding Problem: Which output link to choose for a given data packet?

![](../attachments/Pasted%20image%2020250320131951.png)

![](../attachments/Pasted%20image%2020250320132004.png)

### Forwarding Table: mapping of destination address to router output links

![](../attachments/Pasted%20image%2020250320132233.png)

Forwarding decision steps:
1. a router first extracts the destination address from the header of an arrived packet, and then
2. determines an output link by using a local forwarding table.

Further details on forwarding table:
- Its configuration drastically affects a network performance;
- It is defined by a specific routing algorithm (OSPF, RIP, BGP, or other);
- It is update periodically, to reflect changes in a network topology (by routing protocol messages).

![](../attachments/Pasted%20image%2020250320132621.png)

### Forwarding Table Style: The Principle of Address Ranges

How to fit a huge number of IP addresses into a forwarding table?

![](../attachments/Pasted%20image%2020250320132920.png)

By specifying address ranges, we do not need to have entry for each possible address.

### Forwarding Table Style: The Principle of Address Prefixes

![](../attachments/Pasted%20image%2020250320133027.png)

Address prefix - the beginning part of IP addresses
Forwarding table contains address prefixes (the beginning part of addresses)
The longest prefix match rule - to choose a table entry with the longest prefix matching.

### Router Architecture

![](../attachments/Pasted%20image%2020250320133421.png)

![](../attachments/Pasted%20image%2020250320133446.png)

### Input Link Functions

![](../attachments/Pasted%20image%2020250320133802.png)

1. Storing arriving data packets into its local buffers (physical link termination function);
2. Data extraction from packet header (de-encapsulation);
3. Determination of appropriate output links;
4. Verification of packets correctness (typically limited to packet headers, by using checksum method);
5. Control of Time-to-Live (the maximum number of routers, or hops, allowed to pass through);
6. Collecting statistics;
7. Other functions.

### Lookup Function at Input Links

Time-to-Live. The maximum number of routers, or hops, allowed to pass through.

![](../attachments/Pasted%20image%2020250320133838.png)

Stages of Lookup:
- Packet is taken from an input buffer;
- Processor extracts address from packet header, and
- Defines a corresponding output link number from a forwarding table.

![](../attachments/Pasted%20image%2020250320134009.png)

Possible optimization for lookup function:
- Each input link has its own dedicated processor and
- A shadow copy of a forwarding table

### Types of Switching Fabric

![](../attachments/Pasted%20image%2020250320134200.png)

Switching Fabric function - to propagate data packets from input to output ports (connection)
Types of switching fabric:
- A shared memory
- A communication bus
- An interconnection network

![](../attachments/Pasted%20image%2020250320134453.png)

### Routing Processor (CPU)

![](../attachments/Pasted%20image%2020250320134515.png)

Routing Processor functions:
- Maintenance of forwarding tables;
- Execution of routing protocols;
- Other management functions.

### Output Link Functions

![](../attachments/Pasted%20image%2020250320135028.png)

Output Link functions: 
- To store packets received from a switching factory into a local buffer;
- To encapsulate necessary data into packet headers;
- To transmit packets from a buffer into a physical link.

### Packet Scheduling in a Router

![](../attachments/Pasted%20image%2020250320135156.png)

### Performance Bottlenecks in a Router Architecture

Some performance bottlenecks:
- Limited capacities of input/output line buffers;
- Speed of switching fabric;
- Speed of transmission at output links;
- Configuration of a forwarding table;
- Search time in forwarding table

### Comparison: Routers vs. Switches

![](../attachments/Pasted%20image%2020250320135417.png)


| Criteria                              | Router                                                           | Switch (Bridge)                                     |
| ------------------------------------- | ---------------------------------------------------------------- | --------------------------------------------------- |
| Operation Layer of the Protocol Stack | Network Layer                                                    | Data Link Layer                                     |
| Primary Objective                     | Forwarding and routing (Implementation of routing protocols)     | Forwarding only (Simple interconnection of devices) |
| Addressing Principles                 | IP addresses, routing tables with IP prefixes                    | MAC addresses, lookup tables                        |
| Target Network Scale                  | LAN, MAN, WAN                                                    | LAN only                                            |
| Connection Types                      | Wired and wireless                                               | Wired only                                          |
| Error Checking of Incoming Packets    | Yes: single-parity check, two-dimensional parity check, checksum | Yes: Cyclic Redundancy Check (CRC)                  |
| Security Mechanisms                   | Nono                                                             | None                                                |
| NAT support                           | Yes, for NAT-enabled routers                                     | None                                                |
| DHCP support                          | Yes, for DHCP-enabled routers                                    | None                                                |

![](../attachments/Pasted%20image%2020250320135514.png)

![](../attachments/Pasted%20image%2020250320135733.png)

![](../attachments/Pasted%20image%2020250320135817.png)

![](../attachments/Pasted%20image%2020250320135859.png)

![](../attachments/Pasted%20image%2020250320135943.png)

NAT (Network Address Translation) - the replacement of a private IP address with an IP address of a gateway router.