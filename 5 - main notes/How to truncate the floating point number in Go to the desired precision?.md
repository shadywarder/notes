**2024-12-18 22:54**
Tags: [[go]] [[tba]]

## How to truncate the floating point number in Go to the desired precision?
Recently, I ran into a problem while trying to testing my nonlinear affine transformation function. Here it is:
$$
\text{x\_new} = \frac{1}{\pi} \arctan \sin (\pi \sqrt{x^2+y^2})
$$
$$
\text{y\_new} = \frac{1}{\pi} \arctan \cos (\pi \sqrt{x^2+y^2})

$$

And here is the actual log:

![[Pasted image 20241218230456.png]]

So, I came to the following (possible) solution:

```go
package pkg

import (
	"math"
)

func TruncateFloat(f float64, precision int) float64 {
	factor := math.Pow(10, float64(precision))
	return math.Trunc(f*factor) / factor
}
```

Let me illustrate it with the following example:

```go
TruncateFloat(-0.2441499708997524, 5)

factor = 10000
f*factor = -24414.99708997524
math.Trunc(f*factor) = -24144

math.Trunc(f*factor) / factor = -0.24144
```

## References
https://habr.com/ru/articles/251537/