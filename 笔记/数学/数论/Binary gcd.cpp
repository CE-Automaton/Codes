#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, a[5005], b[5005], ans;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T& x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int gcd(int x, int y) {
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

int main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]);
	for(int i = 1; i <= n; ++i, write(ans), putchar('\n')) 
		for(int j = 1, sum = i; j <= n; ++j)
			ans=upd(ans+1LL*gcd(a[i], b[j])*sum%mod), sum=1LL*sum*i%mod;
	return 0;
}
