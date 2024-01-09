#include <bits/stdc++.h>

using ll = long long;

using namespace std;

const int mod = 998244353, K = 23, Root = 31;
int norm(int x) { return x >= mod ? x - mod : x; }
int reduce(int x) { return x < 0 ? x + mod : x; }
int neg(int x) { return x ? mod - x : 0; }
int quo2(int x) { return (x + (x & 1 ? mod : 0)) >> 1; }
void add(int &x, int y) { if ((x += y - mod) < 0) x += mod; }
void sub(int &x, int y) { if ((x -= y) < 0) x += mod; }
void fam(int &x, int y, int z) { x = (x + (ll)y * z) % mod; }
int mpow(int a, int b) {
  int ret = 1;
  for (; b; b >>= 1) {
    if (b & 1) ret = (ll)ret * a % mod;
    a = (ll)a * a % mod;
  }
  return ret;
}

const int BRUTE_N2_LIMIT = 50;

struct NumberTheory {
  void exGcd(int a, int b, int &x, int &y) {
    if (!b) { x = 1, y = 0; return; }
    exGcd(b, a % b, y, x), y -= a / b * x;
  }
  int inv(int a, int p = mod) { int x, y; exGcd(a, p, x, y); if (x < 0) x += p; return x; }
} nt;

namespace Simple {
  int n = 1;
  vector<int> fac({1, 1}), ifac({1, 1}), inv({0, 1});
  void build(int m) {
    n = m;
    fac.resize(n + 1), ifac.resize(n + 1), inv.resize(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % mod, ifac[i] = (ll)ifac[i - 1] * inv[i] % mod;
  }
  void check(int k) {
    int m = n;
    if (k > m) {
      while (k > m) m <<= 1;
      build(m);
    }
  }
  int gfac(int k) {
    check(k);
    return fac[k];
  }
  int gifac(int k) {
    check(k);
    return ifac[k];
  }
  int ginv(int k) {
    check(k);
    return inv[k];
  }
}

struct SimpleSequence {
  function<int(int)> func;
  SimpleSequence(const function<int(int)> &func): func(func) {}
  int operator[](int k) const { return func(k); }
} gfac(Simple::gfac), gifac(Simple::gifac), ginv(Simple::ginv);

int binom(int n, int m) {
  if (m > n || m < 0) return 0;
  return (ll)gfac[n] * gifac[m] % mod * gifac[n - m] % mod;
}

namespace NTT {
  int L = -1;
  vector<int> root;
  void init(int l) {
    L = l;
    root.resize((1 << L) + 1);
    int n = 1 << L, *w = root.data();
    w[0] = 1, w[1 << L] = mpow(Root, 1 << (K - 2 - L));
    for (int i = L; i; --i) w[1 << (i - 1)] = (ll)w[1 << i] * w[1 << i] % mod;
    for (int i = 1; i < n; ++i) w[i] = (ll)w[i & (i - 1)] * w[i & -i] % mod;
  }
  void DIF(int *a, int l) {
    int n = 1 << l;
    for (int len = n >> 1; len; len >>= 1)
      for (int *j = a, *o = root.data(); j != a + n; j += len << 1, ++o)
        for (int *k = j; k != j + len; ++k) {
          int r = (ll)*o * k[len] % mod;
          k[len] = reduce(*k - r), add(*k, r);
        }
  }
  void DIT(int *a, int l) {
    int n = 1 << l;
    for (int len = 1; len < n; len <<= 1)
      for (int *j = a, *o = root.data(); j != a + n; j += len << 1, ++o)
        for (int *k = j; k != j + len; ++k) {
          int r = norm(*k + k[len]);
          k[len] = (ll)*o * (*k - k[len] + mod) % mod, *k = r;
        }
  }
  void fft(int *a, int lgn, int d = 1) {
    if (L < lgn) init(lgn);
    int n = 1 << lgn;
    if (d == 1) DIF(a, lgn);
    else {
      DIT(a, lgn), reverse(a + 1, a + n);
      int nInv = mod - (mod - 1) / n;
      for (int i = 0; i < n; ++i) a[i] = (ll)a[i] * nInv % mod;
    }
  }
}

struct poly {
  vector<int> a;
  poly(ll v = 0): a(1) {
    if ((v %= mod) < 0) v += mod;
    a[0] = v;
  }
  poly(const poly &o): a(o.a) {}
  poly(const vector<int> &o): a(o) {}
  operator vector<int>() const { return a; }
  int operator[](int k) const { return k < a.size() ? a[k] : 0; }
  int &operator[](int k) {
    if (k >= a.size()) a.resize(k + 1);
    return a[k];
  }
  int deg() const { return (int)a.size() - 1; }
  void redeg(int d) { a.resize(d + 1); }
  int size() const { return a.size(); }
  void resize(int s) { a.resize(s); }
  poly slice(int d) const {
    if (d < a.size()) return vector<int>(a.begin(), a.begin() + d + 1);
    vector<int> ret = a;
    ret.resize(d + 1);
    return ret;
  }
  bool operator<(const poly &o) const {
    for (int i = 0; i <= min(deg(), o.deg()); ++i)
      if (a[i] != o[i])
        return a[i] < o[i];
    return deg() < o.deg();
  }
  int *base() { return a.data(); }
  const int *base() const { return a.data(); }

