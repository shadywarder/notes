```cpp
#include <iostream>

struct S {
    void f() {
        std::cout << "Hi!";
    }
};

int main() {
    const S s;
    s.f(); // CE
}
```

`void f()` implicitly takes non-const `this` as a first argument (like `self` in python) -> we cannot call such method from constant object because it an implicit cast from const to non-const will try to be executed.
We cannot call non-constant methods from constant objects.
Constant objects lack some of the operations relative to the original one.

```cpp
#include <iostream>

struct S {
    void f() const {
        std::cout << "Hi!";
    }
};

int main() {
    const S s;
    s.f(); // OK
}
```

```cpp
#include <iostream>

struct S {
    void f() const {
        std::cout << "Hi!";
    }
};

int main() {
    S s;
    const S& r = s;
    s.f(); // still CE
}
```

We cannot change fields in constant methods.

```cpp
#include <iostream>

struct S {
    int x = 0;
    void f() const {
        std::cout << 1;
    }

    void f() {
        std::cout << 2;
    }
};

int main() {
    const S s;
    s.f(); // 1
}
```

```cpp
int main() {
    std::string s = "abcd";
    const std::string& cs = s;
    const char& c = cs[0];
    s[0] = 'b';
    std::cout << c << "\n";
}
```

That's way override version of  `operator []` should return `const char&` not `char` be. Otherwise, we'd have `a` as output.

```cpp
int x = 0;
struct S {
    int& r = x;

    void f(int y) const {
        r = y;
    }
};
```

It will work because reference is a pointer on low-level. 

```cpp
struct S {
    int x = 1;
    int& r = x;

    void f(int y) const {
        r = y;
        std::cout << 1;
    }
};

```

`mutable` is needed, for example, when we start to count some actions on a class.
`static` is a method that belongs to the class as a whole.
`static` methods cannot be const.

```cpp
struct S {
    static int x = 1; // CE
    static const int x = 1; // OK

    static void f() {
        std::cout << "Hi!";
    }
};
```

Singletone design pattern

```cpp
#include <iostream>

struct Singleton {
private:
    Singleton() {}
    static Singleton* ptr;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton) = delete;
public:
    static Singleton& getObject() {
        if (ptr == nullptr) {
            ptr = new Singleton();
        }
        return *ptr;
    }
};

Singleton* Singleton::ptr = nullptr;

int main() {
    Singleton& s = Singleton::getObject();
}
```

```cpp
struct Latitude {
    double value;
    explicit Latitude(double value): value(value) {}

    explicit operator double() const {
        return value;
    }
};

struct Longitude {
    double value;
    explicit Longitude(double value): value(value) {}

    explicit operator double() const {
        return value;
    }
};
```

Implicit conversions `double -> Latitude` or `double -> Longitude` are prohibited.

Constructors with one argument should be explicit according to code style.

```cpp
explicit operator bool() const {

}
```
