#include<iostream>
#include<cstdio>
#include<vector>
#define N 125
#define M 62
using namespace std;
int read()
{
	char c=0;
	int sum=0;
	while (c<'0'||c>'9') c=getchar();
	while ('0'<=c&&c<='9') sum=sum*10+c-'0',c=getchar();
	return sum;
}
int T,n,Base,tong[N+1],length,tong2[N+1],length2;
char c[N+1],cs[N+1];
__int128 res,ans,dst;
long long rst;
vector<long long>p[N+1];
int main()
{
	freopen("grow.in","r",stdin);
	freopen("grow.out","w",stdout);
	bool op;
	string s;
	cin>>s,n=s.length(),length=length2=0,dst=1;
	for (int i=1;i<=n;++i) c[i]=cs[i]=s[i-1];
	for (int i=n;i>=1;i-=2,dst<<=2)
	{
		op=1;
		for (int j=i+1;j<=n;++j)
			if (c[j]=='1')
				op=0;
		if (!op) continue;
		if (i==1) ans=dst;
		Base=(i+1)>>1,length=length2=0;
		for (int j=i+1;j<=n;++j) cs[j]='0';
		for (int j=1;j<=Base;++j)
			if (c[j]=='?')
				tong[++length]=j;
		for (int j=Base+1;j<=i;++j)
			if (c[j]=='?')
				tong2[++length2]=j;
		if (length<=length2)
		{
			for (int j=0;j<(1<<length);++j)
			{
				for (int k=1;k<=length;++k)
				{
					if (j&(1<<(k-1))) cs[tong[k]]='1';
					else cs[tong[k]]='0';
				}
				res=0;
				for (int k=1;k<=i;++k)
				{
					if (k<=Base) res=(res<<1)|(cs[k]-'0');
					else res=(res<<1)|1;
				}
				rst=0,op=1;
				for (int k=M;k>=0;--k)
					if ((__int128)(rst+(1ll<<k))*(rst+(1ll<<k))<=res)
						rst+=(1ll<<k);
				res=(__int128)(rst)*rst,op=1;
				for (int k=1;k<=i;++k)
					if (c[k]!='?'&&c[k]-'0'!=((res>>(i-k))&1))
						op=0;
				if (res>=((__int128)(1)<<i)) op=0;
				if (op) ans=(__int128)(rst)*rst*dst;
			}
		}
		else
		{
			for (int j=0;j<(1<<length2);++j)
			{
				for (int k=1;k<=length2;++k)
				{
					if (j&(1<<(k-1))) cs[tong2[k]]='1';
					else cs[tong2[k]]='0';
				}
				rst=0;
				for (int k=Base+1;k<=i;++k) rst=(rst<<1)|(cs[k]-'0'),p[k].clear();
				if (!(rst&1)) continue;
				p[i].push_back(1);
				for (int k=i-1;k>=Base+1;--k)
					for (int t=0;t<p[k+1].size();++t)
					{
						if ((((__int128)(p[k+1][t])*p[k+1][t])&((1ll<<(i-k+1))-1))==(rst&((1ll<<(i-k+1))-1))) p[k].push_back(p[k+1][t]);
						if ((((__int128)(p[k+1][t]+(1ll<<(i-k)))*(p[k+1][t]+(1ll<<(i-k))))&((1ll<<(i-k+1))-1))==(rst&((1ll<<(i-k+1))-1))) p[k].push_back(p[k+1][t]+(1ll<<(i-k)));
				    }
				for (int k=0;k<p[Base+1].size();++k)
				{
					res=(__int128)(p[Base+1][k])*p[Base+1][k],op=1;
					for (int t=1;t<=i;++t)
						if (c[t]!='?'&&c[t]-'0'!=((res>>(i-t))&1))
							op=0;
					if (res>=((__int128)(1)<<i)) op=0;
					if (op) ans=(__int128)(p[Base+1][k])*p[Base+1][k]*dst;
					res=(__int128)(p[Base+1][k]+(1ll<<(i-Base)))*(p[Base+1][k]+(1ll<<(i-Base))),op=1;
					for (int t=1;t<=i;++t)
						if (c[t]!='?'&&c[t]-'0'!=((res>>(i-t))&1))
							op=0;
					if (res>=((__int128)(1)<<i)) op=0;
					if (op) ans=(__int128)(p[Base+1][k]+(1ll<<(i-Base)))*(p[Base+1][k]+(1ll<<(i-Base)))*dst;
				}
			}
		}
	}
	for (int i=1;i<=n;++i) printf("%c",(char)(((ans>>(n-i))&1)+'0'));
	return 0;
}
