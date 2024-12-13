A type for which part of the operations of the original type is prohibited.

```cpp
int x = 5;
int y = 6;
int *p = &x;

const int* pc = p; // int* -> const int*
*pc = 1; // CE

int* const cp = p;
cp = &y; // CE
```

```cpp
const int* pc = p; // int* -> const int*
int* p2 = pc; // CE
```

```cpp
int* -> const int* - OK
const int* -> int* - CE
```

```cpp
int x = 5;
const int* p = &x;
++x;
std::cout << *p; 

output: 6
```

```cpp
int x = 5;
const int& r = x;
int& const rc = x; // CE 
int& r2 = r; // CE
```

```cpp
const int* p = new const int; // CE
const int* p = new const int(1); // OK
const int* p = new const int[10]; // CE
const int* p = new const int[10]{}; // OK
int* p = new const int[10]{}; // CE
```

Const reference can be initialized by rvalue.

```cpp
{
    // Lifetime extension
    const std::string& s = "aaaaaaaa";
}
```

```cpp
void f(const std::string&);
void f(std::string&);

int main() {
    std::string s = "abc";
    f(s); // second function will be called
}
```

```cpp
const int& g(int x) {
    return x++;
} // no lifetime extension

int main() {
    g(5);
}
```

```cpp
int main() {
    int* p = new int(0);
    int** p = &p; 
    const int** cpp = pp;
}
```

Why it is actually prohibited:

```cpp
int main() {
    const char x = 'a';
    char* p = nullptr;
    const char** q = &p; // q now points to p; this is (fortunately!) an error
    *p = &x; // p now points to x
    *p = 'b'; // ouch: modifies a const
    std::cout << x;
}
```
