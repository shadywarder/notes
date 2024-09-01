Motivation;

```cpp
void swap(int& x, int& y) {
	int t = x;
	x = y;
	y = t;
}

int max(int x, int y) {
	return x > y ? x : y;
}
```

We want write such code that for all types `T` something will be defined.

```cpp
template <typename T>
void swap(T& x, T& y) {
	T t = x;
	x = y;
	y = t;
}

template <typename T>
T max(T x, T y) {
	return x > y ? x : y;
}
```

Actually, these implementations are not good enough.
`template <typename T>` == `template <class T>` (overlook some corner case)

```cpp
template <typename T>
class vector {
	T* arr;
	size_t sz;
	size_t cap;
};
```

We can use `template` in a couple with `using`

```cpp
template <typename T>
struct less {
	bool operator()(const T& x, const T& y) {
		return x < y;
	}
};

struct greater {
	bool operator()(const T& x, const T& y) {
		return x > y;
	}
};

template <typename T>
using mymap = std::map<T, T, std::greater<T>>;
```

```cpp
int main() {
	int a = 1;
	long long b = 2;
	swap(a, b); // CE, because compiler only can generate version for similar T
}
```

The question of deciding what type of template will be precedes everything else.

```cpp
int main() {
	int a = 1;
	int aa = 2;
	int b = 1;
	int bb = 2;
	swap(a, aa);
	swap(b, bb);
	swap(a, b); // still CE
}
```

```cpp
swap<long long>(a, b); // CE
```

```cpp
int a = 1;
long long& x = a; // a: int -> long long conversion, got rvalue, non-const ref -> CE
```

```cpp
template <typename T>
void f(T x) {}

void f(int x) {}

int main() {
	int x = 0;
	f(x); // second version (exact type matchin)
}
```

The particular is better than general (Частное лучше общего).
The choice between first and second version happens before code generation for templates.

```cpp
```cpp
template <typename T>
void f(T x) {}

void f(long long x) {}

int main() {
	int x = 0;
	f(x); // first version
}
```

```cpp
template <typename T>
void f(T x) {
	std::cout << 1;
}

void f(int x) {
	std::cout << 2;
}

int main() {
	int x = 0;
	f<int>(x); // 1
}
```

No CE.

```cpp
template <typename T>
void f(T x) {
	std::cout << 1;
}

template <typename T>
int f(T x) {
	std::cout << 2;
	return 0;
}

int main() {
	int x = 0;
}
```

CE (redefinition).

```cpp
template <typename T>
void f(T x) {
	std::cout << 1;
}

template <typename T>
void f(T x) {
	std::cout << 2;
}

int main() {
	int x = 0;
}
```

```cpp
template <typename T, typaname U = int>
U f(T x) {
	std::cout << 1;
	return 0;
}
```

```cpp
template <typename T, typaname U>
U f(T x) {
	std::cout << 1;
	return x;
} 

f<int>(x); // CE

template <typename U, typaname T>
U f(T x) {
	std::cout << 1;
	return x;
}

f<int>(x); // OK 
```

```cpp
template <typename T>
void f(T& x) {
	std::cout << 1;
}

template <typename T>
void f(T x) {
	std::cout << 2;
}

int main() {
	int x = 0;
	f(x); // CE
}
```

```cpp
template <typename T>
void f(const T& x) {
	std::cout << 1;
}

template <typename T>
void f(T& x) {
	std::cout << 2;
}

int main() {
	int x = 0;
	f(x); // 2
}
```

Template specialization

```cpp
template <typename T>
class vector {
	T* arr;
	size_t sz;
	size_t cap;
};

// Full specialization
template <>
class vector<bool> {
	char* arr;
	size_t sz;
	size_t cap;
};
```

```cpp
template <typename T, typename U>
struct S {};

// Partial specialization
template <typename W>
struct S<int, W> {};

template <typename W>
struct S<W, int> {};

int main() {
	S<int, int> s; // ambiguous
}
```

We cannot redeclare a template structure with a different number of template parameters.

```cpp
template <typename T>
struct A {};

template <typename T>
struct A<T&> {};

template <typename T>
struct A<const T> {};

int main() {
	A<const int&> a; // second version
}
```