  poly &operator+=(const poly &o) {
    if (o.size() > a.size()) a.resize(o.size());
    for (int i = 0; i < o.size(); ++i) add(a[i], o[i]);
    return *this;
  }
  poly operator+(const poly &o) const {
    poly ret(a);
    ret += o;
    return ret;
  }
  poly operator-() const {
    poly ret = a;
    for (int i = 0; i < a.size(); ++i) ret[i] = neg(ret[i]);
    return ret;
  }
  poly &operator-=(const poly &o) { return operator+=(-o); }
  poly operator-(const poly &o) { return operator+(-o); }
  poly operator*(const poly &) const;
  poly &operator*=(const poly &o) {
    *this = operator*(o);
    return *this;
  }
  poly quo(const poly &) const;
};

poly zeroes(int d) { return vector<int>(d + 1); }

namespace NTT {
  void fft(poly &a, int lgn, int d = 1) { fft(a.base(), lgn, d); }
  void fft(vector<int> &a, int lgn, int d = 1) { fft(a.data(), lgn, d); }
}

using NTT::fft;

struct Newton {
  void inv(const poly &f, const poly &dftf, poly &g, const poly &dftg, int t) {
    int n = 1 << t;
    poly prod = dftf;
    for (int i = 0; i < (n << 1); ++i) prod[i] = (ll)prod[i] * dftg[i] % mod;
    fft(prod, t + 1, -1);
    memset(prod.base(), 0, sizeof(int) << t);
    fft(prod, t + 1);
    for (int i = 0; i < (n << 1); ++i) prod[i] = (ll)prod[i] * dftg[i] % mod;
    fft(prod, t + 1, -1);
    for (int i = 0; i < n; ++i) prod[i] = 0;
    g -= prod;
  }
  void inv(const poly &f, const poly &dftf, poly &g, int t) {
    poly dftg(g);
    dftg.resize(2 << t);
    fft(dftg, t + 1);
    inv(f, dftf, g, dftg, t);
  }
  void inv(const poly &f, poly &g, int t) {
    poly dftf(f), dftg(g);
    dftf.resize(2 << t), dftg.resize(2 << t);
    fft(dftf, t + 1), fft(dftg, t + 1);
    inv(f, dftf, g, dftg, t);
  }
} nit;

poly poly::operator*(const poly &o) const {
  int n = deg(), m = o.deg();
  if (n <= 10 || m <= 10 || n + m <= BRUTE_N2_LIMIT) {
    poly ret = zeroes(n + m);
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= m; ++j) fam(ret[i + j], a[i], o[j]);
    return ret;
  }
  n += m;
  int l = 0;
  while ((1 << l) <= n) ++l;
  poly ret = a, tmp = o;
  ret.resize(1 << l), tmp.resize(1 << l);
  fft(ret, l), fft(tmp, l);
  for (int i = 0; i < (1 << l); ++i) ret[i] = (ll)ret[i] * tmp[i] % mod;
  fft(ret, l, -1);
  return ret.slice(n);
}
poly poly::quo(const poly &o) const {
  if (o.deg() == 0) return (ll)a[0] * nt.inv(o[0]) % mod;
  poly g = nt.inv(o[0]);
  int t = 0, n;
  for (n = 1; (n << 1) <= o.deg(); ++t, n <<= 1) nit.inv(o.slice((n << 1) - 1), g, t);
  poly dftg = g;
  dftg.resize(n << 1), fft(dftg, t + 1);
  poly eps1 = o;
  eps1.resize(n << 1), fft(eps1, t + 1);
  for (int i = 0; i < (n << 1); ++i) eps1[i] = (ll)eps1[i] * dftg[i] % mod;
  fft(eps1, t + 1, -1);
  for (int i = 0; i < n; ++i) eps1[i] = eps1[i + n], eps1[i + n] = 0;
  fft(eps1, t + 1);
  poly h0 = slice(n - 1);
  h0.resize(n << 1), fft(h0, t + 1);
  poly h0g0 = zeroes((n << 1) - 1);
  for (int i = 0; i < (n << 1); ++i) h0g0[i] = (ll)h0[i] * dftg[i] % mod;
  fft(h0g0, t + 1, -1);
  poly h0eps1 = zeroes((n << 1) - 1);
  for (int i = 0; i < (n << 1); ++i) h0eps1[i] = (ll)h0[i] * eps1[i] % mod;
  fft(h0eps1, t + 1, -1);
  for (int i = 0; i < n; ++i) h0eps1[i] = reduce(operator[](i + n) - h0eps1[i]);
  memset(h0eps1.base() + n, 0, sizeof(int) << t);
  fft(h0eps1, t + 1);
  for (int i = 0; i < (n << 1); ++i) h0eps1[i] = (ll)h0eps1[i] * dftg[i] % mod;
  fft(h0eps1, t + 1, -1);
  for (int i = 0; i < n; ++i) h0eps1[i + n] = h0eps1[i], h0eps1[i] = 0;
  return (h0g0 + h0eps1).slice(o.deg());
}

