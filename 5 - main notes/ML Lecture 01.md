**2025-02-02 17:22**
**Tags:** [ml](../2%20-%20tags/ml.md) [university](../3%20-%20indexes/university.md)

## ML Lecture 01
**Machine Learning** - computer programs that *improve* their *performance* at some *task* through *experience*.

### Data
$$ D = \{(x_i, y_i)\}_{i=1}^N$$
- $x_i$ - predictors: for example, execution behavior of a program
- $y_i$ - targets: for example, malware or not
- $N$ - number of available examples

### Performance
- Needs to be defined according to the given task
- For example: the ratio of correctly identified malware

### Goal of Learning
- Learning or inferring a "functional" relationship between predictors and target
$$ D = \{(x_i, y_i)\}_{i=1}^N, x \in \mathbb{R}^d$$
$$y = f(x), \hat{f} \approx f - \text{goal of learning}$$
### Estimating $f$
$$y=f(x;\text{parameters})$$
$$y=f(x;w)$$
$$y=f(x;w_{0}, w_{1}) = w_{0} + w_{1}x$$
### Putting It All Together

![](../attachments/Pasted%20image%2020250202175657.png)

Due to the presence of $Y$ we call such algorithm supervised learning.
### Compare the Response Variable

![](../attachments/Pasted%20image%2020250202180010.png)

So, the response can be categorical data or numerical.
$$Y \text{ categorical} \to \text{classification problems}$$
$$Y \text{ numerical} \to \text{regression problems}$$
### Accessing the Quality of Learning
- Let $T_r = \{x_{i}, y_{i}\}_{i=1}^N$ be the training data we used to estimate $\hat{f}(x)$.
- To access the quality of estimate, we can compute
$$\text{MSE}_{T_{r}}=\text{Ave}_{i\in T_{r}}[y_{i}-\hat{f}(x_{i})]^2$$
- But this is not a reliable approach

### What can go wrong?

![](../attachments/Pasted%20image%2020250202181422.png)

### Thus Use Separate Test Data
- This, if possible, we should try to use the test data $T_{e} = \{x_{i},y_{i}\}_{i=1}^M$

### Bias Variance Tradeoff
$$\mathbb{E}(y_{0}-\hat{f}(x_{0}))^2=\mathbb{V}(\hat{f}(x_{0})) + [\text{Bias}(\hat{f}(x_{0}))]^2+\mathbb{V}(\epsilon)$$
Typically, as the *flexibility or complexity* of $\hat{f}$ increases, its variance increases, and its bias decreases. So choosing the flexibility based on the average test error amounts to a *bias-variance trade-off*.

- Variance is high -> model is overfitting (way to complex models).
- Bias is high -> model is underfitting (way to simple models).

## References