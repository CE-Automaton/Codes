# 竞赛图 $\text{(tournament)}$

若简单图$G$满足任意不同两点间均存在一条有向边，则称$G$为竞赛图$\text{(tournament)}$。

### 比分序列 $\text{(Scores\ Sequence)}$

定义一个竞赛图的比分序列$\text{(Scores Sequence)}$，是把竞赛图的每一个点的出度从小到大排列得到的序列。

$\text{Landau’s Theorem}$ 与 $\text{Scores Sequence}$ 的性质、判定
$\text{Landau’s Theorem}:$一个长度为$n$的序列$s(s_1\le s_2\le …\le s_n),n\ge1$是竞赛图的比分序列充要条件为$:$
$$
\forall 1\le k\le n,\sum_{1\le i\le k}s_i \ge \binom{k}{2}
$$
切当$k=n$时上式取等号。

### $\text{Scores Sequence}$ 的性质

对于任意一个$n$个点的竞赛图$G$，其比分序列$s(s_1\le s_2\le …\le s_n),n\ge1$，满足于$\forall 1\le k\le n,\sum_{1\le i\le k}s_i \ge \binom{k}{2}$。

### $\text{Scores Sequence}$ 的判定

一个长度为$n$的序列$s(s_1\le s_2\le …\le s_n),n\ge1$若满足于$\forall 1\le k\le n,\sum_{1\le i\le k}s_i \ge \binom{k}{2}$，那么该序列是竞赛图的比分序列。

### $\text{Landau’s Theorem}$的证明与$\text{tournament}$的构造

其定理的必要性（即$\text{Scores Sequence}$的性质）的证明是显然的：

对于$n$个点的竞赛图，其任意由$k(k\le n)$个点构成的子图一定也是竞赛图，且满足出度和为$\binom{k}{2}$，而其子图内部的度数和一定小于等于全局的度数和。

接下来考虑证明$\text{Landau’s Theorem}$的充分性（即$\text{Scores Sequence}$的判定)：

我们考虑从从一个已知的$n$个点的竞赛图开始构造，具体地：每次改变一条边的方向，直到将其$\text{Scores Sequence}$“改造”成我们钦定的，满足定理的序列。

首先，我们构造一个“平凡的$n$个点的竞赛图$G$”，具体地：对于任一点$i$，我们向$\forall 1\le j < i$连边，其对应的$\text{Scores Sequence}$为$u(0,1,2,3,…n-1)$，我们的目标为将其“改造”为满足定理的任一序列$s(s_1\le s_2\le…\le s_n)$。

我们如下定义$dist(u.s)$：
$$
dist(u.s)=\sum_{1\le i\le n}|s_i-u_i|
$$
因为
$$
\sum_{1\le i\le n}s_i = \sum_{1\le i\le n}u_i=\binom{n}{2}
$$
$$
S_1=\sum_{1\le i\le n,s_i-u_i<0}s_i-u_i,S_2=\sum_{1\le i\le n,s_i-u_i>0}s_i-u_i
$$
所以
$$
S_1+S_2=\sum_{1\le i\le n}s_i-\sum_{1\le i\le n}u_i=0
$$
即$|S_1|=|S_2|$，且$dist(u.s)=|S_1|+|S_2|$，因此$dist(u.s)|2$。

因为$\forall 1\le i\le n,|s_i-u_i|\ge 0$，所以$dist(u.s)=0$当且仅当$\forall 1\le i\le n,s_i=u_i$。

那么我们的目标就很明显了：通过将若干条边改变方向，令$dist(u.s)=0$。

假定当前步我们构造到的竞赛图所对应的$\text{Scores Sequence}$为$u(u_1\le u_2\le…\le u_n)$，且满足于：
$$
\forall 1\le k\le n, \sum_{1\le i\le k}s_i \ge\sum_{1\le i\le k}u_i
$$
且在$k=n$时，上式取等号。

令$\alpha$为满足第一个$s_\alpha > u_\alpha$的位置，$\beta$为最后一个满足$u_\alpha=u_\beta$的位置，$\gamma$为第一个满足$s_\gamma<u_\gamma$的位置。

在我们未构造出满足$\text{Scores Sequence}$为$s(s_1\le s_2\le…\le s_n)$的竞赛图时，我们可以确定位置$\alpha$一定是存在的，因为若位置$\alpha$不存在，我们当前一定是构造成功的。

而因为位置$\alpha$存在，因此 位置$\beta,\gamma$也一定是存在的。

且位置$\gamma$一定是在位置$\beta$后面的，若$\gamma$在$\alpha$前面，那么一定有$\sum_{1\le i\le \gamma}s_i <\sum_{1\le i\le \gamma}u_i$。

而且其一定是不能在位置$\alpha\sim \beta$之间的。

因此$u_\gamma > s_\gamma \ge s_\beta > u_\beta$,即$u_\gamma\ge u_\beta+2$。

其意味着一定存在一个点$\lambda$，满足$\lambda\not= \beta,\lambda\not=\gamma$，存在边$(\gamma,\lambda),(\lambda,\beta)$。

简单反证即可。

那么我们将边$(\gamma,\lambda),(\lambda,\beta)$翻转为$(\beta,\lambda),(\lambda,\gamma)$。

其影响为$u_\gamma-1$,$u_\beta + 1$。且经过更改后的序列仍然满足：
$$
\forall 1\le k\le n, \sum_{1\le i\le k}s_i \ge\sum_{1\le i\le k}u_i
$$

而且因为$u_\gamma > s_\gamma$，$u_\beta<s_\beta$，因此这样操作下来我们可以使得其$dist(u.s)-2$，而又因为$dist(u.s)|2$，因此操作至多$\frac{1}{2}dist(u.s)$次就可以构造出满足$\text{Scores Sequence}$为$s(s_1\le s_2\le…\le s_n)$的竞赛图。

在证明了$\text{Landau’s Theorem}$的充要性的同时，我们也得到了一个$O(n^3)$的竞赛图构造算法。
