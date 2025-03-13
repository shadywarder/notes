**Author: Sergey Razmakhov**
**Group: CBS-02**
**Lab 7: Systemd and Package managers**

### 1. Tracing

![](../attachments/Pasted%20image%2020250310230000.png)

1. The `graphical.target` requires `multi-user.target` to be active first in order to ensure the system reaches a multi-user state before starting the GUI.
2. The `multi-user.target` requires `basic.target`, which sets up basic system functionality (paths, timers, sockets, etc.) required for multi-user environments.
3. The `basic.target` requires `sysinit.target`, which initializes core system components like filesystems, swap.
4. Dead End: `sysinit.target` has no `Requires` dependencies. 

#### `Wants` Instead of `Requires`

`sysinit.target` allows the system to boot even if these units fail, missing or disabled, because these units only enhance functionality.

### 2. Simple Web Server

Here is the all taken steps:

![](../attachments/Pasted%20image%2020250310231908.png)

And web server itself:

![](../attachments/Pasted%20image%2020250310231934.png)

Bash script of the server itself, service file and slice file will be in the archive.

### `apt upgrade` vs. `apt full-upgrade`

`full-upgrade` will remove software packages if necessary while upgrade won't, which makes `apt upgrade` safe to use and `full-upgrade` not to safe.

### 4. Hello World Package

Create all the necessary directories & files.

![](../attachments/Pasted%20image%2020250310233027.png)

Set the appropriate permissions.

![](../attachments/Pasted%20image%2020250310233129.png)

Now we can actually build the package, list the content of the package and install it!

![](../attachments/Pasted%20image%2020250310233438.png)

Now we are able to run `helloworld.sh` from the terminal without additional steps!

![](../attachments/Pasted%20image%2020250310233835.png)







