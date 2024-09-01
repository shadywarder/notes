```cpp
struct S {
    int x;
    double d = 3.14;
    void f(int y);
    void ff(int x) {
        this->x;
    }
};

void S::f(int y) {
    std::cout << x + y;
    ff(y);
}
```

```cpp
struct A {
    int x;
    double d = 3.14;

    struct AA {
        char c;
    };
};

sizeof(A) = 16
```

Privacy checks during compilation.

```cpp
#include <iostream>


class C {
private:
    const int x{5};
public:
    void f(int y) {
        std::cout << x + y;
    }
};


int main() {
    C c;
    std::cout << (int&)c;
}

output: 5
```
