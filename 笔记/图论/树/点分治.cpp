#include <bits/stdc++.h>
#define pi pair<int, int>
#define xx first
#define yy second
using namespace std;
int n, m, u, v, w, rt, siz[10004], mx[10004], vis[10004], dis[10004], sum,
pro[105], zhan[10004], tot, ans[105];
vector <pi> to[10004];
void getrt(int x, int fa) {
	siz[x]=1; mx[x]=0;
	for(auto j:to[x]) {
		if(j.xx == fa || vis[j.xx]) continue;
		getrt(j.xx, x);
		siz[x]+=siz[j.xx];
		mx[x]=max(mx[x], siz[j.xx]);
	}
	mx[x]=max(mx[x], sum-siz[x]);
	if(mx[x] <= mx[rt]) rt=x;
}
void getdis(int x, int fa) {
	zhan[++tot]=x;
	for(auto j:to[x]) {
		if(j.xx == fa || vis[j.xx] || dis[x]+j.yy > 10000000) continue;
		dis[j.xx]=dis[x]+j.yy;
		getdis(j.xx, x);
	}
}
void dfs(int x) {
	vis[x]=1;
	unordered_map <int, int> qwq;
	qwq[0]=1;
	for(auto j:to[x]) {
		if(vis[j.xx]) continue;
		dis[j.xx]=j.yy; getdis(j.xx, x);
		for(int i = 1; i <= tot; ++i)
			for(int k = 1; k <= m; ++k)
				if(!ans[k] && pro[k] >= dis[zhan[i]] && qwq.find(pro[k]-dis[zhan[i]]) != qwq.end())
					ans[k]=1;
		while(tot)
			qwq[dis[zhan[tot--]]]=1;
	}
	for(auto j:to[x]) {
		if(vis[j.xx]) continue;
		sum=siz[j.xx]; rt=0;
		getrt(j.xx, x);
		dfs(rt);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++i)
		scanf("%d%d%d", &u, &v, &w), 
		to[u].push_back(pi{v, w}), 
		to[v].push_back(pi{u, w});
	for(int i = 1; i <= m; ++i)
		scanf("%d", &pro[i]);
	mx[0]=10000000, sum=n;
	getrt(1, 1);
//	printf("%d\n", rt);
	dfs(rt);
	for(int i = 1; i <= m; ++i)
		puts((ans[i] ? "AYE" : "NAY"));
	return 0;
} 
