#include <bits/stdc++.h>
using namespace std;
int n, m, u[1000005], v[1000005], bl[1505], ans[1505][1505], zhan[1505], tot, dfn[1505], low[1505], cnt, qwq;
vector <int> to[1505];
bitset<1505> vis;
bitset<1505> to_[1505];
void Tarjan(int x) {
	dfn[x]=low[x]=++cnt;
	zhan[++tot]=x;
	for(int j : to[x]) {
		if(!dfn[j]) {
			Tarjan(j), low[x]=min(low[x], low[j]);
		}
		else
			if(!bl[j])
				low[x]=min(low[x], dfn[j]);
	}
	if(dfn[x] == low[x]) {
		bl[x]=++qwq;
		while(zhan[tot] != x) bl[zhan[tot]]=qwq, --tot;
		--tot;
	}
}

void bfs(int s, int x) {
	queue<int> q;
	vis[s]=1;
	q.push(s);
	while(!q.empty()) {
		int it = q.front(); q.pop();
		bitset<1505> aaa = ~vis&to_[it];
		for(int i = aaa._Find_first(); i <= n; i=aaa._Find_next(i)) {
			if(i == x)
				continue;
			if(vis[i] == 0) {
				vis[i]=1, q.push(i);
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d", &u[i], &v[i]), to_[u[i]][v[i]]=1, to[u[i]].push_back(v[i]);
	for(int i = 1; i <= n; ++i)
		if(!dfn[i])
			Tarjan(i);
	
	for(int i = 1; i <= n; ++i) {
		if(to[i].size() == 0) continue;
		vis.reset();
		for(int j = 0; j < to[i].size(); ++j) {
			int o = to[i][j];
			if(vis[o]) ans[i][o]=1;
			if(vis[o] == 0)
				bfs(o, i);
		}
		vis.reset();
		for(int j = to[i].size()-1; j >= 0; --j) {
			int o = to[i][j];
			if(vis[o]) ans[i][o]=1;
			if(vis[o] == 0)
				bfs(o, i);
		}
	}
	
	for(int i = 1; i <= m; ++i) 
		if((bl[u[i]] == bl[v[i]] && !ans[u[i]][v[i]]) || (bl[u[i]] != bl[v[i]] && ans[u[i]][v[i]]))
			puts("1");
		else
			puts("0");
	return 0;
}
