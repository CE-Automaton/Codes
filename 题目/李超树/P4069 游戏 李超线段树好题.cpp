#include <bits/stdc++.h>
#define inf 123456789123456789LL
using namespace std;
const int N = 1e5+5;
int n, u, v, m, siz[N], dfn[N], top[N], up[N], mxs[N], tt[N], tot, op, s, t, a;
long long dis[N], dep[N], w, b; 
struct qwq {
	int k;
	long long b;
}xd[N<<1];
vector <qwq> to[N]; 

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
long long ask(int nmb, int x) {
	return (long long) xd[nmb].k*dis[tt[x]]+xd[nmb].b;
}
int pd(int nmb, int tr, int x) {
	if(ask(nmb, x) < ask(tr, x))
		return 1;
	return 0;
}
struct tree {//李超线段树
	int tr[N<<2];
	long long mn[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		mn[k]=inf;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int nmb) {
		mn[k]=min(mn[k], min(ask(nmb, l), ask(nmb, r)));//线段的最值在两端 
		if(tr[k] == 0) {
			tr[k]=nmb;
			return ;
		}
		int mid = ((l+r)>>1);
		if(pd(nmb, tr[k], mid)) 
			swap(nmb, tr[k]);
		if(l == r) return ;
		if(pd(nmb, tr[k], l))
			updt(ls, l, mid, nmb); 
		if(pd(nmb, tr[k], r))
			updt(rs, mid+1, r, nmb); 
		mn[k]=min(mn[k], min(mn[ls], mn[rs]));
	}
	void upd(int k, int l, int r, int lq, int rq, int nmb) {
		if(lq <= l && r <= rq) {
			updt(k, l, r, nmb);
			return ;
		}
		int mid = ((l+r)>>1);
		if(lq <= mid)
			upd(ls, l, mid, lq, rq, nmb);
		if(mid+1 <= rq)
			upd(rs, mid+1, r, lq, rq, nmb); 
		mn[k]=min(mn[k], min(mn[ls], mn[rs]));
	}
	long long find(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return mn[k];
		int mid = ((l+r)>>1);
		long long ret=min(ask(tr[k], max(l, lq)), ask(tr[k], min(r, rq)));
		if(lq <= mid)
			ret=min(ret, find(ls, l, mid, lq, rq));
		if(mid+1 <= rq)
			ret=min(ret, find(rs, mid+1, r, lq, rq));
		return ret;
	}
}A;
void dfs(int x, int fa) {
	dep[x]=dep[fa]+1;
	up[x]=fa;
	siz[x]=1;
	for(qwq y : to[x]) 
		if(y.k != fa) {
			dis[y.k]=dis[x]+y.b;
			dfs(y.k, x);
			siz[x]+=siz[y.k];
			if(siz[y.k] > siz[mxs[x]])
				mxs[x]=y.k;
		}
}
void dfs2(int x, int fa, int tp) {
	dfn[x]=++tot;
	tt[tot]=x;
	top[x]=tp;
	if(mxs[x])
		dfs2(mxs[x], x, tp);
	for(qwq y : to[x])
		if(y.k != fa && y.k != mxs[x])
			dfs2(y.k, x, y.k);
}

signed main() {
	read(n), read(m);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), read(w), to[u].push_back(qwq {v, w}), to[v].push_back(qwq {u, w});
	dfs(1, 0);
	dfs2(1, 0, 1);
	xd[0]=qwq {0, inf};
	A.built(1, 1, n);
	for(int i = 1; i <= m; ++i) {
		read(op);
		if(op == 1) {
			read(s), read(t), read(a), read(b);
			u=s, v=t;
			while(top[u] != top[v]) {
				if(dep[top[u]] < dep[top[v]]) swap(u, v);
				u=up[top[u]];
			}
			if(dep[u] > dep[v]) swap(u, v);
			xd[++tot]=qwq {a, b+(dis[s]-2*dis[u])*a};
			while(top[t] != top[u])
				A.upd(1, 1, n, dfn[top[t]], dfn[t], tot), t=up[top[t]];
			A.upd(1, 1, n, dfn[u], dfn[t], tot);
			xd[++tot]=qwq {-a, b+dis[s]*a};
			while(top[s] != top[u])
				A.upd(1, 1, n, dfn[top[s]], dfn[s], tot), s=up[top[s]];
			A.upd(1, 1, n, dfn[u], dfn[s], tot);
		} 
		else {
			long long ans = inf;
			read(u), read(v);
			while(top[u] != top[v]) {
				if(dep[top[u]] < dep[top[v]]) swap(u, v);
				ans=min(ans, A.find(1, 1, n, dfn[top[u]], dfn[u]));
				u=up[top[u]];
			}
			if(dep[u] > dep[v]) swap(u, v);
			ans=min(ans, A.find(1, 1, n, dfn[u], dfn[v]));
			write(ans, '\n');
		}
	}
	return 0;
}
