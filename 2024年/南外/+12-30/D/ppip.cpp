#include<cstdio>
#include<vector>
using namespace std;
#define N 100500
#define ll long long
int n,m,a,b,head[N],cnt;
struct edge{int t,next;}ed[N*2];
void adde(int f,int t)
{
	ed[++cnt]=(edge){t,head[f]};head[f]=cnt;
	ed[++cnt]=(edge){f,head[t]};head[t]=cnt;
}
int f[N];
void dfs0(int u,int fa)
{
	f[u]=fa;
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=fa)dfs0(ed[i].t,u);
}
int is[N],rt=0;
void dfs1(int u,int fa)
{
	f[u]=fa;
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=fa)dfs1(ed[i].t,u),is[u]|=is[ed[i].t];
}
vector<int> rs[N];
ll as;
vector<int> su[N*4];//f g d q
int id[N][4],le[N],fg[N],sn[N];
void merge(int a,int s,int b,int t)
{
	int sa=su[id[a][s]].size(),sb=su[id[b][t]].size();
	if(sa<sb)sa^=sb^=sa^=sb,id[a][s]^=id[b][t]^=id[a][s]^=id[b][t];
	for(int i=0;i<sb;i++)su[id[a][s]][i+sa-sb]+=su[id[b][t]][i];
}
ll calc(vector<int> &sf,vector<int> &sg)
{
	ll as=0,a=sf.size(),b=sg.size();
	if(!a||!b)return 0;
	if(b<=a)for(int i=0;i<b;i++)as+=1ll*sf[i+a-b]*(sg[i]-(i?sg[i-1]:0));
	else
	{
		as=1ll*sf[a-1]*sg[b-1];
		for(int i=0;i<a;i++)as-=1ll*sg[i+b-a-1]*(sf[i]-(i?sf[i-1]:0));
	}
	return as;
}
void append(int x,int y)
{
	if(su[id[x][y]].size())su[id[x][y]].push_back(su[id[x][y]].back());
	else su[id[x][y]].push_back(0);
}
void dfs2(int u)
{
	for(int i=0;i<4;i++)id[u][i]=u*4-i;
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=f[u])
	{
		dfs2(ed[i].t);
		if(le[ed[i].t]>le[sn[u]])sn[u]=ed[i].t;
	}
	le[u]=le[sn[u]]+1;
	su[id[u][2]].push_back(1);
	if(is[u])
	{
		for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=f[u]&&!is[ed[i].t])
		{
			int t=ed[i].t;
			for(int j=0;j<rs[t].size();j++)
			{
				int v=rs[t][j];
				if(is[v])fg[t]=fg[t]?-1:v;
			}
			if(fg[t]>0&&fg[t]!=f[u])
			{
				int sa=su[id[t][0]].size(),sb=su[id[fg[t]][2]].size();
				for(int j=0;j<sa&&j<sb;j++)
				as+=1ll*(su[id[t][0]][sa-j-1]-(sa-j-1?su[id[t][0]][sa-j-2]:0))*(su[id[fg[t]][2]][sb-j-1]-(sb-j-1?su[id[fg[t]][2]][sb-j-2]:0));
			}
			su[id[t][3]].resize(le[t]+1);
			if(!fg[t])append(t,0);
			merge(t,3,t,1);merge(t,3,t,0);
		}
		else if(ed[i].t!=f[u])
		{
			int t=ed[i].t;
			if(su[id[t][3]].size())su[id[t][3]].pop_back();
		}
		for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=f[u])
		{
			int t=ed[i].t;append(t,2);
			as+=calc(su[id[t][3]],su[id[u][2]]);
			as+=calc(su[id[u][3]],su[id[t][2]]);
			merge(u,2,t,2);merge(u,3,t,3);
		}
		for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=f[u]&&!is[ed[i].t]&&fg[ed[i].t]==f[u]&&f[u])
		{
			int t=ed[i].t;
			for(int j=0;j<su[id[t][0]].size();j++)
			su[id[u][3]][j+su[id[u][3]].size()-su[id[t][0]].size()-1]+=su[id[t][0]][j]-(j?su[id[t][0]][j-1]:0);
		}
	}
	else
	{
		su[id[u][0]].push_back(1);
		for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=f[u])
		{
			int fg=0,t=ed[i].t;
			append(t,2);
			for(int j=0;j<rs[t].size();j++)if(rs[t][j]==f[u])fg=1;
			if(fg)
			{
				as+=calc(su[id[t][1]],su[id[u][2]]);
				as+=calc(su[id[t][0]],su[id[u][2]]);
				as+=calc(su[id[u][1]],su[id[t][2]]);
				as+=calc(su[id[u][0]],su[id[t][2]]);
				merge(u,0,t,1);
				merge(u,1,t,0);
				merge(u,2,t,2);
			}
			else
			{
				append(t,0);
				as+=calc(su[id[t][1]],su[id[u][2]]);
				as+=calc(su[id[t][0]],su[id[u][2]]);
				as+=calc(su[id[u][1]],su[id[t][2]]);
				as+=calc(su[id[u][0]],su[id[t][2]]);
				merge(u,0,t,1);
				merge(u,0,t,0);
				merge(u,2,t,2);
			}
		}
		append(u,1);
	}
}
int main()
{
    freopen("sayaka.in","r",stdin);
    freopen("sayaka.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)scanf("%d%d",&a,&b),adde(a,b);
	dfs0(1,0);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(f[a]==b||f[b]==a)continue;
		if(f[f[a]]==b||f[f[b]]==a||f[a]==f[b])rs[a].push_back(b),rs[b].push_back(a);
		else is[a]=is[b]=1,rt=a;
	}
	dfs1(rt,0);
	dfs2(rt);
	if(!rt)as=1ll*n*(n-1);
	printf("%lld\n",1ll*n*(n-1)-as);
}
