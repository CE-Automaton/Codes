#include<bits/stdc++.h>
using namespace std;
constexpr int S1=1<<20;
char buf1[S1],*l1,*r1;
#define getchar() ((l1==r1&&(r1=(l1=buf1)+fread(buf1,1,S1,stdin)),l1!=r1)?*l1++:EOF)
template<typename T=int>inline T read()
{
	T x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
constexpr int S2=1<<20;
char buf2[S2],*l2=buf2;
#define putchar(c) (l2==buf2+S2&&(fwrite(buf2,1,S2,stdout),l2=buf2),*l2++=(c))
int _st[22];
template<typename T>inline void write(T x)
{
	int tp=0;
	do
		_st[++tp]=x%10;
	while(x/=10);
	while(tp)
		putchar(_st[tp--]+'0');
	putchar('\n');
}
int n,N,cnt,m,c,q,a[200005],w[400005],fa[400005],lc[400005],rc[400005],id[200005],rk[200005],bz[20][400005],dep[400005];
struct edge
{
	int u,v,w;
}e[300005];
int get(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=get(fa[x]);
}
void dfs(int x)
{
	if(x<=n)
	{
		id[x]=++cnt;
		rk[cnt]=x;
		return;
	}
	dep[lc[x]]=dep[rc[x]]=dep[x]+1;
	bz[0][lc[x]]=bz[0][rc[x]]=x;
	dfs(lc[x]),dfs(rc[x]);
}
int LCA(int u,int v)
{
	if(dep[u]<dep[v])
		swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<20;i++)
		if((d>>i)&1)
			u=bz[i][u];
	if(u==v)
		return u;
	for(int i=19;~i;i--)
		if(bz[i][u]!=bz[i][v])
		{
			u=bz[i][u];
			v=bz[i][v];
		}
	return bz[0][u];
}
multiset<int>st;
int main()
{
	freopen("noip.in","r",stdin);
	freopen("noip.out","w",stdout);
	N=n=read(),m=read(),c=read(),q=read();
	for(int i=0;i<m;i++)
		e[i].u=read(),e[i].v=read(),e[i].w=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n*2;i++)
		fa[i]=i;
	sort(e,e+m,[](edge x,edge y){
		return x.w<y.w;
	});
	for(int i=0;i<m;i++)
	{
		int x=get(e[i].u),y=get(e[i].v);
		if(x==y)
			continue;
		fa[x]=fa[y]=++N;
		lc[N]=x,rc[N]=y;
		w[N]=e[i].w;
	}
	dfs(N);
	for(int j=1;j<20;j++)
		for(int i=1;i<=N;i++)
			bz[j][i]=bz[j-1][bz[j-1][i]];
	for(int i=1;i<n;i++)
	{
		int x=rk[i],y=rk[i+1];
		if(a[x]!=a[y])
			st.insert(w[LCA(x,y)]);
	}
	while(q--)
	{
		int x=read(),y=read(),p=id[x];
		if(p>1&&a[x]!=a[rk[p-1]])
			st.erase(st.find(w[LCA(rk[p-1],x)]));
		if(p<n&&a[x]!=a[rk[p+1]])
			st.erase(st.find(w[LCA(rk[p+1],x)]));
		a[x]=y;
		if(p>1&&a[x]!=a[rk[p-1]])
			st.insert(w[LCA(rk[p-1],x)]);
		if(p<n&&a[x]!=a[rk[p+1]])
			st.insert(w[LCA(rk[p+1],x)]);
		write(*st.begin());
	}
	fwrite(buf2,1,l2-buf2,stdout);
	return 0;
}
