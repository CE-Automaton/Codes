#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+5;
int n, m, k, c[N][N], vis[N][N], f[N][N], ans, invv;

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
int sum(int x, int y) {
	if(x < 0) return 0;
	if(y == 1)
		return (x <= k);
	if(x == 0) 
		return 1;
	if(vis[x][m-y] == k)
		return f[x][m-y];
	vis[x][m-y]=k;
	return (f[x][m-y]=1LL*y*upd(sum(x-1, y)-1LL*sum(x-k-1, y-1)*c[x-1][k]%mod+mod)%mod);
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>=1);
	}
	return ret;
}

signed main() {
	read(n), read(m);
	memset(vis, -1, sizeof vis);
	for(int i = 0; i <= n; ++i) {
		c[i][0]=1;
		for(int j = 1; j <= i; ++j)
			c[i][j]=upd(c[i-1][j-1]+c[i-1][j]);
	}
	invv = ksm(ksm(m, n), mod-2);
	for(k = 0; k <= n; ++k)
		ans=upd(ans+1+1LL*upd(mod-sum(n, m))*invv%mod);
	write(ans, '\n');
	return 0;
}