#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, u, v, dp[N][2], vis[N][2];
vector <int> to[N];

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
int dfs(int x, int pd) {
	if(vis[x][pd])
		return dp[x][pd];
	vis[x][pd]=1;
	dp[x][pd]=x;
	
	if(pd == 0) {
		int w = 0;
		for(int y : to[x])
			w=max(w, dfs(y, pd^1));
		dp[x][pd]=max(dp[x][pd], w);
	}
	else {
		int w = 1000000007;
		for(int y : to[x])
			w=min(w, dfs(y, pd^1));
		dp[x][pd]=max(dp[x][pd], (w == 1000000007 ? 0 : w));
	}
	return dp[x][pd];
}

signed main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u].push_back(v);
	for(int i = 1; i <= n; ++i) {
		write(dfs(i, 0), ' ');
		for(int j = 1; j <= n; ++j)
			dp[j][0]=dp[j][1]=vis[j][0]=vis[j][1]=0;
	}
	return 0;
}
