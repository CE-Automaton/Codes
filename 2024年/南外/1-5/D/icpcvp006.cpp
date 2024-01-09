// 6th gen
#include <iostream>
#include <algorithm>
using namespace std;
namespace lly {
constexpr int N = 1e6 + 5;
using ll = long long;
struct edge {
    int to, nxt;
} e[N << 1];
int head[N], cnt = 0;
inline void add(int u, int v) {
    e[++cnt] = (edge) {
        v, head[u]
    };
    head[u] = cnt;
}
int siz[N], son[N], dep[N], fa[N];
inline void dfs1(int u, int f) {
    siz[u] = 1;
    dep[u] = dep[f] + 1;
    fa[u] = f;

    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;

        if (v == f)
            continue;

        dfs1(v, u);
        siz[u] += siz[v];

        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}
int top[N], idx = 0, dfn[N], nfd[N];
inline void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++idx;
    nfd[idx] = u;

    if (son[u])
        dfs2(son[u], tp);

    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;

        if (v == fa[u] || v == son[u])
            continue;

        dfs2(v, v);
    }
}
ll vl[N];
namespace st {
int lg[N], st[21][N];
inline int get(int x, int y) {
    return vl[x] > vl[y] ? x : y;
}
inline void init(int n) {
    lg[0] = -1;

    for (int i = 1; i <= n; i++)
        lg[i] = lg[i >> 1] + 1, st[0][i] = nfd[i];

    for (int i = 1; i <= 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = get(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
inline int query(int l, int r) {
    int k = lg[r - l + 1];
    return get(st[k][l], st[k][r - (1 << k) + 1]);
}
}
struct dat {
    int l, r, id;
};
inline bool operator<(const dat &x, const dat &y) {
    return vl[x.id] < vl[y.id] || (vl[x.id] == vl[y.id] && x.id < y.id);
}
namespace myq {
dat a[1005];
int tp = 0;
inline const dat &top() {
    return a[1];
}
inline void push(const dat &x) {
    a[++tp] = x;
    push_heap(a + 1, a + tp + 1);
}
inline void pop() {
    pop_heap(a + 1, a + tp + 1);
    tp--;
}
inline bool empty() {
    return !tp;
}
inline void clear() {
    tp = 0;
}
}
inline void push(int l, int r) {
    if (l > r)
        return;

    myq::push((dat) {
        l, r, st::query(l, r)
    });
}
inline void split(int u, int v) {
    myq::clear();

    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);

        push(dfn[top[u]], dfn[u]), u = fa[top[u]];
    }

    if (dfn[u] > dfn[v])
        swap(u, v);

    push(dfn[u], dfn[v]);
}
ll ts[1005];
int tsp = 0;
inline void gen(int n) {
    while (!myq::empty() && tsp < n) {
        dat t = myq::top();
        myq::pop();
        ts[++tsp] = vl[t.id];
        push(t.l, dfn[t.id] - 1);
        push(dfn[t.id] + 1, t.r);
    }

    if (tsp < n)
        ts[++tsp] = 0;
}
inline ll calc(int m) {
    tsp = 0;
    ll ans = 0;
    int flag = true;

    for (int i = 61; i >= 0; i--) {
        int tot = 0;

        for (int j = 1; j <= tsp; j++)
            if (ts[j] & (1ll << i))
                ++tot;

        while (tot < m && flag) {
            gen(tsp + 1);

            if ((ts[tsp]&ans) < ans) {
                tsp--;
                flag = false;
                break;
            }

            if (ts[tsp] & (1ll << i))
                ++tot;
            else
                break;
        }

        if (tot >= m) {
            ans |= 1ll << i;
            int ttsp = 0;

            for (int j = 1; j <= tsp; j++)
                if ((ts[j]&ans) == ans)
                    ++ttsp, ts[ttsp] = ts[j];

            tsp = ttsp;
        }
    }

    return ans;
}
inline ll query(int u, int v, int x) {
    return split(u, v), calc(x);
}
inline void work() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }

    for (int i = 1; i <= n; i++)
        cin >> vl[i];

    dfs1(1, 0);
    dfs2(1, 1);
    st::init(n);
    ll lans = 0;
    int qr;
    cin >> qr;

    while (qr--) {
        int u, v, x;
        cin >> u >> v >> x;
        u = static_cast<int>((u ^ lans) % n + 1),
        v = static_cast<int>((v ^ lans) % n + 1);
        cout << (lans = query(u, v, x)) << "\n";
    }
}
}
int main() {
    lly::work();
    return 0;
}
