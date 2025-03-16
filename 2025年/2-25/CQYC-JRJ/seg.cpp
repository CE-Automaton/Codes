#include <bits/stdc++.h>
#define mod 998244353
#define inf 1000000000000000LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 65;
int n, k, a[N], ans;
LL dp[N][N][N], yb[N];

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
	File("seg");
	read(n);
	yb[0]=-inf;
	for(int i = 1; i <= n; ++i)
		read(a[i]), yb[i]=max(yb[i-1]+a[i], (LL) a[i]);
	read(k);
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= k; ++j)
			for(int kk = 0; kk <= k; ++kk)
				dp[i][j][kk]=inf;
	dp[0][0][0]=-inf;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= k; ++j)
			for(int kk = 0; kk <= k; ++kk)
				for(int l = 0; j+l <= k; ++l) {
					LL now = max(yb[i-1]-kk+a[i]-l, (LL) a[i]-l);
					dp[i][j+l][yb[i]-now]=min(dp[i][j+l][yb[i]-now], max(dp[i-1][j][kk], now));
				}
	for(int j = 1; j <= k; ++j) {
		LL now = inf;
		for(int kk = 0; kk <= k; ++kk)
			now=min(now, dp[n][j][kk]);
		ans=upd(ans+upd(now%mod+mod));
	}
	write(ans, '\n');
	return 0;
}
