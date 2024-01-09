#include <bits/stdc++.h>
#define mod 998244353
#define inv 499122177
using namespace std;
const int N = 2e5+5, M = 21;
int n, a[N], o[M], O[(1<<M)+5], f[(1<<M)+5], p[(1<<M)+5], F[(1<<M)+5], po, inc[N], ans, all;
int main() {
	scanf("%d", &n);
	po=inc[0]=1;
	for(int i = 1; i <= n; ++i)
		inc[i]=1LL*inc[i-1]*inv%mod;
	for(int i = 1; i <= n; ++i) 
		scanf("%d", &a[i]), ++f[a[i]], po=(po<<1)%mod, all|=a[i];
	for(int i = 1; i <= n; ++i) 
		for(int j = 0; j < M; ++j)
			if((a[i]>>j)&1)
				o[j]|=a[i];
//	cout<<inv*2%mod<<"\n";
	if(f[0] == n) {
		printf("%d\n", (po-2+mod)%mod);
		return 0;
	}
	for(int i = 0; i < M; ++i)
		for(int j = 0; j < (1<<M); ++j)
			if((j>>i)&1)
				O[j]|=o[i], f[j]+=f[(j^(1<<i))];
	for(int j = 0; j < (1<<M); ++j) {
		int o = 1, P = ((~j)&all);
		for(int i = 0; i < M; ++i)
			if((P>>i)&1)
				o=-o;
		p[j]=(inc[n-f[P]]*o+mod)%mod;
		F[j]=p[j];
	}
	for(int i = 0; i < M; ++i)
		for(int j = 0; j < (1<<M); ++j)
			if((j>>i)&1)
				F[j]=(F[j]+F[(j^(1<<i))])%mod;
	for(int i = 0; i < (1<<M); ++i){
		if((all&i) != i)
			continue;
		(ans+=1LL*p[i]*F[((~O[i])&all)]%mod)%=mod;
	}
	ans=(1LL*ans*po%mod+mod)%mod;
	printf("%d\n", ans);
	return 0;
}
