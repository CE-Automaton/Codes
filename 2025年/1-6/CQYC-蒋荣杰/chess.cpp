#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, u, v, dp[N][3/*don't l mid*/], lst[3], col[N], son[N], ans, pd[N], vis[N], nww;
vector <int> to[N], pp[1100005];

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
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), ++son[x];
	if(son[x] == 0) 
		return ;
	for(int y : to[x])
		if(y != fa)
			dp[x][2]=upd(dp[x][2]+upd(dp[y][1]+dp[y][2]));
	if(son[x] == 1) {
		for(int y : to[x])
			if(y != fa) {
				if(son[y] == 0) 
					dp[x][0]=dp[x][1]=1;
				else if(son[y] == 1) {
					for(int z : to[y])
						if(z != x) {
							dp[x][0]=upd(dp[z][0]+upd(dp[z][1]+dp[z][2]));
							dp[x][1]=dp[z][0];
						}
					dp[x][0]=upd(dp[x][0]+dp[y][1]);//3
				}
			}
		return ;
	}
	lst[0]=lst[1]=lst[2]=0;
	for(int y : to[x])
		if(y != fa) {
			ans=upd(ans+1LL*upd(lst[1]+lst[2])*upd(dp[y][1]+dp[y][2])%mod);
			lst[0]=upd(lst[0]+dp[y][0]);
			lst[1]=upd(lst[1]+dp[y][1]);
			lst[2]=upd(lst[2]+dp[y][2]);
		}
	if(son[x] == 2 && fa == 0) {
		int lll = 0;
		for(int y : to[x])
			if(y != fa) {
				if(!lll) {
					lll = y;
					continue;
				}
				if(son[y] == 0 && son[lll] == 0)
					ans=upd(ans+1);
				else if(son[y] == 0) {
					ans=upd(ans+upd(dp[lll][0]+upd(dp[lll][2]+dp[lll][1])));
					if(son[lll] == 1)
						for(int o : to[lll])
							if(o != fa)
								ans=upd(ans+dp[o][0]);
				}
				else if(son[lll] == 0) {
					ans=upd(ans+upd(dp[y][0]+upd(dp[y][2]+dp[y][1])));
					if(son[y] == 1)
						for(int o : to[y])
							if(o != fa)
								ans=upd(ans+dp[o][0]);
				}
				else if(son[y] == 1 && son[lll] == 1) {
					for(int o : to[y])
						if(o != x)
							for(int p : to[lll])
								if(p != x) 
									ans=upd(ans+1LL*dp[o][0]*dp[p][0]%mod);//3
				}
				else if(son[y] == 1) {
					for(int o : to[y])
						if(o != x)
							ans=upd(ans+1LL*dp[o][0]*dp[lll][0]%mod), //2
							ans=upd(ans+1LL*dp[o][0]*upd(dp[lll][1]+dp[lll][2])%mod), 
							ans=upd(ans+1LL*upd(dp[o][1]+dp[o][2])*dp[lll][0]%mod);
				}
				else if(son[lll] == 1) {
					for(int o : to[lll])
						if(o != x)
							ans=upd(ans+1LL*dp[o][0]*dp[y][0]%mod), //2
							ans=upd(ans+1LL*dp[o][0]*upd(dp[y][1]+dp[y][2])%mod), 
							ans=upd(ans+1LL*upd(dp[o][1]+dp[o][2])*dp[y][0]%mod);
				}
			}
	}
}

signed main() {
	File("chess");
	read(n);
	// if(n <= 20) {
	// 	for(int i = 1; i < (1<<n); ++i) {
	// 		for(int j = 0; j < n; ++j)
	// 			col[j+1]=((i>>j)&1);
	// 		nww=1;
	// 		ans+=nww;
	// 	}
	// 	write(ans, '\n');
	// 	return 0;
	// }
	if(n == 2) {
		puts("2");
		return 0;
	}
	int pdd = 1;
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u), 
		pdd&=(u == 1);
	if(pdd) {
		if(n >= 4) {
			puts("0");
			return 0;
		}
	}
	int rt = 1;
	for(int i = 1; i <= n; ++i)
		if(to[i].size() >= 2)
			rt=i;
	// debug(rt, "???\n");
	dfs(rt, 0);
	// for(int i = 1; i <= n; ++i)
	// 	debug(dp[i][0], dp[i][1], dp[i][2], "???\n");
	write(upd(ans+ans), '\n');
	return 0;
}
