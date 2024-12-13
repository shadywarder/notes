**2024-12-04 02:30**

Tags: [[ai]] [[university]]

## Neural Network Output Problem

![[Pasted image 20241204023058.png]]
$$y_j = f(\sum^n_{i=1}w_{ij}x_i + b_j)$$
$y_j$ - next neuron
$x_i$ - neuron from input layer
$w_{ij}$ - weight of the $x_i \rightarrow y_j$ edge
$b_j$ - bias
$n$ - number of neurons on the input layer
$f$ - activation function
$$f(x) = \max(0,x)$$
$y_1$ = $f(1+1) = 2$
$y_2 = f(2 - 1) = 1$
$y_3 = f(2 \cdot 0.5 + 1 \cdot 0.7 + 0.5) = 2.2$
$y_4 = f(2 \cdot 0.3 - 0.2 - 0.5) = 0$
$y_5 = f(2.2 \cdot 1 + 0.3) = 2.5$
$y_6 = f(2.2 \cdot 0.6 - 0.3) = 1.02$
$\text{output} = f(2.5 \cdot 1.2 - 1.02 \cdot 0.5) = 2.49$

## References
Daniel Gevorgyan @danielambda