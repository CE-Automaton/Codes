#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, m, cnt, fa[N], ccc[N], mn[N], rt, siz[N], dp[N], mid, vis[N], fx[5][3]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, ans;
struct qvq { int v, w; } tt[N];
vector <int> d[N], dd[N], to[N], a[N];

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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void prdfs(int x) {
	siz[x]=1;
	for(int y : to[x])
		prdfs(y), siz[x]+=siz[y];
}
void dfs(int x) {
	for(int y : to[x])
		dp[y]=min(d[tt[x].v][tt[x].w], dp[x]+siz[x]-siz[y]), dfs(y);
	if(tt[x].v == 1 || tt[x].v == n || tt[x].w == 1 || tt[x].w == m)
		ans=max(ans, min(dp[x]+siz[x], d[tt[x].v][tt[x].w]));
}

signed main() {
	// File("treasure");
	read(n), read(m);
	// d[0].resize(m+2), vis[0].resize(m+2);
	// d[n+1].resize(m+2), vis[n+1].resize(m+2);
	rt=1;
	for(int i = 1; i <= n; ++i) {
		d[i].resize(m+2), dd[i].resize(m+2);
		for(int j = 1; j <= m; ++j)
			read(d[i][j]), d[i][j]=min(d[i][j], n*m), dd[i][j]=(i-1)*m+j;
	}
	for(int i = 1; i <= n*m; ++i)
		fa[i]=i, mn[i]=i;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			a[d[i][j]].push_back(dd[i][j]), 
			tt[++cnt]=qvq {i, j};
	for(int o = n*m; o >= 1; --o) 
		for(int i : a[o]) {
			vis[i]=1, rt=i;
			int x = tt[i].v, y = tt[i].w;
			for(int j = 0; j < 4; ++j) {
				int xx = x+fx[j][0], yy = y+fx[j][1];
				if(xx <= 0 || xx > n || yy <= 0 || yy > m) continue;
				if(vis[dd[xx][yy]] && find(dd[xx][yy]) != find(i)) {
					int op = fa[dd[xx][yy]], po = find(i);
					to[i].push_back(mn[op]);
					mn[op]=i, fa[po]=op;
				}
			}
		}
	prdfs(rt);
	dfs(rt);
	// debug("???\n");
	write(ans, '\n');
	return 0;
}
