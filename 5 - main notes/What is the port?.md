L**2025-03-20 15:18**
**Tags:** [networks](../2%20-%20tags/networks.md)

## What is the port?

To reach a service on any networked computer you need to know 3 parameters. Some of them you provide explicitly and some of the are deduced by operating system implicitly. The three parameters are `IP Address`, `Protocol`, `Port number`. So any running service can be uniquely described by a combination of these three numbers.

Imagine, that we did not use port numbers. That would mean that on each computer we could have only one service using any of the protocols. So a web server could only serve HTTP protocol, mail server could only provide SMTP services and so on.

Usage of ports allows us to multiplex services on same computer. A port number is nothing more than a number, indicating what service should get a data packet. So we can have HTTP server, SMTP server and SSH server all running on a same computer and all using same protocol - namely TCP.

Also, these ports have nothing to do with a physical ports you see on your computer. Once again - they are just a number, allowing to distinguish which service (i.e. program) should receiver which packet.

For example when I enter `www.stackoverflow.com` in my web-browsers address bar, by OS sends a HTTP request to `{IP:104.16.34.249, Proto: TCP, Port: 80}`. How does it know these numbers? IP address is resolved from the host name using the DNS protocol. Web browser is running HTTP protocol, which is using TCP. Port 80 is default port for HTTP. Behind the scenes, each packet will have destination address IP set the above value and TCP payload will have destination port set to 80. On the SO computer, there will a web-serving running, which is listening for data received on port 80 and replies to my packet.

## References
[What exactly is a 'port', and how is it related to the internet?](https://stackoverflow.com/questions/35358596/what-exactly-is-a-port-and-how-is-it-related-to-the-internet)