#include <bits/stdc++.h>
using namespace std;
int n, a[1005][1005], ton[1000005];
long long ans;
int main() {
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]);
	for(int lh = 1; lh <= n; ++lh)
		for(int rh = lh; rh <= n; ++rh)
			for(int ll = 1; ll <= n; ++ll)
				for(int rl = ll; rl <= n; ++rl) {
					int gs = 0;
					for(int i = lh; i <= rh; ++i)
						for(int j = ll; j <= rl; ++j)
							gs+=(ton[a[i][j]] == 0 ? 1 : 0), ton[a[i][j]]=1;
					ans+=1LL*gs;
					for(int i = lh; i <= rh; ++i)
						for(int j = ll; j <= rl; ++j)
							ton[a[i][j]]=0;
				}
	printf("%lld\n", ans);
	return 0;
}
