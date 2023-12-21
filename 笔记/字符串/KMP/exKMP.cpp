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