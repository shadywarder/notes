[[cpp cores]]
**2024-12-03 00:41**

Tags: [[cpp cores]]

## Lecture 03. Declarations and definitions, scopes, namespaces

`using` in contrast with `typedef` can work with templates.

```cpp
template <typename T>
using v = std::vector<T>
```

`typedef` - C-style

```cpp
#include <iostream>

int x = 1;

int main() {
    int x = 0;
    {
        std::cout << ::x; // access to the global variable
    }
}
```

Double declaration (completely valid):

```cpp
void f(int x);
void f(int x);
```

**One Definition Rule (ODR)** - only one definition of any variable, function, class type, enumeration type, concept or template is allowed in any one translation unit.

```cpp
#include <iostream>

int f(int x) { return x + 1; }
int f(float x) { return x + 2; }

int main() {
    std::cout << f(0.0); // CE
}
```

```cpp
x; // unqualified-id
N::x; // qualified-id;
```

lvalue - we can assign to the result of calculation once again (=, +=, etc.)
rvalue - we cannot (+, -, etc.)

## References
