**2025-03-25 10:06**
**Tags:** [course](../2%20-%20tags/course.md) [devops](../2%20-%20tags/devops.md)

## Ch 2. Command Line

### Help

Run `docker help` in your command line interface. It should spit a giant help menu. As you can see there are *a lot* of commands. We're going to learn the most relevant ones.

### Running a Pre-Built Sample Container

Docker hosts a "getting started" image for users to play with. Run Docker's getting started image.

Run this command in your CLI:

```bash
docker run -d -p 80:80 docker/getting-started:latest
```

You should see the container running in the "Containers" tab of Docker Desktop. Next, run:

```bash
docker ps
```

This will list running containers in your command line. On one of the columns you should see this:

```bash
PORTS
0.0.0.0:80->80/tcp
```

This is saying that port `80` on your local "host" machine is being forwarded to port `80` on the running container. Port `80` is conventionally used to indicate HTTP web traffic. Navigate to `http://localhost:80` and you should get a webpage describing the container you're running!

### Stopping a Container

In case you don't believe me that this webpage is being hosted by you on your local machine, allow me to prove it.

Docker has two commands that we can use to stop a Docker container from running.

#### docker stop

This stops the container by issuing a `SIGTERM` signal to the container. You'll typically want to use `docker stop`. If it doesn't work you can always try the harsher `docker kill`.

```bash
docker stop CONTAINER_ID
```

#### docker kill

This stops the container by issuing a `SIGKILL` signal to the container.

```bash
docker kill CONTAINER_ID
```

### Images vs. Containers

We've been throwing around the terms "docker image" and "docker container", let's take a step back and make sure we understand what these terms mean.

- A "docker image" is the read-only *definition* of a container.
- A "docker container" is a virtualized read-write environment.

*A container is essentially just an image that's actively running.*

Run this command:

```bash
docker images
```
``
You should see an image with the name (repository) "docker/getting-started". That's a static image that we downloaded from docker hub. It describes to docker how to start a new container. When we run: 

```bash
docker run -d -p 80:80 docker/getting-started
```

We're starting a new *container* from the "docker/getting-started" *image.*

### Exec

Let's get a little more hands-on with running containers.

List your running containers:

```bash
docker ps
```

If you don't have a running container of the `docker/getting-started` image, start it up again:

```bash
docker run -d -p 8080:80 docker/getting-started
```

#### Running One-Off Commands in the Container

Let's start with something simple. Run this:

```bash
docker exec CONTAINER_ID ls
```

This executes an `ls` (list directory) command in the running container and returns to our current shell session. You should get a list of all the files and directories in the working directory of the container.

![](../attachments/Pasted%20image%2020250325115921.png)

### Exec Find Process

Let's try one more command using `exec`. I'm curious about what software this container is using to serve a webpage.

The `netstat` shows us which programs are bound to which ports. We're looking for the process bound to port `80`, that is, the one serving the webpage.

Run this command:

```bash
docker exec CONTAINER_ID netstat -ltnp
```

![](../attachments/Pasted%20image%2020250325120248.png)

### Live Shell 

Being able to run one-off commands is nice, but it's often more convenient to start a shell session running within the container itself.

Run the following command:

```bash
docker exec -it CONTAINER_ID /bin/sh
```

- `-i` makes the `exec` command interactive
- `-t` gives us a tty (keyboard) interface
- `/bin/sh` is the path to the command we're running. After all, a command line shell is just a program. sh is a more basic version of bash.

Once you have a session in the container print your working directory:

```bash
pwd
```

![](../attachments/Pasted%20image%2020250325121134.png)

When you're done playing around in the container you can get back to your host machine by running the `exit` command.

### Multiple Containers

Now that we have some experience with a single container, let's run multiple containers!

Remember, Docker is very lightweight. It's normal to run many containers on a single host machine.

Run this command several times, but replace `XX` with different ports each time. E.g. `81`, `82`, `83` ...

```bash
docker run -d -p XX:80 docker/getting-started@latest
```

In the `-p XX:YY` flag, the `XX` is the host port, while `YY` is the port within the container. We keep using port `80` within each container because that's the port that Nginx is serving the webpage to *within* the container.

We *have* to use different host ports for different containers because two processes can't bind to the same port on the same operating system. 

You should now be able to load the webpage on different URLs:

- http://localhost:80

- http://localhost:81

- http://localhost:82

- ...

Keep in mind, even though it's the same webpage, they'er each being served from different containers and different running processes.

Run this command:

```bash
docker stats
```

When you're done looking at the state and running the tests you can use `ctrl + c` to get your shell back.


## References
[Ch 2. Command Line](https://www.boot.dev/lessons/515096c0-d3ca-4d50-851e-45a2a4457a87)