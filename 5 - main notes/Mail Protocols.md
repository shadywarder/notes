**2025-03-19 13:54**
**Tags:** [networks](../2%20-%20tags/networks.md) [s25](../3%20-%20indexes/s25.md) [university](../3%20-%20indexes/university.md)

## Mail Protocols

### Sample Application Layer Protocols 

![](../attachments/Pasted%20image%2020250319135436.png)

### Electronic Mail Timeline

![](../attachments/Pasted%20image%2020250319135724.png)

### Email Address Format 
(specified by IETF (Internet Engineering Task Force) organization in RFC 5322 and 6854)

Examples:
`ithelp@university.innopolis.ru`
`"it help"@university.innopolis.ru

![](../attachments/Pasted%20image%2020250319140203.png)

Email addresses are used to define mail receivers and senders, as well as mail servers.

### Client-Server Architecture for Emails Exchange

![](../attachments/Pasted%20image%2020250319140645.png)

Typical assumption on terminology:
**Mail server** - a hardware machine (physical server);
**SMTP server** - a program to get emails from senders, and forward the further to a destination server.
**POP (or IMAP) server** - a program to enable the retrieval of emails by a destination client.

> [!NOTE] 
> HTTP is not dedicated for email communication, but can be used together with web client (for sending and retrieving emails).

### Comparison: Mail User Agents and Servers

![](../attachments/Pasted%20image%2020250319141353.png)

### Incoming and Mail Server

![](../attachments/Pasted%20image%2020250319141604.png)

### Email Client Types

![](../attachments/Pasted%20image%2020250319141716.png)

### POP vs. IMAP Protocols

![](../attachments/Pasted%20image%2020250319144405.png)

### POP vs. IMAP: Advantages and Disadvantages

![](../attachments/Pasted%20image%2020250319144516.png)

### Email Exchange: Single Mail Server Case

![](../attachments/Pasted%20image%2020250319144850.png)

### Email Exchange: The Case of Multiple Mail Servers

![](../attachments/Pasted%20image%2020250319144938.png)

![](../attachments/Pasted%20image%2020250319145020.png)

### Email Routing 

![](../attachments/Pasted%20image%2020250319145224.png)

> [!NOTE]
> The algorithm for choosing the next hop is defined in the SMTP specification.

SMTP - for sending and routing;
POP and IMAP - for retrieving from a server.

SMTP is a handshaking protocol; it controls the delivery of a mail, or reports failure; No data encryption be default, additional mechanisms are used (like Transport Layer Security, TLS)
