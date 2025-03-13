**2025-03-10 13:53**
**Tags:** [networks](../2%20-%20tags/networks.md)

## Networks Devices
In any network, multiple devices play crucial roles in transferring data from one computer to another. Let's explore some of these essential network devices.

### Repeater 

![](../attachments/Pasted%20image%2020250310135457.png)

A network repeater is a device that strengthens and extends the reach of a network's signal. It takes the data signal from one end, amplifies it, and sends it out again. This process increases the distance the signal can travel without losing strength. However, using too many repeaters can introduce latency and signal congestion, which might affect the overall performance of the network.

### Hub

![](../attachments/Pasted%20image%2020250310135821.png)

Hubs are often called "dumb devices", but they were a significant step forward in networking technology. A hub is a basic networking device that serves as a central connection point for multiple devices in a LAN. It receives data from one devices and the **broadcasts** it to all the other connected devices. 
- Hubs operate at the physical layer (Layer 1) of the OSI model.
- All devices connected to a hub share the same bandwidth. If multiple devices try to transmit data simultaneously, it can lead to collisions where data packets collide and need to be retransmitted.

> [!NOTE]
> Devices connected to a hub share bandwidth, which can cause network performance issues if too many devices transmit data at the same time, leading to collisions and retransmissions.

Hubs are simple devices that don't analyze or filter data. They pass the data too all devices except sender, without any form of **intelligence** or **decision-making**. This makes them inexpensive and easy to set up but less efficient compared to switches and routers.

### Bridge

![](../attachments/Pasted%20image%2020250310142302.png)

A bridge is a network device that connects two or more networks. The number of networks it can connect depends on the number of ports it has, usually two or four. Bridges work at the Data Link Layer (Layer 2) of the OSI model, making them slightly more intelligent than hubs.

Bridges use a MAC Address table to keep track of devices and their respective ports.

Below is an example of what a `MAC Address Table` might look like. If you're not familiar with MAC addresses yet, think of them as unique identifiers for each device.

| MAC ADDRESS       | PORT   |
| ----------------- | ------ |
| 00:11:22:33:44:55 | Port 1 |
| 00:AA:BB:CC:DD:EE | Port 2 |
| 11:22:33:44:55:66 | Port 1 |
| 22:33:44:55:66:77 | Port 1 |
Here's how a bridge works:
1. A source device sends data to its network's hub.
2. The hub broadcasts the data to all connected devices, including the bridge.
3. The bridge checks its MAC address table to see if the destination device is on another network.
4. If it is, the bridge sends the data to the hub of the destination network.
5. The hub in the destination network broadcasts the data to all its connected devices.
6. The destination device receives the data.

If the destination device is in the same network, the bridge does not forward the data to another network.

### Switch

![](../attachments/Pasted%20image%2020250310142956.png)

They only forward data to the specific destination device instead of broadcasting to all connected device (unlike hubs). They are using a `MAC Address Table`. Switches operate at Layer 2 of the OSI model (hubs at Layer 1).

Benefits of switches include:
1. **Number of Ports:** Switch can accommodate many ports, connecting hundreds of devices. There is possibility to expand the number of ports by connecting another switch using one port.
2. **Error Checking:** Switches have mechanisms to prevent data corruption.
3. **Data Transmissions Speed:** Switches can achieve data transmission speeds up to 100 Gbps, while hubs are limited to a maximum.

#### A switch receives a frame with an unknown MAC address. What does it do?
If a switch receives a frame with an unknown MAC address, it does **not discard it**. Instead, it **floods the frame to all ports** (except the source port) to ensure the destination receives it. Once the destination responds, the switch updates its MAC address table. This process is called **MAC flooding** or **unknown unicast flooding**.

### Router 

![](../attachments/Pasted%20image%2020250310143602.png)

Routers are more advanced devices that connect multiple networks (such as LANs, MANs, and WANs). Routers operate at Layer 3 of the OSI model, allowing them to perform routing functions.

#### What is Routing?
Routing involves moving data across different networks. Here's simplified overview:
1. **Network Connection:** A router has multiple network interfaces, each connected to a different network. For instance, one could be connected to a LAN and another to the WAN (like the internet).
2. **Routing Table:** Routers maintain a routing table that helps determine the best path for data to travel across networks.
3. **Packet Forwarding:** When a data packet arrives at the router, it checks the packet's destination IP address and uses its routine table to decide the best path to forward the packet.
4. **Network Address Translation (NAT):** Routers often perform NAT, allowing multiple devices on a LAN to share a single public IP address. This function translates private IP addresses into a public IP address and vice versa, effectively managing IP address space.
5. **Firewall and Security:** Many routers have built-in firewalls that control incoming and outgoing traffic, providing an extra layer of security by blocking unauthorized access.

#### Example of a Routing Table

| Network Destination | Subnet mask   | Gateway  | Flag | Outgoing Interface | Metric |
| ------------------- | ------------- | -------- | ---- | ------------------ | ------ |
| 182.168.2.6         | 255.255.255.0 | 11.0.1.2 | U    | eth02              | 1      |
1. **Network Destination:** This is the destination IP address or network. In this case, `182.168.2.6` represents a specific network where the destination device is located.
2. **Subnet Mask:** Defines the range of IP addresses withing the network. A mask of `255.255.255.0` indicates that the first three octets identify the network, and the last octet identifies the host.
3. **Gateway:** The IP address of the next-hop router or gateway. Here, `11.0.1.2` is the router that will take packets to the `182.168.2.6` network.

> [!NOTE]
> The key difference between a router and gateway is that a router connects networks that follow the same protocol, whereas a gateway connects networks that follow different protocols.

4. **Outgoing Interface:** The network interface through which packets should be sent. In this example, it's `eth0`, typically an Ethernet port.
5. **Metric:** This value helps decide the best path when multiple routes to the same destination exist. Lower metrics are preferred.
6. **Flag:** Indicates the route status, such as `U` for operational routes.

## References
[Network Devices](https://nailyourinterview.org/interview-resources/computer-networks/network-devices/)