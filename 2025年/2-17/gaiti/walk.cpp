#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e4+5, M = 1e5+5;
int T, n, m, u, v, p[N], dfn[N], low[N], ddd, zhan[N], tot, cnt, bl[N], ppp, ans[N], jc[N], inv[N], 
val[N], sss[N], g[N], h[N], f[N][2], bei[N];
vector <int> to[N], tt[N];

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
	for(int i = 0; i < to[x].size(); ++i)
		if(!dfn[to[x][i]]) {
			tarjan(to[x][i]);
			if(low[to[x][i]] >= dfn[x]) {
				++cnt;
				int z = -1;
				do { z=zhan[tot], --tot, tt[z].push_back(n+cnt), tt[n+cnt].push_back(z); } while(z != to[x][i]) ;
				tt[x].push_back(n+cnt), tt[n+cnt].push_back(x);
			}
			low[x]=min(low[x], low[to[x][i]]);
		}
		else
			low[x]=min(low[x], dfn[to[x][i]]);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs(int x, int fa) {
	val[x]=(x <= n ? val[fa] : min((int) tt[x].size()-1, 2));
	sss[x]=(val[fa] == 2);
	for(int y : tt[x])
		if(y != fa)
			dfs(y, x), sss[x]+=val[y];
	if(val[x] == 2) {
		if(x <= n) {
			tot=0;
			bei[0]=1;
			for(int y : tt[x])
				if(y != fa && val[y] == 2) {
					bei[tot+1]=0;
					for(int j = tot; j >= 0; --j)
						bei[j+1]=upd(bei[j+1]+1LL*bei[j]*h[y]%mod);
					++tot;
				}
			int pw = 1;
			for(int i = 0; i <= tot; ++i) {
				pw=1LL*pw*inv[sss[x]-2*i]%mod*upd(1-p[x]+mod)%mod;
				g[x]=upd(g[x]+1LL*pw*bei[i]%mod*jc[i]%mod);
				pw=upd(pw<<1);
			}
		}
		else {
			h[x]=1;
			for(int y : tt[x])
				if(y != fa)
					h[x]=1LL*h[x]*g[y]%mod;
		}
	}
}
void dfs2(int x, int fa) {
	if(x <= n) {
		tot=0;
		bei[0]=1;
		int summ = upd(1-g[x]+mod);
		for(int y : tt[x])
			if(y != fa) {
				bei[tot+1]=0;
				for(int j = tot; j >= 0; --j)
					bei[j+1]=upd(bei[j+1]+1LL*bei[j]*h[y]%mod);
				++tot;
			}
		for(int y : tt[x])
			if(y != fa) {
				if(val[y] == 2) {
					for(int j = 1; j <= tot; ++j)
						bei[j]=upd(bei[j]-1LL*bei[j-1]*h[y]%mod+mod);
					--tot;
				}
				int pw = 1, sum = 0;
				for(int i = 0; i <= tot; ++i) {
					pw=1LL*pw*inv[sss[x]-2*i]%mod*upd(1-p[x]+mod)%mod;
					sum=upd(sum+1LL*pw*jc[i]%mod*bei[i]%mod);
					pw=upd(pw<<1);
				}
				sum=1LL*sum*val[y]%mod;
				summ=upd(summ-1LL*upd(1-h[y]+mod)*sum%mod+mod);
				f[y][0]=1LL*sum*upd(f[x][0]+f[x][1])%mod;
				if(val[y] == 2) {
					for(int j = tot; j >= 0; --j)
						bei[j+1]=upd(bei[j+1]+1LL*bei[j]*h[y]%mod);
					++tot;
				}
			}
		ans[x]=1LL*upd(f[x][0]+f[x][1])*summ%mod;
	}
	else {
		int pw = 1LL*f[x][0]*inv[2]%mod;
		for(int y : tt[x])
			if(y != fa) {
				f[y][0]=pw;
				pw=1LL*pw*g[y]%mod;
			}
		pw=1LL*f[x][0]*inv[2]%mod;
		for(int y = (int) tt[x].size()-1; y >= 0; --y)
			if(tt[x][y] != fa) {
				f[tt[x][y]][1]=pw;
				pw=1LL*pw*g[tt[x][y]]%mod;
			}
	}
	for(int y : tt[x])
		if(y != fa) 
			dfs2(y, x);
}

signed main() {
	File("walk");
	jc[0]=jc[1]=inv[0]=inv[1]=1;
	for(int i = 2; i <= 20000; ++i)
		jc[i]=1LL*i*jc[i-1]%mod, inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
	read(T);
	while(T--) {
		read(n), read(m);
		for(int j = 1; j <= n; ++j)
			to[j].clear(), dfn[j]=low[j]=0;
		for(int i = 1; i <= n; ++i)
			read(p[i]);
		for(int j = 1; j <= m; ++j)
			read(u), read(v), 
			to[u].push_back(v), to[v].push_back(u);
		ddd=tot=cnt=0;
		for(int j = 1; j <= n; ++j)
			if(!dfn[j]) 
				tarjan(j);
		f[1][0]=1;
		dfs(1, 0);
		dfs2(1, 0);
		for(int i = 1; i <= n; ++i)
			write(ans[i], ' ');
		putchar('\n');
		for(int j = 1; j <= n+cnt; ++j)
			tt[j].clear(), 
			val[j]=g[j]=h[j]=sss[j]=f[j][0]=f[j][1]=0;
	}
	return 0;
}