#include <bits/stdc++.h>
#define mod 1000000007 
using namespace std;
int n, q, k, a[1005], fy[1005][1005], p, l, r, w;
long long lasans, dp[1005]; 
int main() {
	freopen("chaos.in", "r", stdin);
	freopen("chaos.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
			fy[i][j]=-1;
	for(int i = 1; i <= q; ++i) {
		scanf("%d", &p);
		if(p == 1) {
			scanf("%d%d%d", &l, &r, &w);
			l^=lasans, r^=lasans;
			for(int i = l; i <= r; ++i)
				for(int j = i; j <= r; ++j)
					fy[i][j]=(fy[i][j] == -1 ? w : min(fy[i][j], w));
		}
		else {
			scanf("%d", &k);
			int pd = 1;
			for(int i = 1; i <= k; ++i) scanf("%d", &a[i]), a[i]^=lasans;
			for(int i = 1; i <= k; ++i)
				if(fy[a[i]][a[i]] == -1) {
					lasans = pd = 0;
					break;
				} 
			if(pd) {
				sort(a+1, a+1+k);
				for(int i = 1; i <= k; ++i) {
					dp[i]=dp[i-1]+fy[a[i]][a[i]];
					for(int j = i-1; j >= 1; --j)
						if(fy[a[j]][a[i]] != -1)
							dp[i]=min(dp[i], dp[j-1]+fy[a[j]][a[i]]);
				}
				lasans=dp[k];
			}
			printf("%lld\n", lasans);
			lasans%=mod;
		}
	}
	return 0;
} 
