**2025-03-20 15:49**
**Tags:** [networks](../2%20-%20tags/networks.md)

## Why Are There Only 65,535 Ports, and Will We Ever Have More?

The port is part of the layer 4 protocols in use - TCP or UDP, for the most part; it's not related to the memory addressing of the actual computers; so don't get confused by the 32 or 64 bit memory addressing of modern operating systems. 

The headers of these layer 4 protocols specifically defined structures, for which exactly 16 bits are used for the source and destination ports. Without compatibility-breaking changes to the layer 4 protocols that the entire interned depends on, the number of ports cannot be changed. Even the newer SCTP has the 16 bit constraint on ports.

Keep in mind that these protocols identify traffic based not just on the receiving port, but also the receiving IP and the sending port and IP; you're limited 65535 listening TCP ports (but you don't have that many), and you're limited to 65535 connections to a specific service on a specific remote system (lower in practice), so it's uncommon to run into the limit on these protocols unless you have a system creating a whole lot of connections to a specific remote system.


## References
[Why Are There Only 65,535 Ports, and Will We Ever Have More?](https://serverfault.com/questions/592637/why-are-there-only-65-535-ports-and-will-we-ever-have-more)