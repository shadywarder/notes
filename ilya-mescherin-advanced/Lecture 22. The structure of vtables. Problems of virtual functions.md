```cpp
struct Base {
    int x;
    static virtual void f() {}
};

struct Derived: Base {
    
};

int main() {
    Derived d; // CE
}
```

*Answer from StackOverflow:*
*That would make no sense. The point of virtual member functions is that they are dispatched based on the dynamic type of the object instance on which they are called. On the other hand, static functions are not related to any instances and are rather a property of the class. Thus it makes no sense for them to be virtual.*

```cpp
struct Base {
    int x;
    static virtual void f();
};

struct Derived: Base {
    
};

int main() {
    Derived d; // Linker error
}
```

We cannot leave virtual function without definition, because compiler will try to put the address of this function to vtable but there is nothing to put. We can fix it but specify it as pure virtual function `= 0`

```cpp
struct Base {
    virtual void h() = 0;
    void f() {
        std::cout << "f";
    }
    Base() {
        std::cout << "Base";
        h();
    }
    virtual ~Base() = default;
};

struct Derived: Base {
    int x;
    void h() override {
        std::cout << "h" << x;
    }
    Derived(): x(0) {
        std::cout << "Derived";
    }
};

int main() {
    Derived d; // Linker error
}
```

If a virtual function is called from the constructor, it is dispatched as a regular function, not as virtual one. Similarly for the destructors.

```cpp
struct Base {
    virtual void h() = 0;
    void f() {
        std::cout << "f";
        h();
    }
    Base() {
        std::cout << "Base";
        f();
    }
    virtual ~Base() = default;
};

struct Derived: Base {
    int x;
    void h() override {
        std::cout << "h" << x;
    }
    Derived(): x(0) {
        std::cout << "Derived";
    }
};

int main() {
    Derived d; // Runtime error: pure virtual function called
}
```

During the creation of a polymorphic object, its pointer on vtable undergoes changes: as the constructors of its parents are triggered, it will point to the type that will be constructed at this stage in order to don't fall into the successor's method, which has not yet been constructed. For the destructors it works it reverse order respectively. 
The initialization list follow the same calling rules as the constructor.

```cpp
struct Base {
    virtual void f(int x = 1) {
        std::cout << "Base " << x;
    }
};

struct Derived: Base {
    void f(int x = 2) override {
        std::cout << "Derived " << x;
    }
};

int main() {
    Derived d;
    Base& b = d;
    b.f(); // Derived 1
}
```

`f()` is a function that takes exactly one argument. So, compiler should decide which function to choose in compile time, because we cannot postpone the substitution of arguments to the function until runtime. In compile time compiler only knows about `Base`, so he put `x = 1` as argument and in runtime it call the `Derived` version.

```cpp
struct Mother {
    int x = 0;
    virtual void f() {
        std::cout << x;
    }
};

struct Father {
    int y = 1;
    virtual void g() {
        std::cout << y;
    }
};

struct Son: Mother, Father {
    int z = 2;
    void f() override {
        std::cout << z;
    }
    void g() override {
        std::cout << z;
    }
};

struct S {
    long long a;
    long long b;
}

int main() {
    Son son;
    
    void (Mother::*p)() = &Mother::f;
    Mother& m = son;
    (m.*p)(); // 2

    void (Father::*p2)() = &Father::g;
    Father& f = son;
    (f.*p2)(); // 2

    void (Son::*p3)() = &Father::g;
    (son.*p3)(); // 2

    void (Son::*p4)() = &Son::g;
    (son.*p4)(); // 2
    
    std::cout << sizeof(p) << ' ';
    S s = reinterpret_cast<S&>(p);
    std::cout << s.a << ' ' << s.b << '\n'; // 16 1 0

    std::cout << sizeof(p2) << ' ';
    S s2 = reinterpret_cast<S&>(p2);
    std::cout << s2.a << ' ' << s2.b << '\n'; // 16 1 0

    std::cout << sizeof(p3) << ' ';
    S s3 = reinterpret_cast<S&>(p3);
    std::cout << s3.a << ' ' << s3.b << '\n'; // 1 16
    // 16 - offset from the beginning of the obj

    std::cout << sizeof(p4) << ' ';
    S s4 = reinterpret_cast<S&>(p4);
    std::cout << s4.a << ' ' << s4.b << '\n'; // 9 0 
    // 9 - offset from the beginning of the vtable, because it is second virtual method of son 
}
```

We need to somehow to distinguish virtual pointer to members from non-virtual. Common pointer to members just stores the addresses that are even. So, to mark pointer as virtual we set its last bit to 1. So, if the last bit of the pointer is 1 the compiler understands, that this is not the address of the function but offset from the beginning of the vtable.