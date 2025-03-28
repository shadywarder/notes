**2025-03-19 21:16**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Socket Programming in C Language

 A software mechanism for data exchange between local or remote processes (IPC, Inter-Process Communication service)

#### C header files used

`sys/socket.h` Core socket functions and data structures.
`netinet/in.h` Data structures for representing IP addresses, TCP and UDP port numbers, and other
`arpa/inet.h` Functions for manipulating with numeric IP addresses; An alternative of `<netinet/in.h>` for some operating systems.
`netdb.h` Translation functions of host names into numeric addresses (e.g. by using DNS services), and other
`sys/un.h` Communication function for **local processes** running on the same computer

| Function                       | Description                           | Side using |
| ------------------------------ | ------------------------------------- | ---------- |
| `socket(...)`                  | To create a network socket            | Both sides |
| `bind(...)`                    | To bind (=to link) a socket to a port | Server     |
| `listen(...)`                  | To put socket into listening mode     | Server     |
| `connect(...)`                 | To connect to server                  | Client     |
| `accept(...)`                  | To accept connection from a client    | Server     |
| `send(...)`,  `recv(...)`      | To exchange data in case of TCP       | Both sides |
| `sendto(...)`, `recvfrom(...)` | To exchange data in case of UDP       | Both Sides |
| `shutdown(...)`                | To close TCP connection               | Server     |
| `close(...)`                   | To close a socket                     | Both sides |

### Recap: Key Communication Stages for UDP and TCP 

![](../attachments/Pasted%20image%2020250319214038.png)


### Core Functions (provided by `<sys/socket.h>)`

To create a socket (both, client and server side):

```c
int socketFD = socket(addressDomain, socketType, protocolCode);
```

To bind a socket to a specific port:

```c
int status = bind(socketFD, socketAddress, addressLength);
```

To connect to server (client side, TCP case):

```c
int status = connect(socketFD, remoteSocketAddress, addressLength);
```

To accept connection (server side, TCP case):

```c
int connectionSocketFD = accept(socketFD, &clientSocketAddress, addressLength);
```

### Core Library for Socket Programming: `<sys/socket.h>`

![](../attachments/Pasted%20image%2020250319214624.png)

![](../attachments/Pasted%20image%2020250319214656.png)

![](../attachments/Pasted%20image%2020250319214717.png)

![](../attachments/Pasted%20image%2020250319214833.png)

### Server Side Implementation: TCP Case 

![](../attachments/Pasted%20image%2020250319215511.png)

Format conversion functions:

`htons()`: Host TO Network Short number conversion (byte order change);
`htonl()`: Host TO Network Long number conversion (byte order change);

