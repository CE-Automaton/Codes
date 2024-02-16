#include <bits/stdc++.h>
using namespace std;
static constexpr int Maxn = 1e5 + 5, MaxN = 1 << 18, N = 1 << 17;
static constexpr int Maxm = 5005, M = 5000, B = 60;
bool _Med;
int n, q, bel[Maxm], bn;
int bL[Maxm], bR[Maxm];
struct sgt1 {
  uint64_t tr[MaxN], lz[MaxN];
#define ls (p << 1 | 0)
#define rs (p << 1 | 1)
  inline void pushup(int p) { tr[p] = tr[ls] | tr[rs]; }
  void pushlz(int p, uint64_t w) { tr[p] |= w, lz[p] |= w; }
  void pushdown(int p) { if (lz[p]) pushlz(ls, lz[p]), pushlz(rs, lz[p]), lz[p] = 0; }
  void update(int L, int R, int w, 
      int p = 1, int l = 0, int r = N - 1) {
    if (L <= l && r <= R) return pushlz(p, 1ULL << w);
    if (L > r || l > R) return; pushdown(p);
    int mid = (l + r) >> 1;
    update(L, R, w, ls, l, mid);
    update(L, R, w, rs, mid + 1, r);
    pushup(p);
  } // update
  uint64_t query(int L, int R, 
      int p = 1, int l = 0, int r = N - 1) {
    if (L > r || l > R) return 0;
    if (L <= l && r <= R) return tr[p];
    pushdown(p);
    int mid = (l + r) >> 1;
    return query(L, R, ls, l, mid)
      | query(L, R, rs, mid + 1, r);
  } // query
} t[M / B + 5];
#undef ls
#undef rs
static constexpr int MaxT = 2e7;
int root[Maxm], tn;
bool tr[MaxT], lz[MaxT];
int ls[MaxT], rs[MaxT];
inline void pushup(int p) { tr[p] = tr[ls[p]] | tr[rs[p]]; }
void pushlz(int p) { tr[p] = true, lz[p] = true; }
void pushdown(int p) {
  if (!ls[p]) ls[p] = ++tn;
  if (!rs[p]) rs[p] = ++tn;
  if (lz[p]) pushlz(ls[p]), pushlz(rs[p]), lz[p] = false;
} // pushdown
void update(int &p, int l, int r, int L, int R) {
  if (!p) p = ++tn;
  if (L > r || l > R) return;
  if (L <= l && r <= R) return pushlz(p);
  pushdown(p);
  int mid = (l + r) >> 1;
  update(ls[p], l, mid, L, R);
  update(rs[p], mid + 1, r, L, R);
  pushup(p);
} // update
bool query(int p, int l, int r, int L, int R) {
  if (!p || l > R || L > r) return false;
  if (L <= l && r <= R) return tr[p];
  pushdown(p);
  int mid = (l + r) >> 1;
  return query(ls[p], l, mid, L, R)
    | query(rs[p], mid + 1, r, L, R);
} // query
bool _Mbe;
int main(void) {
  freopen("stl.in", "r", stdin);
  freopen("stl.out", "w", stdout);
  fprintf(stderr, "Memory Elapsed: %.3lf MB\n", (&_Med - &_Mbe) / 1048576.0);
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= M; ++i) bel[i] = (i - 1) / B + 1;
  for (int i = 1; i <= bel[M]; ++i)
    bL[i] = (i - 1) * B + 1, bR[i] = i * B;
  bR[bn = bel[M]] = M;
  while (q--) {
    int op, l, r, k;
    scanf("%d%d%d%d", &op, &l, &r, &k);
    if (op == 1) {
      t[bel[k]].update(l, r, k - bL[bel[k]]);
      update(root[k], 1, n, l, r);
    } else {
      int b = 1;
      for (b = 1; b <= bn; ++b) {
        uint64_t mask = t[b].query(l, r);
        int c = __builtin_popcountll(mask);
        if (k <= c) break;
        else k -= c;
      }
      if (b == tn) { puts("-1"); continue; }
      for (int i = bL[b]; i <= bR[b]; ++i) {
        if (query(root[i], 1, n, l, r)) {
          if (--k == 0) { printf("%d\n", i); goto pause; }
        }
      }
      puts("-1");
    }
pause:; }
  exit(EXIT_SUCCESS);
} // main
