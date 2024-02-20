#include <bits/stdc++.h>
#define mod 998244353
#define inv2 499122177
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, m, u, v, st, up[N], dep[N], dp[N][3][3], az[N][3][3];
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
	dep[x]=dep[fa]+1, up[x]=fa;
	if(dep[x] > dep[st]) st=x;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x);
}
void get(int x, int fa) {
	dep[x]=dep[fa]+1, (dep[x] == (m+1)/2 ? dp[x][1][1] : dp[x][0][0])=1;
	for(int y : to[x])
		if(y != fa) {
			get(y, x);
			for(int i = 0; i < 3; ++i)
				for(int j = 0; j < 3; ++j)
					az[x][i][j]=dp[x][i][j], dp[x][i][j]=0;
			for(int i = 0; i < 3; ++i)
				for(int j = 0; j < 3; ++j)
					for(int o = 0; o < 3; ++o)
						for(int p = 0; p < 3; ++p)
							for(int k = 0, l = 0, r = 0; k < 3; ++k) {
								l=min(2, i+o*(k == 1));
								r=min(2, j+p*(k == 2));
								dp[x][l][r]=upd(dp[x][l][r]+1LL*az[x][i][j]*dp[y][o][p]%mod);
							}
		}
}

signed main() {
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0), dfs(st, 0);
	m = dep[st];
	int ss = (m-1)/2;
	while(ss)
		--ss, st=up[st];
	// debug(st, "!?\n");
	if(m&1) {
		// puts("?");
		get(st, 0);
		write(1LL*dp[st][1][1]*inv2%mod, '\n');
	}
	else {
		int x = st, y = up[st];
		dep[y]=0, get(x, y);
		dep[x]=0, get(y, x);
		write(1LL*upd(dp[x][1][0]+upd(dp[x][1][1]+dp[x][1][2]))*upd(dp[y][1][0]+upd(dp[y][1][1]+dp[y][1][2]))%mod, '\n');
	}
	return 0;
}