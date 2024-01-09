#include <bits/stdc++.h>
using namespace std;
int n, m, l, r, vis[500005], dis[500005];
struct edge {
	int to, w;
};
vector <edge> a[500005];
void SPFA() {
	queue <int> q;
	q.push(0);
	vis[0]=1;
	for(int i = 1; i <= n; ++i)
		dis[i]=1000000000;
	while(!q.empty()) {
		int it = q.front(); q.pop();
		for(auto j : a[it]) 
			if(dis[it]+j.w < dis[j.to]) {
				dis[j.to]=dis[it]+j.w;
				if(!vis[j.to])
					q.push(j.to);
			}
		vis[it]=0;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		a[i+1].push_back(edge{i, 0}), a[i].push_back(edge{i+1, 1});
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &l, &r);
		if((r-l+1)%2 == 1) {
			puts("-1");
			continue;
		}
		int len = (r-l+1)/2;
		a[r].push_back(edge{l-1, -len});
		a[l-1].push_back(edge{r, len});
	}
	SPFA();
	for(int i = 1; i <= n; ++i)
		printf("%d", dis[i]-dis[i-1]);
	return 0;
}
