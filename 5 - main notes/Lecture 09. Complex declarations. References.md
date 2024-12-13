```cpp
void (*pfa[10])(int); 
// arrays of 10 pointers to function which takes int, returns void

void (*(*pff[10])(int))(int); 
// array of 10 pointers to function which takes int, return pointer to function which takes int returns void
```

```md
go right when you can, go left when you must
```

```cpp
char *(*(**foo[][8])())[];
// foo is array of array of 8 pointers to pinter to function returning pointer to array of pointers to char
```

```cpp
int (*(*foo)())()
// foo is pointer to function returning pointer to function returning int
```

```cpp
int& x; // CE
int& r = 5; // 5 is rvalue
int& r = x++; // CE (x++ is rvalue)
int& r = ++x; // OK 
```

lvalue-to-rvalue conversion

```cpp
int& g(int& x) {
    return ++x;
}

*p = *p2;
int t = g(x);
```

Dangling Reference

```cpp
int& f(int& x) {
    int y = ++x;
    return y;
}

int& f(int x) {
    int& y = ++x;
    return y;
}

int& f() {
    static int y = 0;
    return y; 
} // OK

int x = 0;
int& y = f(x); // UB or CE
```

```cpp
int& g() {
    int* p = new int(1);
    return *p;
}

int& x = g(); // int x = g(); munmap_chunk(): invalid pointer, Aborted (core dumped)
delete &x; // OK
```

```cpp
int x = 0;
int* p = &x;
int*& p2 = p;
p = new int(5);
delete p2;
```

```cpp
int a[10];
int (&b)[10] = a;
```

```cpp
void f(int);
void (&g)(int) = f;
```
