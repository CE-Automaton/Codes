#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5, V = 1e7+5;
int n, m, p, rr[V], ans[V], hd, tl, zhan[V];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
	File("memory");
	for(int i = 0; i <= 10000000; ++i)
		rr[i]=1, ans[i]=inf;
	read(n), read(m);
	for(int i = 1; i <= n; ++i) {
		read(p);
		for(int j = 0; j <= 10000000; j+=p)
			rr[j]=max(rr[j], p);
	}
	ans[0]=0;
	zhan[hd=tl=1]=0;
	for(int j = 1; j <= 10000000; ++j) {
		while(hd <= tl && zhan[hd]+rr[zhan[hd]] <= j) ++hd;
		if(hd <= tl) ans[j]=ans[zhan[hd]]+1;
		if(rr[j] > 1) zhan[++tl]=j;
	}
	for(int i = 1; i <= m; ++i) {
		read(p);
		if(ans[p] == inf)
			puts("oo");
		else
			write(ans[p], '\n');
	}
	// debug("clock:", clock());
	return 0;
}