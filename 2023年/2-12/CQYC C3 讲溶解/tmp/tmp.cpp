#include <bits/stdc++.h>
using namespace std;
int n, m, q, x, y, pd[5005][5005], dp[5005][5005];
signed main() {
	freopen("tmp.in", "r", stdin);
	freopen("tmp.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= q; ++i) {
		scanf("%d%d", &x, &y);
		pd[x][y]=1;
		for(int j = 1; j <= n; ++j)
			for(int k = 1; k <= m; ++k)
				dp[j][k]=0;
		dp[1][1]=(pd[1][1]^1);
		for(int j = 1; j <= n; ++j)
			for(int k = 1; k <= m; ++k)
				if(pd[j][k] == 0)
					dp[j][k]|=dp[j-1][k], dp[j][k]|=dp[j][k-1];
		printf("%d", dp[n][m]);
		if(!dp[n][m]) pd[x][y]=0;
	}
	return 0;
}
