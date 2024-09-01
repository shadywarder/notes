```cpp
#include <iostream>

int main() {
    int a[10'000'000]; // segfault
    static int a[10'000'000]; // OK
}
```

```cpp
void (int* a) {}

void (int a[3]) {}

// CE (redefinition)
// sizeof(a) = 8 (size of pointer not array)
```

When passing to a function array == pointer.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v(10);
    v[-1] = 500000;
    // Double free or corruption
    detete &v[0];
    // Double free or corruption
}
```

VLA - variable length array

```cpp
void f(int**) {} // 1
void f(int(*)[5]) {} // 2
void f(int* [5]) {} // 3
// 1 == 3 -> redefinition

int* b[5]; // Arrays of 5 pointers to int
int (*c)[5]; //  Pointer to array of 5 ints
```

```cpp
const char* s = "abcd\0efghi";
std::cout << s; // output: abcd
```

```cpp
#include <iostream>
#includ <algorithm>

bool cmp(int x, int y) {
    return x > y;
}

void f(int) {}
void f(double) {}

int main() {
    int a[5] = {5, 3, 8, 2, 9};
    bool (*p)(int, int) = &cmp;
    bool (*p)(int, int) = cmp; // Function to pointer conversion
    std::sort(a, a + 5, &cmp);
    std::sort(a, a + 5, cmp); // Function to pointer conversion

    void (*p)(int) = &f;
    void (*p2)(double) = &f;
    // p and p2 - two different pointers;
}
```

