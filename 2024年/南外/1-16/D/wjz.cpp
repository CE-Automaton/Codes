#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0, sgn = 0; char s = getchar();
	while(!isdigit(s)) sgn |= s == '-', s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return sgn ? -x : x;
}
inline void print(int x) {
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 1e5 + 5, V = 1.1e6 + 5, mod = 1e9 + 7;

int n, Q, w[N], fc[V], ifc[V];
int bin(int n, int m) {return n < 0 || n < m ? 0 : 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;}
int ksm(int a, int b) {
	int s = 1;
	while(b) {
		if(b & 1) s = 1ll * s * a % mod;
		a = 1ll * a * a % mod, b >>= 1;
	} return s;
}

int cnt, hd[N], nxt[N << 1], to[N << 1];
void add(int u, int v) {nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v;}

int dn, sz[N], dep[N], fa[N], son[N], dfn[N], top[N], rev[N];
void dfs1(int id, int f) {
	sz[id] = 1, fa[id] = f, dep[id] = dep[f] + 1;
	for(int i = hd[id]; i; i = nxt[i]) {
		int it = to[i];
		if(it == f) continue;
		dfs1(it, id), sz[id] += sz[it];
		if(sz[it] > sz[son[id]]) son[id] = it;
	}
}
void dfs2(int id, int t) {
	dfn[id] = ++dn, rev[dn] = id, top[id] = t;
	if(son[id]) dfs2(son[id], t);
	for(int i = hd[id]; i; i = nxt[i])
		if(to[i] != son[id] && to[i] != fa[id]) dfs2(to[i], to[i]);
}

struct BIT {
	int c[N];
	void add(int x, int v) {while(x <= n) c[x] += v, x += x & -x;}
	int query(int x) {int s = 0; while(x) s += c[x], x -= x & -x; return s;}
	int query(int l, int r) {return query(r) - query(l - 1);}
} tr;

struct dat {
	int len, mn, mx, ln, rn, aic, anic;
	void calc(int v) {mn = mx = v, ln = rn = 0, aic = anic = 1;}
	dat operator + (dat x) {
		dat y; int num = rn + x.ln; y.len = len + x.len;
		if(mn == -1 && x.mn == -1) return y.mn = -1, y;
		if(mn == -1) return y = x, y.len += len, y.ln += len, y;
		if(x.mn == -1) return y = *this, y.len += x.len, y.rn += x.len, y;
		y.ln = ln, y.rn = x.rn, y.mn = mn, y.mx = x.mx;
		y.aic = 1ll * aic * x.aic % mod * bin(x.mn - mx - 1, num) % mod;
		y.anic = 1ll * anic * x.anic % mod * bin(x.mn - mx + num, num) % mod;
		return y;
	}
} lv[N << 2], rv[N << 2], I;

void build(int l, int r, int x) {
	lv[x].len = rv[x].len = r - l + 1;
	if(l == r) return lv[x].calc(w[rev[l]]), rv[x].calc(w[rev[l]]);
	int m = l + r >> 1;
	build(l, m, x << 1), build(m + 1, r, x << 1 | 1);
	lv[x] = lv[x << 1] + lv[x << 1 | 1], rv[x] = rv[x << 1 | 1] + rv[x << 1];
}
void modify(int l, int r, int p, int x) {
	if(l == r) return lv[x].calc(w[rev[l]]), rv[x].calc(w[rev[l]]);
	int m = l + r >> 1;
	if(p <= m) modify(l, m, p, x << 1);
	else modify(m + 1, r, p, x << 1 | 1);
	lv[x] = lv[x << 1] + lv[x << 1 | 1], rv[x] = rv[x << 1 | 1] + rv[x << 1];
}
dat query(int l, int r, int ql, int qr, int x, bool tp) {
	if(ql <= l && r <= qr) return tp ? rv[x] : lv[x];
	int m = l + r >> 1;
	if(ql <= m && m < qr) return tp ?
		query(m + 1, r, ql, qr, x << 1 | 1, tp) + query(l, m, ql, qr, x << 1, tp):
		query(l, m, ql, qr, x << 1, tp) + query(m + 1, r, ql, qr, x << 1 | 1, tp);
	if(ql <= m) return query(l, m, ql, qr, x << 1, tp);
	if(m < qr) return query(m + 1, r, ql, qr, x << 1 | 1, tp);
	assert(0);
}
void update(int x, int v) {
	if(w[x] == -1) tr.add(dfn[x], -1);
	if((w[x] = v) == -1) tr.add(dfn[x], 1);
	modify(1, n, dfn[x], 1);
}

int inc(int u, int v, bool type, int a, int b) {
	static pair <int, int> su[N], sv[N];
	int nu = 0, nv = 0, tot = 0;
	dat pre = (dat){0, -2, -2, 0, 0, 1, 1}, suf = (dat){0, V, V, 0, 0, 1, 1};
	while(top[u] != top[v]) {
		if(dep[top[u]] > dep[top[v]]) su[++nu] = {dfn[top[u]], dfn[u]}, u = fa[top[u]];
		else sv[++nv] = {dfn[top[v]], dfn[v]}, v = fa[top[v]];
	} if(dep[u] < dep[v]) sv[++nv] = {dfn[u], dfn[v]}; else su[++nu] = {dfn[v], dfn[u]};
	reverse(sv + 1, sv + nv + 1);
	for(int i = 1; i <= nu; i++) tot += tr.query(su[i].first, su[i].second);
	for(int i = 1; i <= nv; i++) tot += tr.query(sv[i].first, sv[i].second);
	if(!tot) {
		for(int i = 1; i <= nu; i++) pre = pre + query(1, n, su[i].first, su[i].second, 1, 1);
		for(int i = 1; i <= nv; i++) pre = pre + query(1, n, sv[i].first, sv[i].second, 1, 0);
		return type ? pre.aic : pre.anic;
	}
	while(nu) {
		int lb = su[1].first, rb = su[1].second, tot = tr.query(lb, rb);
		if(tot) {
			int l = lb + 1, r = rb + 1;
			while(l < r) {
				int m = l + r >> 1;
				tr.query(m, rb) ? l = m + 1 : r = m;
			} if(r <= rb) pre = pre + query(1, n, r, rb, 1, 1);
			su[1].second = r - 1; break;
		} pre = pre + query(1, n, lb, rb, 1, 1);
		for(int i = 1; i < nu; i++) su[i] = su[i + 1]; nu--;
		if(type && !pre.aic) return 0;
		if(!type && !pre.anic) return 0;
	}
	if(!nu) {
		while(nv) {
			int lb = sv[1].first, rb = sv[1].second, tot = tr.query(lb, rb);
			if(tot) {
				int l = lb - 1, r = rb - 1;
				while(l < r) {
					int m = l + r + 2 >> 1;
					tr.query(lb, m) ? r = m - 1 : l = m;
				} if(l >= lb) pre = pre + query(1, n, lb, l, 1, 0);
				sv[1].first = l + 1; break;
			} pre = pre + query(1, n, lb, rb, 1, 0);
			for(int i = 1; i < nv; i++) sv[i] = sv[i + 1]; nv--;
			if(type && !pre.aic) return 0;
			if(!type && !pre.anic) return 0;
		}
	}
	while(nv) {
		int lb = sv[nv].first, rb = sv[nv].second, tot = tr.query(lb, rb);
		if(tot) {
			int l = lb + 1, r = rb + 1;
			while(l < r) {
				int m = l + r >> 1;
				tr.query(m, rb) ? l = m + 1 : r = m;
			} if(r <= rb) suf = query(1, n, r, rb, 1, 0) + suf;
			sv[nv].second = r - 1; break;
		} suf = query(1, n, lb, rb, 1, 0) + suf, nv--;
		if(type && !suf.aic) return 0;
		if(!type && !suf.anic) return 0;
	}
	if(!nv) {
		while(nu) {
			int lb = su[nu].first, rb = su[nu].second, tot = tr.query(lb, rb);
			if(tot) {
				int l = lb - 1, r = rb - 1;
				while(l < r) {
					int m = l + r + 2 >> 1;
					tr.query(lb, m) ? r = m - 1 : l = m;
				} if(l >= lb) suf = query(1, n, lb, l, 1, 1) + suf;
				su[nu].first = l + 1; break;
			} suf = query(1, n, lb, rb, 1, 1) + suf, nu--;
			if(type && !suf.aic) return 0;
			if(!type && !suf.anic) return 0;
		}
	}
	
	pre.mx = max(pre.mx, a - type), suf.mn = min(suf.mn, b + type);
	for(int i = 1; i <= nu; i++) {
		pre = pre + query(1, n, su[i].first, su[i].second, 1, 1);
		if(type && !pre.aic) return 0;
		if(!type && !pre.anic) return 0;
	}
	for(int i = 1; i <= nv; i++) {
		pre = pre + query(1, n, sv[i].first, sv[i].second, 1, 0);
		if(type && !pre.aic) return 0;
		if(!type && !pre.anic) return 0;
	}
	pre = pre + suf;
	return type ? pre.aic : pre.anic;
}

int main() {
	freopen("ynycoding.in", "r", stdin);
	freopen("ynycoding.out", "w", stdout);
	for(int i = fc[0] = 1; i < V; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
	ifc[V - 1] = ksm(fc[V - 1], mod - 2);
	for(int i = V - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
	cin >> n >> Q;
	for(int i = 1; i <= n; i++) w[i] = read();
	for(int i = 1, u, v; i < n; i++) add(u = read(), v = read()), add(v, u);
	dfs1(1, 0), dfs2(1, 1), build(1, n, 1);
	for(int i = 1; i <= n; i++) if(w[i] == -1) tr.add(dfn[i], 1);
	for(int _ = 1, u, v, a, b; _ <= Q; _++) {
		static char str[15]; scanf("%s", str + 1);
		if(str[1] == 'U') u = read(), a = read(), update(u, a);
		else {
			u = read(), v = read(), a = read(), b = read();
			if(str[1] == 'I') print(inc(u, v, 1, a, b)), putchar('\n');
			if(str[1] == 'D') print(inc(v, u, 1, a, b)), putchar('\n');
			if(str[5] == 'D') print(inc(u, v, 0, a, b)), putchar('\n');
			if(str[5] == 'I') print(inc(v, u, 0, a, b)), putchar('\n');
		}
	} return 0;
}
