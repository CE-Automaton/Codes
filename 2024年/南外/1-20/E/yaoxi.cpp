#include <bits/stdc++.h>
using namespace std;
#define TIME (1e3 * clock() / CLOCKS_PER_SEC)
#define debug(fmt, ...) \
  fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
#define __nflsoj_stop_multithreading(tl) while (TIME < tl) ;
template <class _Tx, class _Ty>
inline void chkmin(_Tx& x, const _Ty& y) { if (y < x) x = y; }
template <class _Tx, class _Ty>
inline void chkmax(_Tx& x, const _Ty& y) { if (x < y) x = y; }
namespace io {
const int MAXBUF = 1 << 23;
char buf[MAXBUF], *p1 = buf, *p2 = buf;
char pbuf[MAXBUF], *pp = pbuf;
inline char getc() {
  return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, MAXBUF, stdin)),
         p1 == p2 ? EOF : *p1++;
}
inline void putc(char c) {
  (pp == pbuf + MAXBUF) && (fwrite(pbuf, 1, MAXBUF, stdout), pp = pbuf),
      *pp++ = c;
}
inline void flush() {
  fwrite(pbuf, 1, pp - pbuf, stdout), pp = pbuf;
}
struct _ { ~_() { flush(); }} __;
} // namespace io
using io::getc;
using io::putc;
template <class _Tp>
inline _Tp& read(_Tp& x) {
  bool sign = false;
  char ch = getc();
  for (; !isdigit(ch); ch = getc()) sign |= (ch == '-');
  for (x = 0; isdigit(ch); ch = getc()) x = x * 10 + (ch ^ 48);
  return sign ? (x = -x) : x;
}
template <class _Tp>
inline void write(_Tp x) {
  if (x < 0) putc('-'), x = -x;
  if (x > 9) write(x / 10);
  putc((x % 10) ^ 48);
}
bool Mbe;
using ll = long long;
constexpr int N = 5e5 + 10, B = 3055;
int n, m, q, bsz, blk, ibsz, iblk;
int prf[B], tag[B], val[N], bst[B], bed[B], bel[N], ibst[B], ibed[B], ibel[N];
ll ans[N];
struct opti {
  int op, l, r, v;
} opt[N];
struct quer {
  int t, p, id;
  bool operator<(const quer& rhs) const { return t < rhs.t; }
} qrys[N];
namespace blk1 {
ll sum[B], val[N];
void init() {
  fill(sum + 1, sum + ibsz + 1, 0);
  fill(val + 1, val + max(n, m) + 1, 0);
}
void update(int p, ll v) {
  val[p] += v, sum[ibel[p]] += v;
}
ll query(int p) {
  ll ret = 0;
  for (int i = p; i <= ibed[ibel[p]]; ++i) ret += val[i];
  for (int i = ibel[p] + 1; i <= ibsz; ++i) ret += sum[i];
  return ret;
}
} // namespace blk1
namespace blk2 {
ll sum[B], val[N];
void init() {
  fill(sum + 1, sum + ibsz + 1, 0);
  fill(val + 1, val + max(n, m) + 1, 0);
}
void update(int p, ll v) {
  for (int i = 1; i < ibel[p]; ++i) sum[i] += v;
  for (int i = ibst[ibel[p]]; i <= p; ++i) val[i] += v;
}
ll query(int p) {
  return val[p] + sum[ibel[p]];
}
} // namespace blk2
bool is_last_small(int p) {
  return tag[p] == -1;
}
void push_small(int l, int r, int v) {
  int p = bel[l], las = val[l], len = r - l + 1;
  blk1::update(las, (ll)len * opt[las].v * v * prf[p]);
}
void push_small_all(int l, int r, int v) {
  for (int i = l, j; i <= r; i = j + 1) {
    j = i;
    while (j < r && val[j + 1] == val[i]) ++j;
    push_small(i, j, v);
  }
}
void work1_small(int id, int l, int r) {
  int p = bel[l];
  if (is_last_small(p)) {
    push_small_all(l, r, 1);
    for (int i = l; i <= r; ++i) val[i] = id;
    push_small(l, r, -1);
  } else {
    for (int i = bst[p]; i <= bed[p]; ++i)
      val[i] = l <= i && i <= r ? id : tag[p];
    if (bst[p] < l) push_small(bst[p], l - 1, -1);
    push_small(l, r, -1);
    if (r < bed[p]) push_small(r + 1, bed[p], -1);
    tag[p] = -1;
  }
}
void work1_large(int id, int l, int r) {
  for (int i = l; i <= r; ++i) {
    if (is_last_small(i)) push_small_all(bst[i], bed[i], 1);
    tag[i] = id;
  }
}
void work1(int id, int l, int r) {
  if (bel[l] == bel[r]) {
    work1_small(id, l, r);
  } else {
    work1_small(id, l, bed[bel[l]]);
    work1_small(id, bst[bel[r]], r);
    work1_large(id, bel[l] + 1, bel[r] - 1);
  }
}
void work2_small(int l, int r) {
  int p = bel[l];
  if (tag[p] != -1) {
    if (tag[p]) blk1::update(tag[p], (ll)opt[tag[p]].v * (r - l + 1));
  } else {
    for (int i = l; i <= r; ++i)
      if (val[i]) blk1::update(val[i], opt[val[i]].v);
  }
}
void work2_large(int l, int r) {
  for (int i = l; i <= r; ++i) {
    ++prf[i];
    if (!is_last_small(i)) {
      int las = tag[i], len = bed[i] - bst[i] + 1;
      if (las) blk1::update(las, (ll)opt[las].v * len);
    }
  }
}
void work2(int l, int r) {
  if (bel[l] == bel[r]) {
    work2_small(l, r);
  } else {
    work2_small(l, bed[bel[l]]);
    work2_small(bst[bel[r]], r);
    work2_large(bel[l] + 1, bel[r] - 1);
  }
}
void solve(int p) {
  blk2::init();
  int prf = 0, tag = 0, ptrq = 1;
  fill(val + bst[p], val + bed[p] + 1, 0);
  auto push_small = [&](int l, int r, int v) {
    int las = val[l], len = r - l + 1;
    blk2::update(las, (ll)len * opt[las].v * v * -1);
  };
  auto push_small_all = [&](int l, int r, int v) {
    for (int i = l, j; i <= r; i = j + 1) {
      j = i;
      while (j < r && val[j + 1] == val[i]) ++j;
      push_small(i, j, v);
    }
  };
  for (int i = 1; i <= m; ++i) {
    if (opt[i].op == 1) {
      if (bel[opt[i].l] < p && p < bel[opt[i].r]) {
        if (tag == -1) push_small_all(bst[p], bed[p], 1);
        tag = i;
      } else {
        int l = max(opt[i].l, bst[p]);
        int r = min(opt[i].r, bed[p]);
        if (l <= r) {
          if (tag == -1) {
            push_small_all(l, r, 1);
            for (int j = l; j <= r; ++j) val[j] = i;
            push_small(l, r, -1);
          } else {
            for (int j = bst[p]; j <= bed[p]; ++j)
              val[j] = l <= j && j <= r ? i : tag;
            if (bst[p] < l) push_small(bst[p], l - 1, -1);
            push_small(l, r, -1);
            if (r < bed[p]) push_small(r + 1, bed[p], -1);
            tag = -1;
          }
        }
      }
    } else {
      if (bel[opt[i].l] < p && p < bel[opt[i].r]) ++prf;
    }
    while (ptrq <= q && qrys[ptrq].t <= i)
      ans[qrys[ptrq].id] += blk2::query(qrys[ptrq].p) * prf, ++ptrq;
  }
}
bool Med;
int main() {
  freopen("mfsn.in", "r", stdin);
  freopen("mfsn.out", "w", stdout);
  // debug("Mem: %.4lfMB.", fabs(&Med - &Mbe) / 1048576);
  read(n), read(m), read(q);
  blk = 3000, iblk = sqrt(m) + 1;
  for (int i = 1; i <= m; ++i) {
    int op, l, r, v;
    read(op), read(l), read(r);
    if (op == 1) {
      read(v);
      opt[i] = {op, l, r, v};
    } else {
      opt[i] = {op, l, r, 0};
    }
  }
  for (int i = 1; i <= q; ++i) {
    int l, r;
    read(l), read(r);
    qrys[i] = {r, l, i};
  }
  sort(qrys + 1, qrys + q + 1);
  for (int l = 1; l <= n; l += blk) {
    int r = min(n, l + blk - 1);
    ++bsz, bst[bsz] = l, bed[bsz] = r;
    fill(bel + l, bel + r + 1, bsz);
  }
  for (int l = 1; l <= m; l += iblk) {
    int r = min(m, l + iblk - 1);
    ++ibsz, ibst[ibsz] = l, ibed[ibsz] = r;
    fill(ibel + l, ibel + r + 1, ibsz);
  }
  int ptrq = 1;
  blk1::init();
  for (int i = 1; i <= m; ++i) {
    if (opt[i].op == 1) {
      work1(i, opt[i].l, opt[i].r);
    } else {
      work2(opt[i].l, opt[i].r);
    }
    while (ptrq <= q && qrys[ptrq].t <= i)
      ans[qrys[ptrq].id] += blk1::query(qrys[ptrq].p), ++ptrq;
  }
  for (int i = 1; i <= bsz; ++i) solve(i);
  for (int i = 1; i <= q; ++i) write(ans[i]), putc('\n');
  __nflsoj_stop_multithreading(8888); // nflsoj should stop multi-threading!
  return 0;
}
