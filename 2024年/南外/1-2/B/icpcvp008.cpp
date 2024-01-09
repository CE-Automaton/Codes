#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define maxn 100005
#define put() putchar('\n')
#define Tp template <typename T>
#define Ts template <typename T, typename... Ar>
using namespace std;
Tp void read(T& x) {
    int f = 1;
    x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    x *= f;
}
namespace Debug {
Tp void _debug(char* f, T t) { cerr << f << '=' << t << endl; }
Ts void _debug(char* f, T x, Ar... y) {
    while (*f != ',') cerr << *f++;
    cerr << '=' << x << ",";
    _debug(f + 1, y...);
}
#define gdb(...) _debug((char*)#__VA_ARGS__, __VA_ARGS__)
}  // namespace Debug
using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod = 1e9 + 7;
int power(int x, int y = mod - 2) {
    int sum = 1;
    while (y) {
        if (y & 1)
            sum = sum * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return sum;
}
int h, w, n;
int times;
void add(int& x, int y) { x = (x + y) % mod; }
namespace seg {
int f[maxn << 2];
vector<pair<int, int> > stac[maxn << 2];
int len[maxn << 2];
void init(void) { memset(len, -1, sizeof(len)); }
void pushup(int rt) { f[rt] = min(f[rt << 1], f[rt << 1 | 1]); }
void Update(int l, int r, int rt, int head, int k) {
    if (l == r) {
        stac[rt].push_back(mk(0, 0));
        stac[rt][++len[rt]] = mk(times, k);
        f[rt] = times;
        return;
    }
    int mid = l + r >> 1;
    if (head <= mid)
        Update(l, mid, rt << 1, head, k);
    else
        Update(mid + 1, r, rt << 1 | 1, head, k);
    pushup(rt);
}
const int inf = 2e9 + 10;
int Query(int l, int r, int rt, int head, int tail, int L) {
    // gdb(l,r,rt,head,tail,f[rt],L);
    if (f[rt] > L)
        return 0;
    if (l == r) {
        int res = 0;
        while (len[rt] >= 0 && stac[rt][len[rt]].fi <= L) add(res, stac[rt][len[rt]].se), len[rt]--;
        if (len[rt] >= 0)
            f[rt] = stac[rt][len[rt]].fi;
        else
            f[rt] = inf;
        return res;
    }
    int mid = l + r >> 1, res = 0;
    if (head <= mid)
        res += Query(l, mid, rt << 1, head, tail, L);
    if (tail > mid)
        res += Query(mid + 1, r, rt << 1 | 1, head, tail, L);
    pushup(rt);
    return res % mod;
}
}  // namespace seg
struct node {
    int u, l, r, s;
} a[maxn];
bool cmp(node x, node y) { return x.u > y.u; }
signed main(void) {
    freopen("fall.in", "r", stdin);
    freopen("fall.out", "w", stdout);
    int i, res;
    read(h);
    read(w);
    read(n);
    seg::init();
    for (i = 1; i <= n; i++) {
        read(a[i].u), read(a[i].l), read(a[i].r), read(a[i].s);
    }
    sort(a + 1, a + 1 + n, cmp);
    times = h + 1;
    for (i = 1; i <= w; i++) seg::Update(1, w, 1, i, 1);
    for (i = 1; i <= n; i++) {
        times = a[i].u;
        int res = seg::Query(1, w, 1, a[i].l, a[i].r, a[i].u + a[i].s);
        // gdb(a[i].u,a[i].l,a[i].r,a[i].s,res);
        if (!res)
            continue;
        if (a[i].l == 1)
            seg::Update(1, w, 1, a[i].r + 1, res * 2);
        else if (a[i].r == w)
            seg::Update(1, w, 1, a[i].l - 1, res * 2);
        else
            seg::Update(1, w, 1, a[i].l - 1, res), seg::Update(1, w, 1, a[i].r + 1, res);
    }
    int sum = 0;
    for (i = 1; i <= w; i++) res = seg::Query(1, w, 1, i, i, h + 1), add(sum, res);
    printf("%lld\n", sum);
    return 0;
}
// i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
