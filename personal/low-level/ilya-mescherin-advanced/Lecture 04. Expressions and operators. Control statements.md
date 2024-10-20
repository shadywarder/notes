`a++` - lvalue
`++a` - rvalue

```md
++a++ = ++(a++) -> CE (lvalue operator cannot be applied to rvalue)
```

```md
(false ? a++ : ++a) = 1 -> CE (type of value cannot be determined) 
```

```cpp
**i = ++i + 2;       // well-defined
i = i++ + 2;       // undefined behavior until C++17
f(i = -2, i = -2); // undefined behavior until C++17
f(++i, ++i);       // undefined behavior until C++17, unspecified after C++17
i = ++i + i++;     // undefined behavior**
```

From C++17
```cpp
if (int x = 0; y > x) {

}
```
