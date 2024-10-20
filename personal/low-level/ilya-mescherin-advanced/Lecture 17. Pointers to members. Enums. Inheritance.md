```cpp
#include <iostream>

struct S {
    int x;
    double y;

    void f(int z) {
        std::cout << x + z;
    }
};

int main() {
    int S::* p = &S::x;
    S s{1, 3.14};
    s.*p = 2;
    std::cout << s.*p;

    S* ps = &s;
    std::cout << ps->*p;

    void (S::* pf)(int) = &S::f;
    (s.*pf)(3); // 5
    (ps->*pf)(5); // 7
}
```

Actually, we `int S::* p = &S::x;` is size of shift to get required size.

```cpp
#include <iostream>

enum E {
    White, 
    Gray, 
    Black
};

int main() {
    E e = White;
    int e = White; // OK
    E e = 3; // CE
}
```

Enum classes appeared in C++11.

```cpp
#include <iostream>

enum class E {
    White, 
    Gray, 
    Black
};

int main() {
    E e = E::White;
    int e = E::White; // CE
    E e = 3; // CE
    std::cout << static_cast<int>(e);
}
```

```cpp
enum class E: int8_t {
    White, 
    Gray, 
    Black
};
```

```cpp
#include <iostream>

struct Granny {
    int x;
    void f() {}
};

struct Mom: protected Granny {
    int y;
    void g() {
        std::cout << x; // OK
    }
};

struct Son: Mom {
    int z;
    void h() {
        std::cout << x; // OK
    }
};

int main() {
    Son s;
    s.x // no access
}
```

```cpp
#include <iostream>

struct Granny {
    friend int main();
    friend struct Son;
    int x;
    void f() {}
};

struct Mom: protected Granny {
    int y;
    void g() {
        std::cout << x; // OK
    }
};

struct Son: Mom {
    int z;
    void h() {
        std::cout << x; // OK
    }
};

int main() {
    Son s;
    s.x; // no access
}
```

```cpp
#include <iostream>

struct Granny {
    friend int main();
    friend struct Son;
private:
    int x;
    void f() {}
};

struct Mom: private Granny {
    int y;
    void g() {
        std::cout << x; // no access
    }
};

struct Son: Mom {
    int z;
    void h() {
        std::cout << x; // no access
    }
};

int main() {
    Son s;
    s.x; // no access
}
```

```cpp
#include <iostream>

struct Granny {
    friend int main();
protected:
    int x;
    void f() {}
};

struct Mom: private Granny {
    friend struct Son;
    int y;
    void g() {
        std::cout << x; // no access because of private
    }
};

struct Son: Mom {
    int z;
    void h() {
        std::cout << x; // no access because of Mom
    }
};

int main() {
    Son s;
    s.x; // no access because of Mom
}
```

```cpp
#include <iostream>

struct Granny {
    friend int main();
protected:
    int x;
    void f() {}
};

struct Mom: private Granny {
    friend struct Son;
    int y;
    void g() {
        std::cout << x; // OK, int x is protected
    }
};

struct Son: Mom {
    int z;
    void h() {
        std::cout << x; // OK, because friend struct Son;
    }
};

int main() {
    Son s;
    s.x; // no access, because protected
}
```

```cpp
#include <iostream>

struct Granny {
    friend int main();
protected:
    int x;
    void f() {}
};

struct Mom: private Granny {
    friend struct Son;
    int y;
    void g() {
        std::cout << x;
    }
};

struct Son: Mom {
    int z;
    void h(Granny& g) {
        std::cout << g.x; // no access because it is external function for Granny
    }
};

int main() {
    Son s;
    s.x;
}
```

Friend does not inherited.

```cpp
#include <iostream>

struct Base {
    int x;
    void f() {
        std::cout << 1;
    }
};

struct Derived: Base {
    int y;
    void f() {
        std::cout << 2;
    }
};

int main() {
    Derived d;
    d.f(); // 2
}
```

```cpp
#include <iostream>

struct Base {
    int x;
    void f(int) {
        std::cout << 1;
    }
};

struct Derived: Base {
    int y;
    void f(double) {
        std::cout << 2;
    }
};

int main() {
    Derived d;
    d.f(0); // 2
}
```

```cpp
#include <iostream>

struct Base {
    int x;
    void f(int) {
        std::cout << 1;
    }
};

struct Derived: Base {
    int y;
    void f() {
        std::cout << 2;
    }
};

int main() {
    Derived d;
    d.f(0); // CE, since f(int) is not considered
}
```
