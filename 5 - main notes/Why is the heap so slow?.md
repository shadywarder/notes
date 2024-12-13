**2024-12-04 18:51**

Tags: [[os]] [[low-level]]

## Why is the heap so slow?

### System Calls
- System calls are the API provided by the OS and we use them to request some service that only OS can perform.
- System calls can be expensive in terms of performance.
- System call -> OS -> CPU 

*Context switch - storing the state of a process or thread, so that it can be restored and resume execution at a later point, and then restoring a different, previously saved, state.*

A context switch takes time and resources. 

![[Pasted image 20241204190931.png]]

- Whenever process makes memory request it actually followed by system call.
- Text stores solely instructions. 
- OS allocates memory by chunks, so if there is enough free space from previous allocations we can simply write our value there
 - In the heap there is no certainty regarding the order in which value will be removed -> it is harder to avoid fragmentation in this case
 - Whenever we need to allocate space of a value in the heap we should check if any of these holes are sufficiently large because if so we can bypass the overhead of invoking a system call.

![[Pasted image 20241204192409.png]]
- First fit is the fast one but not the best choice to avoid fragmentation.
- Best fit and worst fit may reduce fragmentation in certain scenarios but they may not be as fast.

> [!IMPORTANT]
> If value are too large to fit them on the stack we store on the heap and on the stack we just maintain a reference on it.


| Pros                                   | Cons                                                                 |
| -------------------------------------- | -------------------------------------------------------------------- |
| Dynamic size                           | Allocations require searching available sub-regions withing the heap |
| Large memory allocations               | Allocation may require a system call                                 |
| Fast accessing times if used correctly | Memory leaks                                                         |
|                                        | Null pointers dereferences                                           |
|                                        | Dangling pointers                                                    |
|                                        | Fragmentation                                                        |

## References
https://www.youtube.com/watch?v=ioJkA7Mw2-U