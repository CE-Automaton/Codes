/********************************************************************************
	
	Code by a weak man named CYJian, and he hopes the code can get more points.

	Algorithm: 

 ********************************************************************************/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//{{{ FAST IO AND SOME FUNCTIONS
const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
#define ri read_int()
#define rl read_ll()
#define FILE(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

template<typename T>
inline void read(T &x) {
	char ch, t = 0; x = 0;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
	x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

template<typename T> inline void chkmin(T&a, T b) { a = a < b ? a : b; }
template<typename T> inline void chkmax(T&a, T b) { a = a > b ? a : b; }
//}}}

const int MAXN = 200010;

vector<int>to[MAXN];

// {{{ Find Root
namespace Find_Root {

int sta[MAXN];
int vis[MAXN];
int tim, top;

inline int BFS(int x) {
	queue<int>q;
	q.push(x), ++tim;
	int las = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(auto u : to[x]) {
			if(vis[u] == tim) continue;
			q.push(u), vis[u] = tim;
		} las = x;
	} return las;
}

inline int DFS(int x, int la, int goal) {
	sta[++top] = x;
	if(x == goal) return sta[(top + 1) >> 1];
	for(auto u : to[x]) {
		if(u == la) continue;
		int t = DFS(u, x, goal);
		if(t) return t;
	} return --top, 0;
}

inline int GetRoot() {
	int u = BFS(1), v = BFS(u);
	return DFS(u, 0, v);
}

}
// }}}

int n;
int m;
int Rt;
int now;
int tim;
int fa[MAXN];
int si[MAXN];
int hs[MAXN];
int top[MAXN];
int dep[MAXN];
int dfn[MAXN];
int las[MAXN];
int pos[MAXN];
int f[MAXN], frf[MAXN];
int g[MAXN], frg[MAXN];

// {{{ Segment Tree
struct Segment_Tree {
#define ls (x << 1)
#define rs (x << 1 | 1)

	struct Node {
		int v00, v01;
		int v10, v11;
		int t0, t1;
	} T[MAXN << 2];

	inline void pushup(int x) {
		T[x].v00 = T[ls].v00 ^ T[rs].v00;
		T[x].v10 = T[ls].v10 ^ T[rs].v10;
		T[x].v01 = T[ls].v01 ^ T[rs].v01;
		T[x].v11 = T[ls].v11 ^ T[rs].v11;
	}

	inline void Give0(int x) { swap(T[x].v00, T[x].v01), swap(T[x].v10, T[x].v11), T[x].t0 ^= 1; }
	inline void Give1(int x) { swap(T[x].v00, T[x].v10), swap(T[x].v01, T[x].v11), T[x].t1 ^= 1; }
	inline void pushdown(int x) {
		if(T[x].t0) Give0(ls), Give0(rs), T[x].t0 = 0;
		if(T[x].t1) Give1(ls), Give1(rs), T[x].t1 = 0;
	}

	inline void build(int x, int l, int r) {
		if(l == r) {
			T[x].v00 = g[pos[l]];
			T[x].v01 = f[pos[l]];
			T[x].v10 = T[x].v11 = 0;
			return ;
		}
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
		pushup(x);
	}

	inline void Rev0(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return Give0(x);
		int mid = (l + r) >> 1; pushdown(x);
		if(L <= mid) Rev0(ls, l, mid, L, R);
		if(mid < R) Rev0(rs, mid + 1, r, L, R);
		pushup(x);
	}

	inline void Rev1(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return Give1(x);
		int mid = (l + r) >> 1; pushdown(x);
		if(L <= mid) Rev1(ls, l, mid, L, R);
		if(mid < R) Rev1(rs, mid + 1, r, L, R);
		pushup(x);
	}

	inline int Q() { return T[1].v00; }

#undef ls
#undef rs
}seg;
// }}}

// {{{ Shu Pou
inline void dfs1(int x, int la) {
	si[x] = 1, fa[x] = la, dep[x] = dep[la] + 1;
	for(auto u : to[x]) {
		if(u == la) continue;
		dfs1(u, x);
		si[x] += si[u];
		if(g[x] < f[u] + 1) g[x] = f[u] + 1, frg[x] = u;
		if(g[x] > f[x]) swap(f[x], g[x]), swap(frf[x], frg[x]);
		if(si[u] > si[hs[x]]) hs[x] = u;
	}
}

inline void dfs2(int x, int la) {
	if(la) {
		int t = frf[la] == x ? g[la] : f[la];
		if(g[x] < t + 1) g[x] = t + 1, frg[x] = la;
		if(g[x] > f[x]) swap(f[x], g[x]), swap(frf[x], frg[x]);
	} pos[dfn[x] = ++tim] = x;
	if(hs[x]) top[hs[x]] = top[x], dfs2(hs[x], x);
	for(auto u : to[x]) {
		if(hs[x] == u || la == u) continue;
		top[u] = u, dfs2(u, x);
	} las[x] = tim;
}

inline int find(int x, int rt) {
	while(top[x] != top[rt]) {
		x = top[x];
		if(fa[x] == rt) break;
		x = fa[x];
	} return top[x] != top[rt] ? x : hs[rt];
}

inline void Rev0(int u, int v) {
	if(u != v) {
		int x = find(v, Rt);
		if(x == frf[u]) seg.Rev0(1, 1, n, 1, 1);
	}
	while(top[u] != top[v]) {
		seg.Rev0(1, 1, n, dfn[top[v]], dfn[v]);
		v = fa[top[v]];
	} seg.Rev0(1, 1, n, dfn[u], dfn[v]);
}

inline void Rev1(int u, int v) {
	while(top[u] != top[v]) {
		if(dfn[top[u]] < dfn[top[v]]) swap(u, v);
		seg.Rev1(1, 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	} if(dep[u] > dep[v]) swap(u, v);
	seg.Rev1(1, 1, n, dfn[u], dfn[v]);
}
// }}}

int main() {
	FILE("tree");

	n = ri, m = ri;

	for(int i = 1; i < n; i++) {
		int u = ri, v = ri;
		to[u].push_back(v);
		to[v].push_back(u);
	}

	Rt = Find_Root::GetRoot(), now = 1;
	dfs1(Rt, 0), dfs2(Rt, 0);
	seg.build(1, 1, n);
	Rev0(Rt, now);

	for(int i = 1; i <= m; i++) {
		int op = ri;
		if(op == 1) Rev1(ri, ri);
		else {
			int x = ri;
			if(now == x) seg.Rev1(1, 1, n, 1, n);
			else if(dfn[now] < dfn[x] || dfn[now] > las[x])
				seg.Rev1(1, 1, n, dfn[x], las[x]);
			else {
				x = find(now, x);
				seg.Rev1(1, 1, n, 1, n);
				seg.Rev1(1, 1, n, dfn[x], las[x]);
			}
		}
		Rev0(Rt, now);
		now = ri;
		Rev0(Rt, now);
		printf("%d\n", seg.Q());
	}
	return 0;
}
