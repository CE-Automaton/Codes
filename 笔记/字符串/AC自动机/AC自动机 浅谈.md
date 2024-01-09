## [AC 自动机](https://oi-wiki.org/string/ac-automaton/)

前置知识：Trie 树、[KMP](https://oi-wiki.org/string/kmp/)

> AC 自动机是 **以 Trie 的结构为基础**，结合 **KMP 的思想** 建立的自动机，用于解决多模式匹配等任务。
>
> 简单来说，建立一个 AC 自动机有两个步骤：
>
> 1. 基础的 Trie 结构：将所有的模式串构成一棵 Trie。
> 2. KMP 的思想：对 Trie 树上所有的结点构造失配指针。
>
> 然后就可以利用它进行多模式匹配了。

建树略 QwQ

### 失配指针

失配指针的目的在于省略多余的判断，和 KMP 的 $nxt$ 数组差不多，状态 $u$ 的 $fail$ 指针指向另一个状态 $v$，其中 $v\in Q$，且 $v$ 是 $u$ 的最长后缀（即在若干个后缀状态中取最长的一个在字典树上出现的作为 $fail$ 指针）

> 简单对比一下这里的 $fail$ 指针与 KMP 中的 $nxt$ 指针：
>
> 1. 共同点：两者同样是在失配的时候用于跳转的指针。
> 2. 不同点：nxt 指针求的是最长 Border（即最长的相同前后缀），而 fail 指针指向所有模式串的前缀中匹配当前状态的最长后缀。

因为 KMP 只对一个模式串做匹配，而 AC 自动机要对多个模式串做匹配。有可能 fail 指针指向的结点对应着另一个模式串，两者前缀不同。而因为 Trie 的结构，AC 自动机在做匹配时，同一位上可匹配多个模式串。

#### 构造指针

构造指针的思想也和 KMP 差不多，考虑字典树中当前的结点 $u$，$u$ 的父结点是 $p$，$p$ 通过字符 `c` 的边指向 $u$，即 $trie[p,\mathtt{c}]=u$。假设深度小于 $u$ 的所有结点的 $fail$ 指针都已求得。

1. 如果 $\text{trie}[\text{fail}[p],\mathtt{c}]$ 存在：则让 $u$ 的 $fail$ 指针指向 $\text{trie}[\text{fail}[p],\mathtt{c}]$。相当于在 $p$ 和 $\text{fail}[p]$ 后面加一个字符 `c`，分别对应 $u$ 和 $fail[u]$。
2. 如果 $\text{trie}[\text{fail}[p],\mathtt{c}]$ 不存在：那么我们继续找到 $\text{trie}[\text{fail}[\text{fail}[p]],\mathtt{c}]$。重复 $1$ 的判断过程，一直跳 $fail$ 指针直到根结点。
3. 如果真的没有，就让 $fail$ 指针指向根结点。

如此即完成了 $\text{fail}[u]$ 的构建，实现可直接使用 $BFS$，详见代码：

```cpp
queue <int> q;
for(int i = 1; i <= 26; ++i) 
    if(AC[0].vis[i])
        AC[AC[0].vis[i]].fil=0, q.push(AC[0].vis[i]);//第一层的fail指向根 
while(!q.empty()) {
    int u = q.front(); 
    q.pop();
    for(int i = 1; i <= 26; ++i)
        if(AC[u].vis[i])
            AC[AC[u].vis[i]].fil=AC[AC[u].fil].vis[i], 
            q.push(AC[u].vis[i]);//更新点的fail 
        else
            AC[u].vis[i]=AC[AC[u].fil].vis[i];//不存在, 则指向fail的vis[i]
}//因为到u时, u的fail指针已经处理过, 所以反复跳fail判vis的步骤就被替代了
```

#### 匹配模式串+优化

当文本串在 AC 自动机上走到状态 $u$ 的时候，可以一直跳 $fail$ 快速匹配模式串：

```cpp
int now = 0;
scanf("%s", t+1);
n=strlen(t+1);
for(int i = 1; i <= n; ++i) {
    now=AC[now].vis[t[i]-'a'+1];//文本串在Trie上的状态
    int tt = now;
    while(tt)//跳fail匹配
        ans+=AC[tt].cnt, tt=AC[tt].fil;
}
```

但每次走到一个状态就跳 $fail$ 的话时间复杂度是近似模式串总长度乘以文本串长度的，又由于 AC 自动机有个性质：“一个 AC 自动机中，如果只保留 $fail$ 边，那么剩余的图一定是一棵树。”所以我们可以先打上标记，再使用拓扑排序，在最后的时候一起跳 $fail$，这样时间复杂度就近似模式串总长度加文本串长度了，也可以使用子树求和

