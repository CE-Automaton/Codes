#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e4+5, M = 6e4+5;
int T, inv[N], n, m, p[N], u, v, dfn[N], low[N], ddd, cnt, tot, zhan[N], rt, pd[N], inn[N], ds[N], 
dp[N]/*经过但不停下的概率*/, ans[N]/*停在该点的概率*/, fir[N], to[M], nxt[M], ppp[M], edg, bl[N], sum[N];
vector <int> dias[N], tt[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
void tarjan(int x) {
	dfn[x]=low[x]=++ddd, zhan[++tot]=x;
	int son = 0;
	for(int i = fir[x]; i; i=nxt[i])
		if(!dfn[to[i]]) {
			tarjan(to[i]);
			if(low[to[i]] >= dfn[x]) {
				++son;
				++cnt;
				if(x != rt || son > 1)
					pd[x]=-1;
				dias[cnt].clear();
				int z = -1;
				do { z=zhan[tot], --tot, dias[cnt].push_back(z); } while(z != to[i]) ;
				dias[cnt].push_back(x);
			}
			low[x]=min(low[x], low[to[i]]);
		}
		else
			low[x]=min(low[x], dfn[to[i]]);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
void dfs(int x, int w) {
	int too = 0;
	for(int i = fir[x]; i; i=nxt[i])
		if(!ppp[i])
			++too;
	for(int i = fir[x]; i; i=nxt[i])
		if(!ppp[i])
			ppp[i]=ppp[i^1]=1, dfs(to[i], 1LL*w*upd(1-p[x]+mod)%mod*inv[too]%mod), ppp[i]=ppp[i^1]=0;
	if(!too)
		ans[x]=upd(ans[x]+w);
	else
		ans[x]=upd(ans[x]+1LL*w*p[x]%mod);
}
void huan(int x) {
	// debug(x, "???\n");
	zhan[++tot]=x;
	dfn[x]=tot;
	for(int i = fir[x]; i; i=nxt[i])
		if(!ppp[i]) {
			ppp[i]=ppp[i^1]=1;
			if(!dfn[to[i]])
				huan(to[i]);
			else {
				++cnt;
				// debug("???\n");
				dias[cnt].clear();
				while(tot >= dfn[to[i]])
					dias[cnt].push_back(zhan[tot]), --tot;
			}
		}
	if(tot == dfn[x])
		--tot;
}
void sol(int x, int fa, int w) {
	if(!dfn[x] && bl[x]) {
		int nw = bl[x];
		for(int i = 0; i < dias[nw].size(); ++i)
			dfn[dias[nw][i]]=1;

		ans[x]=upd(ans[x]+1LL*w*p[x]%mod);

		int ls = dias[nw][(int) dias[nw].size()-1];
		sum[ls]=1LL*w*upd(1+mod-p[x])%mod*inv[ds[x]-(fa ? 1 : 0)]%mod;

		for(int i = (int) dias[nw].size()-2; i >= 0; --i)
			sum[dias[nw][i]]=1LL*sum[ls]*upd(1+mod-p[ls])%mod*inv[ds[ls]-1]%mod, 
			ls=dias[nw][i];
		
		if(ds[x]-(fa ? 1 : 0)-2 == 0)
			ans[x]=upd(ans[x]+2LL*sum[x]%mod);
		else
			ans[x]=upd(ans[x]+2LL*sum[x]%mod*p[x]%mod);
		
		sum[x]=1LL*upd(2LL*sum[x]%mod*inv[ds[x]-(fa ? 1 : 0)-2]%mod+1LL*w*inv[ds[x]-(fa ? 1 : 0)]%mod)*upd(1+mod-p[x])%mod;

		ls=1LL*w*upd(1+mod-p[x])%mod*inv[ds[x]-(fa ? 1 : 0)]%mod;
		for(int i = 1; i < dias[nw].size(); ++i) {
			ans[dias[nw][i]]=upd(ans[dias[nw][i]]+1LL*upd(sum[dias[nw][i]]+ls)*p[dias[nw][i]]%mod);
			sum[dias[nw][i]]=1LL*upd(sum[dias[nw][i]]+ls)*inv[ds[dias[nw][i]]-1]%mod;
			ls=1LL*ls*upd(1+mod-p[dias[nw][i]])%mod*inv[ds[dias[nw][i]]-1]%mod;
		}
		for(int i = 0; i < dias[nw].size(); ++i)
			sol(dias[nw][i], (i == 0 ? fa : -1), sum[dias[nw][i]]);
		return ;
	}
	if(!bl[x]) {
		int too = 0;
		for(int i = fir[x]; i; i=nxt[i])
			if(to[i] != fa)
				++too;
		for(int i = fir[x]; i; i=nxt[i])
			if(to[i] != fa)
				sol(to[i], x, 1LL*w*upd(1-p[x]+mod)%mod*inv[too]%mod);
		if(!too)
			ans[x]=upd(ans[x]+w);
		else
			ans[x]=upd(ans[x]+1LL*w*p[x]%mod);
	}
	else {
		for(int i = fir[x]; i; i=nxt[i])
			if(to[i] != fa && bl[to[i]] != bl[x])
				sol(to[i], x, w);
	}
}

signed main() {
	File("walk");
	inv[0]=inv[1]=1;
	for(int i = 2; i <= 10000; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
	read(T);
	while(T--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i)
			read(p[i]), fir[i]=dfn[i]=low[i]=pd[i]=ans[i]=dp[i]=ds[i]=bl[i]=0;
		edg=1;
		for(int i = 1; i <= m; ++i)
			read(u), read(v), 
			nxt[++edg]=fir[u], to[edg]=v, ppp[edg]=0, fir[u]=edg, ++ds[u], 
			nxt[++edg]=fir[v], to[edg]=u, ppp[edg]=0, fir[v]=edg, ++ds[v];
		if(n <= 11 || m == n-1) {
			dfs(1, 1);
			for(int i = 1; i <= n; ++i)
				write(ans[i], ' ');
			putchar('\n');
			continue;
		}
		ddd=tot=cnt=0;
		huan(1);
		for(int i = 1; i <= cnt; ++i) {
			reverse(dias[i].begin(), dias[i].end());
			for(int j = 0; j < dias[i].size(); ++j)
				bl[dias[i][j]]=i;
		}
		for(int i = 1; i <= n; ++i)
			dfn[i]=0;
		sol(1, 0, 1);
		for(int i = 1; i <= n; ++i)
			write(ans[i], ' ');
		putchar('\n');
	}
	return 0;
}
