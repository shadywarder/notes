```cpp
struct Complex {
    double re = 0.0;
    double im = 0.0;
    
    Complex(double re): re(re) {}
    Complex(double re, double im): re(re), im(im) {}

    Complex operator+(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }
};
```

Now `operator+` is not transitive. 

```cpp
Complex c(1.0);
c + 3.14; // c.operator+(3.14) will work
3.14 + c; // won't work
```

So, it's better to overload operators outside of the class. We don't need `const` anymore.

```cpp
Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.re + b.re, a.im + b.im);
}
```

```cpp
Complex& operator+=(const Complex& other) {
    *this = *this + other;
    return *this;
}
```

It is a bad practice to overload `+=` like this. 

```cpp
#include <iostream>

struct Complex {
    double re = 0.0;
    double im = 0.0;

    Complex(double re): re(re) {}
    Complex(double re, double im): re(re), im(im) {}

    Complex& operator+=(const Complex& other) {
        re += other.re;
        im += other.re;
        return *this;
    }
};

Complex operator+(const Complex& a, const Complex& b) {
    Complex result = a;
    result += b;
    return result;
}
```

```cpp
int main () {
    Complex a(1.0);
    Complex b(2.0);
    Complex c(3.0);

    a + b = c; // assignment to rvalue, but it will compile because we did not do necessary overload for operator =
}
```

```cpp
Complex& operator=(const Complex& other) & { }
```

```cpp
bool operator<(const Complex& a, const Complex& b) {
    return a.re < b.re || a.re == b.re && a.im == b.im;
}

bool operator>(const Complex& a, const Complex& b) {
    return b < a;
}
```

Will compile.

```cpp
std::ostream& operator<<(std::ostream& out, const Complex& other);
std::istream& operator>>(std::istream& out, Complex& other);
```

```cpp
std::weak_ordering operator<=>(const char* other) const {
    return std::week_ordering::equivalent;
};
```

We can compare `const char* and std::string` as well as `std::string and const char*`.

If we implemented own `<=>` `==` won't be defined by default.

```cpp
struct UserId {
    int value;
    
    UserId& operator++() {
        ++value;
        return *this;
    } 

    UserId operator++(int) {
        UserId copy = *this;
        ++value;
        return value;
    }
};
```
