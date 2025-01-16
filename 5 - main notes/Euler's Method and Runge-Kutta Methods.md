**2024-12-13 22:16**
Tags: [[diffeq]] [[math]]

## Euler's and Runge-Kutta Methods
### Problem
Find a partial solution of the differential equation 
$$
y \prime +2y = x^2
$$
corresponding to the initial condition $y(0) = 1$ using Euler's method in the interval $[0,1]$ with step $h=0.1$. Build a table and plot of the approximate solution.

The actual solution is 
$$
y = \frac{3}{4}e^{-2x}+\frac{1}{2}x^2-\frac{1}{2}x+\frac{1}{4}
$$

So, we should find and draw a *polyline* that approximates plot of the $y = \frac{3}{4}e^{-2x}+\frac{1}{2}x^2-\frac{1}{2}x+\frac{1}{4}$ in the interval $[0,1]$. Since the length of the interval is $1$, and the step is $0.1$, the *polyline* will consist of $10$ segments: $M_{0}M_{1}, \dots, M_{9}M_{10}$. Moreover, the point $M_{0}(x_{0},y_{0}) = M_{o}(0,1)$ is already known - it corresponds the initial condition $y(0) = 1$. In addition, the $x$ coordinates of other points are obvious: $M_{1}(0.1, y_{1}), \dots, M_{10}(1, y_{0})$.

$y_{1}, \dots, y_{10}$ remains to find. No differentiation and integration - just addition and multiplication! Each subsequent $y$ coordinate is obtained from the previous one using a simple recurrent formula:
$$
y_{i+1}=y_{i}+h\cdot f(x_{i},y_{i})
$$
$$
f(x,y)=x^2-2y
$$
$$
y_{1}=y_{0} + h \cdot f(x_{0}, u_{0}) = 1 - 0.2=0.8
$$
$$
\vdots
$$

| $i$     | $x_{i}$ | $y_{i}$ | $f(x_{i}, y_{i})$ | $hf(x_{i}, y_{i})$ |
| ------- | ------- | ------- | ----------------- | ------------------ |
| $0$     | $0$     | $1$     | $-2$              | $-0.2$             |
| $1$     | $0.1$   | $0.8$   | $-1.59$           | $-0.159$           |
| $2$     | $0.2$   | $0.641$ | $-1.242$          | $-0.1242$          |
| $\dots$ |         |         |                   |                    |

## References