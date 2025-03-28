**2025-03-24 11:16**
**Tags:** [system design](../2%20-%20tags/system%20design.md)

## Scaling. Vertical and Horizontal Strategies

![](../attachments/Pasted%20image%2020250324111631.png)

Scaling is a critical concept in managing the growth of your web application. As your user base expands, ensuring your server infrastructure can handle increased traffic becomes essential. Let's explore different scaling strategies to understand how to keep your application running smoothly under varying load conditions.

### Initial Setup

Imagine you launched a website and started with a modest server setup:

**Initial Setup**: You deploy your application on a server with 4GB RAM and a dual-core CPU. This setup handler your initial traffic of 10.000 users per month smoothly.

### Vertical Scaling (Scaling Up)

As your website gains popularity, traffic increases dramatically:

- **First Challenge**: Traffic jumps to 10.000 users per day. Your current server crashes under this heavy load.

- **Solution**: You upgrade to a more powerful server with 64GB RAM and 16 cores. This vertical scaling boosts your server power significantly, allowing your website to handle the increased traffic.

- **Limitations**: Despite this powerful upgrade, as your user base continues to grow (now over 100.000 users per day), your single server struggles again due to its limits. Vertical scaling has a ceiling - you can't keep adding more power indefinitely. Moreover, it introduces a single point of failure: if this server goes down, your entire website goes offline.

### Horizontal Scaling (Scaling Out)

To handle the increasing demand beyond vertical scaling capabilities, you opt for horizontal scaling:

- **Adding More Servers**: You purchase 4 additional servers and set up a load balancer to distribute traffic among them. Each server now handles a portion of the traffic.

- **Challenges**: Horizontal scaling introduces new complexities:
	- **Network Calls**: Unlike vertical scaling, where processes communicate quickly within the same server, horizontal scaling requires network communication. Requests pass through a load balancer to reach different servers, adding latency due to network delays.
	- **Data Sharding**: Data is split across multiple servers (sharding), meaning some data is stored on one server, while other data is on another. Queries might need to fetch data from multiple servers, requiring additional network calls.
	- **Session Management**: For systems using persistent connections like websockets, where a client needs to stay connected to the same server, managing sessions becomes complex. Techniques such as sticky sessions (where the load balancer sends each client to the same server) or distributed caches like Redis can help manage session state.

- **Consistency Challenges**: 
	- **Replication**: Ensuring data consistency across all servers is crucial. If one server fails, others must seamlessly take over without data loss.
	- **Transactions**: For transactions that span multiple servers, ensuring all steps succeed or fail together (atomicity) requires careful coordination, using methods like two-phase commit or distributed transactions.

### When to Choose Vertical or Horizontal Scaling

#### Vertical Scaling

- **Immediate Performance Boost**: When you current server's resources (like CPU or RAM) are reaching their limits, and upgrading those resources can handle you current and foreseeable future workload effectively.

- **Limited Budget for Initial Investment**: Start with vertical scaling if your application's traffic and resource needs are predictable and manageable withing one server's capacity.

#### Horizontal Scaling

- **Scalability Strategy**: Use a combination of vertical and horizontal scaling. Start with vertical scaling to meet immediate performance needs. As your application grows, incorporate horizontal scaling by adding more servers to handle the distributed workload.

- **Auto-Scaling**: Utilize cloud services that offer auto-scaling capabilities. These services automatically add or remove servers based on predefined criteria, such as CPU usage, traffic load, or other metrics, ensuring efficient resource management.

By understanding and implementing these scaling strategies, you can ensure that your web application remains performant and available, even as traffic demands increase.

> [!NOTE]
> Consider using cloud platforms like AWS, Azure, or Google Cloud that provide build-in scaling solutions, making it easier to manage both vertical and horizontal scaling needs efficiently.

## References
[Scaling: Vertical and Horizontal Strategies](https://nailyourinterview.org/interview-resources/system-design/scaling)