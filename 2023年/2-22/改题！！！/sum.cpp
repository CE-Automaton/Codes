#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n, a[100005], gs[35][2][35][2], f[35][35], bs[75], ans;
int main() {
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		for(int o = 0; o <= 29; ++o)
			for(int k = 0; k <= 29; ++k) 
				f[o][k]=(f[o][k]+gs[o][(1^((a[i]>>o)&1))][k][(1^((a[i]>>k)&1))])%mod;
		for(int o = 0; o <= 29; ++o)
			for(int k = 0; k <= 29; ++k) 
				gs[o][(a[i]>>o)&1][k][(a[i]>>k)&1]=(gs[o][(a[i]>>o)&1][k][(a[i]>>k)&1]+1)%mod;
	}
	bs[0]=1;
	for(int i = 1; i <= 29+29; ++i)
		bs[i]=(bs[i-1]+bs[i-1])%mod;
	for(int o = 0; o <= 29; ++o)
		for(int k = 0; k <= 29; ++k)
			ans=(ans+1LL*bs[o+k]*f[o][k]%mod)%mod;
	printf("%d\n", ans*2%mod);
	return 0;
}
