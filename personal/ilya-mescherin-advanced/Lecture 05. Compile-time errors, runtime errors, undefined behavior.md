Floating Point Exception (FPE)

```cpp
#include <iostream>

int main() {
    int x;
    std::cout << 5 / x;
}
```

```cpp
#include <iostream>

int main() {
    for (int i = 0; i < 300; ++i) {
        std::cout << i << " " << i * 12345678 << "\n";
    }
}
```

```md
g++ -O2 main.cpp - infinite loop
```

`i * 12345678 -> i <= 174` - compiler does not check this condition 

Compiler flags:

```md
-Wall - turns all the warnings that g++ can tell you about
-Wextra - some more warnings
-Wpedantic - add warnings according to the c++ standard
-Werror - turns warnings into errors
```

Additionally we can disable certain warnings:

```md
-Wno-error=unused-variable
-Wno-unused-variable
```
