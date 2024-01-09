#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e6+5;
int n, k, a[N], jc[N<<1], inv[N<<1], inc[N<<1], dp[N], ans;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
int c(int x, int y) {
	return 1LL*jc[x]*inc[y]%mod*inc[x-y]%mod;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	read(n), read(k);
	jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
	for(int i = 2; i <= n+k; ++i)
		jc[i]=1LL*jc[i-1]*i%mod, inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	for(int i = 1; i <= n; ++i) 
		read(a[i]);
	dp[0]=1;
	a[0]=1;
	for(int i = 1; i <= n; ++i) {
		dp[i]|=dp[i-1];
		if(i != 1 && (a[i] == 0 || a[i] < a[i-1])) 
			dp[i]=0;
		if(dp[i]) 
			ans=upd(ans+upd(c(n-i-a[i-1]+k, n-i+1)-c(n-i-a[i]+k, n-i+1)+mod));
		if(i != 1)
			ans=upd(ans+c(n-i+k-1, n-i+1));
	}
	write(upd(ans+dp[n]), '\n');
	return 0;
}
