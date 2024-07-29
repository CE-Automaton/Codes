#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 75005, M = 150005;
int n, m, u, v, p[N], ans[N], vis[N], ppd[N], cnt, h[N], nxt[M], to[M],
tr[N], tot, siz[N], dfn[N], ff[N], ccc[N], jp[N][23], dep[N];
LL sum;
queue <int> q;

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
void sol(int x) {
	q.push(x);
	// memset(ppd, 0, sizeof ppd);
	while(!q.empty()) {
		int it = q.front(); q.pop();
		// if(ppd[it]) continue;
		// ppd[it]=1;
		for(int i = h[it]; i; i=nxt[i]) 
			if(ans[it]+vis[to[i]] < ans[to[i]]) {
				ans[to[i]]=ans[it]+vis[to[i]];
				q.push(to[i]);
			}
	}
}
void add(int x, int w) {
	while(x <= n)
		tr[x]+=w, x+=(x&(-x));
}
int ask(int x, int ret=0) {
	while(x >= 1)
		ret+=tr[x], x-=(x&(-x));
	return ret;
}
void dfs(int x, int fa) {
	dfn[x]=++tot, siz[x]=1;
	for(int i = h[x]; i; i=nxt[i])
		if(to[i] != fa)
			dfs(to[i], x), siz[x]+=siz[to[i]];
}
void dfss(int x, int fa) {
	dfn[x]=++tot, siz[x]=1;
	dep[x]=dep[fa]+1;
	jp[x][0]=fa;
	for(int i = 1; i <= 20; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1];
	for(int i = h[x]; i; i=nxt[i])
		if(to[i] != fa)
			dfss(to[i], x), siz[x]+=siz[to[i]];
}
int find(int x) {
	return (ff[x] == x ? x : ff[x]=find(ff[x]));
}
int merge(int x, int y) {
	x=find(x), y=find(y);
	if(x == y) return 0;
	if(ccc[x] < ccc[y]) swap(x, y);
	ccc[x]+=ccc[y];
	ff[y]=x;
	return 1;
}
int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; --i)
		if(dep[jp[x][i]] >= dep[y])
			x=jp[x][i];
	for(int i = 20; i >= 0; --i)
		if(jp[x][i] != jp[y][i])
			x=jp[x][i], y=jp[y][i];
	return (x == y ? x : jp[x][0]);
}

signed main() {
	File("walk");
	read(n), read(m);
	if(n <= 2000) {
		for(int i = 1; i < n; ++i)
			read(p[i]), vis[i]=1, ans[i]=inf;
		for(int i = 1; i <= m; ++i) {
			read(u), read(v);
			nxt[++cnt]=h[u], to[cnt]=v, h[u]=cnt;
			nxt[++cnt]=h[v], to[cnt]=u, h[v]=cnt;
		}
		sol(n);
		for(int i = 1; i < n; ++i)
			--ans[p[i]], vis[p[i]]=0, sum+=1LL*ans[p[i]], sol(p[i]);
		write(sum, '\n');
		return 0;
	}
	if(m == n-1) {
		for(int i = 1; i < n; ++i)
			read(p[i]);
		for(int i = 1; i <= m; ++i) {
			read(u), read(v);
			nxt[++cnt]=h[u], to[cnt]=v, h[u]=cnt;
			nxt[++cnt]=h[v], to[cnt]=u, h[v]=cnt;
		}
		dfs(n, 0);
		for(int i = 1; i <= n; ++i)
			add(dfn[i], 1), add(dfn[i]+siz[i], -1);
		for(int i = 1; i < n; ++i)
			sum+=1LL*(ask(dfn[p[i]])-2), add(dfn[p[i]], -1), add(dfn[p[i]]+siz[p[i]], 1);
		write(sum, '\n');
		return 0;
	}
	if(m == n) {
		int aa = 0, bb = 0;
		for(int i = 1; i < n; ++i)
			read(p[i]);
		for(int i = 1; i <= n; ++i)
			ff[i]=i, ccc[i]=1;
		for(int i = 1; i <= m; ++i) {
			read(u), read(v);
			if(merge(u, v)) {
				nxt[++cnt]=h[u], to[cnt]=v, h[u]=cnt;
				nxt[++cnt]=h[v], to[cnt]=u, h[v]=cnt;
			}
			else
				aa=u, bb=v;
		}
		dfss(n, 0);
		for(int i = 1; i <= n; ++i)
			add(dfn[i], 1), add(dfn[i]+siz[i], -1);
		for(int i = 1; i < n; ++i) {
			int aaa = ask(dfn[p[i]]), bbb = ask(dfn[aa]), ccc = ask(dfn[bb]), qwq = aaa, op = 0;
			op=lca(aa, p[i]);
			qwq=min(qwq, bbb+aaa-ask(dfn[op])-ask(dfn[jp[op][0]])+ccc);
			op=lca(bb, p[i]);
			qwq=min(qwq, ccc+aaa-ask(dfn[op])-ask(dfn[jp[op][0]])+bbb);
			sum+=1LL*(qwq-2);
			add(dfn[p[i]], -1), add(dfn[p[i]]+siz[p[i]], 1);
		}
		write(sum, '\n');
		return 0;
	}
	for(int i = 1; i < n; ++i)
		read(p[i]), vis[i]=1, ans[i]=inf;
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		nxt[++cnt]=h[u], to[cnt]=v, h[u]=cnt;
		nxt[++cnt]=h[v], to[cnt]=u, h[v]=cnt;
	}
	sol(n);
	for(int i = 1; i < n; ++i)
		--ans[p[i]], vis[p[i]]=0, sum+=1LL*ans[p[i]], sol(p[i]);
	write(sum, '\n');
	return 0;
}