#include<cstdio>
#include<algorithm>
#define int long long
const int N=1000005;
struct D{int w,x,s;}d[N];int n,he[N],to[N],nx[N];
bool cmp(D x,D y){return x.x>y.x;}
inline void wk(int w,int x,int y)
{to[w]=y,nx[w]=he[x],he[x]=w;}
int dfs(int x,int y)
{
	int z=y;
	for(int i=he[x];i;i=nx[i])
		z+=dfs(to[i],y+1);
	return z;
}
signed main()
{
    freopen("defence.in","r",stdin);
    freopen("defence.out","wb",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%lld",&d[i].x),d[i].w=i,d[i].s=1;
		if(i!=1&&d[i].x==d[i-1].x)
			puts("Wrong Data");
	}//
	std::sort(d+1,d+n+1,cmp);
	for(int i=1,x,l,r,I;i<n;++i)
	{
		for(x=0,l=i+1,r=n;l<=r;)
			I=l+r>>1,d[I].x>=d[i].x+2*d[i].s-n?(x=I,l=I+1):(r=I-1);
		if(!x||d[x].x!=d[i].x+2*d[i].s-n)
			return 0&printf("-1");
		d[x].s+=d[i].s,wk(i,d[x].w,d[i].w);
	}
	if(dfs(d[n].w,0)!=d[n].x)return 0&printf("-1");
	for(int i=1;i<=n;++i)
		for(int j=he[i];j;j=nx[j])
			printf("%lld %lld\n",i,to[j]);
	return 0;
}
