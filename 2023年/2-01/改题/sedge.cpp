#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, m, c, a[300005], b[300005], ans, t, p, q;
int gcd(int x, int y) {
	return (x%y == 0 ? y : gcd(x%y, x));
}
map< pair<int,int>, int> qwq; 
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
	read(t);
	while(t--) {
		read(p), read(q);
		if(qwq.find(make_pair(p, q)) != qwq.end()) {
			write(qwq[make_pair(p, q)]), putchar('\n');
			continue;
		} 
		ans = 0;
		if(p > q)
			for(int x = 1; x <= n && x*p < c; ++x) {
				if((c-x*p)%q) continue;
				ans=(ans+1LL*a[x]*b[(c-x*p)/q]%mod)%mod;
			}
		else
			 for(int x = 1; x <= m && x*q < c; ++x) {
				if((c-x*q)%p) continue;
				ans=(ans+1LL*a[(c-x*q)/p]*b[x]%mod)%mod;
			}
		qwq[make_pair(p, q)]=ans;
		write(ans), putchar('\n');
	}
	return 0;
}
