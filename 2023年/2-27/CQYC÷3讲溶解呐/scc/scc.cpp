#include <bits/stdc++.h>
#define pi pair<int, int>
#define xx first
#define yy second
using namespace std;
int n, m, u[1000005], v[1000005], pd[1000005], cnt, aaa, qwq, low[1505], dfn[1505], zhan[1505], tot, vis[1505];
vector <pi> to[1505];
void Tarjan(int x, int fa) {
	low[x]=dfn[x]=++aaa;
	zhan[++tot]=x;
	for(auto j : to[x]) {
		if((pd[j.xx] == 1 && x != v[j.xx]) || (pd[j.xx] == 0 && x != u[j.xx])) continue;
		int y = j.yy;
		if(!dfn[y]) {
			Tarjan(y, x);
			low[x]=min(low[x], low[y]);
		}
		else
			if(!vis[y])
				low[x]=min(low[x], dfn[y]);
	}
	if(dfn[x] == low[x]) {
		++qwq;
		while(tot) {
			int ooo = zhan[tot--];
			vis[ooo]=1;
			if(ooo == x) break;
		} 
	}
} 
int main() {
	freopen("scc.in", "r", stdin);
	freopen("scc.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d", &u[i], &v[i]), to[u[i]].push_back(pi{i, v[i]}), to[v[i]].push_back(pi{i, u[i]});
	for(int i = 1; i <= n; ++i)
		if(!dfn[i])
			Tarjan(i, i);
	cnt=qwq;
	for(int i = 1; i <= m; ++i) {
		pd[i]=1;
		qwq=aaa=tot=0;
		for(int i = 1; i <= n; ++i)
			dfn[i]=vis[i]=0;
		for(int i = 1; i <= n; ++i)
			if(!dfn[i])
				Tarjan(i, i);
		if(cnt != qwq)
			puts("1");
		else
			puts("0");
		pd[i]=0;
	}
	return 0;
}
