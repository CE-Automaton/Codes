#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 2e3+5;
int n, u, v, f[N][N], g[N][N], siz[N], tf[N], tg[N], c[N][N];
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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs(int x, int fa) {
	siz[x]=f[x][0]=1;
	for(int y : to[x]) 
		if(y != fa) {
			dfs(y, x);
			for(int i = 0; i <= siz[x]; ++i)
				for(int j = 0; j <= siz[y]; ++j)
					tf[i+j]=upd(tf[i+j]+1LL*f[x][i]*f[y][j]%mod*c[i+j][j]%mod), 
					tg[i+j]=upd(tg[i+j]+1LL*upd(1LL*g[x][i]*f[y][j]%mod+1LL*f[x][i]*g[y][j]%mod)*c[i+j][j]%mod);
			siz[x]+=siz[y];
			for(int i = 0; i <= siz[x]; ++i)
				f[x][i]=tf[i], g[x][i]=tg[i], tf[i]=tg[i]=0;
		}
	for(int i = 0; i <= siz[x]-1; ++i)
		tf[i+1]=1LL*f[x][i]*(i+1)%mod, 
		tg[i+1]=upd(1LL*g[x][i]*(i+1)%mod+1LL*f[x][i]*(i*(i+1)/2)%mod);
	for(int i = 1; i <= siz[x]; ++i)
		tf[i-1]=upd(tf[i-1]+f[x][i]), 
		tg[i-1]=upd(tg[i-1]+g[x][i]);
	for(int i = 0; i <= siz[x]; ++i)
		f[x][i]=tf[i], g[x][i]=tg[i], tf[i]=tg[i]=0;
}

signed main() {
//	freopen("desire.in", "r", stdin);
//	freopen("desire.out", "w", stdout);
	read(n);
	for(int i = 0; i <= n; ++i)
		c[i][0]=1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= i; ++j)
			c[i][j]=upd(c[i-1][j-1]+c[i-1][j]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	write(f[1][0], ' '), write(g[1][0], '\n');
	return 0;
}