int d, n, m, k, a, b, c;

poly solve(int d, int n, int a) {
  poly f = zeroes(d), g = zeroes(d);
  g[0] = 1;
  for (int i = 1; i <= d; ++i) {
    if (~(a + i) & 1) sub(f[i], binom(i, (a + i) >> 1));
    if (~(n + 1 - a + i) & 1) sub(f[i], binom(i, (n + 1 - a + i) >> 1));
    if (~i & 1) add(g[i], binom(i, i >> 1));
    if (~(n + 1 + i) & 1) add(g[i], binom(i, (n + 1 + i) >> 1));
  }
  poly ret = f.quo(g) + 1;
  for (int i = 1; i <= d; ++i) add(ret[i], ret[i - 1]), add(ret[i], ret[i - 1]);
  for (int i = 0; i <= d; ++i) ret[i] = (ll)ret[i] * gifac[i] % mod;
  return ret;
}

int main() {
  freopen("homura.in", "r", stdin), freopen("homura.out", "w", stdout);
  scanf("%d%d%d%d%d%d%d", &d, &n, &m, &k, &a, &b, &c);
  poly f = solve(d, n, a) * solve(d, m, b);
  poly g = solve(d, k, c);
  int ans = 0;
  for (int i = 0; i <= d; ++i) fam(ans, f[i], g[d - i]);
  ans = (ll)ans * gfac[d] % mod;
  printf("%d\n", ans);
}
