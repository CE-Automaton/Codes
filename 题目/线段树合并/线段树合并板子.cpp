#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int rt[N], gs, tot, zhan[N*30], n, m, u, v, w, dep[N], top[N], mxs[N], siz[N], ans[N], up[N];
vector <int> to[N];
struct qwq {
	int d, w;
};
vector <qwq> pro[N];
struct node {
	int ls, rs, mx, ss;
}tr[N*30];//空间是log的! 
struct tree {//线段树合并板子 
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
	#define mx(x) tr[x].mx
	#define ss(x) tr[x].ss
	void upup(int k) {
		if(mx(ls(k)) > mx(rs(k))) mx(k)=mx(ls(k)), ss(k)=ss(ls(k));
		else if(mx(ls(k)) < mx(rs(k))) mx(k)=mx(rs(k)), ss(k)=ss(rs(k));
		else mx(k)=mx(ls(k)), ss(k)=ss(ls(k));
	}
	void dlt(int k) { zhan[++tot]=k; }
	void cnw(int& ret) {
		if(tot) ret=zhan[tot], --tot;//回收空间,用处不是很大,兴许什么时候要卡空间了就用上看能不能过吧 
		else ret=(++gs); 
		tr[ret]=node {0, 0, 0, 0};
	}
	int merge(int x, int y, int l, int r) {
		if(!x || !y) return (x|y);
		if(l == r) {//注意线段树叶子结点也要合并!!! 
			mx(x)+=mx(y), dlt(y);
			return x;
		}
		int mid = ((l+r)>>1); 
		ls(x)=merge(ls(x), ls(y), l, mid);
		rs(x)=merge(rs(x), rs(y), mid+1, r);
		upup(x), dlt(y);
		return x;
	}
	void updt(int& k, int l, int r, int tt, int ww) {
		if(!k) cnw(k);
		if(l == r) {
			mx(k)+=ww;
			ss(k)=l; 
			return ;
		} 
		int mid = ((l+r)>>1);
		if(tt <= mid)
			updt(ls(k), l, mid, tt, ww);
		else
			updt(rs(k), mid+1, r, tt, ww);
		upup(k);
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
void dfs(int x, int fa) {
	siz[x]=1, dep[x]=dep[fa]+1, up[x]=fa;
	for(int y : to[x])
		if(y != fa) {
			dfs(y, x);
			siz[x]+=siz[y];
			mxs[x]=(siz[mxs[x]] < siz[y] ? y : mxs[x]);
		}
}
void dfs2(int x, int fa, int tp) {
	top[x]=tp;
	if(mxs[x])
		dfs2(mxs[x], x, tp);
	for(int y : to[x])
		if(y != fa && y != mxs[x])
			dfs2(y, x, y);
}
void dfss(int x, int fa) {
	if(mxs[x])
		dfss(mxs[x], x), rt[x]=rt[mxs[x]];
	for(int y : to[x])
		if(y != fa && y != mxs[x])
			dfss(y, x), rt[x]=A.merge(rt[x], rt[y], 1, 100000);
	for(qwq y : pro[x])
		A.updt(rt[x], 1, 100000, y.d, y.w);
	ans[x]=(tr[rt[x]].mx ? tr[rt[x]].ss : 0);
}

signed main() {
	read(n), read(m);
	for(int i = 2; i <= n; ++i)
		read(u), read(v),
		to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	dfs2(1, 0, 1);
	for(int i = 1; i <= m; ++i) {
		read(u), read(v), read(w);
		pro[u].push_back(qwq {w, 1});
		pro[v].push_back(qwq {w, 1});
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]]) swap(u, v);
			u=up[top[u]];
		}
		if(dep[u] > dep[v]) swap(u, v);
		pro[u].push_back(qwq {w, -1});
		pro[up[u]].push_back(qwq {w, -1});
	}
	dfss(1, 0);
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}
