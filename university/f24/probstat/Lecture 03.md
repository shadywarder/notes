## Random vectors
Given $(\Omega, \mathcal{F})$ a random vector $X : \Omega \rightarrow \mathbb{R}^d$ is simply an ordered collection of $d$ random variables $X_1, ..., X_d$ on $\Omega$ without any further assumptions. The $d$ components of the random vector $X$ could all be the same, for example. Or some of the components may be discrete random variables while the others are non-discrete. What matters is that they all be defined on the same $\Omega$ and be random variables with respect to the same $\sigma$-algebra $\mathcal{F}$. The number $d$ is referred to as the dimension of the random vector $X$.

**Example 3.1.** A dice is thrown twice. Let $X_1$ be the sum of the numerical outcomes in the two throws, and $X_2$ be the difference. Then $X = (X_1, X_2)$ is a random vector.

If, in addition, a probability measure $\mathbb{P}$ is given on $(\Omega, \mathcal{F})$, then any probability statement regarding the vector is captured by the distribution function (also called the cumulative distribution function) of the random vector $X = (X_1, ..., X_d)$, denoted by $F_X$, which is a function defined on $\mathbb{R}^d$ and taking values in the interval $[0, 1]$, defined by
$$F_X(x_1, ..., x_d)=\mathbb{P}(X_1\leq x_1, ..., X_d \leq x_d)$$
for any $(x_1, ..., x_d) \in \mathbb{R}^d$.
Any random vector has a distribution function (whether its components are discrete random variables or not). Finding the cdf of the random vector of **Example 3.1.** is a bit cumbersome. Notice that both components of that random vector are discrete random variables. Thus, we will discuss now *discrete random vectors*.

A *discrete random vector* is a random vector each of whose components is a discrete variable (recall, however, that they all need to be defined on the same probability space!). For discrete random vectors, we have the concept of joint probability mass function.

### Joint probability mass function of a discrete random vector
Given a random vector $X$ on $(\Omega, \mathcal{F}, \mathbb{P})$, the joint probability mass function is the function defined on $\mathbb{R}^d$, taking values in the interval $[0,1]$ denoted by $p_X$ and satisfying 
$$p_x(x_1, ..., x_d) = \mathbb{P}(X_1=X_1, ..., X_d=x_d)$$
For any discrete random vector,
$$\sum_{(x_1, ..., x_d) \in \mathbb{R}^d}p_X(x_1,...,x_d)=1$$
Let us explore some of the values of the pmf random vector of **Example 3.1.**. Denoting by $\xi_1$ the numerical outcome of the first dice throw, and by $\xi_2$ that of the second one, we have:
$$p_X(12,0)=p_X(10,0)=...=p_X(2,0)=\mathbb{P}(\xi_1=\xi_2=1)=\frac{1}{36}$$
$$p_X(11,1)=...=p_X(5,1)=p_X(3,1)=\mathbb{P}(\{\xi_1=2,\xi_2=1\} \cup\ \{\xi_1=1,\xi_2=2\}) = \frac{2}{36}$$
$$\vdots$$
$$p_X(7,5)=\mathbb{P}(\{\xi_1=6,\xi_2=1\}\cup\{\xi_1=1,\xi_2=6\})=\frac{2}{36}$$
and it's good exercise to describe this pmf in words and find a concise formula for it.

