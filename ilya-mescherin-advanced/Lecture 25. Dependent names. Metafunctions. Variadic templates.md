```cpp
#include <iostream>
#include <array>

template <typename T>
struct S {
	using A = int;
};

template <>
struct S<double> {
	static const int A = 5;
};

template <typename T>
void f() {
	S<T>::A* x; // declaration or expression. however, by default is expression according to standard.
	typename S<T>::A* x; // declaration
};

int main() {
	f<int>(); // OK
	f<double>(); // CE, if there is typename
}
```

```cpp
#include <iostream>
#include <array>

template <typename T>
struct S {
	template <int N>
	using A = std::array<int, N>;
};

template <>
struct S<double> {
	static const int A = 5;
};

template <typename T>
void f() {
	S<T>::A<10> x; // A < 10 > x
	typename S<T>::A<10> x; // not enough (from g++11 works)
	typename S<T>::template A<10> x;
};

int main() {
	f<int>();
}
```
\
```cpp
#include <iostream>
#include <array>

template <typename T>
struct S {
	template<int N>
	void foo(int) {}
};

template <>
struct S<double> {
	const int foo = 1;
};

template <typename T>
void var(int x, int y) {
	S<T> s;
	s.template foo<5>(x + y); // s.foo < 5 > (x + y);
}

int main() {
	bar<int>(2, 3); 
}
```

```cpp
#include <iostream>
#include <array>

template <typename T>
struct Base {
	int x = 0;
};

template <typename T>
struct Derived: Base<T> {
	void f() {
		++x; // error
		++this->x; 
		++Base<T>::x;
	}
};
```

To get access to the field of template parent we should use `this` keyword: `++this->x`.

Two phase translation: 
1. Before `T` substitution: basic syntax/semantics checks independent from `T` names.
2. After `T` substitution: we can catch many errors only after instantiation of the object.

### Metafunctions and type traits.
Functions, that takes not objects, but types.

```cpp
#include <iostream>

template <typename T, typename U>
struct is_same {
	static constexpr bool value = false;
};

template <typename T>
struct is_same<T, T> {
	static constexpr bool value = true;
};

template <typename T, typename U>
void f(T x, U y) {
	if (typeid(x) == typeid(y)) // bad practise
	if constexpr  (is_same<T, U>::value) {
		x = y;
	}
}

int main() {
	f<int, std::string>(5, "abc"); // constexpr just ejects code inside if-statement if condition is false, some semantics checks will be skipped. without constexpr it will be CE
}
```

```cpp
#include <type_traits> // from c++11

template <typename T>
struct remove_reference {
	using type = T;
};

template <typename T>
struct remove_reference<T&> {
	using type = T;
};

template <typename T>
struct remove_const {
	using type = T;
};

template <typename T>
struct remove_const<const T> {
	using type = T;
};

template <typename T>
void f() {
	typename remove_reference<T>::type x; // dependent name
}
```

```cpp
template <bool B, typename T, typename F>
struct conditional {
	using type = F;
};

template <typename T, typename F>
struct conditional<true, T, F> {
	using type = T;
};
```

In order to more convenient usage of metafunctions in c++14 were added some template usings:

```cpp
template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;
```

For `type_traits` that returns value there was also added more convenient way to interact:

```cpp
template <typename T, typename U>
const bool is_same_v = is_same<T, U>::value;
```

Variable template from c++14.

### Variadic templates.

```cpp
template <typename... Types> // ... means package declaration
void f(Types... tx) { // ... means unpackaging 
	g(tx...);
}

template <typename... Types>
void print(Types... tx) {

}
```

`Types` is package of arguments.

```cpp
void print() {}

template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail) {
	std::cout << head << ' ';
	print(tail...);
}
```

Actually, size of `tail` versions of `print` will be generated.

```cpp
#include <type_traits>

template <typename First, typename Second, typename... Types>
struct is_homogeneous {
	static constexpr bool value = std::is_same_v<First, Second> && is_homogeneous<Second, Types...>::value;
};

template <typename First, typename Second>
struct is_homogeneous<First, Second> {
	static constexpr bool value = std::is_same_v<First, Second>;
};
```

There is no `struct` overloading.

```cpp
sizeof...(tail); 
```

