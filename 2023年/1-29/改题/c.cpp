#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n, m, x, y, ans=1, lx[45][45], zg[65], bs[1605], dp[65][65];
int upd(int x) {
	return (x < 0 ? x+mod : (x >= mod ? x-mod : x));
}
int gs(int a, int b) {
	memset(lx, 0, sizeof lx);
	memset(dp, 0, sizeof dp);
	for(int i = 0; i <= 64; ++i) zg[i]=0;
	for(int i = 1; i <= a; ++i) lx[i][1]|=1, lx[i][b]|=2;
	for(int i = 1; i <= b; ++i) lx[1][i]|=4, lx[a][i]|=8;
	for(int i = 1; i <= a; ++i)
		for(int j = 1; j <= b; ++j) {
			if(!((i <= x && j <= y) || (i >= a-x+1 && j >= b-y+1)))
				lx[i][j]|=16;
			if(!((i <= x && j >= b-y+1) || (i >= a-x+1 && j <= y)))
				lx[i][j]|=32;
			++zg[lx[i][j]];
		}
	dp[64][15]=dp[64][31]=dp[64][47]=1;
	for(int i = 63; i >= 0; --i)
		for(int j = 63; j >= 0; --j) {
			dp[i][j]=upd(dp[i][j]+1LL*upd(bs[zg[i]]-1)*dp[i+1][i|j]%mod);
			dp[i][j]=upd(dp[i][j]+dp[i+1][j]);
		}
	return dp[0][0];
}
int main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &x, &y);
	bs[0]=1;
	for(int i = 1; i <= n*m; ++i)
		bs[i]=upd(bs[i-1]+bs[i-1]);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			ans=upd(ans+1LL*gs(i, j)*(n-i+1)%mod*(m-j+1)%mod);
	printf("%d\n", ans);
	return 0;
}
