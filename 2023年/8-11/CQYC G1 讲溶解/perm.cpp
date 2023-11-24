#include <bits/stdc++.h>
using namespace std;
const int N = 1e7;
int n, dp[N+5], sum, sum2, jc[N+5], ans, mod;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
	read(n), read(mod);
	jc[1]=1;
	for(int i = 2; i <= n; ++i) {
		jc[i]=1LL*jc[i-1]*i%mod;
		dp[i]=upd(sum+sum2);
		sum=upd(sum+1LL*jc[i-1]*(1LL*(i-1)*i/2%mod)%mod);
		sum2=upd(sum2+1LL*dp[i-1]*i%mod);
//		write(dp[i], ' ');
		ans^=dp[i];
	}
	write(ans, '\n');
	return 0;
}
