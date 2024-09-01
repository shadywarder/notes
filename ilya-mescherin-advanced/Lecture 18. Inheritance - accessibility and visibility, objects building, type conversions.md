```cpp
struct Base {
    void f(int) {
        std::cout << 1;
    }
}

struct Derived: Base {
    void f(int) {
        std::cout << 2;
        return 0;
    }
}

int main() {
    Derived d;
    d.f(0);
}
```

1. Canditates selection
2. Overloading resolution
3. Privacy checking
All steps is processed during compilation

```cpp
struct Base {
    void f(int) {
        std::cout << 1;
    }
}

struct Derived: Base {
    using Base::f;
    
    void f(int) {
        std::cout << 2;
        return 0;
    }
}

int main() {
    Derived d;
    d.f(0); // 2 because f() in Derived overshadow f() Base
}
```

```cpp
struct Base {
    int x = 1;
    void f(int) {
        std::cout << 1;
    }
}

struct Derived: Base {
    // using Base::x; - CE
    int x = 2;
private:
    using Base::f;
public:
    void f(int) {
        std::cout << 2;
        return 0;
    }
}

int main() {
    Derived d;
    std::cout << d.Base::x << d.x; 
}
```

Privacy has no effect on the absence or presence of any methods in the class.

```cpp
struct Granny {
    int x;
    void f() {}
};

struct Mom: private Granny{
    friend int main();
    int x;
};

struct Son: Mom {
    int x;
    void f(Granny& g) { // CE because Granny is private within Son
        std::cout << g.x;
    }

    void f(::Granny& g) { // Correct
        std::cout << g.x;
    }
};

int main() {
    Son s;
    s.Granny::x;
}
```

`sizeof()` of empty struct is 1 byte.

```cpp
struct Base {
    void f() {}
};

// EBO - empty base optimization -> sizeof() = 8
struct Derived: Base {
    double y;
    void g() {}
};

int main() {
    std::cout << sizeof(Derived);
}
```

```cpp
struct Base {
    int x;
    Base(int x): x(x) {}
};

struct Derived: Base {
    double y;
    Derived(double y): y(y) {}
};

int main() {
    Derived d = 3.14; // CE, no default ctor for Base
}
```

```cpp
struct A {
    A(int x) { std::cout << "A" << x; }
};

struct Base {
    A x;
    Base(int x): x(x) { std::cout << "Base";}
};

struct Derived: Base {
    A y;
    Derived(double y): Base(0), y(y) {std::cout << "Derived" << y; }
};

int main() {
    Derived d = 1; // A0BaseA1Derived
}
```

First, the destructor body is processed, then the fields are destroyed.

```cpp
struct A {
    A(int x) { std::cout << "A" << x; }
     ~A() { std::cout << "~A" << x; }
};

struct Base {
    A x;
    Base(int x): x(x) { std::cout << "Base";}
    ~Base() { std::cout << "~Base" << x; }
};

struct Derived: Base {
    A y;
    Derived(double y): Base(0), y(y) {std::cout << "Derived" << y; }
    ~Derived() { std::cout << "~Derived" << x; }
};

int main() {
    Derived d = 1;
}

//~Derived~A~Base~A
```

Destructors works in reverse order compared to constructors.
Constructors inheritance (from C++11)

```cpp
struct A {
    A(int x) { std::cout << "A" << x; }
     ~A() { std::cout << "~A" << x; }
};

struct Base {
    A x;
    Base(int x): x(x) { std::cout << "Base"; }
    Base(const Base& other): x(other.x) { std::cout << "Copy"; }
};

struct Derived: Base {
    int y = 0;
    using Base::Base;
    Derived(double y): Base(x), y(y) {}
};

int main() {
    Derived d = 1;

    Base b = 1;
    Derived d2 = b; // implicit cast from child to parent, but copy constructors doesn't inherit
    std::cout << d2.y;
}
```

Copy constructors doesn't inherit.

```cpp
struct Base {
    int x = 1;
};

struct Derived: Base {
    int y = 2;
};

void f(Base& b) {
    std::cout << b.x;
}

// Slicing (in the Base will implicitly define constructor from Derived)
void f(Base b) {
    std::cout << b.x;
}

int main() {
    Derived d;
    f(d);
}
```

Base and Derived similarly to const and non-const

```cpp
struct Base {
    int x = 1;
    Base() = default;
    Base(const Base& other): x(other.x) { std::cout << "Copy!" }
};

struct Derived: Base {
    int y = 2;
};

void f(Base& b) {
    std::cout << b.x;
}

void f(Base b) {
    std::cout << b.x; // Copy!1
}

int main() {
    Derived d;
    f(d);
}
```