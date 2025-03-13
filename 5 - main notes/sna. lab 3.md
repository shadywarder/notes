**Author: Sergey Razmakhov**
**Group: CBS-02**
**Lab 3: File permissions and text filtering editors**
### 1. File permissions

![](../attachments/Pasted%20image%2020250210194504.png)


I complete this task relying on the lab work, therefore, there is no chance for `paul` to change a file inside `/home/shared` directory, because he simply does not have an access to this directory. Even though we changed ownership to the new group, it has no effect in case of `paul`.

### 2. Text filtering editors
#### 2.1.
![](../attachments/Pasted%20image%2020250210200127.png)

#### 2.2.
![](../attachments/Pasted%20image%2020250210200244.png)

#### 2.3.
![](../attachments/Pasted%20image%2020250210200321.png)

#### 2.4.
![](../attachments/Pasted%20image%2020250210205510.png)

#### 2.5.
![](../attachments/Pasted%20image%2020250210220820.png)
1. `[0-9]{4}(/[0-9]{2}){2}` - date in format `YYYY/MM/DD`
2. `[0-9]{2}(:[0-9]{2}){2}` - time in format `HH:MM:SS`
3. `'[0-9]{1,3}(\.[0-9]{1,3}){3}/[0-9]{1,2}'` - IP address.

#### 2.6.
![](../attachments/Pasted%20image%2020250210212450.png)
5. `at (.*)\(` - everything after `at` and before `(`
6. `.([a-z]+)\` - file extension
7. `:([0-9]+)\` - line number