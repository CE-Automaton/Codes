#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef double db;
inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
const ll N = 2e5 + 5;
int n, F[N], a[N], L[N], R[N], cnt, id[N], son[N], val[N];
bool chs[N];
vector<int> v[N], lf;
void dfs(int x, int fa) {
    L[x] = n + 1, R[x] = 0;
    F[x] = fa;
    if (v[x].size() == 1 && fa)
        lf.push_back(x), L[x] = R[x] = ++cnt;
    for (int to : v[x]) {
        if (to == fa)
            continue;
        dfs(to, x);
        L[x] = min(L[x], L[to]), R[x] = max(R[x], R[to]);
    }
}
struct DSU {
    int fa[N];
    void init() {
        for (int i = 1; i <= cnt + 1; i++) fa[i] = i;
    }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy)
            return false;
        fa[fx] = fy;
        return true;
    }
} dsu;
vector<array<int, 2>> ans;
void solve(int x, int fa, ll sum) {
    if (chs[x]) {
        val[x] = (son[x] % n - sum % n + n) % n;
        if (!val[x])
            val[x] = n;
        ans.push_back({ x, val[x] });
        for (int to : v[x])
            if (to != fa)
                solve(to, x, sum + val[x]);
    } else
        for (int to : v[x])
            if (to != fa)
                solve(to, x, sum);
}
int main() {
    freopen("segtree.in", "r", stdin);
    freopen("segtree.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read(), id[i] = i;
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1, 0);
    sort(id + 1, id + n + 1, [&](int &x, int &y) { return a[x] < a[y]; });
    dsu.init();
    for (int i = 1; i <= n; i++)
        if (dsu.merge(L[id[i]], R[id[i]] + 1))
            chs[id[i]] = true;
    for (int nw : lf) {
        int tmp = nw;
        while (!chs[tmp]) tmp = F[tmp];
        son[tmp] = nw;
    }
    solve(1, 0, 0);
    cout << ans.size() << '\n';
    for (array<int, 2> nw : ans) cout << get<0>(nw) << ' ' << get<1>(nw) << '\n';
    return 0;
}