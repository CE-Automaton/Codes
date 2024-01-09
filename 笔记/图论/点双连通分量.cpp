#include <bits/stdc++.h>
using namespace std;
int n, m, u, v, zhan1[600005], tot1, dfn[600005], low[600005], cnt, haha;
vector <int> to[600005];
vector <int> ans[600005]; 
void Tarjan(int x, int fa) {
	low[x]=dfn[x]=++cnt;
	zhan1[++tot1]=x;
	int son = 0;
	for(auto y : to[x]) {
		if(y == fa) continue;
		if(!dfn[y]) {
			++son;
			Tarjan(y, x);
			low[x]=min(low[x], low[y]);
			if(low[y] >= dfn[x]) {//’“µΩ∏Óµ„ 
				ans[++haha].push_back(x);
				while(1) {
					int w = zhan1[tot1--];
					ans[haha].push_back(w);
					if(w == y) break;
				}
			}
		}
		else
			low[x]=min(low[x], dfn[y]);
	}
	if(son == 0 && fa == x) 
		ans[++haha].push_back(x);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) 
		scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i) 
		if(!dfn[i]) cnt=0, Tarjan(i, i);
	printf("%d\n", haha);
	for(int i = 1; i <= haha; ++i) {
		printf("%d ", ans[i].size());
		for(auto j : ans[i])
			printf("%d ", j);
		printf("\n");
	}
	return 0;
} 
