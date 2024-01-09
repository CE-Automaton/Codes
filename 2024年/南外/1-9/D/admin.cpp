#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define nn 200080
#define ll long long
ll f[nn],rf[nn];
ll C(ll x,ll y)
{
	if(x>y) return 0;
	return f[y]*rf[x]%mod*rf[y-x]%mod;
}
ll qpow(ll x,ll y)
{
	x%=mod;y%=(mod-1);
	ll res=1;
	while(y)
	{
		if(y&1) res=res*x%mod;
		x=x*x%mod,y=y/2;
	}
	return res;
}
ll n,m,u,v;ll T;
ll calc(ll x)
{
	return qpow(u*x+v+u,n+m-1);
}
int main()
{
	freopen("oier.in","r",stdin);
	freopen("oier.out","w",stdout);
	
	f[0]=1;for(int i=1;i<nn;i++) f[i]=f[i-1]*i%mod,rf[i]=qpow(f[i],mod-2);
	rf[0]=1;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld",&n,&m,&u,&v);
		assert(u&&v);
		ll ans=0;
		for(int i=0;i<=m-1;i++)
		{
			if((m-1-i)%2==0)
				ans+=C(i,m-1)*calc(i)%mod;
			else 
				ans+=mod-C(i,m-1)*calc(i)%mod;
		}
		ans=ans%mod*rf[m-1]%mod*qpow(qpow(u,m-1),mod-2)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
