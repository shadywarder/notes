## Communicating on the web
Instagram would be pretty terrible if you had to manually copy your photos to your friend's phone when you wanted to share them. Modern applications need to be able to communicate information *between devices* over the internet.

- Gmail doesn't just store your emails in variables on your computer, it stores them on computers in their data centers
- You don't lose your Slack messages if your drop computer in a lake, those messages exists on Slack's servers

## How does web communication work?
When two computers communicate with each other, they need to use the same rules. An English speaker can't communicate verbally with a Japanese speaker, similarly, two computers need to speak the same language to communicate. 

This "language" that computers used called a <u>protocol</u>. The most popular protocol for web communication is <u>HTTP</u>, which stands for Hypertext Transfer Protocol.

Protocol is tells to computer to how parse a bunch of 0 and 1 to something meaningful.

## HTTP Requests and Responces
At the heart of HTTP is a simple request-response system. The "requesting" computer, also known as the "client", asks another computer for some information. That computer, "the server" sends back a response with the information that was requested. 

![[../../../1 - source materials/attachments/Pasted image 20240921225756.png]]

- Request: "What are the items in the Fantasy Quest game?"
- Response: `["Sword", "Shield", "Potion"]`

## HTTP powers websites
<u>HTTP</u>, of Hypertext Transfer Protocol, is a <u>protocol</u> designed to transfer information between computers. 

There are other protocols for communicating over internet, but HTTP is the most popular and is *particularly great for websites and web applications*. Each time you visit a website, your browser is making an HTTP request to that website's server. The server responds with all the text, images, and styling information that your browser needs to render its pretty website!

![[../../../1 - source materials/attachments/Pasted image 20240921230327.png]]

## HTTP URLs 
A URL, of <u>Uniform Resource Locator</u>, is the address of another computer, or "server" on the internet. Part of the URL specifies *where to reach* the server, and part of it tells the server *what information we want*.

![[../../../1 - source materials/attachments/Pasted image 20240921230940.png]]

Put simply, a URL a *piece of information on some computer somewhere*. We can get access to it by making a *request*, and reading the *response* that the server replies with.

## Using URLs in HTTP
The `http://` at the  beginning of a <u>website URL</u> specifies that the `http` protocol will be used for communication.

![[../../../1 - source materials/attachments/Pasted image 20240921231808.png]]

Other communication protocols URLs as well, (hence "Uniform Resource Locator"). That's why we need to be specific when we're making HTTP requests by prefixing the URL with `http://`

## `net/http`
In this course we'll be using Go's standard `net/http` package and the `http.Client` to make HTTP requests. In fact, we've already been using it! The `http.Get` function uses the `http.DefaultClient` under the hood.

## Making a Request
```go
import (
	"fmt"
	"io"
	"net/http"
)

func getSpells() ([]byte, error) {
	res, err := http.Get("https://api.fantasyquest.com/spell")
	if err != nil {
		return []byte{}, fmt.Errorf("error making request: %w", err)
	}
	defer res.Body.Close()

	data, err := io.ReadAll(res.Body)
	if err != nil {
		return []byte{}, fmt.Errorf("error reading response: %w", err)
	}
	return data, nil
}
```

- `http.Get` uses the `http.DefaultClient` to make a request to the given `url`
- `res` is the HTTP response that comes back from server
- `defer res.Body.Close()` ensures that the response body is properly closed after reading. Not doing so can cause memory issues.
- `io.ReadAll` reads the response body into a slice of bytes `[]byte` called data

## Web Clients
As we've discussed, a web client is a device making requests to a web server.

A client can be any type of device but is often something users physically interact with. For example:

- A desktop computer
- A mobile phone
- A tablet

In a website or web application, we call the user's device the "front-end".
A front-end client makes requests to a back-end server.

![[../../../1 - source materials/attachments/Pasted image 20240921233130.png]]

## Web Servers
Up to this point, most of the data you have worked with in your code has simply been generated and stored locally in variables. 

While you'll always use variables to store and manipulate data while your program is running, most websites and apps use a web server to store, sort, and serve data so that it sticks around for longer than a single session, and can be accessed by multiple devices.

### Listening and serving data
Similar to how a server at a restaurant brings your food to the table, a <u>web server</u> serves web resources, such as web pages, images and other data. The server is turned on the "listening" for inbound requests constantly so that the second it receives a new request, it can send appropriate response. 

### The server is the back-end
While the "front-end" of a website of web application is the device the user interacts with, the "back-end" is the server that keeps all the data housed in a central location.

### A server is just a computer
"Server" is just the name we give to a computer that is taking on the role of serving data across a network connection. A good server is turned on and available 24 hours a day, 7 days a week. While your laptop *can* be used as a server, it makes more sense to use a computer in a data center that's designed to be up and running constantly.