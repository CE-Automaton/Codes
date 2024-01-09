#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e5+5;
int n, m, pri[N], vis[N], tot, pp[N][25], su[25], mx, gs[N], jc[25], inv[25], inc[25], dp[N][25][2], ans;

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
int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}

signed main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= m; ++i) {
		pp[i][1]=1;
		for(int o = 1; o <= 17; ++o)
			for(int j = i+i; j <= m; j+=i)
				pp[j][o+1]=upd(pp[j][o+1]+pp[i][o]);
		for(int o = 1; o <= 18; ++o)
			su[o]=upd(su[o]+pp[i][o]);
	}
	for(int i = 1; i <= 18; ++i)
		dp[i][i][0]=su[i];
	for(int i = 2; i <= n; ++i)
		for(int j = min(18, i); j >= 1; --j)
			for(int lp = 0; lp <= 1; ++lp)
				for(int lj = 1; lj <= 18 && lj <= i-j; ++lj) 
					if(dp[i-j][lj][lp]) {
						int tp = (lp|(lj != 1));
						dp[i][j][tp]=upd(upd(dp[i][j][tp]+1LL*su[j]*dp[i-j][lj][lp]%mod)-(j+lj <= 18 ? dp[i][j+lj][lp] : 0)+mod);
					}
	write(dp[n][1][0], '\n');
	return 0;
}
