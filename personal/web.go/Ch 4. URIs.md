## Uniform Resource Identifiers
We briefly touched on URLs earlier, let's dive a little deeper into the subject.

A <u>URI</u>, or Uniform Resource *Identifier*, is a unique character sequence that identifiers a resource that it (almost always) accessed via the internet.

Just like Golang has syntax rules, so do URIs. These rules help ensure uniformity so that any program can interpret the meaning of the URI in the same way.

URIs come in two main types:
- <u>URLs</u>
- <u>URNs</u>

We will focus specifically on URLs in this course, but it's important to know that URLs are only one kind of URI.

![[Pasted image 20240922172758.png]]

## Sections of a URL
URLs have quite a few sections. Some are required, some are not.

## Further dissecting a URL
There are 8 main parts to a URL, though not all the sections are always present. Each piece plays a role in helping clients locate the (((droids))) resources they're looking for.

![[Pasted image 20240922174006.png]]

|Part|Required|
|---|---|
|Protocol|Yes|
|Username|No|
|Password|No|
|Domain|Yes|
|Port|No (defaults to 80 or 443)|
|Path|No (defaults to /)|
|Query|No|
|Fragment|No|
### Don't memorize
Because names for the different sections are often used... sloppily... and because not all the parts of the URL are always present, it can be hard to keep things straight.

Don't worry about memorizing this stuff! Like any good developer, now that you know about URL sections, you can always look up the specifics again in the future when you need them.

## The Protocol
The "protocol" (also referred to as the "scheme") is the first component of a URL. It defines the rules by which the data being communicated is displayed, encoded or formatted.

Some examples of different URL protocols:
- http
- ftp
- mailto
- https

For example:
- `http://example.com`
- - `mailto:noreply@fantasyquest.app`

### Not all schemes require a "//"
The "http" in a URL is always followed by `://`. All URLs have the colon, but the `//` part is only included for schemes that have an <u>authority component</u>. As you can see above, the `mailto` scheme doesn't use an authority component, so it doesn't need the slashes.

## URL Ports 
The port in a URL is a virtual point where network connections are made. Points are managed by a computer's operating system and are numbered from `0` to `65,535` (*though port `0` is reserved for the system API*).

Whenever you connect to another computer over a network, you're connecting to a specific port on that computer, which is listened to by a program on that computer. A port can only be used by one program at a time, which is why there are so many possible ports.

The port component of a URL is often not visible when browsing normal sites on the internet, because 99% of the time you're using the default ports for the HTTP and HTTPS schemes: `80` and `443` respectively.

![[Pasted image 20240922175507.png]]

Whenever you aren't using a default, you need to specify it in the URL. For example, port `8080` is often used by web developers when they're running their server it "test mode" on their own machines.

Hosts are virtual little hubs manage by the OS, that allows to segment incoming requests/data streams. Thanks to ports we can run multiple piece of software on the same machine.

## URL Paths
On static sites (like blogs and documentation sites) a URL's path mirrors the server's filesystem hierarchy. 

For example, if the website `https://exampleblog.com` had a static web server running in its `/home` directory, then a request to `https://exampleblog.com/site/index.html` would probably return the file located at `/home/site/index.html`.

*But technically, this is just a convention. The server could be configured to return any file or data given that path.*

### It's not always that simple
Paths in URLs are essentially just another type of parameter that can be passed to the server when making a request. For dynamic sites and web applications, the path is often used to denote a specific resource or endpoint.

## Query parameters 
Query parameters in a URL are *not* always present. In the context of websites, query parameters are often used for marketing analytics or for changing a variable on the web page. With website URLs, query parameters *rarely* change *which* page you're viewing, though they often will change the page's *contents*.

That said, query parameters can be used for anything the server chooses to use them for, just like the URL's path.

### How Google uses query parameters
1. Open a new tab and go to <u>https://google.com</u>.
2. Search for the term "hello world"
3. Take a look at your current URL. It should start with `https://www.google.com/search?q=hello+world`
4. Change the URL to say `https://www.google.com/search?q=hello+universe`
5. Press "enter"

You should see new search results for the query "hello universe". Google chose to use query parameters to represent the value of your search query. It makes sense - each search result page is *essentially* the same page as far as HTML structure and CSS styling are concerned - it's just showing you different results based on the search query.
 