#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e6+5;
int n, m, s, q, u, v, t[N], g[N], d[N], dep[N], in[N], ans;
struct edge { int to, i; };
vector <edge> to[N];
queue <int> p;
int ksm(int x, int nnn, int ret = 1) {
	while(nnn) {
		if(nnn&1) ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		nnn>>=1;
	}
	return ret;
}
int main() {
	scanf("%d%d%d%d", &n, &m, &s, &q);
	for(int i = 1; i <= m; ++i) 
		scanf("%d%d", &u, &v), to[u].push_back(edge{v, i}), ++in[v];
	for(int i = 1; i <= n; ++i) dep[i]=100000000, g[i]=-1;
	p.push(s); dep[s]=0; g[s]=0;
	while(!p.empty()) {
		int it = p.front(); p.pop();
		for(auto j:to[it]) {
			int so = j.to, i = j.i;
			dep[so]=min(dep[so], dep[it]+1);
			if(g[it] == 0) t[i]=i;
			else t[i]=g[it];
			if(g[so] == -1) g[so]=t[i];
			else if(g[so] != t[i]) g[so]=0;
			if((--in[so]) == 0) p.push(so);
		}
	}
	for(int i = 1; i <= n; ++i)
		for(auto j:to[i]) 
			d[j.i]=q-dep[j.to];
	for(int i = 1; i <= n; ++i)
		ans=(ans+d[g[i]])%mod;
	printf("%d\n", 1LL*ans*ksm(n, mod-2)%mod);
	return 0;
}
