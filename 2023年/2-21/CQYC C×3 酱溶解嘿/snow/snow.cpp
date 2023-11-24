#include <bits/stdc++.h>
using namespace std;
int n, a[100005], u, v, lca[105][105], jm[105][15], dep[105], ans=1000000007;
vector <int> to[100005];
void dfs(int x, int fa) {
	dep[x]=dep[fa]+1;
	jm[x][0]=fa;
	for(int y:to[x]) {
		if(y == fa) continue;
		dfs(y, x);
	}
	for(int i = 1; i <= 10; ++i)
		jm[x][i]=jm[jm[x][i-1]][i-1];
} 
int get_lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	for(int j = 10; j >= 0; --j)
		if(jm[y][j] != 0 && dep[jm[y][j]] >= dep[x])
			y=jm[y][j];
	for(int j = 10; j >= 0; --j)
		if(jm[y][j] != 0 && jm[x][j] != 0 && jm[y][j] != jm[x][j])
			x=jm[x][j], y=jm[y][j];
	if(x != y) x=jm[x][0];
	return x;
}
void ddfs(int x, int sum) {
	if(sum >= ans) return ;
	int b[10], pd = 0;
	for(int i = 1; i <= n; ++i)
		b[i]=a[i], pd|=(a[i] != 0);
//	for(int i = 1; i <= n; ++i)
//		cout<<a[i]<<" ";puts("");
	if(pd == 0) {
		ans=min(ans, sum);
		return ;
	}
	for(int o = 1; o <= n; ++o)
		for(int k = o; k <= n; ++k) {
			for(int i = 1; i <= n; ++i)
				a[i]=b[i];
			int u = o, pdd = 0;
			if(o == k) {
				if(a[o] <= 0)
					pdd=1;
				else
					--a[o];
			}
			else {
				while(u != jm[lca[o][k]][0]) {
					if(a[u] <= 0)
						pdd=1;
					else
						--a[u];
					u=jm[u][0];
				}
				u = k;
				while(u != jm[lca[o][k]][0]) {
					if(a[u] <= 0)
						pdd=1;
					else
						--a[u];
					u=jm[u][0];
				}
				++a[lca[o][k]];
			}
			if(pdd) continue;
			ddfs(x+1, sum+1);
		}
}
int main() {
	freopen("snow.in", "r", stdin);
	freopen("snow.out", "w", stdout);
	scanf("%d", &n);
	if(n > 100)
		return 0;
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n-1; ++i)
		scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
			lca[i][j]=lca[j][i]=get_lca(i, j);
	ddfs(1, 0);
	printf("%d\n", ans);
	return 0;
} 
