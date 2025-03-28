**2025-03-24 17:17**
**Tags:** [system design](../2%20-%20tags/system%20design.md)

## Proxy. Forward, Reverse, and More

A proxy acts as an intermediary between your computer and the backend server. When you use a proxy, your requests to visit websites go through this intermediary first. The proxy can perform various functions such as filtering or transforming the request before forwarding it to the website.

### Types of Proxies

#### Forward Proxy

![](../attachments/Pasted%20image%2020250324171928.png)

A forward proxy is a proxy server that sits in front of clients. It intercepts client requests and communicates with the server on their behalf.

**Example**: Imagine you're a student at a college that uses a forward proxy server. When you try to visit a website, your request first go to the proxy server. The proxy then sends the request to the website and returns the response to you. Colleges use forward proxies for various reasons:

**Advantages**: 

1. **Access Control**: Proxies can be configured to block access to certain sites, like social media, to enforce content policies.

2. **Anonymity**: Websites only see the proxy's IP address, not yours, which can protect user privacy.

3. **Caching**: Frequently accessed content can be cached by proxy, speeding up access for everyone.

4. **Bypass Restrictions**: Proxies can be used to access websites that are blocked in your region or country.

**Disadvantages**: 

1. **Latency**: Since your request goes through the proxy before reaching the website, it can introduce delays.

2. **Single Point of Failure**: If the proxy server crashes, no one can access the Internet.

3. **Different Proxies for Different Applications**: Different types of traffic (e.g., web, email) may require different proxy configurations. Unified proxies can become complex, less flexible, and single points of failure.

#### Reverse Proxy

![](../attachments/Pasted%20image%2020250324172613.png)

A reverse proxy is a proxy server that sits in front of web servers. It intercepts client requests and forwards them to the appropriate server.

**Example**: Think of a popular online store using a reverse proxy to manage incoming traffic. When you visit the store's website, your request first goes to the reverse proxy. The proxy then forwards your request to one of the store's backend servers. Online stores use reverse proxies for several reasons:

**Advantages**: 

1. **Security**: Hackers only see the proxy server's IP address, not the actual servers, making it harder to target attacks.

2. **Load Balancing**: The proxy distributes requests across multiple, preventing any single server from becoming overloaded.

3. **SSL Termination**: The proxy can decrypt incoming SSL/TLS traffic to inspect it for security and caching purposes.

4. **Content Delivery Network (CDN)**: Reverse proxies can cache content at multiple locations worldwide, reducing latency by serving content from the nearest node.

5. **DDoS Protection**: Reverse proxies can filter out malicious traffic before it reaches the origin using techniques such as rate limiting and traffic analysis.

**Disadvantages**: 

1. **Single Point of Failure**: If the proxy server fails, clients cannot access the backend servers, even if those servers are operational.

2. **Complexity**: Managing a reverse proxy requires handling SSL/TLS certificates and increasing the number of proxies to avoid failure points, which adds complexity.

3. **Different Proxies for Different Applications**: Like forward proxies, reverse proxies may need specialized configurations for load balancing, SSL terminatin, etc., making unified proxy solutions less scalable.

#### Key Differences


| Forward Proxy                                                               | Reverse Proxy                                                               |
| --------------------------------------------------------------------------- | --------------------------------------------------------------------------- |
| Sits in front of clients; servers cannot communicate directly with clients. | Sits in front of servers; clients cannot communicate directly with servers. |
| Used when clients want to access services outside their private network.    | Acts on behalf of servers to handle incoming requests from clients.         |

### VPN vs. Proxy

1. **Anonymity**: Both VPNs and proxies hide the client's IP address, providing anonimity.

2. **Private Browsing**: Both allow for private web browsing by masking the user's IP.

3. **Encryption**: VPNs offer out-of-the-box encryption, protecting all traffic from hackers. Proxies may only encrypt specific types of traffic (e.g., HTTPS), not providing full encryption.

4. **Data Privacy**: VPNs encrypt the entire data stream, making it difficult for ISPs to track browsing activities, whereas proxies may not encrypt initial connection setups and data exchanges.

### Load Balancer vs. Reverse Proxy

1. **Use Case**: Load balancers are typically used when there are multiple servers to distribute traffic among. Reverse proxies can be used even if there is only server, providing additional functionality like security and caching.

2. **Functionality**: Reverse proxies offer features like IP filtering, rate limiting, authentication, caching, SSL termination, and load balancing. While reverse proxies can act as load balancers, the reverse is not true.

### Firewall vs. Proxy

1. **Firewall**: Operates at the network level (Layers 3 and 4 of the OSI model), filtering traffic based on IP address, ports, and protocols to protect against unauthorized access.

2. **Proxy**: Operates at the application layer (Layer 7), focusing on content filtering and application-level control.

3. **Proxy Firewalls**: Combine features of both firewalls and proxies, providing application-level content filtering along with network-level security features such as packet filtering, deep packet inspection, and stateful inspection.

> [!NOTE]
> Choosing between these technologies depends on your specific needs. Firewalls provide network-level security, proxies offer content control and anonymity. VPNs ensure encrypted private browsing, and load balancers manage traffic distribution for high availability.

## References

[Proxy: Forward, Reverse, and More](https://nailyourinterview.org/interview-resources/system-design/proxy)