#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 2e3+4;
int n, q, fa[N], u, v, opt[N], p[N], siz[N], mxs[N], top[N], dfn[N], dep[N], cnt;
long long vv;
vector <int> to[N];
struct qwq {
	int a, b;
}pro[N];
vector <qwq> az[N];
struct tree {
	int tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		if(l == r)
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int to, int ww) {
		if(l == r) {
			tr[k]=max(tr[k], ww);
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, ww);
		else
			updt(rs, mid+1, r, to, ww);
		tr[k]=max(tr[ls], tr[rs]);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=max(ret, ask(ls, l, mid, lq, rq));
		if(mid+1 <= rq)
			ret=max(ret, ask(rs, mid+1, r, lq, rq));
		return ret;
	}
}A; 

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
void dfs(int x, int fat) {
	dep[x]=dep[fat]+1;
	siz[x]=1;
	for(int y : to[x])
		if(y != fat) {
			fa[y]=x, dfs(y, x), siz[x]+=siz[y];
			if(siz[y] > siz[mxs[x]])
				mxs[x]=y;
		}
}
void dfs2(int x, int fat, int tp) {
	top[x]=tp;
	dfn[x]=++cnt;
	if(mxs[x]) dfs2(mxs[x], x, tp);
	for(int y : to[x])
		if(y != fat && y != mxs[x])
			dfs2(y, x, y);
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	int pd = 1;
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(opt[i]), read(p[i]), read(pro[i].a);
		if(opt[i] == 1)
			read(pro[i].b);
		else
			pd&=(pro[i].a == 0);
	}
	dfs(1, 0);
	if(pd) {
		dfs2(1, 0, 1), A.built(1, 1, n);
		for(int i = 1; i <= q; ++i) {
			if(opt[i] == 1) 
				A.updt(1, 1, n, dfn[p[i]], pro[i].b);
			else {
				u = p[i], v = 0;
				while(u) {
					v=max(v, A.ask(1, 1, n, dfn[top[u]], dfn[u]));
					u=fa[top[u]];
				}
				write(v, '\n');
			}
		}
		return 0;
	}
	for(int i = 1; i <= q; ++i) {
		if(opt[i] == 1) 
			az[p[i]].push_back(qwq {pro[i].a, pro[i].b});
		else {
			u = p[i], vv = 0;
			while(u) {
				for(qwq y : az[u])
					vv=max(vv, (long long) y.a*pro[i].a+y.b);
				u=fa[u];
			}
			write(vv, '\n');
		}
	}
	return 0;
}
