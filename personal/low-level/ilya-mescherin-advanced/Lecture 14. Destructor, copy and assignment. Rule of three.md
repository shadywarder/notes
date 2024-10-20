```cpp
struct C {
    int& r;
    const int c;
};
```

Default constructor cannot be generated.

```cpp
int x = 0;
struct C {
    int& r = x;

    C(int y) {
        r = y;
    }
};
```

Actually, we just say that `x = y` (no dangling reference, since `r` is initially assigned) 

```cpp
int x = 0;
struct C {
    int& r = x;

    C(int y): r(y) {}
};
```

Dangling reference (`int& r = x` was not executed)

```cpp
class C {
    const int& r;

    C(): r(5) {}
};
```

Undefined behavior. Constant references extend the lifetime of objects until the lifetime of the references itself ends, but this only works inside functions when you declare local variables. If you are trying to extend the lifetime of a class field in this way, then this does not work anymore.

We need non-trivial destructor when we are capturing resources.

```cpp
class String {
private:
    char* arr = nullptr;
    size_t size = 0;
    size_t cap = 0;
public:
    String() {} // default constructor

    String(size_t n, char c): arr(new char[n + 1]), size(n), cap(n + 1) {
        memset(arr, c, n);
        arr[size] = '\0';
    }

    String(std::initializer_list<char> list)
        : arr(new char[list.size() + 1])
        , size(list.size())
        , cap(size + 1) {
            std::copy(list.begin(), list.end(), arr);
            arr[size] = '\0';
        }
    
    ~String() {
        delete[] arr;
    }
};
```

`memcpy` only for primitive types (`std::string` we should use `std::copy`)

```cpp
class String {
private:
    char* arr = nullptr;
    size_t size = 0;
    size_t cap = 0;

    String(size_t n): arr(new char[n + 1]), size(n), cap(n + 1) {
        arr[size] = '\0';
    }
public:
    String() = default; // default constructor

    String(size_t n, char c): String(n) {
        memset(arr, c, n);
    }

    String(std::initializer_list<char> list): String(list.size()) {
        std::copy(list.begin(), list.end(), arr);
    }
    
    String(const String& other): String(other.size) {
        memcpy(arr, other.arr, size + 1);
    }

    String(String&) = default;

    ~String() {
        delete[] arr;
    }
};
```

Delegate constructor.

```cpp
String s4 = s4; // UB
```

Copy constructor will be called. Actually we will call `String(other.size)` , but `other.size` is our field which is not defined yet.

We can restrict some constructors.
```cpp
String() = delete;
```

From C++11:
- initializer lists
- delegate constructors
- `=default`,  `=delete`

```cpp
String& operator=(const String& other) {
    if (this == &other) return *this;
    delete[] arr; 
    size = other.size;
    cap = other.cap;
    arr = new char[other.cap];
    memcpy(arr, other.arr, size + 1); // without (this == &other) it won't work because we already free our arr
    return *this;
}
```

The return type is `String&` because we want to change our exact string.

Copy & Swap

```cpp
String& operator=(const String& other) {
    String copy = other;
    swap(copy);
    return *this;
}

void swap(String& other) {
    std::swap(arr, other.arr);
    std::swap(size, other.size);
    std::swap(cap, other.size);
}
```

```cpp
String& operator=(String other) {
    swap(other);
    return *this;
}

void swap(String& other) {
    std::swap(arr, other.arr);
    std::swap(size, other.size);
    std::swap(cap, other.size);
}
```

Rule of Three
If there is non-trivial copy-constructor or non-trivial `=` operator or non-trivial destructor in your class - you should implement all three.