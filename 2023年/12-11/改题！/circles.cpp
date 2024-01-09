#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e3+5;
int n, a[N], dp[2][N], ans;

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
	// freopen("circles.in", "r", stdin);
	// freopen("circles.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	sort(a+1, a+1+n);
	dp[0][0]=1;
	int now = 0;
	for(int i = 1; i <= n; ++i) {
		now^=1;
		for(int j = 0; j <= a[i-1]; ++j)
			dp[now][j]=dp[now^1][j];
		for(int o = 1; o <= (a[i]-a[i-1]); ++o)
			for(int j = a[i]; j >= 0; --j)
				dp[now][j+1]=upd(dp[now][j+1]+dp[now][j]);
		ans=upd(ans+upd(dp[now][1]-a[i]+mod));
		for(int j = 1; j <= a[i]; ++j)
			dp[now][j-1]=upd(dp[now][j-1]+1LL*dp[now][j]*(j-1)%mod*j%mod);
	}
	write(1LL*ans*(mod-mod/2)%mod, '\n');
	return 0;
}
