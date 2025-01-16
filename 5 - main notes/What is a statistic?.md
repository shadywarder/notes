 **2024-12-05 20:27**

Tags: [[statistics]] [[math]]

## What is a statistic?
$$
T : (\xi_1, \dots, \xi_n) \longrightarrow \mathbb{R}
$$
Where $(\xi_{1}, \dots, \xi_{n})$ is a sample of a random variable $\xi$.

The most simple statistic is a sample mean:
$$
\bar{x} = \frac{\sum^{n}_{i=1}\xi_{i}}{n}
$$
$$
\bar{x} \xrightarrow{p} \mu
$$
Means: "Converges to".

There also exists sample variance:
$$
S^2 = \frac{1}{n-1}\sum_{i=1}^{n} (\xi_{i}-\bar{x})^2
$$
$T$ is a function of a random variable $\rightarrow$ statistic is a random variable itself. It implies that statistics have everything that random variables have:
- pdf
- cdf
- $\mu$ (mostly)
- $\mathbb{V}$ (mostly)

Actually the sample distribution is a pdf of a statistic.
## References
https://www.youtube.com/watch?v=mX8qg0TXoPA 