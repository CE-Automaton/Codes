#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include<iostream>
#include<queue>
#include<string>
#include<ctime>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<long long,long long> pll;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i,j,k)  for(rereadster int i=(int)(j);i<=(int)(k);i++)
#define rrep(i,j,k) for(rereadster int i=(int)(j);i>=(int)(k);i--)
#define Debug(...) fprintf(stderr, __VA_ARGS__)

ll read() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
const int N=1e5+5;
int n,m,fa[N],dep[N],sz[N],len[N],son[N],top[N],dfn[N],low[N],id[N],tim,st[3][18][N],lg[N],s[N],q[N],mrk[N],dp[N];
vector<int>E[N];
void dfs1(int u,int f) {
	fa[u]=f;
	dep[u]=dep[f]+1;
	sz[u]=1;
	for(int v:E[u])if(v!=f)dfs1(v,u),sz[u]+=sz[v],len[u]=max(len[u],len[v]+1);
}
void dfs2(int u,int f) {
	top[u]=f;
	id[dfn[u]=++tim]=u;
	for(int v:E[u])if(v!=fa[u]&&sz[v]>sz[son[u]])son[u]=v;
	if(son[u])dfs2(son[u],f);
	for(int v:E[u])if(v!=fa[u]&&v!=son[u])dfs2(v,v);
	low[u]=tim;
}
bool cmp(int i,int j) {
	return dfn[i]<dfn[j];
}
int lca(int u,int v) {
	while(top[u]!=top[v])
		if(dep[top[u]]>dep[top[v]])u=fa[top[u]];
		else v=fa[top[v]];
	return dep[u]<dep[v]?u:v;
}
int jump(int u,int v) {
	int res;
	while(top[u]!=top[v])res=top[v],v=fa[top[v]];
	return u==v?res:son[u];
}
int kthfa(int u,int k) {
	while(dep[u]-dep[top[u]]<k)k-=dep[u]-dep[top[u]]+1,u=fa[top[u]];
	return id[dfn[u]-k];
}
void dfs3(int u) {
	dp[u]=mrk[u]?0:1<<30;
	for(int v:E[u])dfs3(v),dp[u]=min(dp[u],dp[v]+dep[v]-dep[u]);
}
void dfs4(int u) {
	for(int v:E[u])dp[v]=min(dp[v],dp[u]+dep[v]-dep[u]),dfs4(v);
}
int rmq(int t,int l,int r) {
	if(l>r)return -1<<30;
	int k=lg[r-l+1];
	int res=max(st[t][k][l],st[t][k][r-(1<<k)+1]);
	return res;
}
int solve(int t,int u,int v) {
	if(dep[u]>=dep[v])return -1<<30;
	int res=-1<<30;

	while(top[u]!=top[v]) {
		res=max(res,rmq(t,dfn[top[v]],dfn[v]-1));
		v=top[v];
		int w=fa[v];
		res=max(res,rmq(0,dfn[w],dfn[v]-1)-dep[w]+(t&1?dep[w]:-dep[w]));
		res=max(res,rmq(0,low[v]+1,low[w])-dep[w]+(t&1?dep[w]:-dep[w]));
		v=w;
	}
	res=max(res,rmq(t,dfn[u],dfn[v]-1));
	return res;
}
int work(int u,int v) {
	int p=dep[u]+dep[v]+dp[v]-dp[u]+1>>1,w=kthfa(v,dep[v]-p),res;
	if(w==u)res=solve(2,jump(u,v),v)+dep[v]+dp[v];
	else if(w==v)res=solve(1,jump(u,v),v)-dep[u]+dp[u];
	else
		res=max(solve(1,jump(u,v),w)-dep[u]+dp[u],solve(2,w,v)+dep[v]+dp[v]);
	return res;
}

void work() {
	n=read();
	m=read();
	for(int i=1; i<n; ++i) {
		int x=read(),y=read();
		E[x].push_back(y);
		E[y].push_back(x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int u=1; u<=n; ++u) {
		int mx=0;
		for(int v:E[u])if(v!=fa[u]&&v!=son[u])mx=max(mx,len[v]+1);
		st[0][0][dfn[u]]=dep[u];
		st[1][0][dfn[u]]=mx+dep[u];
		st[2][0][dfn[u]]=mx-dep[u];
	}
	for(int i=2; i<=n; ++i)lg[i]=lg[i>>1]+1;
	for(int t=0; t<3; ++t)
		for(int i=1; i<=lg[n]; ++i)
			for(int j=1; j+(1<<i)-1<=n; ++j)
				st[t][i][j]=max(st[t][i-1][j],st[t][i-1][j+(1<<i-1)]);
	for(int i=1; i<=n; ++i)E[i].clear();
	while(m--) {
		int k=read();
		for(int i=1; i<=k; ++i)mrk[s[i]=read()]=1;
		sort(s+1,s+k+1,cmp);
		for(int i=1,j=k; i<j; ++i)s[++k]=lca(s[i],s[i+1]);
		s[++k]=1;
		sort(s+1,s+k+1,cmp);
		k=unique(s+1,s+k+1)-s-1;
		for(int i=1,tp=0; i<=k; ++i) {
			while(tp&&low[q[tp]]<dfn[s[i]])--tp;
			if(tp)E[q[tp]].push_back(s[i]);
			q[++tp]=s[i];
		}
		dfs3(s[1]);
		dfs4(s[1]);
		int ans=0;
		for(int i=1; i<=k; ++i) {
			int u=s[i],lst=dfn[u];
			for(int v:E[u]) {
				ans=max(ans,work(u,v));
				int w=jump(u,v);
				ans=max(ans,rmq(0,lst,dfn[w]-1)-dep[u]+dp[u]);
				lst=low[w]+1;
			}
			ans=max(ans,rmq(0,lst,low[u])-dep[u]+dp[u]);
		}
		printf("%d\n",ans);
		for(int i=1; i<=k; ++i)mrk[s[i]]=0,E[s[i]].clear();
	}
}

int main() {
#ifdef LZT
	freopen("in","r",stdin);
#endif

	work();

#ifdef LZT
	Debug("My Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
}
