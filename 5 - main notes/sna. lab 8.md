**Author: Sergey Razmakhov**
**Group: CBS-02**
**Lab 8: Docker**

### 1. `ENTRYPOINT` vs. `CMD`

The `ENTRYPOINT` specifies a command that will always be executed when the container starts. The `CMD` specifies arguments that will be fed to the `ENTRYPOINT`.

Both `CMD` and `ENTRYPOINT` instructions define what command gets executed when running a container. There are few rules that describe their co-operation.

1. Dockerfile should specify at least one of `CMD` or `ENTRYPOINT` commands.
2. `ENTRYPOINT` should be defined when using the container as an executable.
3. `CMD` should be used as a way of defining default arguments for an `ENTRYPOINT` command or for executing an ad-hoc command in a container.
4. `CMD` will be overridden when running the container with alternative arguments.

### 2. 5 Security Precautions

1. Keep Host and Docker Up to Date
2. Do Not Expose the Docker Daemon Socket
3. Run Docker in Rootless Mode
4. Avoid Privileged Containers
5. Limit Container Resources

### 3. Remove All Exited Docker Containers

```bash
docker system prune
```

![](../attachments/Pasted%20image%2020250317210713.png)

### 4. Outside Copy

```bash
docker cp ./some_file CONTAINER:/work
```

### 5. Dockerized Web Application

![](../attachments/Pasted%20image%2020250317215610.png)

![](../attachments/Pasted%20image%2020250317215625.png)
