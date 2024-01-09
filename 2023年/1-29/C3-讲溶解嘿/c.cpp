#include <bits/stdc++.h>
#define mod 1000000007
#define inv 500000004
using namespace std;
int n, m, x, y, ans=1;
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &x, &y);
	ans=upd(ans+1LL*(n-x+1)*(m-y+1)%mod);
	ans=upd(ans+1LL*(n-x+1)*(n-x)%mod*(m-y+1)%mod*(m-y)%mod*inv%mod);
	ans=upd(ans+1LL*(n-x+1)*(m-y+1)%mod*(m-y)%mod*inv%mod);
	ans=upd(ans+1LL*(n-x+1)*(n-x)%mod*(m-y+1)%mod*inv%mod);
	printf("%d\n", ans);
	return 0;
}
