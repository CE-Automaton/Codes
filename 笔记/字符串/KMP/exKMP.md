## [扩展 KMP/exKMP（Z 函数）](https://www.luogu.com.cn/problem/P5410)

> Z 函数，又称**扩展 KMP (exkmp)**，可以 $O(n)$ 求出一个字符串的所有后缀与这个字符串的 LCP 长度。

Z 函数的做法与 Manacher 有着异曲同工之妙，即存下了目前已扩展到的右端点最靠右端的后缀 $i$ 与原串的 LCP：$[i,i+Z[i]-1]$，可以发现，当 $i<j\leq i+Z[i]-1$ 时，字符串 $[j,i+Z[i]-1]$ 与 $[j-i+1,z[i]]$（相当于将 $[1,Z[i]]$、$[i,i+Z[i]-1]$ 按 $j$ 对应的位置切开取了右半边） 一定是相同的，那么 $Z[j]$ 就可以直接初赋值上 $\min\{Z[j-i+1],i+Z[i]-j\}$，这样就能保证每个字符只会被扩展到 $1$ 次，因此总时间复杂度是 $O(n)$ 的~~（纯意识流是因为懒得画图嘿嘿）~~。

于是我们可以在 $O(|a|+|b|)$ 的时间中求模式串 $b$ 与另一个字符串 $a$ 所有后缀的 LCP 长度，具体的，可以先求出 $b$ 的 Z 函数后参照求 Z 函数的思路求 $a$ 的所有后缀与 $b$ 的 LCP，也可以将 $b$、$a$ 拼在一起后求一次 Z 函数，模板代码如下：（此处只展示第一种先求 $b$ 的 Z 函数的做法 QwQ，毕竟会求 Z 函数就会第二种求法了）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e7+5;
int n, m, z[N], p[N];
char a[N], b[N];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}

signed main() {
	scanf("%s%s", a+1, b+1);
    n=strlen(a+1), m=strlen(b+1);
    //求Z函数：
    z[1]=m;//初赋值
    for(int i = 2, l = 0, r = 0; i <= m; ++i) {
        if(i <= r) z[i]=min(z[i-l+1], r-i+1);//与Manacher异曲同工之处
        while(i+z[i] <= m && b[i+z[i]] == b[z[i]+1]) ++z[i];//向右扩展没有被扩展过的位置
        if(i+z[i]-1 > r) r=i+z[i]-1, l=i;//更新
    }
    //求a的后缀与b的LCP长度：
    for(int i = 1/*从1开始，求Z函数时则不能从1开始*/, l = 0, r = 0; i <= n; ++i) {
        if(i <= r) p[i]=min(z[i-l+1], r-i+1);//是对b求得的Z函数取min！一定要注意
        while(i+p[i] <= n && a[i+p[i]] == b[p[i]+1]) ++p[i];//a与b比较
        if(i+p[i]-1 > r) r=i+p[i]-1, l=i;//更新
    }
    long long ans1 = 0, ans2 = 0;
    for(int i = 1; i <= m; ++i)
        ans1^=1LL*i*(z[i]+1);
    for(int i = 1; i <= n; ++i)
        ans2^=1LL*i*(p[i]+1);
    write(ans1, '\n');
    write(ans2, '\n');
	return 0;
}
```

~~看着似乎用处不大可以被二分加哈希代替但是~~在有时~~不能二分哈希或者卡常的时候~~还是很有用的