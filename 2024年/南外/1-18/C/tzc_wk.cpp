#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/hash_policy.hpp>
// #include <ext/pb_ds/priority_queue.hpp>
using namespace std;
// using namespace __gnu_pbds;
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
const int MAXN = 1e5;
const int MOD = 998244353;
const int INV2 = MOD + 1 >> 1;
int n, m; pair<ll, int> p[MAXN + 5];
int l[MAXN + 5], r[MAXN + 5], tim[MAXN + 5];
ll sum[MAXN + 5];
set<int> st[MAXN + 5];
int f[MAXN + 5];
int find(int x) {return (!f[x]) ? x : f[x] = find(f[x]);}
int df0[MAXN + 5], df1[MAXN + 5];
void add(int &x, int v) {((x += v) >= MOD) && (x -= MOD);}
void dec(int &x, int v) {((x -= v) < 0) && (x += MOD);}
int main() {
	freopen("boxes.in", "r", stdin);
	freopen("boxes.out", "w", stdout);
	read(n); read(m); int S = 0;
	for (int i = 1; i <= n; i++) read(p[i].fi), read(p[i].se), S = (S + p[i].fi * p[i].se) % MOD;
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++) sum[i] = p[i].se, l[i] = r[i] = i;
	for (int i = 1; i < n; i++) {
		ll nd = sum[i] / (p[i + 1].fi - p[i].fi);
		st[nd].insert(i);
	}
	for (int i = 1; i <= n; i++) tim[i] = m;
	vector<tuple<int, ll, int, int> > vec;
	for (int i = m; i; i--) {
		while (!st[i].empty()) {
			int x = *st[i].begin(); st[i].erase(st[i].find(x));
			int Lx = l[find(x)], Rx = r[find(x)];
			int Ly = Rx + 1, Ry = r[find(Ly)];
			int fx = find(x), fy = find(Ly);
			vec.pb(mt(Lx, sum[fx], i + 1, tim[fx]));
			vec.pb(mt(Ly, sum[fy], i + 1, tim[fy]));
			if (Ry != n) {
				ll nd = sum[fy] / (p[Ry + 1].fi - p[Ly].fi);
				st[nd].erase(st[nd].find(fy));
			}
			sum[fx] += sum[fy]; f[fy] = fx; l[fx] = Lx; r[fx] = Ry;
			tim[fx] = i;
			if (Ry != n) {
				ll nd = sum[fx] / (p[Ry + 1].fi - p[Lx].fi);
				st[nd].insert(fx);
			}
		}
	}
	for (int i = 1; i <= n; i++) if (find(i) == i)
		vec.pb(mt(l[find(i)], sum[i], 1, tim[i]));
	cerr << clock() << endl;
	for (auto t : vec) {
		int lp = get<0>(t), L = get<2>(t), R = get<3>(t);
		ll ss = get<1>(t); int sv = ss % MOD;
		int ori = 1ll * p[lp].fi % MOD * sv % MOD;
		for (int l = L, r; l <= R; l = r + 1) {
			r = R; if (ss / l) chkmin(r, ss / (ss / l));
			int val = (ss / l) % MOD;
			int v0 = (1ll * sv * val + ori) % MOD;
			int v1 = (1ll * val * (MOD - val - 1) % MOD * INV2) % MOD;
			add(df0[l], v0); dec(df0[r + 1], v0);
			add(df1[l], v1); dec(df1[r + 1], v1);
		}
	}
	for (int i = 1; i <= m; i++) {
		df0[i] = (df0[i] + df0[i - 1]) % MOD;
		df1[i] = (df1[i] + df1[i - 1]) % MOD;
	}
	for (int i = 1; i <= m; i++) print((1ll * df1[i] * i + df0[i] - S + MOD) % MOD, " \n"[i == m]);
	print_final();
	return 0;
}
