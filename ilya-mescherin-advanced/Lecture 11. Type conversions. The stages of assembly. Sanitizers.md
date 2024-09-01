Using `reinterpret_cast` we can only look at the old in a new way. That's way we can only cast to `&` or `*`.

```cpp
long long y = 1729;
double& d = reinterpret_cast<double&>(y); // UB
d = 3.14;
std::cout << y;
```

```cpp
const int c = 5;
int& cc = const_cast<int&>(c); // UB
cc = 7;
std::cout << c << " " << cc; 

output:
5 7
```

C-style cast - all possible combinations of `static_cast`, `const_cast` and `reinterpret_cast`

Translation Hierarchy of C++ Program
1. Preprocessor (`#include <>` says to the processor the exact path to file) (.cpp file as a result)
2. Compiler (.cpp -> .s)
3. Assembler (.s -> .o) - object file (binary code)
4. Linker (.o -> .out) (pasting definition of functions)

`-E` - only preprocessing
`-S` - assembly file
`-c` - object file