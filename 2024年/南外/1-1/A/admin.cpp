#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<typename T>
inline T range(T l, T r) {
	return uniform_int_distribution<T>(l, r)(rng);
}

const int Maxn = 200005;
int n, m, w[Maxn], fa[Maxn], siz[Maxn], dfn[Maxn], faz[Maxn], cho[Maxn];
long long ans;
vector <int> G[Maxn];
struct Edg
{
	int x, y, w, id;
	bool operator < (const Edg &tmp) const
	{
		return w < tmp.w;
	}
} E[2 * Maxn];
int get_fa(int x)
{
	return x == fa[x] ? x : fa[x] = get_fa(fa[x]);
}
void merge(int x, int y)
{
	int a = get_fa(x), b = get_fa(y);
	fa[a] = b;
}
void kruskal(void)
{
	sort(E + 1, E + 1 + n);
	for (int i = 1; i <= n; i++)
		if (get_fa(E[i].x) != get_fa(E[i].y))
			merge(E[i].x, E[i].y), ans += E[i].w,
			cho[E[i].id] = 1;
}
void init_dfs(int u, int fa)
{
	if (u != 1 && G[u].size() == 1) siz[u] = 1, dfn[u] = ++dfn[0];
	else dfn[u] = 0x3f3f3f3f;
	for (auto to : G[u])
		if (to != fa)
			init_dfs(to, u), siz[u] += siz[to], dfn[u] = min(dfn[u], dfn[to]);
	faz[u] = fa;
}
void dfs(int u, int fa, long long sum)
{
	if (cho[u])
		cho[u] = ((cho[u] - sum - 1) % n + n) % n + 1,
		sum += cho[u];
	for (auto to : G[u])
		if (to != fa)
			dfs(to, u, sum);
}
int main(int argc, char ** argv)
{
	freopen("segtree.in", "r", stdin);
	freopen("segtree.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]), fa[i] = i;
	for (int i = 1; i < n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y), G[y].push_back(x);
	}
	init_dfs(1, 0);
	for (int i = 1; i <= n; i++)
		E[i] = (Edg){dfn[i], dfn[i] + siz[i], w[i], i};
	kruskal();
	for (int i = 2; i <= n; ++i) if ((int)G[i].size() == 1) {
		int x = i;
		while (!cho[x]) x = faz[x];
		cho[x] = i;
	}
	dfs(1, 0, 0);
	printf("%d\n", dfn[0]);
	for (int i = 1; i <= n; ++i) if (cho[i])
		printf("%d %d\n", i, cho[i]);
	return 0;
}
