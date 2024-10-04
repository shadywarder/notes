The string-matching can be stated formally as follows. The text is given as an array $T[1:n]$ of length $n$, and the pattern is an array $P[1:m]$ of length $m \leq n$. The elements of $P$ and $T$ are characters drawn from an alphabet $\Sigma$ , which is a finite set of characters. For example, $\Sigma$ could be the set $\{0, 1\}$, or it could be the set $\{a, b, ..., z\}$. The character arrays $P$ and $T$ are often called *strings* of characters.

The *string-matching problem* is the problem of finding all valid shifts with which a given pattern $P$ occurs in a given text $T$. 

![[Pasted image 20240908005929.png]]

| Algorithm          | Preprocessing time | Matching time      |
| ------------------ | ------------------ | ------------------ |
| Naive              | 0                  | $O((n - m + 1) m)$ |
| Rabin-Karp         | $\Theta(m)$        | $O((n - m + 1) m)$ |
| Finite automaton   | $O(m\|\Sigma\|)$   | $\Theta(n)$        |
| Knuth-Morris-Pratt | $\Theta(m)$        | $\Theta(n)$        |
| Suffix array       | $O(n \lg n)$       | $O(m \lg n + km)$  |

A string $w$ is a *proper prefix* of $x$ if $w \sqsubset x$ and $|w| < |x|$, and likewise for a *proper suffix*. The empty string $\epsilon$ is both a suffix and a prefix of every string. 

***Overlapping-suffix lemma***
Suppose than $x$, $y$, and $z$ string such that $x \sqsupset z$   and $y \sqsupset z$. If $|x| \leq |y|$, then $x \sqsupset y$. If $|x| = |y|$, then $x = y$.  

## The naive string-matching algorithm

```
Naive-String-Matcher(T, P, n, m)
	for s = 0 to n - m
		if P[1:m] == T[s + 1:s + m]
			print "Pattern occurs with shift" s
```

```go
func NaiveStringMatcher(T, P string, n, m int) {
	for s := range n - m {
		if P == T[s:m + s] {
			fmt.Println("Pattern occurs with shift", s)
		}
	}
}
```

Procedure `Naive-String-Matcher` takes $O((n - m + 1) m)$ time, and this bound is tight in the worst case.

## The Rabin-Karp algorithm

