```md
&: T -> T* Adresss
*: T* -> T Dereference
```

```cpp
#include <iostream>

int main() {
    int x = 0, y = 1;
    std::cout << &x << " " << &y << "\n";

    int* p = &x;
    std::cout << *p;

    p += 1;
}
```

```md
T* p = &x;
++p -> new address = old + sizeof(T);
```

```cpp
#include <iostream>

int main() {
    int a = 0;
    int* p = &a;
    std::cout << p << "\n";
    int** pp = &p;
    std::cout << pp << "\n";
}
```

```md
possible output:
0x7ffedeed5614
0x7ffedeed5618
```

`*p` - lvalue
`&a` - rvalue

```cpp
#include <iostream>

int main() {
    int a = 1;
    int* p = &a;
    {
        int b = 2;
        p = &b;
    }

    std::cout << p << "\n";
    std::cout << *p << "\n"; // UB, but most likely 2

    int c = 3, d = 4, e = 5, f = 6;

    ++*p; // still UB, and it's possible for on of c, d, e, f to be changed

    std::cout << c << d << e << f << "\n"; // possibly something different from 3456
    std::cout << *p << "\n"; // possibly not 2 already
}
```

```cpp
#include <iostream>

int main() {
    int x = 0;
    double d = 3.14;

    std::cout << (&x < &d) << "\n"; // CE
}
```

```cpp
#include <iostream>

int main() {
    int z = 23456325;
    std::cout << *(double*)z; // SEGFAULT
}
```
