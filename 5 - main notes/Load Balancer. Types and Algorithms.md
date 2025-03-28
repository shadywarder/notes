**2025-03-24 13:52**
**Tags:** [system design](../2%20-%20tags/system%20design.md)

## Load Balancer. Types and Algorithms

A load balancer is a crucial component in a distributed system, responsible for distributing incoming network traffic across multiple servers to ensure no single server becomes overwhelmed. This improves the performance, reliability, and availability of the application.

### Why Do You Need a Load Balancer?

Imagine you have a popular website that initially runs on a single server. As traffic increases, you add more servers to handle the load. But how would clients know which server to connect to - Server1, Server2, etc.? A load balancer steps is to manage traffic distribution among these servers.

### Roles of a Load Balancer

- **Distributing Traffic**: The primary role is to evenly distribute incoming requests across multiple servers to prevent any single server from becoming a bottleneck.

- **High Availability**: If one server goes down, the load balancer redirects traffic to the remaining healthy servers, ensuring continuous operation.

- **Improving Performance**: By spreading the load, it helps maintains quick response times for users, ensuring optimal performance.

- **Scalability**: Makes it easy to add new servers to handle increased traffic without disrupting service.

### Load Balancing Algorithms

Load balancing algorithms can be broadly classified into static and dynamic types:

#### Static Algorithms

![](../attachments/Pasted%20image%2020250324142008.png)

##### Round Robin

- **How it Works**: The load balancer cycles through a list of servers in sequential order, assigning each incoming request to the next server in line.

- **Example**:
	- Request1 -> Server1
	- Request2 -> Server2
	- Request3 -> Server1 (cycle repeats)

- **Pros**: Simple to implement and ensures even distribution of requests.

- **Cons**: May lead to performance issues if servers have different capacities since all servers receive an equal number of requests regardless of their capability.

##### Weighted Round Robin

- **How it Works**: Similar to Round Robin, but each server is assigned a weight based on its capacity, determining how many requests it should handle relative to others. 

- **Example**: Server1 (weight 3), Server2 (weight 1)
	- Request 1, 2, 3 -> Server1
	- Request 4 -> Server2

- **Pros**: Allows more powerful servers to handle more requests.

- **Cons**: If a low-capacity server receives a high-computation request, it may become a bottleneck despite the weight distribution.

##### IP Hash

- **How it Works**: The load balancer uses the client's IP address to determine which server will handle the request. A hash function computes a hash of the client's IP, directing the request to a specific server.

- **Example**: 
	- Client IP 192.168.1.100 -> Server2
	- Client IP 172.178.200.10 -> Server1

- **Pros**: Ensures a particular client always connects to the same server, useful for session persistence.

- **Cons**: Performance can degrade if the server assigned to a client's IP is heavily loaded.

#### Dynamic Algorithms

![](../attachments/Pasted%20image%2020250324142937.png)

##### Least Connections

- **How it Works**: Routes traffic to the server with the fewest active connections.

- **Example**: If Server1 has 2 active connections and Server2 has 1, the next request goes to Server2.

- **Pros**: Balances the load based on the current number of connections, preventing any single server from becoming overwhelmed.

- **Cons**: Does not account for the complexity of the connections. A server with fewer connections might still be heavily loaded if those connections are resource-intensive.

##### Least Response Time

- **How it Works**: Routes traffic to the server with the lowest response time, considering both the number of connections and server performance.

- **Example**: The load balancer monitors the Time to First Byte (TTFB) for each server and directs requests to the server with the lowest TTFB.

- **Pros**: Optimizes user experience by reducing latency.

- **Cons**: Requires continuous monitoring of server response times, which can introduce additional overhead.

##### Resource-Based 

- **How it Works**: Routes traffic based on real-time metric such as CPU usage, memory usage, or other performance indicators.

- **Example**: If Server1 has 50% CPU usage and Server2 has 20%, the next request goes the Server2.

- **Pros**: Ensures efficient user of server resources by directing traffic to the least utilized servers.

- **Cons**: Requires detailed monitoring and a more complex setup, potentially leading to higher overhead.

### Types of Load Balancing

#### Layer 7 (Application Layer)

Layer 7 load balancing operates at the application layer, making routing decisions based on the content of the requests, such as URLs, HTTP headers, and cookies.

##### Examples

1. **Routing API and Static Content**
	- **Scenario**: A website serving both static content (images, CSS) and dynamic content via an API.
	- **Solution**: An L7 load balancer routes requests based on URL paths, directing static content requests to a Static Content Server and API requests to an API Server.

2. **User-Specific Content Routing**
	- **Scenario**: An e-commerce website with different servers for logged-in users and guests.
	- **Solution**: An L7 load balancer uses cookies to determine user login status and routes requests accordingly.

##### Advantages

1. **Smart Load Balancing**: Can make routing decisions based on the content of the HTTP request.

2. **Caching**: Can cache frequently requested content, reducing backend load.

3. **Ideal for Microservices**: Can route requests to different services based on content type.

4. **Sticky Sessions**: Can maintain session persistence, directing requests from the same client to the same server.

##### Disadvantages

1. **Expensive**: More complex and resource-intensive than Layer 4, leading to higher costs.

2. **TLS Termination**: Decrypts SSL/TLS traffic for inspection, which requires careful management of certificates.

3. **Increased Overhead**: Maintains separate TCP connections for clients and backend servers, adding overhead.

#### Layer 4 (Transport Layer)

Layer 4 load balancing operates at the transport layer, making routing decisions based on IP addresses and ports without inspecting the actual content of the packets.


##### Examples

1. **Online Game Server Distribution**
	- **Scenario**: Players connecting to different game servers based on active connections.
	- **Solution**: An L4 balancer distributes players to the server with the fewest active connections

2. **Simple Web Server Distribution**
	- **Scenario**: A website with high traffic distributed across multiple identical servers.
	- **Solution**: An L4 load balancer uses Round Robin to evenly distribute requests.

##### Advantages

1. **Simple Load Balancing**: Distributes traffic based on IP addresses and ports.

2. **Efficient**: Operates with lower latency and handles a high number of connections efficiently.

3. **NAT**: Uses Network Address Translation to direct traffic to the appropriate backend server.

4. **Lower Overhead**: Maintains a single TCP connection between client and server, reducing overhead.

##### Disadvantages

1. **No Content-Based Routing**: Cannot make decisions based on the content of the traffic, limiting advanced routing capabilities.

2. **Not Ideal for Microservices**: Lacks features needed for content-based routing and SSL termination.

3. **No Caching**: Cannot cache content, limiting its ability to reduce backend load.

### Redundancy and High Availability

To prevent the load balancer itself from becoming a single point of failure:

1. **Active-Passive Setup**: A backup load balancer is in standby mode, ready to take over it the primary fails.

2. **Active-Active Setup**: Multiple load balancers are used simultaneously, distributing the load among them for redundancy.

> [!NOTE]
> Choosing the right type of load balancer depends on your application's specific needs. Layer 7 load balancers offer more flexibility and are suited for complex applications, while Layer 7 load balancers provide efficient performance for simpler traffic distribution.

## References
[Load Balancer: Types and Algorithms](https://nailyourinterview.org/interview-resources/system-design/load-balancer/)