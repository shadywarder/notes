**2025-02-12 13:30**
**Tags:** [ml](../2%20-%20tags/ml.md) [university](../3%20-%20indexes/university.md)

## ML Lecture 03
### Iteratively Reducing the Loss

![](../attachments/Pasted%20image%2020250212135024.png)

### Binary Classification
Classification task that has two class labels.
For example,
- People whose credit applications were either approved or denied
- For simplicity, we are using a single feature

### What if we Treat the Problem As Predicting Class Probability?
Instead if predicting the class of a data point, what if we computed the probability of the data point belonging to a certain class?
That is $p(\text{approved = yes | creditscore})$.
We can "threshold" the result to decide the class.
What can be the advantage of doing this?
- $y$ becomes continuous
- Thus, we can solve this as a regression problem (reuse of what we learned earlier).

### Using Regression for Probability Estimation

![](../attachments/Pasted%20image%2020250212141411.png)

In such a way the probability may exceed one, but there is no way we want it!

### Restricting the Output to be between 0 and 1

![](../attachments/Pasted%20image%2020250212141713.png)

### Logistic Regression
Thus, we must model $p(x)$ using a function that gives outputs between 0 and 1 for all values of $x$.
One such function is the **Logistic or sigmoid function**
$$\sigma(z)=\frac{1}{1+e^{-z}}$$
This, in logistic regression, we use the **Logistic Function**.
$$z = w_{0}+w_{1}x_{1}+\dots+w_{d}x_{d}$$

### Loss Function of Logistic Regression
First take a look at **linear regression loss function**
$$\mathcal{L}(\textbf{w})=\frac{1}{n}\sum^n_{i=1}(y^i-\hat{y}^i)^2$$
$$\hat{y}= \frac{1}{1+e^{-w^{T}x^i}}$$
Due to **non-linearity of the sigmoid function in <ins>hypothesis of Logistic Regression</ins>**, MSE in **not convex** anymore.

### Loss Function for Logistic Regression 
Imagine a positive example in our credit approval application

![](../attachments/Pasted%20image%2020250212144534.png)

Thus we have two <ins>probability distributions</ins> for each training example: one is the true distribution and the other is the distribution that the model predicts for the training example.

In order to see how well our model is doing, we can measure the **difference between these two distributions**, and this is where cross entropy comes into play.

#### Cross Entropy
- is a measure of the difference between two probability distributions. The cross-entropy loss between two probability distributions $t$ and $p$ is defined as:
$$H(t, p)=-\sum_{i=1}^n t(i)\cdot \log(p(i))$$
Cross entropy goes two zero when predicted probability tends to exact probability.

Binary Cross Entropy Loss = $-(y\cdot\log(p)+(1-y)\cdot\log(1-p))$
Where:
- $y$ is the true label (0 or 1)
- $p$ is the predicted probability of the positive class (usually between 0 and 1)
- $\log$ is the natural logarithm function

## References