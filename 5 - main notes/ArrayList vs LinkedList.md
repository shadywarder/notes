**2024-12-19 19:08**
Tags: [[low-level]] 

## Why we should avoid linked lists?
The main advantage of vector over the linked is memory locality. Vector stores data in the contiguous piece of memory whereas elements of linked list is not next to each other in the memory. So, here are some points about superior performance of contiguously stored data vs non-contiguous one.

### Cache misses
Modern CPUs does not fetch single but from memory but slightly larger chunks. Thus, if size of your object is less than size of those chunks, you can get more than one elements at a time.






## References
https://youtu.be/xFMXIgvlgcY?si=3aJMfF6DPjPmHxYV
https://youtu.be/YQs6IC-vgmo?si=vkUlu4GGe16WqvXf
https://youtu.be/cvZArAipOjo?si=KWfAH7_Mw-cirxrw
https://stackoverflow.com/questions/34170566/bjarne-stroustrup-says-we-must-avoid-linked-listshttps://stackoverflow.com/questions/17299951/c-vector-what-happens-whenever-it-expands-reallocate-on-stack/17302443#17302443