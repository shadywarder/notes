**2025-03-19 16:03**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Domain Name System (DNS)

### DNS Motivation: Webpage Retrieval Example

1. Webpages are hosted by servers;
2. Network devices are identified by IP addresses;
3. Users access webpages by human-friendly domain names;
4. Network communication is however based on IP addresses!
5. Domain names are translated into server IP addresses;
6. DNS is a database of domain names and IP addresses;
7. DNS translates Domain Name <> IP acting as a "phone book";

### DNS Performance

![](../attachments/Pasted%20image%2020250319160553.png)

Local caching of frequently used IP addresses (reduces DNS servers load, network congestion, other)

### DNS Optimization: Frequently used IP address caching

![](../attachments/Pasted%20image%2020250319161126.png)

![](../attachments/Pasted%20image%2020250319161203.png)

### DNS Database: Organizational Aspects

![](../attachments/Pasted%20image%2020250319161458.png)

### DNS Organization

![](../attachments/Pasted%20image%2020250319161651.png)

![](../attachments/Pasted%20image%2020250319161840.png)

![](../attachments/Pasted%20image%2020250319162049.png)

### DNS Lookup Process

![](../attachments/Pasted%20image%2020250319162216.png)

**Local DNS Server**
- Does not strictly belong to the DNS hierarchy;
- Each ISP or organization typically has one dedicated DNS;
- Local DNS acts as a proxy server: has its local cached DNS data;
- When needed (that is data is missing in cache or becomes invalid) it forwards DNS queries from local hosts into the DNS hierarchy.

![](../attachments/Pasted%20image%2020250319171435.png)

![](../attachments/Pasted%20image%2020250319171757.png)

### DNS Records Time Validity

![](../attachments/Pasted%20image%2020250319171923.png)

### DNS Record Format 

![](../attachments/Pasted%20image%2020250319172134.png)

![](../attachments/Pasted%20image%2020250319172215.png)

![](../attachments/Pasted%20image%2020250319172323.png)

![](../attachments/Pasted%20image%2020250319172558.png)

### Attacking DNS
**DDoS attacks** 
- Bombard root servers with traffic
	- Not successful to date
	- Traffic filtering
	- Local DNS servers cache IPs of TLD servers, allowing root server bypass 
- Bombard TLD servers
	- Potentially more dangerous

**Redirect attacks**
- Main-in-middle
	- Intercept queries
- DNS poisoning
	- Send bogus relies to DNS server, which caches

**Exploit DNS for DDoS**
- Send queries with spoofed source address: target UP
- Requires amplification
