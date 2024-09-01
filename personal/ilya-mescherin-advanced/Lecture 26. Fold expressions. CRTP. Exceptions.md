```cpp
template <typename... Types>
struct all_pointers {
	static const bool value = (std::is_pointer_v<Types> && ...);
};
```

```cpp
template <typename Head, typename... Tail>
struct is_homogeneous {
	static const bool value = (std::is_same_v<Head, Tail> && ...);
};
```

```cpp
template <typename... Types>
void print(const Types&... types) {
	(std::cout << ... << types) << "\n";
};
```
### CRTP - Curiously Recurring Template Pattern

```cpp
template <class T>
struct Base {
	void interface() {
		// ...
		static_cast<T*>(this)->implementation();
		// ...
	}

	static void static_func() {
		T::static_sub_func();
	}
};

struct Derived: Base<Derived> {
	void implementation();
	static void static_sub_func();
};
```

### Exceptions