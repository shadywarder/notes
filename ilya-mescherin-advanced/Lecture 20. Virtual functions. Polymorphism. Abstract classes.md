```cpp
struct Base {
    void f() {
        std::cout << 1;
    }
};

struct Derived: Base {
    void f() {
        std::cout << 2;
    }
};

int main() {
    Derived d;
    Base& b = d; // 1
    b.f();
}
```

Naturally, we want a more special case to be chosen, if possible. For instance, calculating the are of a polygon is quite a difficult task, and calculating the area of a square is a trivial. But actually, a square is a special case of a polygon, so we just want to calculate its area as a `side^2` and that's it. Here comes the virtual functions.

```cpp
// polymorphic type
struct Base {
    virtual void f() {
        std::cout << 1;
    }
};

struct Derived: Base {
    void f() {
        std::cout << 2;
    }
};

int main() {
    Derived d;
    Base& b = d; // 2
    Base* b = &d; // 2
    Base b = d; // 1 (copy constructor)
}
```

Type is called polymorphic if there is at least one virtual method.

```cpp
struct Base {
    virtual void f() {
        std::cout << 1;
    }
};

struct Derived: Base {
    int* p = new int(0);
    void f() {
        std::cout << 2;
    }
    ~Derived() {
        delete p;
    }
};

int main() {
    Base* b = new Derived();
    delete b; // memory leak, non-trivial ~Derived() won't be called
}
}```

```cpp
struct Base {
    virtual void f() {
        std::cout << 1;
    }

    virtual ~Base() = default;
};

struct Derived: Base {
    int* p = new int(0);
    void f() {
        std::cout << 2;
    }
    ~Derived() {
        delete p;
    }
};

int main() {
    Base* b = new Derived();
    delete b; // now everything is ok
}
```

```cpp
struct Base {
    virtual void f() const {
        std::cout << 1;
    }
};

struct Derived: Base {
    /* void f() const {
        std::cout << 2;
    } */

    void f() { 
        std::cout << 3;
    }
    
};

int main() {
    Derived d;
    Base& b = d;
    b.f(); // 1, because different signatures, if we mark it as virtual there will be no effect
}
```

We can write virtual both in the parent and in the child too.
From C++11 `override` specifier. Actually, is just adds some CE

```cpp
struct Base {
    virtual void f() const {
        std::cout << 1;
    }
};

struct Derived: Base {
    /* void f() const {
        std::cout << 2;
    } */

    void f() override { 
        std::cout << 3;
    }
    
};

int main() {
    Derived d;
    Base& b = d;
    b.f(); // CE
}
```

If we'll change return type it will be CE.
`final` keyword prohibits declaring methods with the same signature to their successors. It allows compiler to perform some optimizations and add some CE.

```cpp
```cpp
struct Base {
    virtual void f() const {
        std::cout << 1;
    }
};

struct Derived: Base {
    /* void f() const {
        std::cout << 2;
    } */

    void f() const final { 
        std::cout << 3;
    }
};

int main() {
    Derived d;
    Base& b = d;
    b.f();
}
```

`override final == final` because `final` includes `override` as well
we only need one of the `virtual`, `override` and `final`.

```cpp
int override = 5;
```

`override` in context-depending keyword, so we can declare the variable with such name.

```cpp
struct Granny {
    virtual void f() const {
        std::cout << 1;
    }
};

struct Mom: Granny {
    void f() const override{
        std::cout << 2;
    }
};

struct Son: Mom {
    void f() const final {
        std::cout << 3;
    }
};

int main() {
    Mom d;
    Granny& b = d;
    b.f(); // 2
}
```

```cpp
struct Granny {
    virtual void f() const {
        std::cout << 1;
    }
};

struct Mom: Granny {
private:
    void f() const override{
        std::cout << 2;
    }
};

struct Son: Mom {
    void f() const final {
        std::cout << 3;
    }
};

int main() {
    Mom d;
    Granny& b = d;
    b.f(); // 2 also
}
```

Privacy in compile time event and virtual is runtime -> not CE because it cannot choose function in compile time.

```cpp
int main() {
    Mom m;
    Granny g;

    int x; 
    std::cin >> x;

    Granny& gg = (x % 2 ? m : g);
    gg.f();
}
```

It proves that overloading resolving happens in runtime, because if not - it would be CE always.

```cpp
struct Granny {
private:
    virtual void f() const {
        std::cout << 1;
    }
};

struct Mom: Granny {
private:
    void f() const override{
        std::cout << 2;
    }
};

struct Son: Mom {
    void f() const final {
        std::cout << 3;
    }
};

int main() {
    Mom m;
    Granny g;

    int x; 
    std::cin >> x;

    Granny& gg = (x % 2 ? m : g);
    gg.f(); // CE because its private
}
```

```cpp
struct Mom {
    virtual void f() {
        std::cout << 2;
    }
};

struct Dad {
    virtual void f() {
        std::cout << 2;
    }
};

struct Son: Mom, Dad {
    void f() override {
        std::cout << 3;
    }
};

int main() {
    Son s;
    Mom& m = s;
    Dad& d = s;
    m.f(); // 3
    d.f(); // 3
}
```

```cpp
struct Mom {
    virtual void f() {
        std::cout << 2;
    }
};

struct Dad {
    void f() {
        std::cout << 2;
    }
};

struct Son final: Mom, Dad { // we cannot inherite this class
    void f() override {
        std::cout << 3;
    }
};

int main() {
    Son s;
    Mom& m = s;
    Dad& d = s;
    m.f(); // 3
    d.f(); // 2
}
```

`final` from C++11

```cpp
struct Shape {
    virtual double area() const = 0; // pure virtual method
    virtual ~Shape() = default;
};

int main() {
    Shape s; // CE
}
```

Class is called abstract if there is at least one pure virtual method;

```cpp
struct Shape {
    virtual double area() const = 0; // pure virtual method
    virtual ~Shape() = default;
};

struct Square: Shape {
    double a;
    Square(double a): a(a) {}
    double area() const override {
        return a * a;
    }
};

struct Circle: Shape {
    double r;
    Circle(double r): r(r) {}
    double area() const override {
        return 3.14 * r * r;
    }
};

int main() {
    Square sq(1.0);
    Shape& s = sq;
    s.area();
}
```

Polymorphism - by referring to the same and performing the same actions, we can get different results.

```cpp
int main() {
    std::vector<Shape*> v;
    v.push_back(new Square(1.0));
    v.push_back(new Circle(1.0));

    for (Shape* s : v) {
        std::cout << s->area() << "\n";
    } 
}
```

Static polymorphism - e.g. functions overloading
Dynamic polymorphism - the exact operation to be performed is defining in runtime