#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, m, q, u, v, tot, fa[N*3], top[N*3], dep[N*3], siz[N*3], mxs[N*3], lca[N], ans;
vector <int> to[N*3];
struct tree {
	int tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=lca[l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=max(tr[ls], tr[rs]);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=ask(ls, l, mid, lq, rq);
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
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void dfs(int x) {
	siz[x]=1;
	for(int y : to[x]) {
		dep[y]=dep[x]+1, dfs(y);
		siz[x]+=siz[y];
		fa[y]=x;
		if(siz[y] > siz[mxs[x]]) 
			mxs[x]=y;
	}
}
void dfs2(int x, int tp) {
	top[x]=tp;
	if(mxs[x]) dfs2(mxs[x], tp);
	for(int y : to[x])
		if(y != mxs[x])
			dfs2(y, y);
}

signed main() {
	read(n), read(m), read(q);
	tot=n; 
	for(int i = 1; i <= n; ++i)
		fa[i]=i;
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		u=find(u), v=find(v);
		++tot;
		fa[tot]=tot;
		if(u == v) continue;
		to[tot].push_back(u);
		to[tot].push_back(v);
		fa[u]=tot;
		fa[v]=tot;
	}
	tot=find(1); 
	fa[tot]=0;
	dfs(tot);
	dfs2(tot, tot);
	for(int i = 1; i <= n-1; ++i) {
		u=i, v=i+1;
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]])
				swap(u, v);
			u=fa[top[u]];
		}
		if(dep[u] > dep[v]) swap(u, v);
		lca[i]=u;
	}
	A.built(1, 1, n-1);
	for(int i = 1; i <= q; ++i) 
		read(u), read(v), ans=(ans^max(0, (u != v ? A.ask(1, 1, n-1, u, v-1) : n)-n));
	write(ans);
	cout<<endl;
    return 0 ;
}
