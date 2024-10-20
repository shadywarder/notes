**Casts**
**Public Inheritance**
<center> Derived -> Base </center>

|                 | copy | ptr | ref |
| --------------- | ---- | --- | --- |
| **implicit**    | OK   | OK  | OK  |
| **static**      | OK   | OK  | OK  |
| **reinterpret** | CE   | OK  | OK  |
<center> Base -> Derived </center>

|                 | copy | ptr | ref |
| --------------- | ---- | --- | --- |
| **implicit**    | CE   | CE  | CE  |
| **static**      | CE   | OK  | OK  |
| **reinterpret** | CE   | OK  | OK  |
OK here is possibly UB

**Private Inheritance**
<center> Derived -> Base </center>

|                 | copy | ptr | ref |
| --------------- | ---- | --- | --- |
| **implicit**    | CE   | CE  | CE  |
| **static**      | CE   | CE  | CE  |
| **reinterpret** | CE   | OK  | OK  |
<center> Base -> Derived </center>

|                 | copy | ptr | ref |
| --------------- | ---- | --- | --- |
| **implicit**    | CE   | CE  | CE  |
| **static**      | CE   | CE  | CE  |
| **reinterpret** | CE   | OK  | OK  |
OK here is possibly UB

![[Pasted image 20240704000113.png | center]]

```cpp
class Mom {
    int x;
};

class Dad {
    int y;
};

class Son: public Mom, public Dad {
    int z;
};

void f(Dad*); // if we pass &son to this function pointer will be implicitly shifted by 4 bytes
```

![[Pasted image 20240704000953.png | center]]
Diamond Problem

![[Pasted image 20240704001203.png | center]]

Son object: gmgds = 20 byte

```cpp
class Granny {
    int g;
    voif f();
};

class Mom: public Granny {
    int m;
};

class Dad: public Granny {
    int d;
};

class Son: public Mom, public Dad {
    int s;
};

int main() {
    Granny& g = s; // CE - ambiguous cast
    s.f(); // CE
    Mom& m = s;
    static_cast<Dad&>(m); // CE
}
```

How to cast to Granny? Son -> Mam/Dad -> Granny

![[Pasted image 20240704002200.png | center]]
Inaccessible Base Class

```cpp
class Mom {
    void f();
};

class Dad {
    void f();
};

class Son {
    void f();
};

int main() {
    void (Mom::*p)() = &Mom::f; // shift = 0
    void (Son::*ps)() = p; // implicit cast, shift = 4 (or CE)
    (s.*p)(); // CE
    void (Dad::*p)() = &Dad::f; // OK
}
```

Pointer to method: 8 bytes (pointer) + 8 bytes (shift)

```cpp
class Granny {
    int g;
    voif f();
};

class Mom: public virtual Granny {
    int m;
};

class Dad: public virtual Granny {
    int d;
};

class Son: public Mom, public Dad {
    int s;
};

int main() {
    Son s; // sizeof s = 40 byte
    s.g; // OK
    s.f(); // OK
}
```

![[Pasted image 20240704004252.png | center]]

Vtable lie in a static memory

![[Pasted image 20240704011737.png | center]]

`static_cast<Son&>(g); // CE, there is no static_cast to derived class in case of virtual inheritance`

Mom -> Son - will work (because it starts from the piece of memory)
In vtable there are parameter "top offset" that stores the offset of the parents relative to the beginning of the object

```cpp
class Granny {
    int g;
};

class Mom: public Granny {
    int m;
};

class Dad: public  Granny {
    int d;
};

class Son: public virtual Mom, public virtual Dad {
    int s;
};
```

![[Pasted image 20240704014034.png | center]]


```cpp
class V {
    void f();
};

class W {
    void g();
};

class B: public virtual V, public W{
    void f();
    void g();
};

class C: public virtual V, public W {

};

class A: public B, public C {

};

int main() {
    A a;
    a.f(); // B overshadow method from virtual parent and other paths to f() is not considering
    a.g(); // two paths to g() from non-virtual parents -> CE
}
```

![[Pasted image 20240704014406.png | center]]
