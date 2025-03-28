**2025-03-18 22:40**
**Tags:** [networks](../2%20-%20tags/networks.md)

## What is the difference between URI, URL and URN?

A Uniform Resource Identifier (`URI`) is a string of characters used to identify a name or a resource on the Internet.

A URI identifiers a resource by location, or a name, or both. **A URI has two specializations known as URL and URN.** 

A Uniform Resource Locator (`URL`) is a subset of the Uniform Resource Identifier (`URI`) that specifies where an identified resource is available and the mechanism for retrieving it. A URL defined how the resource can be obtained. It does not have to be a HTTP (`http://`), a URL can also start with `ftp://` or `smb://`, specifying the protocol that's used to get the resource.

A Uniform Resource Name (`URN`) is a Uniform Resource Identifier (`URI`) that uses the URN scheme, and **does not imply availability of the identified resource**. Both URNs (names) and URLs (locators) are URIs, and a particular URI may be both a name and a locator at the same time.

This diagram visualized the relationship between URI, URN, and URL:

![](../attachments/Pasted%20image%2020250318225453.png)

The URNs are part of a larger internet information architecture which is composed of URNs, URCs and URLs.

**bar.html is not a URN.** A URN is similar to a person's name, while a URL is like a street address. The URN defines something's identity, while the URL provides a location. Essentially URN vs. URL is "what" vs. "where". A URN has to be one of this form `<URN> ::= "urn:" <NID> ":" <NSS>` where `<NID>` is the Namespace Identifier, and `<NSS>` is Namespace Specific String.

**To put it differently:** 
- A URL is a URI that identifiers a resource and also provides the means of locating the resource by describing the way to access it.
- A URL is a URI.
- A URI is not necessarily a URL.

I'd say the only thing left to make it 100% clear would be to have an example of an URI that is not an URL. We can use the examples in <u>RFC3986</u>.

```
URL: ftp://ftp.is.co.za/rfc/rfc1808.txt
URL: http://www.ietf.org/rfc/rfc2396.txt
URL: ldap://[2001:db8::7]/c=GB?objectClass?one
URL: mailto:John.Doe@example.com
URL: news:comp.infosystems.www.servers.unix
URL: telnet://192.0.2.16:80/
URN (not URL): urn:oasis:names:specification:docbook:dtd:xml:4.1.2
URN (not URL): tel:+1-816-555-1212 (disputed, see comments)
```

## References
[What is the difference between URI, URL and URN?](https://stackoverflow.com/questions/4913343/what-is-the-difference-between-uri-url-and-urn)
[Lab Week 2 Questions](Lab%20Week%202%20Questions.md)