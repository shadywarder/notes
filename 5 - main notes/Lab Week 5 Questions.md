**2025-03-19 19:24**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Lab Week 5 Questions

<details>
<summary>What is the domain name?</summary>
Human-readable name that's associated with a physical IP address on the Internet.
</details>
<details>
<summary>Why do we need a domain name?</summary>
The memorization of raw IP address is simply not convenient. They also allow websites changing their hosting architecture (IP addresses are not permanent), serving as an additional layer of abstraction.
</details>
<details>
<summary>Why do we need DNS?</summary>
DNS is an effective protocol for obtaining IP address from domain names.
</details>
<details>
<summary>Why do we need caching of IP addresses with corresponding Domain names?</summary>
Caching reduces network traffic, DNS server workload and time overhead.
</details>
<details>
<summary>Which levels of Hierarchical DNS structure do you know?</summary>
RLD, TLD, 2LD, LLD.
</details>
<details>
<summary>What is the main purpose of LOCAL DNS Server?</summary>
The Local DNS Server reduces workload of the actual DNS servers Hierarchy as well as holds a cache of IP addresses.
</details>
<details>
<summary>What is the difference between Recursive and iterative DNS queries types?</summary>
Recursive - load is distributed across all DNS hierarchy. Iterative - local DNS server is more loaded.
</details>
<details>
<summary>What is the DNS Record Time Validity?</summary>
The time after the data in local cache or in the ISP DNS server  needs to be reset and actualized.
</details>
<details>
<summary>How does Root identified in the Domain Name?</summary>
The dot at the end of the domain name (e.g. ozon.ru.)
</details>
