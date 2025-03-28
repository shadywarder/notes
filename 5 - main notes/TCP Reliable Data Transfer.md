**2025-03-20 11:05**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## TCP Reliable Data Transfer

### Transport Layer Service 

![](../attachments/Pasted%20image%2020250320110636.png)

### Network Layer: Software/Hardware Interface

![](../attachments/Pasted%20image%2020250320110730.png)

![](../attachments/Pasted%20image%2020250320110852.png)

**An unreliable channel (reality)**
- Data packets can be corrupted;
- Data packets can be lost;
- The order of packets can be incorrect.

![](../attachments/Pasted%20image%2020250320111015.png)

### Reliable Data Transfer (RDT) Protocol

![](../attachments/Pasted%20image%2020250320111111.png)

- Theoretical abstraction for illustrating reliable communication concepts;
- RDT design is a fundamental theoretical problem;
- Concepts are not limited to Transport layer and adjustable to others;
- Its aim is to provide an illusion of a 100% reliable communication channel (e.g. through socket libraries)

![](../attachments/Pasted%20image%2020250320111315.png)

### RDT Conceptual Interface Functions

![](../attachments/Pasted%20image%2020250320111413.png)

### RDT Sender Side FSM

![](../attachments/Pasted%20image%2020250320111534.png)

Transition trigger - an action initiating the transition;
Transition actions - actions (function calls) to be executed during the transition process.

![](../attachments/Pasted%20image%2020250320111925.png)

Receiver provides feedback to Sender through control messages: ACK and NAK
**ACK** - positive acknowledgment:
- Data is received;
- Data is not corrupted (corresponds to checksum).

**NAK** - a negative acknowledgment:
- Data is received, but
- Data is corrupted (corresponds to checksum)

![](../attachments/Pasted%20image%2020250320112209.png)

![](../attachments/Pasted%20image%2020250320113051.png)

### RDT 2.0 Protocol Implementation: FSM Design

![](../attachments/Pasted%20image%2020250320113149.png)

### RDT 3.0 Protocol Implementation: FSM Design

