#include <bits/stdc++.h>
#define vct vector <int>
#define mod 1000000007
using namespace std;
int s, n, k, inv[1005], cnt, to[1000005], tot[1000005], f[1000005], g[1000005], ww[1000005], ans;
vct now, fa;
map <vct, int> qwq;
int ksm(int x, int nnn, int ret = 1) {
	while(nnn) { if(nnn&1) ret=1LL*ret*x%mod; x=1LL*x*x%mod; nnn=(nnn>>1); }
	return ret;
}
vct cl(vct ha) {
	vct ret(k-1);
	for(int i = 0; i < k-1; ++i) 
		ret[i]=ha[i+1]-1;
	int lst = -1; 
	for(int i = 0; i < k-1; ++i) 
		if(ha[i+1] == 0) {
			if(lst == -1)
				ret[i]=i, lst = i;
			else
				ret[i]=lst;
		}
	return ret;
}
int find(int x) { return (fa[x] == x ? x : fa[x]=find(fa[x])); }
int dfs(vct ha) {
	if(qwq.find(ha) != qwq.end()) return qwq[ha];
	int i = (++cnt); vct nxt = ha;
//	cout<<i<<":"; for(int j : ha) cout<<j<<" ";cout<<"\n";
	qwq[ha]=i;
	nxt.push_back(k-1);
	for(int j = 0; j < k; ++j)
		fa[j]=nxt[j];
	for(int j = 1; j*2 <= k; ++j) {
		int u = find(j-1), v = find(k-j);
		if(u == v) continue;
		if(u > v) swap(u, v);
		fa[v]=u;
		++ww[i];
	}
//	cout<<i<<":"; for(int j : fa) cout<<j<<" "; cout<<"\n";
	to[i]=dfs(cl(fa));
	tot[i]=dfs(cl(nxt));
	ww[i]=mod-inv[ww[i]];
	return i;
}
int main() {
	scanf("%d%d%d", &s, &n, &k);
//	if(n < k) {
//		ans=1;
//		for(int i = 1; i <= n; ++i)
//			ans=1LL*ans*s%mod;
//		printf("%d\n", ans);
//		return 0;
//	}
	inv[0]=1;
	for(int i = 1, o = ksm(s, mod-2); i <= n; ++i)
		inv[i]=1LL*inv[i-1]*o%mod;
	for(int i = 0; i < k-1; ++i)
		now.push_back(i), fa.push_back(i);
	fa.push_back(k-1);
	f[dfs(now)]=1;
//	cout<<"???\n";
//	for(int j = 1; j <= cnt; ++j)
//		cout<<to[j]<<" ";cout<<"\n";
//	for(int j = 1; j <= cnt; ++j)
//		cout<<tot[j]<<" ";cout<<"\n";
//	for(int j = 1; j <= cnt; ++j)
//		cout<<ww[j]<<" ";cout<<"\n";
	for(int i = n-k; i >= 0; --i) {
		for(int j = 1; j <= cnt; ++j)
			g[j]=f[j], f[j]=0;
		for(int j = 1; j <= cnt; ++j)
			if(g[j])
				f[tot[j]]=(f[tot[j]]+g[j])%mod, f[to[j]]=(f[to[j]]+1LL*g[j]*ww[j]%mod)%mod;
	}
	for(int i = 1; i <= cnt; ++i) 
		ans=(ans+f[i])%mod;
	for(int i = 1; i <= n; ++i)
		ans=1LL*ans*s%mod;
	printf("%d\n", ans);
	return 0;
}
