#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5e6+5;
char str[MAXN<<1];
int n,stk[MAXN],tp,dep[MAXN],fa[MAXN];
int son[MAXN],mx[MAXN],sx[MAXN],g[MAXN];
ll dp[MAXN],f[MAXN];
bool vis[MAXN];
void trans(int u,int v,int p) {
	dp[u]=min(dp[u],dp[v]+(f[v]-f[u])-1ll*(g[v]-g[u])*dep[v]+max(dep[u]-p,0));
}
signed main() {
	freopen("handout.in","r",stdin);
	freopen("handout.out","w",stdout);
	scanf("%d%s",&n,str+1);
	for(int i=1,id=0;i<=2*n;++i) {
		if(str[i]==')') --tp;
		else {
			fa[++id]=stk[tp];
			mx[id]=sx[id]=dep[id]=dep[fa[id]]+1;
			vis[fa[id]]=true;
			stk[++tp]=id;
		}
	}
	for(int i=n;i;--i) {
		if(!vis[i]) f[i]=dep[i],g[i]=1;
		int j=fa[i];
		f[j]+=f[i],g[j]+=g[i];
		if(mx[i]>mx[j]) son[j]=i,sx[j]=mx[j],mx[j]=mx[i];
		else sx[j]=max(sx[j],mx[i]);
	}
	memset(vis,false,sizeof(vis));
	memset(dp,0x3f,sizeof(dp)),dp[1]=0;
	for(int i=1;i<=n;++i) if(!vis[i]) {
		tp=0;
		for(int j=i;j;j=son[j]) {
			vis[j]=true;
			if(i>1) trans(j,fa[i],mx[fa[i]]);
			if(j!=i) trans(j,fa[j],sx[fa[j]]);
			while(tp&&sx[stk[tp]]<dep[j]) --tp;
			if(tp) trans(j,stk[tp],sx[stk[tp]]);
			while(tp&&sx[stk[tp]]<=sx[j]) --tp;
			stk[++tp]=j;
		}
	}
	ll ans=1e18;
	for(int i=1;i<=n;++i) ans=min(ans,dp[i]+f[i]-1ll*g[i]*dep[i]);
	printf("%lld\n",ans);
	return 0;
}
