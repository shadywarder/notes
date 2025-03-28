**2025-03-21 10:49**
**Tags:** [cpp cores](../2%20-%20tags/cpp%20cores.md)

## Future vs. Promises

I'm confusing myself with difference between `std::future` and `std::promise`. Obviously, they have different methods and stuff, but what is the actual use case?

Is it?:
- When I'm managing some async task, I use `std::future` to get the value "in future"
- When I'm the async task, I use `std::promise` as the return type to allow the user get a future from my promise

---

Future and Promise are two separate sides of an asynchronous operation.
`std::promise` is used by the "producer/writer" of the asynchronous operation.
`std::future` is used by the "consumer/reader" of the asynchronous operation.

The reason it is separated into these two separate "interfaces" is the **hide** the "write/set" functionality from the "consumer/reader":

```cpp
auto promise = std::promise<std::string>();

auto producer = std::thread([&]
{
	promise.set_value("Hello World");
});

auto future = promise.get_future();

auto consumer = std::thread([&]
{
	std::cout << future.get();
});

producer.join();
consumer.join();
```

## References
[Futures vs. Promises](https://stackoverflow.com/questions/12620186/futures-vs-promises)