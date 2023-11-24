#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, m, a[5005], dp[5005][5005], c[5005][5005], ans;
int main() {
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	scanf("%d%d", &n, &m);
	c[0][0]=1;
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]), c[i][0]=1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= i; ++j)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	dp[0][0]=1;
	for(int i = 0; i <= m; ++i)
		for(int j = 0; j+i <= m; ++j)
			dp[i][j+1]=(dp[i][j+1]+2LL*i*dp[i][j]%mod)%mod, 
			dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
	for(int i = 0; i <= n; ++i)
		for(int j = i+1; j <= n+1; ++j) {
			if(j-2 >= i+1 && a[j-2] > a[j-1]) break;
			int qwq = i+n-j+1;
			if(qwq > m) continue;
			ans=(ans+1LL*dp[qwq][m-qwq]*c[qwq][i]%mod)%mod;
		}
	printf("%d\n", ans);
	return 0;
}
