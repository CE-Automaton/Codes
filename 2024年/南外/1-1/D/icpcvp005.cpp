#include<cstdio>
using namespace std;
#define ll long long
#define mod 998244353
struct sth{int a,b,c;};
struct st1{int a,b,c;};
st1 operator +(st1 a,st1 b){return (st1){(a.a+b.a)%mod,(a.b+b.b)%mod,(a.c+b.c)%mod};}
st1 operator *(st1 a,sth b){return (st1){a.a,(1ll*a.b*b.a+1ll*b.b*a.a)%mod,(1ll*a.c*b.a+1ll*b.c*a.a)%mod};}
sth operator *(sth a,sth b){return (sth){1ll*a.a*b.a%mod,(1ll*a.b*b.a+b.b)%mod,(1ll*a.c*b.a+b.c)%mod};}
sth vl[19][19][167][19],rv[19][19],tr[19][19][11][167][19];
st1 dp[19][19][167][19],su[19][19][11][167][19],rs[19];
int nt[19][19][167][19],pw[19],st[19][19][11][167][19];
int id[167][167],rid[167][19];
void init_dp()
{
	pw[0]=1;for(int i=1;i<=18;i++)pw[i]=10ll*pw[i-1]%mod;
	for(int r=0;r<=162;r++)
	{
		int ci=0;
		for(int j=1;j<=162;j++)if((j+162-r)%9==1)id[r][j]=++ci,rid[r][ci]=j;
	}
	rv[0][1]=(sth){1,0,0};
	for(int s=1;s<=18;s++)
	{
		for(int r=1;r<=9*s;r++)
			for(int x=1;x<=s;x++)
				if(rid[r][x]>1)vl[s][0][r][x]=(sth){1,0,0},nt[s][0][r][x]=id[r-1][rid[r][x]-1];
		else vl[s][0][r][x]=(sth){pw[s],0,1},nt[s][0][r][x]=id[r-1][r];
		for(int d=1;d<s;d++)
			for(int r=1;r<=9*(s-d);r++)
			{
				for(int x=1;x<=s;x++)tr[s][d][0][r][x]=(sth){1,0,0},st[s][d][0][r][x]=x;
				for(int u=0;u<=9;u++)
					for(int x=1;x<=s;x++)
					{
						sth r1=vl[s][d-1][r+u][x];r1.b=(r1.b+1ll*u*pw[d-1]*r1.c)%mod;
						tr[s][d][u+1][r][x]=r1*tr[s][d][u][r][nt[s][d-1][r+u][x]],
						st[s][d][u+1][r][x]=st[s][d][u][r][nt[s][d-1][r+u][x]];
					}
				for(int x=1;x<=s;x++)vl[s][d][r][x]=tr[s][d][10][r][x],nt[s][d][r][x]=st[s][d][10][r][x];
			}
		for(int x=1;x<=s;x++)
		{
			int nw=x;
			sth tp=(sth){1,0,0};
			for(int u=9;u>0;u--)
			{
				sth r1=vl[s][s-1][u][nw];r1.b=(r1.b+1ll*u*pw[s-1]*r1.c)%mod;
				tp=tp*r1;nw=nt[s][s-1][u][nw];
			}
			rv[s][x]=tp*rv[s-1][nw];
		}
	}
	for(int s=1;s<=18;s++)
	{
		for(int r=1;r<=9*s;r++)dp[s][0][r][id[r-1][r]]=(st1){1,0,1};
		for(int d=1;d<s;d++)
			for(int r=1;r<=9*(s-d);r++)
			{
				for(int u=0;u<=9;u++)
				{
					for(int x=1;x<=s;x++)su[s][d][u+1][r][x]=su[s][d][u][r][x];
					for(int x=1;x<=s;x++)
					{
						st1 si=dp[s][d-1][r+u][x];si.b=(si.b+1ll*u*pw[d-1]*si.c)%mod;
						su[s][d][u+1][r][st[s][d][u][r][x]]=su[s][d][u+1][r][st[s][d][u][r][x]]+si*tr[s][d][u][r][x];
					}
				}
				for(int x=1;x<=s;x++)dp[s][d][r][x]=su[s][d][10][r][x];
			}
		rs[s]=rs[s-1];
		for(int u=1;u<=9;u++)
			for(int x=1;x<=s;x++)
			{
				st1 si=dp[s][s-1][u][x];si.b=(si.b+1ll*u*pw[s-1]*si.c)%mod;
				int nw=x;
				for(int y=u-1;y>0;y--)
				{
					sth r1=vl[s][s-1][y][nw];r1.b=(r1.b+1ll*y*pw[s-1]*r1.c)%mod;
					si=si*r1;nw=nt[s][s-1][y][nw];
				}
				rs[s]=rs[s]+si*rv[s-1][nw];
			}
	}
}
st1 s1[19],s2[19];
int query(ll rb)
{
	if(rb<=9)return rb*(rb+1)/2;
	int as=0;
	if(rb==1000000000000000000ll)rb--,as=753831110;
	int le=0;ll tp=1,t1=rb;
	while(tp<=rb)tp*=10,le++;
	for(int i=1;i<=18;i++)s1[i]=s2[i]=(st1){0,0,0};
	int sr=0;while(t1)sr+=t1%10,t1/=10;
	for(int d=1;d<le;d++)
	{
		int ri=rb%10;rb/=10;sr-=ri;
		for(int i=1;i<=18;i++)
		{
			st1 r1=s1[i];r1.b=(r1.b+1ll*ri*pw[d-1]*r1.c)%mod;
			s2[st[le][d][ri][sr][i]]=s2[st[le][d][ri][sr][i]]+r1*tr[le][d][ri][sr][i];
		}
		for(int i=1;i<=18;i++)s2[i]=s2[i]+su[le][d][ri+(d==1)][sr][i];
		for(int i=1;i<=18;i++)s1[i]=s2[i],s2[i]=(st1){0,0,0};
	}
	for(int i=1;i<=18;i++)s1[i].b=(s1[i].b+1ll*rb*pw[le-1]*s1[i].c)%mod;
	for(int u=rb-1;u>=1;u--)
	{
		for(int i=1;i<=18;i++)
		{
			sth r1=vl[le][le-1][u][i];r1.b=(r1.b+1ll*u*pw[le-1]*r1.c)%mod;
			s2[nt[le][le-1][u][i]]=s2[nt[le][le-1][u][i]]+s1[i]*r1;
		}
		for(int i=1;i<=18;i++)
		{
			st1 si=dp[le][le-1][u][i];si.b=(si.b+1ll*u*pw[le-1]*si.c)%mod;
			s2[i]=s2[i]+si;
		}
		for(int i=1;i<=18;i++)s1[i]=s2[i],s2[i]=(st1){0,0,0};
	}
	for(int i=1;i<=18;i++)as=(as+(s1[i]*rv[le-1][i]).b)%mod;
	as=(as+rs[le-1].b)%mod;
	return as;
}
int T;
ll l,r;
int main(){
	freopen("enigma.in","r",stdin);
	freopen("enigma.out","w",stdout);
	init_dp();
	scanf("%d",&T);
	while(T--)scanf("%lld%lld",&l,&r),printf("%lld\n",(query(r)+mod-query(l-1))%mod);
}
