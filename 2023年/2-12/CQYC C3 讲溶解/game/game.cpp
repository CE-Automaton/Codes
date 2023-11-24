#include <bits/stdc++.h>
#define pi pair<int, int>
#define mod 998244353
using namespace std;
int n, m, s, p, gs, vis[1000006], in[1000006], b[1000006], 
up[1000006], jp[1000006][20], mx[1000006], dep[1000006], cnt, ans;
vector <pi> to3[1000006];
vector <int> to1[1000006], to2[1000006];
struct edge {
	int u, v;
}a[1000006];
queue <int> bs;
int ksm(int x, int nnn, int ret = 1) {
	while(nnn) {
		if(nnn&1) ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		nnn>>=1;
	}
	return ret;
}
void dfs(int x) {
	for(int i = 1; i <= 19; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1];
	for(int i : to2[x])
		dfs(i);
}
void dfs2(int x, int y) {
	vis[x]=1;
	for(auto i : to3[x])
		if(i.second != y)
			dfs2(i.first, y);
}
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &s, &p);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d", &a[i].u, &a[i].v), ++in[a[i].v], 
		to1[a[i].u].push_back(a[i].v);
	bs.push(s); vis[s]=1;
	while(!bs.empty()) {
		int it = bs.front(); bs.pop();
		for(int j : to1[it]) {
			if(vis[j]) continue;
			dep[j]=dep[it]+1;
			jp[j][0]=it;
			vis[j]=1, bs.push(j);
		}
	}
	if(m == n-1) {
		for(int i = 1; i <= n; ++i) vis[i]=0;
		bs.push(s); vis[s]=1;
		while(!bs.empty()) {
			int it = bs.front(); bs.pop();
			for(int j : to1[it]) {
				if(vis[j]) continue;
				mx[j]=max(mx[j], max(mx[it], p-dep[j]));
				vis[j]=1, bs.push(j);
			}
		}
		for(int i = 1; i <= n; ++i)
			ans=(ans+mx[i])%mod;
		printf("%d\n", 1LL*ans*ksm(n, mod-2)%mod);
		return 0;
	}
	if(n <= 1000) {
		for(int i = 1; i <= m; ++i)
			to3[a[i].u].push_back(pi{a[i].v, i});
		for(int i = 1; i <= m; ++i) {
			for(int j = 1; j <= n; ++j) vis[j]=0;
			dfs2(s, i);
			for(int j = 1; j <= n; ++j)
				if(!vis[j])
					mx[j]=max(mx[j], p-dep[a[i].v]);
		}
		for(int i = 1; i <= n; ++i)
			ans=(ans+mx[i])%mod;
		printf("%d\n", 1LL*ans*ksm(n, mod-2)%mod);
		return 0;
	}
	dep[0]=10000000;
	for(int i = 1; i <= n; ++i) vis[i]=0;
	for(int i = 1; i <= m; ++i) {
		if(a[i].u != jp[a[i].v][0])
			b[++cnt]=i;
		else if(vis[a[i].v]) b[++cnt]=i;
		else to2[a[i].u].push_back(a[i].v), vis[a[i].v]=1;
	}
	dfs(s);
	for(int i = 1; i <= cnt; ++i) {
		int u = a[b[i]].u, v = a[b[i]].v;
		if(dep[u] > dep[v]) swap(u, v);
		for(int j = 19; j >= 0; --j)
			if(jp[v][j] != 0 && dep[jp[v][j]] >= dep[u])
				v=jp[v][j];
		for(int j = 19; j >= 0; --j) {
			if(jp[v][j] == 0 || jp[u][j] == 0) continue;
			if(jp[v][j] != jp[u][j])
				v=jp[v][j], u=jp[u][j];
		}
		if(v != u) u=jp[u][0];
//		cout<<b[i].u<<" "<<b[i].v<<" "<<u<<"\n";
		up[a[b[i]].v]=(dep[up[a[b[i]].v]] > dep[u] ? u : up[a[b[i]].v]);
	}
	bs.push(s);
	for(int i = 1; i <= n; ++i) vis[i]=in[i];
	while(!bs.empty()) {
		int it = bs.front(); bs.pop();
		for(int j : to1[it]) {
			--in[j];
			if(vis[j] == 1)
				mx[j]=max(mx[j], max(mx[it], p-dep[j]));
			if(in[j] == 0) {
				if(vis[j] != 1)
					mx[j]=max(mx[j], mx[up[j]]);
				bs.push(j);
			}
		}
	}
	for(int i = 1; i <= n; ++i)
		ans=(ans+mx[i])%mod;
	printf("%d\n", 1LL*ans*ksm(n, mod-2)%mod);
	return 0;
}
