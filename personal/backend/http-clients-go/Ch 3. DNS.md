## Web Addresses 
In the real world, we use physical addresses to help us find where a friend lives, where a business is located, or where a party is being thrown (well, i don't because I'm not invited to parties, but I digress). 

In computing, web clients find other computers over the internet using <u>Internet Protocol</u> (IP) addresses. Each device connected to the internet has a **unique IP address**.

### Domain names and IP Addresses
When we browse the internet, we type in a human readable domain name. That domain is converted into a IP address. The IP address tells our computer where the server is located on the internet.

![[Pasted image 20240922144039.png]]

**IPv4**: `*.*.*.*`
**IPv6**: `*:*:*:*:*:*:*`
We are simply running out of **IPv4** addresses.

**DNS**: `amazon.com` -> `IP`
There are essentially two steps every time wanna send an HTTP request:
1. Resolving DNS (obtaining IP address)
2. Use IP

Why don't we require users to type in IP addresses directly to browse the web? 
**Answer:** Domain names are easier for humans to remember, it's a better user experience 

## DNS
A "domain name" or "hostname" is just one portion of a URL. We'll get to the other parts of a URL later.

For example, the URL `https://homestarrunner.com/toons` has a hostname of `homestarrunner.com`. The `https://` and `/toons` portions aren't part of the `domain name` -> `IP address` mapping that we've been talking about.

### The net/url package 
The `net/url` package is part of Go's standard library. You can instantiate a <u>URL struct</u> using `url.Parse`:

```go
parsedURL, err := url.Parse("https://homestarrunner.com/toons")
if err != nil {
	fmt.Println("error parsing url:", err)
	return
}
```

And then you can <u>extract just the hostname</u>:

```go
parsedURL.Hostname()
// homestarrunner.com
```

## What is the Domain Name System?
So we've talked about domain names, but we haven't talked about *the system* that makes them work.

<u>DNS</u>, or the "Domain Name System", is the phonebook of the internet. Humans type easy-to-read <u>domain names</u> like <u>boot.dev</u>. DNS "resolves" those domain names to their associated <u>IP addresses</u> so that web clients can find the server they're looking for.

*Domain names are for humans, IP addresses are for computers.*

![[Pasted image 20240922170432.png]]

### How does DNS Work?
We'll go into more details on DNS in a future course, but to give you a simplified idea, let's just introduce ICANN. <u>ICANN</u> is a not-for-profit organization that manages DNS for the entire internet.

Whenever your computer attempts to resolve a domain name, it contacts one of ICANN's "root nameservers" whose address is included in your computer's networking configuration. From there, that nameserver can gather the domain the domain records for a specific domain name form their distributed DNS database.

If you think of DNS as phonebook, ICANN is the publisher that keeps the phonebook in print and available.

## Subdomains
We learned about how a domain name resolves to an IP address, which is just a computer on a network - often the internet.

A *subdomain* prefixes a domain name, allowing a domain to route network traffic to many different servers and resources.

For example, the <u>boot.dev</u> website that you're on right now is hosted on a different machine than our blog. Our blog, found at <u>blog.boot.dev</u> is hosted on our "blog" subdomain (and the IP address/computer in points to).