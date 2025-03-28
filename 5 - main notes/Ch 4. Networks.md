**2025-03-25 16:16**
**Tags:** [course](../2%20-%20tags/course.md) [devops](../2%20-%20tags/devops.md)

## Ch 4. Networks

### Ping

We've already done just a bit of networking in Docker. Specifically, we've exposed containers to the host network on various ports and accessed web traffic.

#### Offline Mode

You might be thinking, "why would I want to turn off networking"??? Well, usually for security reasons. You might want to remove the network connection from a container in one of these scenarios:

- You're running 3rd party code that you don't trust, and it shouldn't need network access;

- You're building an e-learning site, and you're allowing students to execute code on your machines;
 
- You know a container has a virus that's sending malicious requests over the internet, and you want to do an audit.

#### Using the "ping" Utility

The `ping` command allows you to check for connectivity to a host by sending small packets of data. Try pinging `google.com`:

```bash
ping google.com
```

Press `ctrl+c` to kill the command after the first few pings.

### Break the Network

Now that you've seen how you can `ping` Google successfully, let's quarantine a container and make sure that we *can't* reach Google.

#### Run the "Getting Started" Container

Start the getting started container, but do it in `--network none` mode. This removes the network interface from the container.

```bash
docker run -d --network none docker/getting-started
```

Next, run the `ping` command with a timeout of 2 seconds inside the container:

```bash
docker exec CONTAINER_ID ping google.com -W 2
```

If all goes well, the program should hang for 2 seconds, then report an error message, because you don't have internet access!

### Load Balancers

Let's try something a bit more complex: let's configure a load balancer!

#### What Is a Load Balancer?

A load balancer behaves as advertised: it balances a load of network traffic. Think of a *huge* websites like `google.com`. There's *no way* that a single server (literally a single computer) could handle all of the Google searches for the entire world. Google uses load balancers to route requests to different servers.

#### How Does a Load Balancer Work?

A central server, called the "load balancer", receives traffic from users (aka clients), then routes those raw requests to different back-end application servers. In the case of Google, this splits the world's traffic across potentially many different thousands of computers.

![](../attachments/Pasted%20image%2020250325163124.png)

#### How Does It "Balance" the Traffic?

A *good* balancer sends more traffic to servers that have unused resources (CPU and memory). The goal is to "balance the load" evenly. We don't want any individual server to fail due to too much traffic. There are many strategies that load balancers use, but a simple strategy is the "round robin". Requests are simply routed one after the other to different back-end servers.

##### Example of "Round Robin" Load Balancing

- Request 1 -> Server 1

- Request 2 -> Server 2

- Request 3 -> Server 3

- Request 4 -> Server 1

- Request 5 -> Server 2

- ...

### Application Servers

First, we need to start some application servers so that we have something to lad balance! We'll be using Caddy, an awesome open-source balancer/web server. Nginx and Apache are other popular alternatives that do similar things, but Caddy is a modern version written in Go, so I think it will be cool to play with.

#### What Will Our Application Servers Do?

Each application server will server a **slightly different** HTML webpage. The reason they're different is just so what we can see load balancing in action!

##### 1. Pull Down the `caddy` Image

```bash
docker pull caddy
```

##### 2. Create index1.html and index2.html in Your Working Directory

##### 3. Run Caddy Containers to Server the HTML

```bash
docker run -d -p 800(1,2):80 -v $PWD/index(1,2).html:/usr/share/caddy/index.html caddy
```

### Custom Network

Docker allows to create custom bridge networks so that our containers can communicate with each other if we want them to, but remain otherwise isolated. We're going to build a system where the application servers are hidden withing a custom network, and only our load balancer is exposed to the host.

Let's create a custom bridge network called "caddytest":

```bash
docker network create caddytest
```

You can see if it worked by listing all the networks:

```bash
docker network ls
```

#### Restart Your Application Servers on the Network

Stop and restart your caddy application servers, but this time, make sure you attach them to the `caddytest` network and give them names:

```bash
docker run --network caddytest --name caddy(1,2) -v $PWD/index(1,2):/usr/share/caddy/index.html caddy
```

Note that we didn't expose any ports with `-p` because we don't need to do need to do that anymore. Instead, we'll use the bridge network to communicate with these containers from another container.

#### Contacting the Caddy Servers Through the Bridge

To make sure it's working, let's get a shell session inside a "getting started" container on the custom network:

```bash
docker run -it --network caddytest docker/getting-started /bin/sh
```

By giving our containers some names, `caddy1` and `caddy2`, and providing a bridge network, Docker has set up name resolution for use! The container names resolve to the individual containers from all other containers on the network. Within your `docker/getting-started` container shell, curl the first container:

![](../attachments/Pasted%20image%2020250325170315.png)

Note that if you need to restart your caddy application servers after naming them, you can use: `docke start caddy1` and `docker start caddy2`.

### Configuring the Load Balancer

We've confirmed that we have 2 application servers (Caddy) working properly on a custom bridge network. Let's create a load balancer that balances network requests between the two! We'll use a round-robin balancing strategy, so each request should route bakck and forth between the servers.

#### Caddyfile for the Load Balancer

Caddy works great as a file server, which is what our little HTML servers are, but it also works great as a load balancer! To use Caddy as a load balancer we need to create a custom Caddyfile to tell Caady how we want it to balance traffic.

Create a new file in you local directory called `Caddyfile`:

```bash
localhost:80

reverse_proxy caddy1:80 caddy2:80 {
	lb_policy    round_robin
}
```

This tells Caddy to run on `localhost:80`, and to round robin any incoming traffic to `caddy1:80` and `caddy2:80`. Remember, this only works because we're going to run the load balancer within the same network, so `caddy1` and `caddy2` will automatically resolve to our application server's containers.

```bash
docker run -p 8080:80 -v $PWD/Caddyfile:/etc/caddy/Caddyfile caddy
```

## References
[Ch 4. Networks](https://www.boot.dev/lessons/f19bd094-8582-4dab-8808-821a3cbf415b)