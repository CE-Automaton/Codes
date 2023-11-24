#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> fa;
    dsu(int n) : fa(n) { iota(fa.begin(), fa.end(), 0); }

    int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return fa[y] = x, true;
    }
};

int main() {
//    freopen("subway.in", "r", stdin);
//    freopen("subway.out", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    int ans = 1;
    vector<int> lst(m, -1), tim, inc(n);
    vector<vector<pair<int, int>>> edge(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0, fir = -1; j < m; j++) {
            if (a[i][j] == '1') {
                if (lst[j] != -1) {
                    inc[lst[j]]--;
                }
                inc[lst[j] = i]++;
                if (fir != -1) {
                    edge[i].emplace_back(fir, j);
                }
                fir = j;
            }
        }
        tim.insert(tim.begin(), i);
        vector<int> _tim;
        dsu d(m);
        int comp = 0;
        for (int _ = 0; _ < tim.size(); _++) {
            int t = tim[_];
            comp += inc[t];
            vector<pair<int, int>> _edge;
            for (auto [u, v] : edge[t]) {
                if (d.merge(u, v)) {
                    _edge.emplace_back(u, v);
                    comp--;
                }
            }
            swap(edge[t], _edge);
            if (inc[t] || !edge[t].empty()) {
                _tim.push_back(t);
            }
            if (comp == 1) {
                ans = max(ans, i - (_ + 1 < tim.size() ? tim[_ + 1] : -1));
            }
        }
        swap(tim, _tim);
    }
    cout << ans << "\n";
    return 0;
}
