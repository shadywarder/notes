```cpp
class C {
private:
    int x{5};
public:
    void f(int y) {
        std::cout << x + y;
    }

    friend void g(C, int);
    friend class CC;
};
  
void g(C c, int y) {
    std::cout << c.x + y + 1;
}
```

The Friend declaration grants a function or another class access to private and protected members of the class where the friend declaration appears.
In general, using friend is bad practice.

```cpp
#include <iostream>

class C {
private:
    class Inner {
    public:
        int x = 1;
    private:
        int y = 2;
    };
public:
    Inner f() {
        return Inner();
    }
};

int main() {
    C c;
    std::cout << c.f().x << "\n"; // 1
}
```

```cpp
#include <iostream>

class C {
private:
    void f(int) {
        std::cout << 1;
    }
public:
    void f(float) {
        std::cout << 2;
    }
};

int main() {
    C c;
    c.f(0); // CE
    c.f(3.14) // CE
}
```

Privacy is checked after the overload is selected.

```cpp
class Complex {
private:
    double re = 0.0;
    double im = 0.0;
public:
    // Initially, field re = 0 and after we assign value from constructor
    Complex(double re) {
        this->re = re;
    }

    // Member Initializer List
    Complex(double re): re(re) {}
    // line double re = 0.0; will be ignored

    Complex(double re, double im): re(re), im(im) {}

    Complex(double re, double im): im(im), re(re) {} // Warning
};

```

In such initialization, default constructor for the class field is called, and then a value is assigned. For non-trivial objects like `std::vector, std::string etc.` this operation is expensive.

If there is even one constructor aggregate initialization won't work. `{}` will be a call to the constructor.

`std::fill` and `memset` are better than usual for-loop since it can does one operation per word unlike for-loop which does one operation per byte.

`std::initializer_list` is lightweight type.

Curly brackets:
1. Checks for constructor from `std::initializer_list`
2. Checks just for some constructor
3. Aggregate Initialization

`String() = default; > String() {}`

```cpp
#include <iostream>
#include <cstring>


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
};


int main() {
    String s = {'a', 'b', 'c', 'd'};
    String s2{2, 'a'};
}
```
