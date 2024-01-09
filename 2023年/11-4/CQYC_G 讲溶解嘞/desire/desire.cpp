#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 2e6+5;
int n, m, k, u, v, jan[N], w[N], dep[N], siz[N], mxs[N], top[N], up[N], jc[N], inv[N], inc[N], ans;
vector <int> to[N];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
void dfs(int x, int fa) {
	up[x]=fa;
	dep[x]=dep[fa]+1;
	siz[x]=1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y], mxs[x]=(siz[y] > siz[mxs[x]] ? y : mxs[x]);
}
void dfs2(int x, int fa, int tp) {
	top[x]=tp;
	if(mxs[x]) dfs2(mxs[x], x, tp);
	for(int y : to[x])
		if(y != fa && y != mxs[x])
			dfs2(y, x, y);
}
int c(int x, int y) {
	if(x < y) return 0;
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs3(int x, int fa) {
	int sum = 0;
	for(int y : to[x])
		if(y != fa)
			dfs3(y, x), w[x]+=w[y]-jan[y], sum+=c(w[y]-jan[y], k);
	ans=upd(ans+upd(c(w[x], k)-sum+mod));
}

signed main() {
	freopen("desire.in", "r", stdin);
	freopen("desire.out", "w", stdout);
	read(n), read(m), read(k);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= m; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	dfs2(1, 0, 1);
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		++w[u], ++w[v];
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]]) swap(u, v);
			u=up[top[u]];
		}
		if(dep[u] > dep[v]) swap(u, v);
		--w[u];
		++jan[u];
	}
	dfs3(1, 0);
	write(ans, '\n');
	return 0;
}
