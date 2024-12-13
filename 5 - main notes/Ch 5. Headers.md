## What are HTTP Headers?
An <u>HTTP header</u> allows clients and servers to pass *additional* information with each request or response. Headers are just case-insensitive <u>key-value pairs</u> that  pass additional <u>metadata</u> about the request or response.

HTTP requests from a web browser automatically carry with them many headers, including but not limited to:
- The type of client (e.g. Google Chrome)
- The Operating system (e.g. Windows)
- The preferred language (e.g. US English)
As developers, we can define custom headers in each request.

### Headers in Go's `net/http` Package 
In Go, the `net/http` package provides us with the necessary tools to work with HTTP headers. We can access headers through the `Header` type, which is essentially a map of string slices (`map[string][]string`). This allows us to perform various actions on our request and response headers such as retrieving, setting, and removing them.

```go
// creating a new request
req, err := http.NewRequest("GET", "https://api.example.com/users", nil)
if err != nil {
	fmt.Println("error creating request: ", err)
	return
}

// setting a header on the new request
req.Header.Set("x-api-key", "123456789")

// making the request
client := http.Client{}
res, err := client.Do(req)
if err != nil {
	fmt.Println("error making request: ", err)
	return
}
defer res.Body.Close()

// reading a header from the response
header := res.Header.Get("last-modified")
fmt.Println("last modified: ", header)

// deleting a header from the response
res.Header.Del("last-modified")
```

## Using the Browser's Developer Tools
Modern web browsers offer developers a powerful set of *developer tools*. The <u>Developer Tools</u> are a front-end web developer's best friend! For example, using the dev tools you can:
- View the web page's JavaScript console output
- Inspect the page's HTML, CSS, and JavaScript code
- View network requests and responses, along with their headers.

The method for accessing dev tools varies from browser to browser:
- **Keyboard Shortcuts**:
	- Windows: `ctrl + shift + I` or `F12`
	- MacOS: `cmd + option + I`

In most browsers, you can just right-click anywhere on a web page and click the "inspect" option. 

### The network tab
While all of the tabs within dev tools are useful, we will focus on the *network tab* in this chapter so we can play with HTTP headers. The network tab monitors your browser's network activity and records all of the requests and responses the browser in making, including how long each of those requests and responses takes to fully process.

![[../../../1 - source materials/attachments/Pasted image 20240922212848.png]]

## Why are headers useful?
Headers are useful for several reasons from design to security, but most often headers are user for <u>metadata</u> *about* the request or response itself. For example, let's say we wanted to ask for a player's level from the Fantasy Quest server. We need to send that player's ID to the server so it knows which player to send back the information for. That ID *is my request*, it's not information *about my request*.

*Authentication* is a common use case for headers. If I ask Fantasy Quest to consume a potion, I need to provide authentication information that I'm logged in, but that auth info isn't the request itself, it's just *additional information* about the request.

## Network Tab Practice
1. Open your browser's Dev Tools
2. Navigate to the *Network* tab at the top.
3. Once you've opened the network tab, refresh this page.

Poke through are different requests that you see. Notice that you can select a request and see its request and response headers. Request headers are sent from your browser to the server. Response headers are the headers sent back from the server to your browser.

![[../../../1 - source materials/attachments/Pasted image 20240922220945.png]]
