#include <bits/stdc++.h>
#define mod 998244353
#define inv 332748118
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int n, m, k, u, v, pd[N][N], dp[N][N];
char cs;

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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod, y=(y>>1);
	}
	return ret;
}

signed main() {
	File("bot");
	read(n), read(m), read(k);
	for(int i = 1; i <= k; ++i)
		read(u), read(v), scanf(" %c", &cs), pd[u][v]=(cs == 'D' ? 1 : (cs == 'R' ? 2 : 3));
	dp[1][1]=1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			if(pd[i][j] == 1 || pd[i][j] == 3)
				dp[i+1][j]=upd(dp[i+1][j]+dp[i][j]);
			if(pd[i][j] == 2 || pd[i][j] == 3)
				dp[i][j+1]=upd(dp[i][j+1]+dp[i][j]);
			if(!pd[i][j])
				dp[i+1][j]=upd(dp[i+1][j]+1LL*upd(dp[i][j]+dp[i][j])*inv%mod), 
				dp[i][j+1]=upd(dp[i][j+1]+1LL*upd(dp[i][j]+dp[i][j])*inv%mod);
		}
	write(1LL*dp[n][m]*ksm(3, n*m-k)%mod, '\n');
	return 0;
}