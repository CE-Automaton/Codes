#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

bool _u;

using ll = long long;
using db = double;
using pii = pair <int, int> ;
using vi = vector <int> ;
#define ci const int
template <class T>
inline void chmax(T &x, const T &y) { if(x < y) x = y; }
template <class T>
inline void chmin(T &x, const T &y) { if(x > y) x = y; }
#define mp make_pair
#define fi first
#define se second
#define pc putchar
#define lb lower_bound
#define ub upper_bound
#define pb push_back
#define eb emplace_back
#define ppc __builtin_popcount
#define ctz __builtin_ctz
#define all(a) a.begin(), a.end()
#define clr(a, n) memset(a, 0, sizeof(a[0]) * (n + 1))
#define rep(i, l, r) for(int i = l, i##end = r; i <= i##end; ++ i)
#define per(i, r, l) for(int i = r, i##end = l; i >= i##end; -- i)
#define fsub(T, S) for(int T = S, T##_f = T; T; T = (T - 1) & T##_f)
#define fsubm(T, S) for(int T = S, T##_f = T; T; T = (T - 1) & T##_f) if(T & (T##_f & -T##_f))
#define Sin(S, i) ((S) >> (i) & 1)

char inputbuf[1 << 23], *p1 = inputbuf, *p2 = inputbuf;
#define getchar() (p1 == p2 && (p2 = (p1 = inputbuf) + fread(inputbuf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
	int res = 0; char ch = getchar(); bool f = true;
	for(; ch < '0' || ch > '9'; ch = getchar())
		f &= ch != '-';
	for(; ch >= '0' && ch <= '9'; ch = getchar())
		res = res * 10 + (ch ^ 48);
	return f ? res : -res;
}

const int N = 5e5 + 15, P = 1e9 + 7;

struct matrix {
	int n, m;
	ll a[4][4];

	void unit() {
		rep(i, 0, 3) a[i][i] = 1;
	}
	matrix operator * (const matrix &b) {
		matrix res(n, b.m);
		rep(i, 0, n - 1) rep(j, 0, m - 1)
			if(a[i][j]) rep(k, 0, b.m - 1)
				(res.a[i][k] += a[i][j] * b.a[j][k]) %= P;
		return res;
	}
	matrix operator * (const ll &x) {
		matrix res(n, m);
		rep(i, 0, n - 1) rep(j, 0, m - 1)
			res.a[i][j] = a[i][j] * x % P;
		return res;
	}
	matrix operator + (const matrix &b) {
		matrix res(n, m);
		rep(i, 0, n - 1) rep(j, 0, m - 1)
			res.a[i][j] = (a[i][j] + b.a[i][j]) % P;
		return res;
	}
	matrix(int _n = 0, int _m = 0) {
		n = _n; m = _m;
		memset(a, 0, sizeof(a));
	}
} B, M, S, pm[N];

int x[N];

bool _v;

signed main() {
	//clock_t _st = clock();
	//cerr << abs(&_u - &_v) / 1048576.0 << " MB" << endl;
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	B = matrix(1, 4);
	B.a[0][0] = 1; B.a[0][1] = 1;
	B.a[0][2] = 5; B.a[0][3] = 18;
	M = matrix(4, 4);
	M.a[1][0] = M.a[2][1] = M.a[3][2] = 1;
	M.a[1][3] = 1; M.a[2][3] = P - 2; M.a[3][3] = 4;
//	matrix tmp = B * M * M;
//	rep(i, 0, tmp.n - 1) {
//		rep(j, 0, tmp.m - 1)
//			printf("%lld ", tmp.a[i][j]);
//		pc(10);
//	}
	pm[0] = M;
	rep(i, 1, 30) pm[i] = pm[i - 1] * pm[i - 1];
	S = B;
	int n = read(), m = read();
	rep(i, 1, m) x[i] = read();
//	rep(i, 1, m) x[i] = i * 100;
	x[++ m] = n;
	ll f = 0;
	rep(i, 1, m) {
		int w = x[i] - x[i - 1];
		per(j, 30, 0) if(w >> j & 1) S = S * pm[j];
		f = P - S.a[0][0];
		S = S + B * f;
	}
	printf("%lld\n", P - f);
	//cerr << (clock() - _st) * 1.0 / CLOCKS_PER_SEC << " s" << endl;
	return 0;
}
