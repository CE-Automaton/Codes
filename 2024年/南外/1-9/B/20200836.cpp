#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007

int n, m, k, u, v, fa[100471], f[100471][7], ans, tim, id[100471], ff[100471], g[100471], g2[100471][7], dfn[100471];
vector<int> G[100471];
vector<pair<int, int>> V;

int find(int u) {
	return u == fa[u] ? u : find(fa[u]);
}

void dfs2(int u, int fa) {
	id[++tim] = u;
	dfn[u] = tim;
	for (auto v : G[u]) {
		if (v != fa) {
			dfs2(v, u);
			ff[dfn[v]] = dfn[u];
		}
	}
}

void dfs(int x, int y) {
	if (x <= m - n) {
		auto [a, b] = V[x];
		for (int i = 0; i <= y; i++) {
			g[a]++;
			g2[a][i]--;
			g2[b][i]++;
			dfs(x + 1, max(y, i + 1));
			g[a]--;
			g2[a][i]++;
			g2[b][i]--;
		}
		return;
	}
	for (int i = 1; i <= n; i++) {
		fill_n(f[i], x + 1, 1);
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j <= x; j++) {
			if (g[id[i]] + g2[id[i]][j]) {
				f[i][j] = 0;
			}
		}
		int y = mod + accumulate(f[i], f[i] + x, (k - x) * f[i][x]) % mod;
		for (int j = 0; j <= x; j++) {
			f[ff[i]][j] = f[ff[i]][j] * (y - f[i][j]) % mod;
		}
	}
	int z = accumulate(f[1], f[1] + y, (k - y) * f[1][y]) % mod;
	for (int i = 0; i < y; i++) {
		z = z * (k - i) % mod;
	}
	ans = (ans + z) % mod;
}

signed main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &k);
	iota(fa, fa + n + 1, 0);
	for (int i = 0; i < m; i++) {
		scanf("%lld%lld", &u, &v);
		if (find(u) != find(v)) {
			fa[find(u)] = find(v);
			G[u].push_back(v);
			G[v].push_back(u);
		} else {
			V.emplace_back(u, v);
		}
	}
	dfs2(1, 0);
	dfs(0, 0);
	printf("%lld\n", ans);
}
