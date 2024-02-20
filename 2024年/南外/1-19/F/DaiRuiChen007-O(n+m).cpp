#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3005;
ll f[MAXN],g[MAXN];
signed main() {
	freopen("chicken.in","r",stdin);
	freopen("chicken.out","w",stdout);
	int n,m,MOD;
	scanf("%d%d%d",&n,&m,&MOD);
	f[0]=f[1]=1;
	for(int i=2;i<=n+1;++i) f[i]=(f[i-1]+f[i-2]*m)%MOD;
	for(int i=0;i<=2;++i) for(int j=0;j<=n-i;++j) {
		g[i+j]=(g[i+j]+f[i]*f[j])%MOD;
	}
	for(int i=3;i<=n;++i) g[i]=(g[i-1]+m*g[i-2]+f[i])%MOD;
	ll ans=m*(m-1)/2*g[n-1]%MOD,c0=0,c1=0;
	for(int len=1;len<=n;len+=2) {
		if(len+2<=n) c0=(c0+2*f[n-len-2])%MOD;
		if(len+4<=n) c1=(c1+g[n-len-4])%MOD;
	}
	for(int x=1;x<m;++x) {
		ans=(ans+MOD-((m-x)*(m-x)*c1+(m-x)*c0+n%2)%MOD*(m-x)%MOD)%MOD;
	}
	for(int len=2;len<=n;++len) {
		ll cnt=0;
		if(len==n) cnt=1;
		else {
			if(len+2<=n) cnt=(cnt+2*m*f[n-len-2])%MOD;
			if(len+4<=n) cnt=(cnt+m*m*g[n-len-4])%MOD;
		}
		ans=(ans+m*(len/2)*cnt)%MOD;
	}
	ans=(ans+f[n+1])%MOD;
	printf("%lld\n",ans);
	return 0;
}
