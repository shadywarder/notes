**2024-12-04 01:06**

Tags: [[ai]] [[university]]

## Selection of a leaf in Monte Carlo Tree Search
*What formula is used for the selection of a leaf in Monte Carlo Tree and how? Explain the variable meanings and which part of the formula is responsible for exploitation and which for exploration.*

$$\text{UCT} = \frac{w_i}{n_i} + C\sqrt{\frac{\ln(N)}{n_i}}$$
$w_i$ - total reward, obtained from simulations of child node $i$
$n_i$ - number of times child node $i$ has been visited
$N$ - total number of visits to the parent node
$C$ - exploration parameter, a constant that controls the trade-off between exploration and exploitation

Higher $C$ - encourages more exploration
Lower $C$ - favors exploitation

1. exploration: $\frac{w_i}{n_i}$  - select the nodes with higher rewards values
2. exploitation: $C\sqrt{\frac{\ln(N)}{n_i}}$ encourages the study of less explored nodes, $\ln (N)$ - decreases exploration rate, $n_i$ - favors the nodes with small visit rate


## References
