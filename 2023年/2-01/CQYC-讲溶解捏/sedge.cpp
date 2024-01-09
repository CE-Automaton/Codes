#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, m, c, a[300005], b[300005], ans, t, p, q;
int gcd(int x, int y) {
	return (x%y == 0 ? y : gcd(x%y, x));
}
template <typename T> void read(T& x) {
	x = 0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
} 
char put[64];
int len;
template <typename T> void write(T x) {
	len = 0; do {put[++len]=x%10, x/=10;} while(x);
	while(len) putchar(put[len--]^48);
} 
int main() {
	freopen("sedge.in", "r", stdin);
	freopen("sedge.out", "w", stdout);
	read(n), read(m), read(c);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= m; ++i)
		read(b[i]);
//	for(int k = 1; k <= n; ++k)
//		for(int x = max((m-c)/k, 1); x <= n; ++x)
//			ans[k]=(ans[k]+1LL*a[x]*b[c-k*x]%mod)%mod;
	read(t);
	while(t--) {
		read(p), read(q);
		ans = 0;
		int az = gcd(p, q), bp = q/az, bq = p/az, 
		st1 = c/(p+q), st2 = c/(p+q);
		if((c-c/(p+q)*(p+q))%p == 0) st1 += (c-c/(p+q)*(p+q))/p;
		else if((c-c/(p+q)*(p+q))%q == 0) st2 += (c-c/(p+q)*(p+q))/q;
		else {
			puts("0");
			continue;
		}
		for(int x = st1, y = st2; x >= 1 && y <= m; x-=bp, y+=bq) 
			ans=(ans+1LL*a[x]*b[y]%mod)%mod;
		for(int x = st1+bp, y = st2-bq; x <= n && y >= 1; x+=bp, y-=bq) 
			ans=(ans+1LL*a[x]*b[y]%mod)%mod;
		write(ans), putchar('\n');
	}
	return 0;
}
