We can avoid effect of virtual functions by explicitly calling function from ancestor:

```cpp
Circle c(1.0);
c.Shape::f();
```

Actually, we can define pure virtual functions:

```cpp
struct Shape {
    virtual double area() const = 0; // pure virtual method
    virtual ~Shape() = default;
};

double Shape::area() const {
    return 0.0;
}
```

It can serves some kind of callback. 

```cpp
struct Base {
    int x = 0;
    virtual void f() {}
    virtual ~Base() = default;
};

struct Derived: Base {
    int y = 0;
    void f() override {}
};

int main() {
    Derived d;
    Base&b = d;
    dynamic_cast<Derived&>(b); // if cast isn't possible will throw std::bad_cast
    dynamic_cast<Derived*>(b); // if cast isn't possible will return nullptr

    Derived* pd = dynamic_cast<Derived*>(&b);
    if (pd) {
        ...
    }
}
```

If there is virtual functions in the class we can determine in runtime its exact type. 
We can only use `dynamic_cast` if there is virtual functions in the class. (Source type is not polymorphic)
`dynamic_cast` is quiet an expensive operation, since we need to go to the vtable via pointer.

RTTI - RunTime Type Information
Polymorphic types has pointer that keep information about the type (in static memory).

```cpp
int main() {
    Derived d;
    Base&b = d;

    typeid(b); // returns std::type_info (comparison operator and string with class name)

    std::cout << typeid(b).name << "\n"; 

    Derived* pd = dynamic_cast<Derived*>(&b);
    if (pd) {
        ...
    }
    
    if (Derived* pd = dynamic_cast<Derived*>(&b); pd) {
        ...
    }
}

```

`typeid` works for non-polymorphic types as well.
We can always do `dynamic_cast` to `void*` from polymorphic type (using this feature we can check is this polymorphic or not).
`dynamic_cast` perfectly fine if we cast type to its parent even if it isn't a polymorphic type.
We can do casting in the side: Mom -> Son -> Dad (Mom should be polymorphic)
In general , polymorphic should be the type from which it is cast (Source type should be polymorphic).
If we want type to be polymorphic but it doesn't have virtual methods we can simply define virtual destructor for it.
If Derived has trivial destructor but its fields doesn't - we need virtual destructor.

Examples when `static_cast`, `dynamic_cast` and `reinterpret_cast` give different results:

1. Casting in the side (from Mam to Dad): 
    - `static_cast` - CE
    - `dynamic_cast` - OK
    - `reinterpret_cast` - UB
2. Downcasting in case of virtual inheritance when ancestor is polymorphic:
    - `static_cast` - CE
    - `dynamic_cast` - OK
    - `reinterpret_cast` - UB

Two possible definitions for virtual functions:
1. If we will call it by reference or pointer to base class successor's method will be called
2. It is such function that decision which function to choose determines not in compile time as usual but in runtime, because polymorphic types have some information that we can use in runtime to determine what type it is.

**Memory layout of polymorphic objects (formally, not part of standard)**

```cpp
struct Base {
    virtual void f() {}
};

sizeof(Base) == 8

struct Base {
    virtual void f() {}
    int x;
};

sizeof(Base) == 16
```

![[Pasted image 20240705012234.png | center]]

```cpp
struct Derived: Base {
    void f() override {}
    virtual void g() {}
    int y;
};
```

Presence of non-virtual methods does not affect somehow to the size of the object because it simply placed in the *text* memory area.

![[Pasted image 20240705012627.png | center]]

A variable cannot change its type, but what lies beneath it can change its type.

```cpp
Base b;
b.f();
```

What's happening?
1. In runtime we follow the pointer that implicitly have our object to vtable
2. `f()` is the first virtual method of our class -> from current place we need to scan 8 bytes and get the pointer of our function.
Summary two pointers dereferencing.

```cpp
Derived d;
Base& b = d;
b.f();
```

Analogously, but we'll go to the Derived d vtable.

How `dynamic_cast` works?
It just follow this pointer and go to the `typeinfo` and then determines actual type of an object.

![[Pasted image 20240705014206.png | center]]

To cast from Son to Granny we'll need a pointer even it isn't a multiple inheritance.
We can do upcasting using `dynamic_cast` but not downcasting since Granny isn't polymorphic. `static_cast` should work properly.