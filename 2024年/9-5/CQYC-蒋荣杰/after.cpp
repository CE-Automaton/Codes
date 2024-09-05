#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int n, a[N], l[N], r[N], zhan[N], tot, f[2][N], sum[2][N];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("after");
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(a[i]);
		r[i]=n+1;
		while(tot && a[zhan[tot]] < a[i])
			r[zhan[tot]]=i, --tot;
		l[i]=zhan[tot];
		zhan[++tot]=i;
	}
	// for(int i = 1; i <= n; ++i)
	// 	debug(l[i], r[i], "???\n");
	int now = 0;
	f[0][0]=1;
	for(int j = 0; j <= n; ++j)
		sum[0][j]=1;
	for(int i = 1; i <= n; ++i) {
		now^=1;
		for(int j = 0; j <= n; ++j)
			f[now][j]=f[now^1][j], sum[now][j]=0;
		for(int j = l[i]+1; j < r[i]; ++j)
			f[now][j]=upd(f[now][j]+upd(sum[now^1][j-1]-(l[i] ? sum[now^1][l[i]-1] : 0)+mod));
		for(int j = 0; j <= n; ++j)
			sum[now][j]=upd((j ? sum[now][j-1] : 0)+f[now][j]);
	}
	write(f[now][n], '\n');
	return 0;
}