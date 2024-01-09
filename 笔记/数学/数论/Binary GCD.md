# Binary GCD

> 众所周知利用欧几里得算法（辗转相除法）可以做到在 log 的时间复杂度内求出两个数的最大公约数
>
> 但是有时候这还是不够快，例如这道题——**[Luogu P5435](https://www.luogu.com.cn/problem/P5435)**
>
> 如果直接辗转相除硬求 gcd 就会 T 得飞起，但是题解里那种方法 O(值域) 预处理 O(1) 查询又好麻烦，那么有没有一种更快的直接求两个数 gcd 的方法呢？
>
> 二进制 gcd 就是这样一种算法，它利用计算机优秀的二进制处理能力来计算 gcd。

已知结论：
$$
gcd(a,b)=\begin{cases}
2\times gcd(\frac{a}{2},\frac{b}{2})& \text{a、b is even}\\
gcd(\frac{a}{2},b)& \text{a is even,b is odd}\\
gcd(a,\frac{b}{2})& \text{a is odd,b is even}\\
gcd(|a-b|,\min{(a,b)})& \text{a、b is odd}\\
\end{cases}
$$
代码初步实现：

```c++
int gcd(int a,int b)
{
	if(a==b) return a;//a=b
	if(!a) return b;//a=0
	if(!b) return a;//b=0
	if(~a&1)//a是偶数
	{
		if(b&1)//b是奇数
			return gcd(a>>1,b);
		else//b是偶数
			return gcd(a>>1,b>>1)<<1;
	}
	if(~b&1)//a是奇数b是偶数
		return gcd(a,b>>1);
	//均为奇数
	if(a>b) return gcd((a-b)>>1,b);
	return gcd((b-a)>>1,a);
}
```

优化：

```c++
int gcd(int a,int b)
{
	if(!a)return b;//a=0
	if(!b)return a;//b=0
	int shift;//a,b二进制下末尾0的个数
	for(shift=0;~(a|b)&1;++shift)a>>=1,b>>=1;//把两个数末尾的shift个0都去掉
	while(~a&1)a>>=1;//现在两个数至少有一个奇数，2一定不是公约数
	//现在a一定是奇数
	do
	{
		while(!(b&1))b>>=1;
		//现在两个数一定都是奇数
		if(a>b)swap(a,b);
		b-=a;//更相减损
	}while(b);
	return a<<shift;//把最开始去掉的2^shift的公约数加上
}
```

再优化：

```c++
int gcd(int x, int y) {
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}
```