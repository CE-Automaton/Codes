#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, u, v, dp[N][8], g[8];
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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs(int x, int fa) {
	dp[x][0]=dp[x][4]=dp[x][6]=1;
	for(int y : to[x])
		if(y != fa) {
			dfs(y, x);
			auto add = [x, y](int i, int j, int k) { g[i]=upd(g[i]+1LL*dp[x][j]*dp[y][k]%mod); };
			add(0, 0, 3);
			add(1, 1, 3), add(1, 0, 4), add(1, 0, 1);
			add(2, 2, 3), add(2, 0, 6), add(2, 0, 2);
			add(3, 3, 3), add(3, 1, 6), add(3, 1, 2), add(3, 2, 4), add(3, 2, 1);
			add(4, 4, 7);
			add(5, 5, 7), add(5, 4, 2), add(5, 4, 6);
			add(6, 6, 5);
			add(7, 7, 5), add(7, 6, 1), add(7, 6, 4);
			for(int i = 0; i <= 7; ++i)
				dp[x][i]=g[i], g[i]=0;
		}
}

signed main() {
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	write(upd(dp[1][3]+upd(dp[1][5]+dp[1][7])), '\n');
	return 0;
}