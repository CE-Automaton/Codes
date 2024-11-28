#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 505;
int n, m, a[N], vis[N], mn[2][N], dp[2][N][N], now, sum[2][N][N], ans;

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
void solve() {
	for(int l = 0; l <= m; ++l)
		for(int r = l; r <= m; ++r)
			sum[0][l][r]=sum[1][l][r]=0;
	for(int l = 0; l <= m; ++l)
		for(int r = l; r <= m; ++r)
			sum[0][l][r]=upd((r == 0 ? 0 : sum[0][l][r-1])+dp[now][l][r]);
	for(int r = m; r >= 0; --r)
		for(int l = r; l >= 0; --l)
			sum[1][l][r]=upd(sum[1][l+1][r]+dp[now][l][r]);
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(a[i]), vis[a[i]]=i;
	now=0;
	if(vis[0]) 
		dp[0][vis[0]-1][vis[0]-1]=1;
	else
		for(int i = 0; i <= m; ++i)
			dp[0][i][i]=1;
	mn[0][0]=mn[1][m+1]=n;
	for(int i = 1; i <= m; ++i)
		mn[0][i]=min(mn[0][i-1], a[i]);
	for(int i = m; i >= 1; --i)
		mn[1][i]=min(mn[1][i+1], a[i]);
	solve();
	for(int i = 1; i < n; ++i) {
		if(!vis[i]) {
			now^=1;
			for(int l = 0; l <= m; ++l)
				for(int r = l; r <= m; ++r)
					dp[now][l][r]=0;
			for(int l = 0; l <= m; ++l)
				for(int r = l; r <= m; ++r) {
					if(mn[1][r+1] > i)
						dp[now][l][r]=sum[0][l][r];
					if(mn[0][l] > i)
						dp[now][l][r]=upd(dp[now][l][r]+sum[1][l][r]);
				}
			// for(int l = 0; l <= m; ++l, debug('\n'))
			// 	for(int r = l; r <= m; ++r, debug(' '))
			// 		debug(dp[now][l][r]);
			// debug('\n');
		}
		solve();
	}
	for(int l = 0; l <= m; ++l)
		for(int r = l; r <= m; ++r)
			ans=upd(ans+dp[now][l][r]);
	write(ans, '\n');
	return 0;
}