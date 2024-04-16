#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5, M = 1e3+5;
int n, fa[N], v[N], a[N], b[N], c[N], dp[M][M], ans[N];
vector <int> to[N];

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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1) ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int gcd(int x, int y) {
	if(x == 0 || y == 0) return (x|y);
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
void dfs(int x) {
	dp[x][0]=upd(1+mod-1LL*a[x]*b[x]%mod);
	dp[x][v[x]]=1LL*a[x]*b[x]%mod;
	for(int y : to[x]) {
		dfs(y);
		for(int j = 0; j <= n; ++j) {
			dp[x][j]=upd(dp[x][j]+1LL*dp[y][j]*upd(1+mod-1LL*a[x]*b[x]%mod)%mod);
			int tt = gcd(j, v[x]);
			dp[x][tt]=upd(dp[x][tt]+1LL*dp[y][j]*a[x]%mod*b[x]%mod);
		}
	}
	for(int i = 1; i <= n; ++i)
		ans[x]=upd(ans[x]+1LL*c[i]*dp[x][i]%mod);
}

signed main() {
	File("journey");
	read(n);
	for(int i = 2; i <= n; ++i)
		read(fa[i]), to[fa[i]].push_back(i);
	for(int i = 1; i <= n; ++i)
		read(v[i]);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]), b[i]=ksm(b[i], mod-2);
	for(int i = 1; i <= n; ++i)
		read(c[i]);
	dfs(1);
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}