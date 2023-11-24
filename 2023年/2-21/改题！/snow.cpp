#include <bits/stdc++.h>
using namespace std;
int n, a[500005], u, v;
long long ans, f[500005], g[500005];
vector <int> to[500005];
void solve(int x, int fa) {
	long long sum = 0, mx = 0;
	for(int y : to[x]) {
		if(y == fa) continue;
		solve(y, x);
		mx=max(mx, g[y]), sum+=g[y], f[x]+=f[y];
	}
	long long az = sum-mx+min((long long) a[x], mx);
	f[x]+=min(az, (long long) a[x]*2);
	g[x]=max(0LL, min((long long) a[x]*2-az, (long long) a[x]));
}
int main() {
	freopen("snow.in", "r", stdin);
	freopen("snow.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]), ans+=a[i];
	for(int i = 1; i <= n-1; ++i) 
		scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	solve(1, 1);
	printf("%lld\n", ans-f[1]);
	return 0;
}
