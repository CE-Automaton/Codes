#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
int n, mod, K, r, u, v, w[N], bs[N], inv[N], rt, siz[N], mx[N], vis[N], f[N], g[N], dep[N], in[N], out[N], sum,
pro, zhan[N], tot;
long long ans;
vector <int> to[N];
int ksm(int x, int nnn, int ret = 1) {
	while(nnn) {
		if(nnn&1) ret = 1LL*ret*x%mod;
		nnn>>=1;
		x=1LL*x*x%mod;
	}
	return ret;
}
void getrt(int x, int fa) {
	siz[x]=1; mx[x]=0;
	for(auto j:to[x]) {
		if(j == fa || vis[j]) continue;
		getrt(j, x);
		siz[x]+=siz[j];
		mx[x]=max(mx[x], siz[j]);
	}
	mx[x]=max(mx[x], sum-siz[x]);
	if(mx[x] <= mx[rt]) rt=x;
}
void getdis(int x, int fa) {
	dep[x]=dep[fa]+1;
	for(auto j:to[x]) {
		if(j == fa || vis[j]) continue;
		g[j]=(1LL*g[x]*K%mod+w[j])%mod;
		f[j]=(f[x]+1LL*w[j]*bs[dep[x]-1]%mod)%mod;
		getdis(j, x);
	}
}
void getson(int x, int fa) {
	zhan[++tot]=x;
	for(auto j:to[x]) {
		if(j == fa || vis[j]) continue;
		getson(j, x);
	}
}
void dfs(int x) {
	vis[x]=1, g[x]=w[x], f[x]=0, dep[x]=1;
	for(auto j:to[x]) {
		if(vis[j]) continue;
		g[j]=(1LL*g[x]*K%mod+w[j])%mod;
		f[j]=w[j];
		getdis(j, x);
	}
	unordered_map <int, int> qwq;
	qwq[0]=1;
	for(int j = 0; j < to[x].size(); ++j) {
		int so = to[x][j];
		if(vis[so]) continue;
		getson(so, x);
		for(int i = 1; i <= tot; ++i) {
			int now = zhan[i], fd = 1LL*(r-g[now]+mod)%mod*inv[dep[now]]%mod;
			if(qwq.find(fd) == qwq.end()) continue;
			out[now]+=qwq[fd];
		}
		while(tot)
			++qwq[f[zhan[tot]]], --tot;
	}
	qwq.clear();
	for(int j = to[x].size()-1; j >= 0; --j) {
		int so = to[x][j];
		if(vis[so]) continue;
		getson(so, x);
		for(int i = 1; i <= tot; ++i) {
			int now = zhan[i], fd = 1LL*(r-g[now]+mod)%mod*inv[dep[now]]%mod;
			if(qwq.find(fd) == qwq.end()) continue;
			out[now]+=qwq[fd];
		}
		while(tot)
			++qwq[f[zhan[tot]]], --tot;
	}
	out[x]+=qwq[1LL*(r-w[x]+mod)%mod*inv[1]%mod];
	qwq.clear();
	qwq[1LL*(r-w[x]+mod)%mod*inv[1]%mod]=1;
	for(int j = 0; j < to[x].size(); ++j) {
		int so = to[x][j];
		if(vis[so]) continue;
		getson(so, x);
		for(int i = 1; i <= tot; ++i) {
			int now = zhan[i], fd = f[now];
			if(qwq.find(fd) == qwq.end()) continue;
			in[now]+=qwq[fd];
		}
		while(tot) {
			int fd = 1LL*(r-g[zhan[tot]]+mod)%mod*inv[dep[zhan[tot]]]%mod;
			++qwq[fd], --tot;
		}
	}
	qwq.clear();
	for(int j = to[x].size()-1; j >= 0; --j) {
		int so = to[x][j];
		if(vis[so]) continue;
		getson(so, x);
		for(int i = 1; i <= tot; ++i) {
			int now = zhan[i], fd = f[now];
			if(qwq.find(fd) == qwq.end()) continue;
			in[now]+=qwq[fd];
		}
		while(tot) {
			int fd = 1LL*(r-g[zhan[tot]]+mod)%mod*inv[dep[zhan[tot]]]%mod;
			++qwq[fd], --tot;
		}
	}
	in[x]+=qwq[0];
	for(auto j:to[x]) {
		if(vis[j]) continue;
		sum=siz[j]; rt=0;
		getrt(j, x);
		dfs(rt);
	}
}
int main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	scanf("%d%d%d%d", &n, &mod, &K, &r);
	bs[0]=1, inv[0]=1, inv[1]=ksm(K, mod-2);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &w[i]), bs[i]=1LL*bs[i-1]*K%mod;
	for(int i = 2; i <= n; ++i)
		scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u), inv[i]=1LL*inv[i-1]*inv[1]%mod;
	mx[0]=10000000, sum=n;
	getrt(1, 1);
	dfs(rt);
	for(int i = 1; i <= n; ++i)
		in[i]+=(w[i] == r), out[i]+=(w[i] == r);
	for(int i = 1; i <= n; ++i)
		ans+=1LL*out[i]*(n-out[i])+1LL*in[i]*(n-in[i])+1LL*in[i]*(n-out[i]);
	printf("%lld\n", 1LL*n*n*n-ans); 
	return 0;
} 
