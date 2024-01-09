#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, u, v, dep[N], mxs[N], p[N<<2], *g[N], *f[N], *o=p;
long long ans;
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
void dfs(int x, int fa) {
	for(int y : to[x])
		if(y != fa) {
			dfs(y, x);
			if(dep[y] > dep[mxs[x]])
				mxs[x]=y;
		}
	dep[x]=dep[mxs[x]]+1;
}
void dp(int x, int fa) {
	if(mxs[x])
		f[mxs[x]]=f[x]+1, g[mxs[x]]=g[x]-1, dp(mxs[x], x);
	f[x][0]=1;
	ans+=g[x][0];
	for(int y : to[x]) 
		if(y != fa && y != mxs[x]) {
			f[y]=o;
			o+=(dep[y]<<1);
			g[y]=o;
			o+=(dep[y]<<1);
			dp(y, x);
			for(int j = 0; j < dep[y]; ++j) {
				if(j) ans+=f[x][j-1]*g[y][j]; 
				ans+=g[x][j+1]*f[y][j];
			}
			for(int j = 0; j < dep[y]; ++j) {
				g[x][j+1]+=f[x][j+1]*f[y][j];
				if(j)
					g[x][j-1]+=g[y][j];
				f[x][j+1]+=f[y][j]; 
			}
		}
}

signed main() {
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	f[1]=o;
	o+=(dep[1]<<1);
	g[1]=o;
	o+=(dep[1]<<1);
	dp(1, 0);
	write(ans, '\n');
	return 0;
}
