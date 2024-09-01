## Peak finder
### One-dimensional version 

| a   | b   | c   | d   | e   | f   | g   | h   | i   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   |


a - i are numbers
Position 2 is a peak iff $b \geq a$ and  $b \leq a$
Position 9 is a peak iff $i \geq h$

### Problem
Find a peak if it exists.

***Straightforward algorithm***
Start from left and just do simple traversal.
Worst-case complexity: $\Theta(n)$ 

***Recursive approach***
Look at $n / 2$ position
1. if $a[n/2] < a[n/2-1]$ then only look at the left half $1 \ldots n/2 - 1$ to look for a peek.
2. Else if $a[n/2] < a[n/2+1]$ then only look at the left half $n/2 + 1 \ldots n$ to look for a peek. 
3. Else $n/2$ position is a peak.

Recursive relation: $T(n) = T(n/2) + \Theta(1)$ 
Base case: $T(1)$ = $\Theta(1)$ 
Overall time complexity: $T(n) = \Theta(1) + \Theta(1) + \ldots + \Theta(1) = \Theta(\log_2 n)$  

## 2D version

Matrix with $n$ rows and $m$ columns. 

|     | c   |     |
| --- | --- | --- |
|     | c   |     |
| b   | a   | d   |
|     | e   |     |


$a$ is a 2D-peak iff $a \geq b, a \geq c, a \geq d, a \geq e$ 

***Greedy Ascent algorithm***
Time complexity: $\Theta(nm)$ 

***Binary-search on 2D*** 
1. Pick the middle column $j = m/2$ 
2. Find a 1D-peek at $(i, j)$
3. Use $(i, j)$ as a start to find a 1D-peek on row $i$.

Incorrect!

*Problem:* 2D peak may not exist on row $i$

|     |     |     |     |
| --- | --- | --- | --- |
|     |     | 10  |     |
| 14  | 13  | 12  |     |
| 15  | 9   | 11  | 17  |
| 16  | 17  | 19  | 20  |


Will take 12 as 1D-peek on column $j$ and then 14 will be selected as a 1D-peek - incorrect!

***Attempt #2***
1. Pick the middle column $j = m/2$ 
2. Find global max on column $j$ at $(i, j)$
3. Compare $(i, j-1), (i, j), (i, j+1)$ - If $(i, j) > (i, j-1), (i, j+1)$ - $(i, j)$ is a 2D-peek

Solve the row problem with the half the number of cols.
When you have a single col, find the global maximum <- done.
Recurrence relation: $T(n, m)=T(n, m/2) + \Theta(n) = \Theta(n \log_2 m)$  
