**2025-03-19 12:23**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Protocol Persistency and Statefulness + Web Cookies + Caching

![](../attachments/Pasted%20image%2020250319122349.png)

### Cookies

![](../attachments/Pasted%20image%2020250319122421.png)

![](../attachments/Pasted%20image%2020250319122752.png)

**Summary on "Cookies":**
- Cookies allow an HTTP server to keep track of users;
- Cookie technology relies on 4 major components:
	1. Set-cookie header in HTTP response;
	2. Cookie header at an HTTTP request;
	3. A cookie file on a user side;
	4. Back-end database on a server side.

### HTTP Pages: Background

![](../attachments/Pasted%20image%2020250319132239.png)

- Addressable by a unique identifier - a Unified Resource Locator (URL) address;
- Corresponds to one base HTML file and a set of referenced objects (images, videos, etc.)
- Objects - separate files stored on a server side, possibly at different locations;
- To download a web page, an HTTP client should download all files related to that web page: a base HTML files and all referenced objects;
- 3 files to be downloaded in this case:
	- 1 base HTML file;
	- 2 JPEG images.
- Objects can be loaded over the same (that is persistent) or independent (that is non-persistent) HTTP sessions

### Page Download

![](../attachments/Pasted%20image%2020250319132817.png)

![](../attachments/Pasted%20image%2020250319132917.png)

![](../attachments/Pasted%20image%2020250319132952.png)

### Round Trip Time (Performance Metric)

![](../attachments/Pasted%20image%2020250319133018.png)

**RTT** (definition): **round trip time** for a small packet to travel from client to server and back.
**HTTP response time:**
- One RTT to initiate TCP connection;
- One RTT for HTTP request and first few bytes of HTTP response to return;
- File transmission time;
- Non-persistent HTTP response time = 2RTT + file transmission time.

![](../attachments/Pasted%20image%2020250319133719.png)

### Web cache (or proxy Server)
*Goal:* satisfy client request without involving origin server.
- User sets his browser: Web accesses via cache
- Browser sends all HTTP requests
	- IF object in cache: then cache returns object;
	- Else cache requests object from origin server, then returns object to client.

![](../attachments/Pasted%20image%2020250319134326.png)

Cache acts as both client and server:
- Server for original requesting client
- Client to origin server

Typically the cache in installed by your ISP (e.g. university, company, or residential ISP)

*Why Web caching?*
- Reduce response time for client requests
- Reduce traffic on an institution's access link
- Internet is dense with caches: enables "weak" content providers to effectively deliver content.