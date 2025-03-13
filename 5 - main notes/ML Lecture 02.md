**2025-02-11 19:36**
**Tags:** [ml](../2%20-%20tags/ml.md) [university](../3%20-%20indexes/university.md)

## ML Lecture 02
### Software Defects
We say a software has defects if
- It does something that it should not
- It does not do something that it should

**Problem Sources**
- Requirements definition
- Design
- Implementation
- Inadequate testing

### Predicting Number of Defects From the Point of view of ML
Given a computer program, let's say $p_i$
1. What will be be the $x_i$? Number of pointers, number of lines of code, number of recursive calls, etc.
2. What will be the $y_i$? Number of defects.

Thus, the goal of learning is to estimate following functional relationship
$$\text{\# of defects in } p_{i} = f(\text{features of }p_{i})$$
- Let's suppose there is just one feature,
- Then we can write the above expression as 
$$y=w_{1}x+w_{0}$$
- Which is the same equation as that of a straight line
- And that is why, we call it "Simple Linear Regression"

### In General, Linear Regression
$$y = w_{0}+w_{1}x_{1}+w_{2}x_{2}+\dots+w_{p}x_{p}$$
- The response variable is **quantitative**;
- The relationship between response and predictors is assumed to be **linear** in the inputs;
- Thus we are restricting ourselves to a hypothesis space of linear functions.

### Why Linear Regression
Although it may seem overly simplistic, linear regression is extremely useful
- Easy for inferencing
- Serves as a good jumping point for more powerful and complex approaches

### How Do We Train Linear Regression Model?

![](../attachments/Pasted%20image%2020250211201726.png)

### Mean Squared Error (MSE)
$$\mathcal{L}(w_{0},w_{1}) = \frac{1}{n}\sum^n_{i=1}(y_{i}-(w_{0}+w_{1}x_{i}))^2$$

### Polynomial Regression
Using the same framework that we learned, to fit a family of more complex models through a <ins>transformation of predictors</ins>.
Linear model has the following form
$$y=w_{0}+w_{1}x$$
It is linear in both predictor ($x$) and parameters ($w_0, w_1$).
Let's keep it linear in parameters, but make it quadratic in predictors.

That is,
$$y=w_{0}+w_{1}x+w_{2}x^2$$
Don't forget, "the model is still linear in parameters".

## References