#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3005;
ll f[MAXN],f1[MAXN],g[MAXN]; //f1: limited a[1]=0
signed main() {
	freopen("chicken.in","r",stdin);
	freopen("chicken.out","w",stdout);
	int n,m,MOD;
	scanf("%d%d%d",&n,&m,&MOD);
	f1[0]=f1[1]=f[0]=1,f1[2]=f[1]=m+1;
	for(int i=2;i<=n;++i) f1[i+1]=f[i]=(f[i-1]+f[i-2]*m)%MOD;
	for(int i=0;i<=n;++i) for(int j=0;j<=n-i;++j) {
		g[i+j]=(g[i+j]+f1[i]*f1[j])%MOD;
	}
	ll ans=0;
	//ci>0
	for(int i=1;i<=n;++i) ans=(ans+f1[i-1]*f1[n-i]%MOD*m*(m-1)/2)%MOD;
	for(int x=1;x<m;++x) { //delete p0x0x0x0x0q
		ll cnt=0;
		for(int len=1;len<=n;len+=2) {
			if(len==n) cnt=(cnt+1)%MOD;
			if(len+2<=n) cnt=(cnt+2*(m-x)*f1[n-len-2])%MOD; //left or right
			if(len+4<=n) cnt=(cnt+(m-x)*(m-x)*g[n-len-4])%MOD; //mid 
		}
		ans=(ans+MOD-cnt*(m-x)%MOD)%MOD;
	}
	//ci=0
	for(int len=2;len<=n;++len) {
		ll cnt=0;
		if(len==n) cnt=1;
		else {
			if(len+2<=n) cnt=(cnt+2*m*f1[n-len-2])%MOD; //[000000]0q|....
			if(len+4<=n) cnt=(cnt+m*m*g[n-len-4])%MOD; //...|p0[000000]0q|...
		}
		ans=(ans+m*(len/2)*cnt)%MOD;
	}
	ans=(ans+f[n])%MOD; //init B
	printf("%lld\n",ans);
	return 0;
}
