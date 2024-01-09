#include <bits/stdc++.h>
using namespace std;
int n, m, u, v, vis[100005], zhan[100005], tot, pd[15][15];
vector <int> to[100005];
int dfs(int x, int fr) {
	vis[x]=1;
	zhan[++tot]=x;
	for(auto v : to[x]) {
		if(v == fr) continue;
		if(vis[v]) {
			int gs = 0;
			for(int i = 1; i <= tot; ++i)
				for(int j = i+1; j <= tot; ++j)
					gs+=pd[zhan[i]][zhan[j]];
			if(gs != tot*(tot-1)) {
				puts("WA");
				return 1;
			}
		}
		else
			if(dfs(v, x))
				return 1;
	}
	--tot;
	vis[x]=0;
	return 0;
}
int main() {
	freopen("question.in", "r", stdin);
	freopen("question.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	if(m == 0) {
		puts("AC");
		return 0;
	}
	if(n <= 10) {
		for(int i = 1; i <= n; ++i)
			for(auto v : to[i])
				pd[i][v]=1;
		for(int i = 1; i <= n; ++i) {
			if(dfs(i, 0))
				return 0;
			memset(vis, 0, sizeof vis);
			tot=0;
		}
		puts("AC");
		return 0;
	} 
	if(m <= n+5) {
		if(m == n-1 || 1LL*m == 1LL*n*(n-1)/2) {
			puts("AC");
			return 0;
		}
		if(m >= n) {
			puts("WA");
			return 0;
		}
	}
	puts("WA");
	return 0;
} 
