#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 5e3+6;
int m, k, n[N], s[N], az[N<<1], dp[2][N]/*左边放了i个,右边最左边无min的方案数*/, jc[N<<1], inv[N<<1], inc[N<<1], ans[2][N], sum;

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
	return (x < y || x < 0 || y < 0 ? 0 : 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}

signed main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= 10000; ++i)
		jc[i]=1LL*jc[i-1]*i%mod, inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
		inc[i]=1LL*inc[i-1]*inv[i]%mod;
	read(m), read(k);
	for(int i = 1; i <= k; ++i)
		read(n[i]);
	sort(n+1, n+1+k);
	for(int i = 1; i <= k; ++i)
		s[i]=s[i-1]+n[i];
	dp[0][0]=1;
	int now = 0, sm = 0;
	for(int i = 1; i <= k; ++i) {//瓶颈/ll,时间复杂度(?),感觉肯定不到n^3又比n^2大,那算作n^2带点大常数吧 
		now^=1;
		for(int j = 0; j <= sm; ++j)
			dp[now][j]=0;
		for(int j = 0; j <= sm; ++j) 
			for(int gs = 1; gs <= n[i]; ++gs)
				dp[now][j+n[i]-gs]=upd(dp[now][j+n[i]-gs]+
				1LL*dp[now^1][j]*c(j+n[i]-gs, j)%mod*c(n[i], n[i]-gs)%mod*jc[n[i]-gs]%mod);
		sm+=n[i]-1;
	}
	int now2 = 0;
	az[0]=inv[s[k]+m];
	ans[0][0]=1LL*(s[k]+m)*inv[s[k]]%mod;
	for(int i = 1; i <= sm+m-1; ++i)
		az[i]=1LL*az[i-1]*inv[s[k]+m-i]%mod, 
		ans[0][i]=ans[0][i-1];
	for(int i = 1; i < m; ++i) {
		now2^=1;
		for(int j = 0; j <= sm+m; ++j)
			ans[now2][j]=0;
		for(int j = 2; sm-j+i >= 1; ++j)
			ans[now2][j]=1LL*ans[now2^1][j-2]*(s[k]+m-j)%mod*inv[s[k]-j+i]%mod;
		for(int j = 0; j <= sm+m; ++j)
			ans[now2][j]=upd(ans[now2][j-1]+ans[now2][j]);
	}
	for(int j = 1; j <= sm; ++j)
		sum=upd(sum+1LL*az[j+m-1]*ans[now2][j+m-2]%mod*dp[now][j]%mod*jc[m]%mod);
	write(sum, '\n');
	return 0;
}
