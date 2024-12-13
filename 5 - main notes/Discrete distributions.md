**2024-12-05 22:38**

Tags: [[math]] [[probability]]

## Discrete distributions

### Bernoulli random variables
The random variable is called $\xi$ is called Bernoulli if there is a real number $0 \leq p \leq 1$ such that $\mathbb{P}(\xi = 0) = 1 - p, \mathbb{P}(\xi=1) = p$.
$$
\xi \sim \text{Bernoulli}(p)
$$
is used to mean that $\xi$ is a Bernoulli random variable.

### Binomial random variables
A binomial random variable $\xi$ is defined by the requirement that its probability mass function be the following:
$$
p_{\xi}(x)=C^x_{n}p^x(1-p)^{n-x}I(x\in \{0, \dots, n\})
$$
 where $n$ is a positive integer and $0 \leq p \leq 1$ a real number.
 A binomial random variable with parameters $n$ and $p$ models *the number of successes in $n$ independent Bernoulli trials with parameter $p$*.

### Geometric random variables
A random variable $\xi$ is said to be geometric with parameter $p$, with notation $\xi \sim \text{Geo}(p)$, if
$$
p_{\xi}(x) = (1-p)^{x-1}pI(x \in \{1,2,3,\dots\})
$$
This random variable models "the number of the trial is a sequence of independent Bernoulli trials (with parameter $p$) in which the first success occurs".
Sometimes a slightly different definition is given, through the pmf
$$
p_{\xi}(x) = (1-p)^{x}pI(x \in \{0,1,2,3,\dots\})
$$
but then the correct interpretation is "the number of trials in a sequence of independent Bernoulli trials (with parameter $p$) *before* the first success occurs".

**Example.** According to estimates from previous days, the user clicks on an advertisement with a probability of $p=0.05$. Today, company B plans to show a very important advertisement and requires Yandex to have a probability of at least 99% have clicked on it at least once. How many different people should I show this ad to?
**Solution.**
$$
\mathbb{P}(\xi\leq n) = \sum_{i=1}^{n} \mathbb{P}(\xi = k) = 1-(1-p)^n
$$
$$
1-(1-p)^n=0.99
$$
$$
n \geq \log_{0.95}0.01 \Rightarrow n \geq 90
$$
$$

$$
## References
https://moodle.innopolis.university/pluginfile.php/211214/mod_resource/content/15/CSE206_Fa24-03.pdf
https://education.yandex.ru/handbook/ml/article/veroyatnostnye-raspredeleniya