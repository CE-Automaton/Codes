#include<bits/stdc++.h>
using namespace std; 
#define ll long long
const int N=100010,mod=1e9+7;
struct E{int v,nxt;}e[N<<2];
int n,m,K,cc,tt,cnt,hd[N],vis[N],d[N],q[N],col[N],pp[100];
ll res,val[N],f[N<<2][2];
struct st{int f,t,i;}g[100];
inline void add(int u,int v){e[++cc]=(E){v,hd[u]};hd[u]=cc;}
void calc(int x,int n)
{
	if(x>tt)
	{
		ll ans=1;for(int i=0;i<n;i++)ans=1ll*ans*(K-i)%mod;
		for(int i=1;i<=cnt;i++)ans=1ll*ans*f[g[i].i][col[g[i].f]==col[g[i].t]]%mod;
		res+=ans;return;
	}
	int p=pp[x];
	calc(x+1,col[p]=n+1);
	for(int i=1;i<=n;i++)col[p]=i,calc(x+1,n);
}
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1,u,v;i<=m;i++){scanf("%d%d",&u,&v);add(u,v);add(v,u);d[u]++;d[v]++;f[i*2-1][0]=f[i*2][0]=1;}
	for(int i=1;i<=n;i++)val[i]=1;
	int l=0,r=0,nn=n;
	for(int i=1;i<=n&&nn>1;i++)if(d[i]==1)q[++r]=i,vis[i]=1,nn--;
	while(l<r)
	{
		int x=q[++l];
		for(int i=hd[x],y;i;i=e[i].nxt)if(!vis[y=e[i].v])
		{
			if(--d[y]==1&&nn>1)q[++r]=y,vis[y]=1,nn--;
			val[y]=val[y]*val[x]%mod*(K-1)%mod;
		}
	}
	for(int i=1;i<=n&&nn>2;i++)if(d[i]==2&&!vis[i])
	{
		int pp[2]={0,0},ed[2]={0,0},c=0;
		for(int j=hd[i],y;j;j=e[j].nxt)if(!vis[y=e[j].v])pp[c]=y,ed[c]=j,c++;
		if(pp[0]==pp[1])continue;
		vis[i]=1;nn--;
		add(pp[0],pp[1]);add(pp[1],pp[0]);
		ll t0=(f[ed[0]][0]*f[ed[1]][0]%mod*(K-2)+(f[ed[0]][0]*f[ed[1]][1]+f[ed[1]][0]*f[ed[0]][1]))%mod*val[i]%mod;
		ll t1=(f[ed[0]][0]*f[ed[1]][0]%mod*(K-1)+f[ed[0]][1]*f[ed[1]][1])%mod*val[i]%mod;
		f[cc][0]=f[cc-1][0]=t0;f[cc][1]=f[cc-1][1]=t1;
	}
	for(int i=1;i<=n;i++)if(!vis[i])pp[++tt]=i;
	for(int i=1;i<=tt;i++)
	{
		int p=pp[i];
		for(int j=hd[p],y;j;j=e[j].nxt)if(!vis[y=e[j].v]&&p<y)g[++cnt]=(st){p,y,j};
	}
	calc(1,0);res%=mod;
	for(int i=1;i<=tt;i++)res=1ll*res*val[pp[i]]%mod;
	printf("%lld\n",res);
	return 0;
}
