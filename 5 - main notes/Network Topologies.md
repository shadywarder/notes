**2025-03-10 14:55**
**Tags:** [networks](../2%20-%20tags/networks.md)

## Network Topologies
Network topology refers to the arrangement of different nodes (devices) in a computer networks. The choice of topology affects the performance and scalability of the network. Let's explore some common network topologies.

### Bus Topology

![](../attachments/Pasted%20image%2020250310145728.png)

In a bus topology, all devices are connected to a single central cable known as the "bus". Each device connects to the bus using a drop cable or tap connector. Data sent by any device travels along the bus in both directions, but only the intended recipient processes the data while others ignore it.
- If device A wants to send data to device B, it sends the data onto the bus, which travels in both directions until it reaches device B.
- Devices in a bus topology shares the same communication medium, which means data collisions can occur if two devices transmit simultaneously. Collisions detection protocols like CSMA/CD (Carrier Sense Multiple Access with Collisions Detection) help manage these collisions.

#### Advantages
1. Simple and inexpensive to set up since it requires minimal cabling.
2. Easy to extend by adding new devices directly to the bus.

#### Disadvantages
1. A single fault in the main cable can disrupt the entire network.
2. Not suitable for large networks with high data traffic, as collisions can become frequent, degrading performance.

### Ring Topology

![](../attachments/Pasted%20image%2020250315134414.png)

In a ring topology, devices are connected in a circular loop, with each device linked to two neighboring devices, forming a closed loop. Data travels around the ring in one direction, passing through each device until it reaches its destination.
- If device A sends data, it travels through each device in sequence until it reaches device B.
- Some ring networks use a token-passing protocol, where a special data packet called a token circulates around the ring. Only the device holding the token can send data, preventing data collisions.

#### Advantages 
1. Suitable for networks with a small number of devices and moderate data traffic.
2. Predictable performance due to the orderly data transmission method.

#### Disadvantages 
1. A failure in any device or connection can break, leading to network failure.
2. Unidirectional data flow can make the network slow and inefficient.

### Star Topology

![](../attachments/Pasted%20image%2020250315154137.png)

In star topology, each device in the network is connected to a central device, such as a hub or switch, using individual cables. These connections resemble the shape of a star.
- When a device wants to communicate with another device, it sends data to the central device.The central device then forwards the data to the intended recipient.
- If the central device is a hub, it broadcasts the data to all devices, whereas a switch directs the data only to the specific destination device.

#### Advantages
1. Easy to set up, manage, and scale. Each device connects directly to the central hub or switch.
2. Better performance compared to bus or ring topologies due to efficient data management.

#### Disadvantages
1. The network's reliability depends on the central device; if it fails, the entire network becomes inaccessible.
2. Requires more cabling and a central device with multiple ports, which can increase setup costs.

### Mesh Topology

![](../attachments/Pasted%20image%2020250315154804.png)

In a mesh topology, each device is connected directly to every other device, creating a network with multiple paths. These connections can be either wired or wireless.
- Mesh topology provides high redundancy and fault tolerance. If one link fails, data can be rerouted through alternative paths.
- Communication between devices can take the shortest and most efficient route, ensuring faster data transmission.

#### Types of Mesh Topology
- **Full Mesh:** Every device is connected to every other device.
- **Partial Mesh:** Only some devices are interconnected, while others are not directly connected to every device.

#### Advantages 
1. High fault tolerance and redundancy, ensuring network reliability even if one connection fails.
2. Efficient data transmission with multiple paths available between devices.

#### Disadvantages
1. Requires a large number of connection, increasing cabling of infrastructure costs.
2. More complex to design and manage, particularly in large-scale networks.

## References
[Network Topologies](https://nailyourinterview.org/interview-resources/computer-networks/network-topologies)O