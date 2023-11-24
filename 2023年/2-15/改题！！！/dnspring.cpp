#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const signed N = 2e5+5;
int n, m, q, inv, p[N], P[N], ans;
int ksm(int x, int y, int ret = 1) {
	while(y) { if(y&1) ret=ret*x%mod; x=x*x%mod; y>>=1; } return ret;
}
signed main() {
	freopen("dnspring.in", "r", stdin);
	freopen("dnspring.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &q);
	inv = ksm(2, mod-2);
	for(int i = 1; i <= n; ++i)
		p[i]=i*(n-i+1)%mod*ksm(n*(n+1)/2%mod, mod-2)%mod, 
		P[i]=(1-p[i]*inv%mod+mod)%mod;
	int sss = ksm(2*m+1, mod-2);
	for(int i = 1; i <= n; ++i) {
		int a = (m*P[i]%mod*2%mod+1)%mod*sss%mod,
			s = (q-(ksm(a, q)-1+mod)%mod*ksm(a-1, mod-2)%mod+mod)%mod;
		ans=(ans+(p[i]*sss%mod)*((m-1)%mod*inv%mod)%mod*s%mod)%mod;
	}
	printf("%lld\n", ans*ksm((2*m+1)*(n*(n+1)/2)%mod, q)%mod);
	return 0;
}
