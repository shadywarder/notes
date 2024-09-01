```cpp
template <typename T, typename U>
void f(T, U) {
	std::cout << 1;
}

template <>
typename f(int, int) {
	std::cout << 3;
}

template <typename T>
void f(T, T) {
	std::cout << 2;
}

int main() {
	f(0, 0); // 2
}
```

```cpp
template <typename T, typename U>
void f(T, U) {
	std::cout << 1;
}

template <typename T>
void f(T, T) {
	std::cout << 2;
}

template <>
typename f(int, int) {
	std::cout << 3;
}

int main() {
	f(0, 0); // 3
}
```

```cpp
```cpp
template <typename T, typename U>
void f(T, U) {
	std::cout << 1;
}

template <typename T>
void f(T, T) {
	std::cout << 2;
}

template <>
void f(int, double) {
	std::cout << 3;
}

void f(int, long long) {
	std::cout << 4;
}

int main() {
	f(0, 0); // 2, since there is conversion to call last function
}
```

1. Overloading among templates
2. Generating version for chosen template
3. Common overloading resolution

For function there is no partial specialization.

Non-type template parameters (nttp). 

```cpp
template <typename T, size_t N>
class array {
	T arr[N];
};

template <size_t M, size_t N, typename Field = Rational>
class Matrix {};

template <size_t N, typename Field = Rational>
using SquareMatrix = Matrix<N, N, Field>;

template <size_t M, size_t K, size_t N, typename Field>
Matrix<M, N, Field> operator*(const Matrix<M, K, Field>& a, 
	const Matrix<K, N, Field>& b); // we prevent multiplying of matrix with incompatable types

int main() {
	std::array<int, 100> a;

	int x;
	std::cin >> x;
	const int y = x;
	// constexpr int y = x; // CE
	Matrix<y, y> m; // CE
}
```

Template template parameters

```cpp
template <typename T, template <typename, typename> typename (until some version we used to write class here) Container = std::vector>
class Stack {
	Container<T, std::allocator<T>> container;
};

int main() {
	Stack<int, std::vector> S:
}
```

```cpp
template <typename T, template <typename> typename Container = std::vector>
class Stack {
	Container<T> container;
};

template <typename T>
using myvector = std::vector<T>;

int main() {
	Stack<int, myvector> s;
}
```

Computations on templates

```cpp
template <int N>
struct Fibonacci {
	static constexpr int value = Fibonacci<N-1>::value + Fibonacci<N -2>::value;
};

template <>
struct Fibonacci<1> {
	static constexpr int value = 1;
};

template <>
struct Fibonacci<0>  {
	static constexpr int value = 0;
};

int main() {
	std::cout << Fibonacci<20>::value;
}
```

$O(n)$

```cpp
template <int N, int D>
struct IsPrimeHelper {
	static constexpr bool value = N % D == 0 ? false : IsPrimeHelper<N, D-1>::value;
};

template <int N>
struct IsPrimeHelper<N, 1> {
	static constexpr bool value = true;
};

template <int N>
struct IsPrime {
	static constexpr bool value = IsPrimeHelper<N, N - 1>::value;
};

template <>
struct IsPrime<1> {
	static constexpr bool value = false;
};
```