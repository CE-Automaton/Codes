#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 8e3+5;
int n, u, v, f[N][N], g[N][N], op[N], siz[N], ans[N];
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
	siz[x]=1;
	f[x][1]=1;
	for(int y : to[x])
		if(y != fa) {
			dfs(y, x);
			for(int i = siz[x]; i >= 1; --i)
				for(int j = 1; j <= siz[y]; ++j)
					f[x][i+j]=upd(f[x][i+j]+1LL*f[x][i]*f[y][j]%mod);
			siz[x]+=siz[y];
		}
}
void dfs2(int x, int fa) {
	if(x != 1) {
		int mn = min(siz[x], n-siz[x]);
		for(int i = 1; i+i <= n && i <= mn; ++i)
			ans[i]=upd(ans[i]+1LL*f[x][i]*g[x][i]%mod);
	}
	for(int y : to[x])
		if(y != fa) {
			// int mn = min(siz[y], n-siz[y]);//这样写会TLE，时间复杂度相当于是n^3的
			// for(int i = 1; i <= mn; ++i)
			// 	g[y][i]=f[x][i];
			// for(int i = 1; i <= mn; ++i)
			// 	for(int j = 1; j <= i; ++j)
			// 		g[y][i]=upd(g[y][i]-1LL*g[y][i-j]*f[y][j]%mod+mod);
			// // debug(g[y][1], mn, siz[y], "???\n");
			// for(int i = mn; i >= 1; --i)
			// 	for(int j = 1; i+j <= mn; ++j)
			// 		g[y][i+j]=upd(g[y][i+j]+1LL*g[y][i]*g[x][j]%mod);
			int mn = siz[y];//这样写才是n^2的！
			for(int i = 2; i <= mn; ++i)
				g[y][i]=g[x][i-1];
			g[y][1]=1;
			for(int z : to[x])
				if(z != y && z != fa)
					for(int nw = mn; nw >= 1; --nw)
						for(int j = 1; j <= siz[z] && j+nw <= mn; ++j)
							g[y][nw+j]=upd(g[y][nw+j]+1LL*f[z][j]*g[y][nw]%mod);
			dfs2(y, x);
		}
}

signed main() {
	File("cl");
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	dfs2(1, 0);
	for(int i = 1; i+i <= n; ++i)
		write(ans[i], ' ');
	return 0;
}