**2025-02-23 13:44**
**Tags:** [go](../3%20-%20indexes/go.md)

## Тип Map в Go
### Разделение на бакеты

![](../attachments/Pasted%20image%2020250223134536.png)

**Проблема**

![](../attachments/Pasted%20image%2020250223134610.png)

### Хэш-функция

```go
bucket = hash(key)
```

Свойства:
- Равномерность
- Быстрота
- Детерминированность 
- Криптоустойчивость

`v = m[k]` скомпилируется в `v = runtime.lookup(m, k)`.
Сигнатура `lookup`: `func<K,V> lookup(m map[K]V, k K) V`.

### Как обойтись без дженериков?
- Все операции выполняются с помощью `unsafe.Pointer`
- Мета-информация о типе хранится в ***type descriptor***
- ***type descriptor*** предоставляет операции `hash`, `equal`, `copy`

```go
type _type struct {
	size uintptr
	ptrdata uintptr // size of memeory prefix holding all pointers
	equal func(unsafe.Pointer, unsafe.Pointer) bool
	...
}

type mapType struct {
	key *_type
	value *_type
	elem *_type
	bucket *_type 
	hasher func(unsafe.Pointer, uintptr) uintptr // function for hashing keys (ptr to key, seed) -> hash
	keysize uint8 // size of key slot
	elemsize uint8 // size of elem slot
	bucketsize uint16 // size of bucket
	flage uint32
}
```

### `v = m[k]`

Скомпилируется в:

```go
pk := unsafe.Pointer(&k)
func lookup(t *mapType, m *mapHeader, k unsafe.Pointer) unsafe.Pointer
pv := runtime.lookup(typeOf(m), m, pk)
v := *(*V)pv
```

Список преобразований

```go
v := m["k"] -> func mapaccess1(t *maptype, h *hmap, k unsafe.Pointer) unsafe.Pointer
v, ok := m["k"] -> func mapaccess2(t *maptype, h *hmap, k unsafe.Pointer) (unsafe.Pointer, bool)
m["k"] = 9001 -> func mapassign(t *maptype, h *hmap, k unsafe.Pointer) unsafe.Pointer
delete(m, "k") -> func mapdelete(t *maptype, h *hmap, k unsafe.Pointer)
```

### Map в Go

![](../attachments/Pasted%20image%2020250223140033.png)

Используем логарифм от количества бакетов, чтобы оптимизировать использование памяти и сделать использование побитовых операций более удобным.
 
![](../attachments/Pasted%20image%2020250223140253.png)

### Low order bits (LOB)

```go
hash(key) = 5461
5461 % 4 = 1
hash(key) = 1010101010101
log_2(buckets) = 2 -> we need to check two least significat bits
lob(hash) = 01
```

### Структура бакета

![](../attachments/Pasted%20image%2020250223140728.png)

Сначала проверяем на наличие ключа с помощью HOB.
Такой порядок выбран из **type alignment**.

```go
type hmap struct {
	count int // # live cells = size of map. 
	flags uint8
	B uint8 // log_2 of # buckets (can hold up to loadFactor * 2^B items).
	noverflow uint16 // approximate number of overflow buckets.
	hash0 uint32

	buckets unsafe.Pointer // array of 2^B buckets. may be nil if count==0.
	oldbuckets unsafe.Pointer // previous buckets array of half the size, non-nil only when growing.
	nevacuate uintptr // progress counter for evacuation.

	extra *mapextra // optional fields
}
```

### Переполнение бакета

![](../attachments/Pasted%20image%2020250223142018.png)

Picking `loadFactor`: too large and we have lots of overflow buckets, too small and we waste a lot of space. I wrote a simple program to check some stats for different loads.

![](../attachments/Pasted%20image%2020250223142310.png)

```md
%oveflow    = percentage of buckets which have an oveflow bucket
bytes/entry = overhead bytes used per key/elem pair
hitprobe    = # of entries to check when looking up a present key
missprobe   = # of entries to check when looking up an absent key
```

### Почему нельзя взять ссылку на элемент мапы?
Если бы берем ссылку на какой-то бакет, то в какой-то момент может произойти эвакуация данных и указатель будет инвалидирован.

### Почему вывод `fmt.Println()` фиксирован?
Перед выводом мапы ее ключи сортируются по возрастанию.

 ## References
[Как на самом деле устроен тип Map в Golang?](https://www.youtube.com/watch?v=P_SXTUiA-9Y&t=1204s)