## 基于值域预处理的快速 GCD

### 原理

#### 定理一

##### 内容

可以将值域中每个 $x$ 分解成 $\{a,b,c\}$，满足 $a,b,c \leq \sqrt{x}$ 或 $\in Prime$ （定义这种分解为合法分解）

##### 证明

不妨设 $a\leq b\leq c$，若 $c \notin Prime$ 且 $c > \sqrt{x}$，则 $c$ 可分解为 $\{d,e\}$ 且 $d\leq e$、$d\leq \sqrt{x}$，而 $a\times b = \frac{x}{c} < \sqrt{x}$，则有 $n$ 的分解 $\{d,a,a\times b,e\}$，若 $e > \sqrt{x}$ 则可按该规律一直分解直到 $e\in Prime$ 或 $e\leq \sqrt{x}$

#### 定理二

##### 内容

对于询问 $\gcd(x,y)$，分别考虑 $a,b,c$ 对答案的贡献，$a$ 对答案的贡献为 $\gcd(a,y)$，再将 $y$ 除以 $\gcd(a, y)$（去重），再对 $b,c$ 干同样的事，三个贡献相乘即为 $gcd(x,y)$

##### 证明

> 易得引理若 $r\ |\ p,r\ |\ q$，则 $\gcd{p,q}=r\times \gcd(\frac{p}{r}, \frac{q}{r})$

分别代入即可证明

### 实现

#### 分解

对于 $x\geq 2$，找到 $x$ 的最小质因子 $p$ 以及 $\frac{x}{p}$ 的合法分解 $\{a,b,c\}$ 且 $a\leq b\leq c$，$x$ 的一种合法分解即为 $\{a\times p,b,c\}$ 的升序排序

考虑证明：

1. $x\in Prime$ 时显然成立，分解为 $\{1, 1, x\}$；
2. 当 $p \leq \sqrt[4]{x}$ 时将 $a\leq \sqrt[3]{\frac{x}{p}}$ 代入有 $a\times p \leq \sqrt{x}$；
3. 考虑 $p > \sqrt[4]{x}$ 的情况：
   - $a=1$，显然有 $a\times p = p \leq \sqrt{x}$；
   - $a\ne 1$，由于 $x$ 不是素数，$\frac{x}{p}$ 的最小质因子 $q$ 即为 $x$ 的第二小质因子，一定满足 $q \ge p$，而 $a,b,c$ 都为 $\frac{x}{p}$ 的非 $1$ 因子，有 $p\leq q \leq a\leq b \leq c$，$p\times a\times b\times c > (\sqrt[4]{x})=x$ 与 $p\times a\times b\times c=x$ 相矛盾，故不存在此情况

所以只用跑一次线性筛，用最小质因子更新即可，然后预处理出 $\sqrt{n} \times \sqrt{n}$ 的 $\gcd$ 数组

代码略

### 询问

直接用定理二的内容即可，值得注意的是有必要时（比如求 $\gcd(x,y)$ 时，$y$ 不被 $x$ 整除，且 $y \ge \sqrt{n}$）要手动套一层欧几里得算法，即：$\gcd(x,y)=\gcd(y\%x,x)$ 