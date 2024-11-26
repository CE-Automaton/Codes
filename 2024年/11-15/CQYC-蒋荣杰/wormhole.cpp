#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int cc, n, m, q, u, v, vis[N], cnt, dfn[N], tt[N], dep[N], jp[N][21], lp[N][21], siz[N], mn[N], 
gs, zhan[N*21], tot/*线段树合并垃圾回收*/, rt[N], ans[N], out[N];
vector <int> to[N], son[N], in[N];
struct qwq {
	int w, d;
};
vector <qwq> que[N];

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
struct node {
	int ls, rs, w;
}tr[N*21];
int blt(node yw) {
	int now = 0;
	if(tot)
		now=zhan[tot], --tot;
	else
		now=++gs;
	tr[now]=yw;
	return now;
}
void upup(int k) {
	tr[k].w=(tr[k].ls ? tr[tr[k].ls].w : 0)+(tr[k].rs ? tr[tr[k].rs].w : 0);
}
void dlt(int &k, int l, int r, int lq, int rq) {
	if(!k) return ;
	if(lq <= l && r <= rq) {
		zhan[++tot]=k, k=0;
		return ;
	}
	int mid = ((l+r)>>1);
	if(lq <= mid)
		dlt(tr[k].ls, l, mid, lq, rq);
	if(mid+1 <= rq)
		dlt(tr[k].rs, mid+1, r, lq, rq);
	upup(k);
}
void updt(int &k, int l, int r, int to, int w) {
	if(!k)
		k=blt(node {0, 0, 0});
	if(l == r) {
		tr[k].w+=w;
		return ;
	}
	int mid = ((l+r)>>1);
	if(to <= mid)
		updt(tr[k].ls, l, mid, to, w);
	else
		updt(tr[k].rs, mid+1, r, to, w);
	upup(k);
}
int ask(int k, int l, int r, int lq, int rq) {
	if(!k) return 0;
	if(lq <= l && r <= rq) 
		return tr[k].w;
	int mid = ((l+r)>>1), ret = 0;
	if(lq <= mid)
		ret=ask(tr[k].ls, l, mid, lq, rq);
	if(mid+1 <= rq)
		ret+=ask(tr[k].rs, mid+1, r, lq, rq);
	return ret;
}
int merge(int k1, int k2, int l, int r) {
	if(!k1 || !k2)
		return k1+k2;
	if(l == r) {
		tr[k1].w=tr[k1].w+tr[k2].w;
		zhan[++tot]=k2;
		return k1;
	}
	int mid = ((l+r)>>1);
	tr[k1].ls=merge(tr[k1].ls, tr[k2].ls, l, mid);
	tr[k1].rs=merge(tr[k1].rs, tr[k2].rs, mid+1, r);
	upup(k1), zhan[++tot]=k2;
	return k1;
}
int merge2(int k1, int k2, int l, int r) {
	if(!k1 || !k2)
		return k1+k2;
	if(k1 == k2) 
		return k1;
	if(l == r) {
		tr[k1].w=tr[k1].w+tr[k2].w;
		return k1;
	}
	int mid = ((l+r)>>1);
	tr[k1].ls=merge2(tr[k1].ls, tr[k2].ls, l, mid);
	tr[k1].rs=merge2(tr[k1].rs, tr[k2].rs, mid+1, r);
	upup(k1);
	return k1;
}
void get_edge(int x) {
	vis[x]=1;
	for(int y : to[x])
		if(!vis[y])
			son[x].push_back(y)/*, debug(x, y, "!\n")*/, vis[y]=1;
		else
			in[y].push_back(x), ++out[x];
	if(son[x].size() == 0) return ;
	sort(son[x].begin(), son[x].end());
	for(int y : son[x])
		get_edge(y);
}
void dfs(int x, int fa) {
	dfn[x]=++cnt, tt[cnt]=x;
	dep[x]=dep[fa]+1, jp[x][0]=fa, siz[x]=1;
	for(int i = 1; i <= 20; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1];
	lp[x][0]=x;
	for(int i = 1; i <= 20; ++i)
		lp[x][i]=jp[lp[x][i-1]][i-1];
	for(int y : son[x])
		dfs(y, x), siz[x]+=siz[y];
}
int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; --i)
		if(jp[x][i] && dep[jp[x][i]] >= dep[y])
			x=jp[x][i];
	for(int i = 20; i >= 0; --i)
		if(jp[x][i] && jp[y][i] && jp[x][i] != jp[y][i])
			x=jp[x][i], y=jp[y][i];
	if(x != y)
		x=jp[x][0];
	return x;
}
void get_mn(int x) {
	vis[x]=1;
	for(int y : in[x]) {
		if(!vis[y])
			get_mn(y);
		rt[x]=merge2(rt[x], rt[y], 1, n);
	}
	updt(rt[x], 1, n, dfn[x], 1);
	// debug(x, "!\n");
	// for(int i = 1; i <= n; ++i)
	// 	debug(ask(rt[x], 1, n, i, i)), debug(' ');
	// debug('\n');
	// int now = x;
	// for(int i = 20; i >= 0; --i) {
	// 	if(jp[now][i] && ask(rt[x], 1, n, dfn[jp[now][i]], dfn[jp[now][i]]+siz[jp[now][i]]-1)-ask(rt[x], 1, n, dfn[lp[now][i]], dfn[lp[now][i]]+siz[lp[now][i]]-1))
	// 		now=jp[now][i];
		// if(jp[now][i])
		// 	debug(now, jp[now][i], lp[now][i], "???\n");
	// }
	mn[x]=dep[x];
	for(int i = 1; i <= n; ++i)
		if(ask(rt[x], 1, n, i, i) != 0)
			mn[x]=min(mn[x], dep[lca(x, tt[i])]);
}
void sol(int x) {
	for(int y : son[x])
		sol(y), rt[x]=merge(rt[x], rt[y], 1, n);
	// debug(x, mn[x], "???\n");
	int gss = 0;
	if(mn[x] < n) {
		gss=ask(rt[x], 1, n, mn[x]+1, n);
		dlt(rt[x], 1, n, mn[x]+1, n);
	}
	updt(rt[x], 1, n, mn[x], 1+gss);
	for(qwq y : que[x])
		ans[y.d]=siz[x]-ask(rt[x], 1, n, 1, dep[y.w]);
}

signed main() {
	File("wormhole");
	read(cc), read(n), read(m), read(q);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u].push_back(v);
	get_edge(1);
	for(int i = 1; i <= q; ++i)
		read(u), read(v), que[v].push_back(qwq {u, i});
	dfs(1, 0);
	for(int i = 1; i <= n; ++i)
		rt[i]=0, vis[i]=0;
	for(int i = 1; i <= n; ++i)
		if(out[i] == 0)
			get_mn(i)/*, debug("---------\n")*/;
	gs=0, tot=0;
	for(int i = 1; i <= n; ++i)
		rt[i]=0;
	sol(1);
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}