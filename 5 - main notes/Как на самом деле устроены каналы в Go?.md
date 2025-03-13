**2025-02-23 14:44**
**Tags:** [go](../3%20-%20indexes/go.md)

## Как на самом деле устроены каналы в Go?
### Интересные для изучения свойства
- goroutine-safe `hchan mutex`
- хранение элементов, семантика FIFO `hchan buf`
- передача данных между горутинами `sendDirect, operations with buf`
- блокировка горутин `sendq/recvq, sudog, calls to scheduler: gopark(), goready()`

```go
ch := make(chan int, 4)
```

![](../attachments/Pasted%20image%2020250223144556.png)

`closed uint32` т. к. мы будет работать с ним с помощью атомиков.

![](../attachments/Pasted%20image%2020250223145043.png)

### Sending 
1. Acquire
2. Add to queue (copy)
3. Release

### Receiving
1. Acquire
2. Get from queue
3. Release

### Buffer overflow

![](../attachments/Pasted%20image%2020250223145342.png)

### Scheduler and goroutines

![](../attachments/Pasted%20image%2020250223145433.png)

Попытаемся выжать максимальную пользу из каждого потока.

### How to pause goroutine?

![](../attachments/Pasted%20image%2020250223145539.png)

### How to resume goroutine?

![](../attachments/Pasted%20image%2020250223145733.png)

![](../attachments/Pasted%20image%2020250223145927.png)

![](../attachments/Pasted%20image%2020250223150041.png)

![](../attachments/Pasted%20image%2020250223150057.png)

### Resume Sender

![](../attachments/Pasted%20image%2020250223150142.png)

Все действия над спящей горутиной совершает та горутина, которая пришла за данными. 

### What if Reader came first?

![](../attachments/Pasted%20image%2020250223150307.png)

![](../attachments/Pasted%20image%2020250223150359.png)

Чтобы не совершать два копирования, мы напрямую копируем данные из sender в receiver.

### Код реализации каналов

```go
type hchan struct {
	qcount   uint      // total data in the queue
	dataqsiz uint      // size of the circular queue
	buf unsafe.Pointer // poiters to an array of dataqsiz elements
	elemsize uint16
	closed   uint32
	elemtype *_type // element type
	sendx    uint   // send index
	recvx    uint   // receive index
	recvq    waitq  // list of recv waiters
	sendq    waitq  // list of send waiters
	lock     mutex
}
```

### Как работает select?

![](../attachments/Pasted%20image%2020250223152426.png)

### Closing
1. Is channels initialized? **Panic if not**
2. Lock the mutex.
3. Is channel closed? **Panic if yes**
4. Set `ch.closed = true`
5. Release all readers.
6. Release all writers - **they will panic**
7. Unlock the mutex.
8. Unlock all goroutines.

### Why channel designed like this?

![](../attachments/Pasted%20image%2020250223152910.png)

## References
[Как на самом деле устроены каналы в Golang?](https://www.youtube.com/watch?v=ZTJcaP4G4JM)