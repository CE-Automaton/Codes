#include<bits/stdc++.h>
using namespace std;
constexpr long long mod=998244353;
constexpr int MN=120;
int n,k,m;
char a[MN];
namespace subtask1
{
int T,ans;
inline void work()
{
	for(int i=m;i;i--)
		T=T<<1|(a[i]=='1');
	for(int ns=0;ns<(1<<(n-m));ns++)
	{
		int S=ns<<m|T,t=0;
		for(int i=0;i<k-1;i++)
			if((S>>i)&1)
				t++;
			else
				t--;
		bool fl=1;
		for(int i=k-1;i<n;i++)
		{
			if((S>>i)&1)
				t++;
			else
				t--;
			fl&=(bool)t;
			if((S>>(i-k+1))&1)
				t--;
			else
				t++;
		}
		ans+=fl;
	}
	printf("%d",ans);
}
}
namespace subtask2
{
long long f[2100000],g[2100000],ans;
inline void work()
{
	int s=0,U=(1<<k-1)-1;
	for(int i=1;i<=m;i++)
		s=s<<1|(a[i]=='1');
	f[s]=1;
	for(int i=m+1;i<=n;i++)
		if(i<k)
		{
			for(int s=1<<i-1;s;s--)
				f[s<<1]+=f[s],f[s<<1|1]+=f[s],f[s]=0;
			f[1]+=f[0];
			for(int s=0;s<1<<i;s++)
				if(f[s]>=mod)
					f[s]-=mod;
		}
		else
		{
			for(int s=0;s<1<<k-1;s++)
			{
				if(__builtin_popcount(s)!=k/2)
					g[s<<1&U]+=f[s];
				if(__builtin_popcount(s)!=k/2-1)
					g[(s<<1|1)&U]+=f[s];
			}
			for(int s=0;s<1<<k-1;s++)
			{
				if(g[s]>=mod)
					f[s]=g[s]-mod;
				else
					f[s]=g[s];
				g[s]=0;
			}
		}
	for(int s=0;s<1<<k-1;s++)
		ans+=f[s];
	printf("%lld",ans%mod);
}
}
namespace subtask3
{
int b,pw[7];
long long f[70][10005],ans;
inline void ck(long long&x,long long y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline long long work()
{
	ans=0;
	b=k/2+1,*pw=1;
	for(int i=1;i<=n/k+1;i++)
		pw[i]=pw[i-1]*b;
	for(int st=0;st<pw[n/k];st++)
	{
		memset(f,0,sizeof f);
		int x=st;
		bool fl=0;
		for(int i=0;i<n/k;i++,x/=b)
			if(x%b==0)
			{
				fl=1;
				break;
			}
		if(fl)
			continue;
		int la=n/k*k,U=pw[n/k+1];
		f[la][st*b+1]=1;
		for(int j=1;j<k;j++)
			for(int i=0;i<=n/k;i++)
			{
				int p=i*k+j;
				if(p>n)
					continue;
				for(int s=0;s<U;s++)
				{
					if(!f[la][s])
						continue;
					if(j==n%k+1&&!i)
					{
						int t=U/b;
						if(p>m||a[p]=='0')
							ck(f[p][s-s/t*t],f[la][s]);
						if(p>m||a[p]=='1')
						{
							if(n/k>1&&s/pw[i]%b<b-1&&s/b%b)
								ck(f[p][s-s/t*t+1-b],f[la][s]);
							if(n/k==1&&s%b<b-1)
								ck(f[p][s-s/t*t+1],f[la][s]);
						}
					}
					else
					{
						if(p>m||a[p]=='0')
							ck(f[p][s],f[la][s]);
						if(p>m||a[p]=='1')
						{
							if(p+k<=n&&s/pw[i]%b<b-1&&s/pw[i+1]%b)
								ck(f[p][s+pw[i]-pw[i+1]],f[la][s]);
							if(p+k>n&&s/pw[i]%b<b-1)
								ck(f[p][s+pw[i]],f[la][s]);
						}
					}
				}
				if(j==n%k+1&&!i)
					U/=b;
				la=p;
			}
		for(int s=0;s<U;s++)
		{
			int x=st,y=s,x1=0,x2=0;
			bool fl=1;
			for(int c=0;c<n/k;c++)
			{
				if(y%b==0)
					fl=0;
				x1+=x%b-1,x2+=y%b-1;
				fl&=(x2==x1||x2+1==x1);
				x/=b,y/=b;
			}
			if(n%k==k-1)
				fl&=(bool)y;
			if(fl)
				ck(ans,f[la][s]);
		}
	}
	return ans;
}
}
namespace subtask5
{
long long f[60][MN][MN*2],g[MN][MN*2],M[10][10],ans;
int t1,U,s[10],sx,sy,ex,ey;
bool fl[MN][MN*2];
int tot=0;
inline long long ksm(long long b,int p=mod-2)
{
	long long res=1;
	for(;p;p>>=1)
	{
		if(p&1)
			res=res*b%mod;
		b=b*b%mod;
	}
	return res;
}
inline long long det(int n)
{
	long long res=1;
	for(int i=0;i<n;i++)
	{
		if(!M[i][i])
		{
			int p;
			for(p=i+1;p<n;p++)
				if(M[p][i])
					break;
			if(p==n)
				return 0;
			res=-res;
			for(int j=i;j<n;j++)
				swap(M[i][j],M[p][j]);
		}
		long long ny=ksm(M[i][i]);
		res=res*M[i][i]%mod;
		for(int j=i;j<n;j++)
			M[i][j]=M[i][j]*ny%mod;
		for(int j=i+1;j<n;j++)
			for(int k=i+1;k<n;k++)
				M[j][k]=((M[j][k]-M[j][i]*M[i][k])%mod+mod)%mod;
	}
	return (res+mod)%mod;
}
void dfs(int p)
{
	if(n%k==0&&p==n/k)
	{
		for(int i=0;i<n/k;i++)
			for(int j=0;j<n/k;j++)
				if(i)
					M[i][j]=f[s[i]-k/2*i+U][k][s[j+1]-k/2*j+U];
				else
					M[i][j]=g[k][s[j+1]-k/2*j+U];
		ans=(ans+det(n/k))%mod;
		return;
	}
	if(n%k&&p>n/k)
	{
		if(s[n/k]+n%k<t1)
			return;
		for(int i=0;i<=n/k;i++)
		{
			for(int j=0;j<=n/k;j++)
				if(i)
					if(j<n/k)
						M[i][j]=f[s[i]-k/2*i+U][k][s[j+1]-k/2*j+U];
					else if(t1)
						M[i][j]=(f[s[i]-k/2*i+U][ex-1][t1]+f[s[i]-k/2*i+U][ex-1][t1-1])%mod;
					else
						M[i][j]=f[s[i]-k/2*i+U][ex-1][t1];
				else if(j<n/k)
					M[i][j]=g[k][s[j+1]-k/2*j+U];
				else if(t1)
					M[i][j]=(g[ex-1][t1]+g[ex-1][t1-1])%mod;
				else
					M[i][j]=g[ex-1][t1];
		}
		long long d=det(n/k+1);
		ans=(ans+d)%mod;
		return;
	}
	for(s[p]=s[p-1];s[p]<s[p-1]+k/2;s[p]++)
		dfs(p+1);
}
inline long long work()
{
	memset(fl,0,sizeof fl);
	ans=0,U=n/k*k/2;
	sx=0,sy=0,ex=n%k;
	for(int y=0;y<=k;y++)
		fl[0][y+U]=1;
	for(int i=1;i<=m;i++)
	{
		sx++;
		if(a[i]=='1')
			sy++;
		for(int y=sy;y<=k;y++)
			fl[sx][y+U]=1;
	}
	for(t1=0;t1<=n;t1++)
	{
		if(fl[ex][t1])
			continue;
		ey=t1-U;
		if(n%k==0)
			s[n/k]=t1;
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		g[sx][sy+U]=1;
		for(int x=sx+1;x<=k;x++)
			for(int y=-U;y<=k;y++)
				if(!fl[x][y+U]&&(x<ex||y>ey))
				{
					if(y+U)
						g[x][y+U]=(g[x-1][y+U]+g[x-1][y+U-1])%mod;
					else
						g[x][y+U]=g[x-1][y+U];
				}
		for(int i=0;i<=U;i++)
		{
			f[i][0][i]=1;
			for(int x=1;x<=k;x++)
				for(int y=-U;y<=k;y++)
					if(!fl[x][y+U]&&(x<ex||y>ey))
					{
						if(y+U)
							f[i][x][y+U]=(f[i][x-1][y+U]+f[i][x-1][y+U-1])%mod;
						else
							f[i][x][y+U]=f[i][x-1][y+U];
					}
		}
		dfs(1);
	}
	return ans;
}
}
int main()
{
	freopen("dance.in","r",stdin);
	freopen("dance.out","w",stdout);
	scanf("%d%d%d%s",&n,&k,&m,a+1);
	if(n<=20)
		subtask1::work();
	else if(k<=22)
		subtask2::work();
	else
	{
		long long t;
		if(n<=66)
			t=subtask3::work();
		else
			t=subtask5::work();
		for(int i=1;i<=m;i++)
			a[i]^=1;
		if(n<=66)
			printf("%lld",(t+subtask3::work())%mod);
		else
			printf("%lld",(t+subtask5::work())%mod);
	}
	return 0;
}
