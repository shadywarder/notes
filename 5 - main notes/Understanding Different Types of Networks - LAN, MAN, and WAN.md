**2025-03-05 14:59**
**Tags:** [networks](../2%20-%20tags/networks.md) [nyi](../2%20-%20tags/nyi.md)

## Understanding Different Types of Networks - LAN, MAN, and WAN

### What is a Network?
A network is a collection if interconnected devices that communicate with each other through a medium, either wired or wireless.

#### A Simple Example of a Network
Imagine a city with many houses connected by roads. In this analogy:
- **City** = Network
- **Houses** = Devices (computers, printers, smartphons)
- **Roads** = Connections (wired or wireless)

![](../attachments/Pasted%20image%2020250305151747.png)

The image above shows a typical network setup where devices like printers, phones, and laptops are interconnected. This kind of setup is often found in offices, schools, or universities, where many devices need to share resources like printers or internet access.

### Types of Network
There are mainly three types of networks that you should know about: LAN, MAN, and WAN.

#### What is a LAN (Local Area Network)?
A Local Area Network (LAN) is a type of network that connects multiple devices within a **limited area** such as a home, office, or university. This network allows devices to share resources and communicate with each other efficiently.

![](../attachments/Pasted%20image%2020250305152641.png)

In a university, for example, many computers are linked to a switch using cables like fiber-optic or twisted pair cables. This setup makes it easy for students and staff to access shared printers, files, and the internet.

> [!NOTE]
> Devices can be directly connected using Ethernet crossover cables or indirectly via a switch with Ethernet straight-through cables.

##### Advantages of LAN
1. **Resource Sharing:** A LAN makes it easy to share resources like printers and files among devices making collaboration straightforward.
2. **Cost-Effective:** Since it requires less infrastructure and maintenance, setting up a LAN is usually affordable.
##### Disadvantages of LAN
1. **Limited Range:** LANs are generally restricted to a small area, like a single building or campus, which can be limiting if you need to connect remotely.
2. **Single Point of Failure:** If a switch fails, it can disrupt the entire network, affecting all connected devices.

##### What is a MAN (Metropolitan Area Network)?
When you need to connect devices across an entire city, a Metropolitan Area Network (MAN) comes into play. Think of a MAN as a larger version of a LAN, spanning a wider area.

![](../attachments/Pasted%20image%2020250305154004.png)

MANs connect multiple LANs withing a city using routers and high-speed connections, making it possible for people in different locations to communicate and share data.

##### Advantages of MAN
1. **Extended Coverage:** MANs can connect different buildings or campuses within a city, facilitating broader communication and data sharing.
2. **High-Speed Connectivity:** These networks often use fiber optic cables, ensuring fast and reliable communication between connected locations.

##### Disadvantages of MAN
1. **Complexity and Cost:** Setting up a MAN requires significant investment in equipment and technical expertise, making it more expensive and complex than a LAN.
2. **Dependency of Infrastructure:** If there's an issue with the physical infrastructure, such as cable cuts or equipment failure, the network can be disrupted.

#### What is a WAN (Wide Area Network)?
If you need to connect devices across different or continents, a Wide Area Network (WAN) is what you would use. The WAN is like the backbone of global communication, often referred to as the internet.

![](../attachments/Pasted%20image%2020250305154742.png)

WANs connect millions of devices globally through a network of cables and satellites, allowing for worldwite communication.

##### Advantages of WAN
1. **Global Connectivity:** WANs make it possible for organizations to connect remote offices, branch locations, and data centers around the world.
2. **Scalability and Flexibility:** They can easily be expanded to include new locations or support more users, making them adaptable to changing business needs.

##### Disadvantages of WAN
1. **Security Risks:** Because WANs cover such vast distances and involve many different networks, they are more vulnerable to security threats like data breaches. 
2. **Complexity:** WANs are complicated to manage because they involve integrating various technologies and protocols. This complexity requires specialized IT staff to maintain and secure the nework.

**Technical Insight:** Switches operate at Layer 2 (Data Link Layer) using MAC addresses. Features like VLANs and port security can isolate traffic and block unauthorized devices, enhancing LAN security. WANs, however, traverse public (e.g., the internet), requiring encryption (like VPNs) to mitigate risks.

## References
[Networks & It's Types](https://nailyourinterview.org/interview-resources/computer-networks/network-and-its-types)