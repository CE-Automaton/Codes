#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long
#define pll pair <ll, ll>

bool Mbe;
char buf[1 << 21], *p1 = buf, *p2 = buf, obuf[1 << 24], *O = obuf;
#define gc (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
// #define gc getchar()
#define pc(x) (*O++ = x)
#define flush() (fwrite(obuf, 1, O - obuf, stdout), O = obuf)
inline ll read() {
	ll x = 0; char s = gc;
	while(!isdigit(s)) s = gc;
	while(isdigit(s)) x = x * 10 + s - '0', s = gc;
	return x;
}
void print(int x) {
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}

const int N = 1e5 + 5;
const int mod = 998244353;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}

int n, m, cur, t[N], k[N], b[N];
void modify(int p, int dk, int db) {add(k[p], dk), add(b[p], db);}
void modify(int l, int r, int dk, int db) {modify(r, dk, db), modify(l - 1, mod - dk, mod - db);}

pll c[N];
ll val(pll v) {return v.fi % mod * (v.se % mod) % mod;}
set <ll> s;
priority_queue <pll> q;
ll calc(int i, int j) {return c[i].se / (c[j].fi - c[i].fi);}
void calc(int id) {
	for(int l = cur + 1, r; l <= t[id]; l = r + 1) {
		ll d = c[id].se / l;
		r = min(t[id], (int)(d ? c[id].se / d : t[id])), d %= mod;
		modify(l, r, (1ll * d * (d - 1) / 2 - 1ll * d * d % mod + mod) % mod, d * (c[id].se % mod) % mod);
	}
}
void merge(int id, int it) {
	int coef = mod - val(c[id]);
	add(coef, mod - val(c[it])), calc(id), calc(it);
	c[it].fi = -1, c[id].se += c[it].se, add(coef, val(c[id]));
	t[id] = cur, add(b[cur], coef);
}

bool Med;
int main() {
	fprintf(stderr, "%.4lf\n", (&Mbe - &Med) / 1048576.0);
	freopen("boxes.in", "r", stdin);
//	freopen("ex_boxes5.in", "r", stdin);
	freopen("boxes.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) c[i].fi = read(), c[i].se = read(), t[i] = m, s.insert(i);
	sort(c + 1, c + n + 1);
	for(int i = 1; i < n; i++) q.push({calc(i, i + 1), i});
	for(int i = cur = m; i; cur = --i) {
		while(!q.empty() && q.top().fi == i) {
			pll t = q.top(); q.pop(); int id = t.se;
			if(c[id].fi == -1) continue;
			auto it = s.upper_bound(id);
			merge(id, *it), s.erase(it), it = s.upper_bound(id);
			if(it != s.end()) q.push({calc(id, *it), id});
		}
	}
	for(int i = 1; i <= n; i++) if(c[i].fi != -1) calc(i);
	for(int i = m; i; i--) add(k[i], k[i + 1]), add(b[i], b[i + 1]);
	for(int i = 1; i <= m; i++) print((1ll * k[i] * i + b[i]) % mod), pc(i == m ? '\n' : ' ');
	return flush(), 0;
}
