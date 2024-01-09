#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
int n, m, S, P, dis[2][N], root = 1;
vector<int> tr[N];
int que[N];

void bfs(int s, int *d, int &x) {
	int l = 1, r = 0;
	for (int i = 1; i <= n; ++i) d[i] = -1;
	d[s] = 0;
	que[++r] = s;
	while (l <= r) {
		int u = que[l++];
		for (int v : tr[u])
			if (d[v] == -1) {
				d[v] = d[u] + 1;
				que[++r] = v;
			}
	}
	x = que[r];
}

int f[N], F[N][2];
int dep[N], fa[N], sz[N], son[N], st[N], ed[N], id[N], top[N], cnt;

void dfs1(int u, int p) {
	dep[u] = dep[p] + 1, fa[u] = p, sz[u] = 1;
	for (int v : tr[u]) {
		tr[v].erase(find(tr[v].begin(), tr[v].end(), u));
		dfs1(v, u);
		sz[u] += sz[v];
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int tp) {
	st[u] = ++cnt, id[cnt] = u, top[u] = tp;
	if (son[u]) dfs2(son[u], tp);
	for (int v : tr[u])
		if (v != son[u])
			dfs2(v, v);
	ed[u] = cnt;
}

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

struct Info {
	int s00, s01, s10, s11;
	inline Info operator + (const Info &o) const { return Info{s00 ^ o.s00, s01 ^ o.s01, s10 ^ o.s10, s11 ^ o.s11}; }
};

struct Node {
	Info s;
	bool ta, tb;
} T[N << 2];

inline void up(int x) { T[x].s = T[ls(x)].s + T[rs(x)].s; }
inline void tagA(int x) { swap(T[x].s.s00, T[x].s.s10), swap(T[x].s.s01, T[x].s.s11), T[x].ta ^= 1; }
inline void tagB(int x) { swap(T[x].s.s00, T[x].s.s01), swap(T[x].s.s10, T[x].s.s11), T[x].tb ^= 1; }

inline void down(int x) {
	if (T[x].ta) tagA(ls(x)), tagA(rs(x)), T[x].ta = 0;
	if (T[x].tb) tagB(ls(x)), tagB(rs(x)), T[x].tb = 0;
}

void build(int x = 1, int l = 1, int r = n) {
	if (l == r) {
		T[x] = Node{Info{F[id[l]][1], F[id[l]][0], 0, 0}, 0, 0};
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(x), l, mid), build(rs(x), mid + 1, r);
	up(x);
}

void upd(int L, int R, int tp, int x = 1, int l = 1, int r = n) {
	if (L <= l && r <= R) return (tp ? tagA(x) : tagB(x));
	int mid = (l + r) >> 1;
	down(x);
	if (L <= mid) upd(L, R, tp, ls(x), l, mid);
	if (R > mid) upd(L, R, tp, rs(x), mid + 1, r);
	up(x);
}

int ask(int L, int R, int x = 1, int l = 1, int r = n) {
	if (L <= l && r <= R) return T[x].s.s00;
	int mid = (l + r) >> 1, res = 0;
	down(x);
	if (L <= mid) res ^= ask(L, R, ls(x), l, mid);
	if (R > mid) res ^= ask(L, R, rs(x), mid + 1, r);
	return res;
}

inline void trpath(int x, int y, int tp, int ban_lca = 0) {
	int tx = top[x], ty = top[y];
	while (tx != ty) {
		if (dep[tx] >= dep[ty]) upd(st[tx], st[x], tp), x = fa[tx], tx = top[x];
		else upd(st[ty], st[y], tp), y = fa[ty], ty = top[y];
	}
	if (st[x] + ban_lca <= st[y]) upd(st[x] + ban_lca, st[y], tp);
	else if (st[y] + ban_lca <= st[x]) upd(st[y] + ban_lca, st[x], tp);
}

inline bool cmp(int i, int j) { return st[i] < st[j]; }

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	int x = 0, y = 0, z = 0;
	bfs(1, dis[1], x);
	bfs(x, dis[0], y);
	bfs(y, dis[1], z);
	for (int i = 1; i <= n; ++i)
		if (dis[0][i] > dis[1][i])
			swap(dis[0][i], dis[1][i]);
	S = P = 1;
	for (int i = 2; i <= n; ++i) {
		if (dis[1][i] < dis[1][S]) S = P = i;
		else if (dis[1][i] == dis[1][S] && i != S) P = i;
	}
	dfs1(S, 0);
	dfs2(S, S);
	for (int i = 1; i <= n; ++i) sort(tr[i].begin(), tr[i].end(), cmp);
	for (int i = n; i >= 1; --i) {
		int u = id[i];
		for (int v : tr[u])
			if (v != P)
				f[u] = max(f[u], f[v] + 1);
	}
	for (int i = 1; i <= n; ++i) {
		F[i][1] = f[i];
		if (st[i] >= st[P] && st[i] <= ed[P]) F[i][0] = dep[i] - 1 + f[S];
		else F[i][0] = dep[i] + f[P];
	}
	build();
	trpath(1, (st[1] >= st[P] && st[1] <= ed[P]) ? P : S, 0);
	while (m--) {
		int op, u, v, x;
		cin >> op;
		if (op == 1) {
			cin >> u >> v >> x;
			trpath(u, v, 1);
		} else {
			cin >> u >> x;
			if (root == u) upd(1, n, 1);
			else if (st[root] >= st[u] && st[root] <= ed[u]) {
				int v = *(upper_bound(tr[u].begin(), tr[u].end(), root, cmp) - 1);
				upd(1, n, 1), upd(st[v], ed[v], 1);
			} else {
				upd(st[u], ed[u], 1);
			}
		}
		trpath(root, x, 0, (st[root] >= st[P] && st[root] <= ed[P]) == (st[x] >= st[P] && st[x] <= ed[P]));
		root = x;
		cout << T[1].s.s00 << '\n';
	}
	return 0;
}
