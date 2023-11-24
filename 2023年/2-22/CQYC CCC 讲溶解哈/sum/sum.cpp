#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n, a[50005], mx, ans, gs[1005];
template<typename T>
inline void read(T& x) {
	x=0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
}
inline int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int main() {
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), mx=max(mx, a[i]);
	if(mx <= 1000) {
		for(int i = 1; i <= n; ++i)
			++gs[a[i]];
		for(int i = 0; i <= mx; ++i)
			for(int j = 0; j <= mx; ++j) {
				int qwq = 1LL*(i^j)*(i^j)%mod;
				ans=upd(ans+1LL*gs[i]*gs[j]%mod*qwq%mod);
			}
	}
	else
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) {
				int qwq = (a[i]^a[j]);
				ans=upd(ans+1LL*qwq*qwq%mod);
			}
	printf("%d\n", ans);
	return 0;
}
