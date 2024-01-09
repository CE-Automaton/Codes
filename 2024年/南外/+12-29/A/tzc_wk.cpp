#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/hash_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
#define fi first
#define se second
#define fill0(a) memset(a, 0, sizeof(a))
#define fill1(a) memset(a, -1, sizeof(a))
#define fillbig(a) memset(a, 63, sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define mt make_tuple
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
template <typename T1, typename T2> void chkmin(T1 &x, T2 y){
	if (x > y) x = y;
}
template <typename T1, typename T2> void chkmax(T1 &x, T2 y){
	if (x < y) x = y;
}
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long double ld;
namespace fastio {
	#define FILE_SIZE 1 << 23
	char rbuf[FILE_SIZE], *p1 = rbuf, *p2 = rbuf, wbuf[FILE_SIZE], *p3 = wbuf;
	inline char getc() {
		return p1 == p2 && (p2 = (p1 = rbuf) + fread(rbuf, 1, FILE_SIZE, stdin), p1 == p2) ? -1: *p1++;
	}
	inline void putc(char x) {(*p3++ = x);}
	template <typename T> void read(T &x) {
		x = 0; char c = getc(); T neg = 0;
		while (!isdigit(c)) neg |= !(c ^ '-'), c = getc();
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getc();
		if (neg) x = (~x) + 1;
	}
	template <typename T> void recursive_print(T x) {
		if (!x) return;
		recursive_print (x / 10);
		putc (x % 10 ^ 48);
	}
	template <typename T> void print(T x) {
		if (!x) putc('0');
		if (x < 0) putc('-'), x = -x;
		recursive_print(x);
	}
	template <typename T> void print(T x,char c) {print(x); putc(c);}
	void readstr(char *s) {
		char c = getc();
		while (c <= 32 || c >= 127) c = getc();
		while (c > 32 && c < 127) s[0] = c, s++, c = getc();
		(*s) = 0;
	}
	void printstr(string s) {
		for (int i = 0; i < s.size(); i++) putc(s[i]);
	}
	void printstr(char *s) {
		int len = strlen(s);
		for (int i = 0; i < len; i++) putc(s[i]);
	}
	void print_final() {fwrite(wbuf, 1, p3 - wbuf, stdout);}
}
using namespace fastio;
const int MAXN = 5e5;
const int INF = 0x3f3f3f3f;
typedef vector<pair<int, int> > vpii;
int n, m, p[MAXN + 5], hd[MAXN + 5], to[MAXN * 2 + 5], nxt[MAXN * 2 + 5], ec = 0;
void adde(int u, int v) {to[++ec] = v; nxt[ec] = hd[u]; hd[u] = ec;}
struct node {int l, r, lz; pii vec[9]; int len;} s[MAXN * 4 + 5];
void pushup(int k) {
	pii *v1 = s[k << 1].vec, *v2 = s[k << 1 | 1].vec, *v3 = s[k].vec;
	s[k].len = 0; int &len = s[k].len; s[k].vec[0] = mp(-INF, 0);
	for (int i = 1, j = 1; i <= s[k << 1].len || j <= s[k << 1 | 1].len; ) {
		if (v1[i] < v2[j]) {
			if (v3[len].fi == v1[i].fi) v3[len].se += v1[i].se;
			else v3[++len] = v1[i]; i++;
		} else {
			if (v3[len].fi == v2[j].fi) v3[len].se += v2[j].se;
			else v3[++len] = v2[j]; j++;
		}
		if (s[k].len == m + 1) {s[k].len --; break;}
	}
	s[k].vec[s[k].len + 1] = mp(INT_MAX, 0);
}
void build(int k, int l, int r) {
	s[k].l = l; s[k].r = r; if (l == r) {
		s[k].vec[1] = mp(INF, 1); s[k].len = 1;
		s[k].vec[2] = mp(INT_MAX, 0); return;
	}
	int mid = l + r >> 1; build(k << 1, l, mid); build(k << 1 | 1, mid + 1, r); pushup(k);
}
void tag(int k, int v) {for (int i = 1; i <= s[k].len; i++) s[k].vec[i].fi += v; s[k].lz += v;}
void pushdown(int k) {if (s[k].lz) tag(k << 1, s[k].lz), tag(k << 1 | 1, s[k].lz), s[k].lz = 0;}
void modify(int k, int l, int r, int v) {
	if (l > r) return;
	if (l <= s[k].l && s[k].r <= r) return tag(k, v), void();
	pushdown(k); int mid = s[k].l + s[k].r >> 1;
	if (r <= mid) modify(k << 1, l, r, v);
	else if (l > mid) modify(k << 1 | 1, l, r, v);
	else modify(k << 1, l, mid, v), modify(k << 1 | 1, mid + 1, r, v);
	pushup(k);
}
void assign(int k, int p, int v) {
	if (s[k].l == s[k].r) {
		s[k].len = 1; s[k].vec[1] = mp(v, 1);
		s[k].vec[2] = mp(INT_MAX, 0);
		return;
	}
	pushdown(k); int mid = s[k].l + s[k].r >> 1;
	(p <= mid) ? assign(k << 1, p, v) : assign(k << 1 | 1, p, v);
	pushup(k);
}
int main() {
	freopen("toccare.in", "r", stdin);
	freopen("toccare.out", "w", stdout);
	read(n); read(m); ll res = 0; build(1, 1, n);
	for (int i = 1; i <= n; i++) read(p[i]);
	for (int i = 1, u, v; i < n; i++) read(u), read(v), u = p[u], v = p[v], adde(u, v), adde(v, u);
	for (int i = 1; i <= n; i++) {
		assign(1, i, -i);
		for (int e = hd[i]; e; e = nxt[e]) {
			int j = to[e];
			if (j < i) modify(1, 1, j, -1);
		}
		for (auto p : s[1].vec) if (p.fi <= m - i - 1) res += p.se;
	}
	printf("%lld\n", res);
	return 0;
}
