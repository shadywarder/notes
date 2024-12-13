**2024-12-09 17:52**

Tags: [[probability]] [[math]]

## Selection with vs. without replacement

>[!NOTE]
> A jar contains 30 red marbles, 50 green marbles and 20 blue marbles. A sample of 15 marbles is selected with replacement. Let $\xi$ be the number of red marbles and $\eta$ be the number of blue marbles. What is the joint probability mass function of $\xi$ and $\eta$.

Since the selection is done with replacement, this situation will involve working with multinomial distribution with parameters $n, m, p_r, p_g, p_b$.

$$
\zeta \sim \text{Multinom}(n, m; p_{r}, p_{g}, p_{b})
$$
Let $x$ be the number of red marbles, and $y$ be the number of blue marbles. Then the p.d.f. of multinomial distribution takes the following form:
$$
p_{\xi, \eta}(x, y) = \binom{15}{x, y, 15-x-y}(p_{r})^x(p_{b})^y(p_{g})^{15-x-y}
$$
>[!NOTE]
> A jar contains 30 red marbles, 50 green marbles and 20 blue marbles. A sample of 15 marbles is selected without replacement. Let $\xi$ be the number of red marbles and $\eta$ be the number of blue marbles. What is the joint probability mass function of $\xi$ and $\eta$.

Now, in the opposite, the selection is done without replacement. Therefore, we will be working with hypergeometric distribution.

$$
p_{\xi, \eta}(x, y) = \frac{\binom{30}{x} \binom{20}{y} \binom{50}{15-x-y}}{\binom{100}{15}}
$$
## References