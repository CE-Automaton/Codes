#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e7+5;
int n, sum[N], f[N], ans; 

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
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

signed main() {
	freopen("lcm.in", "r", stdin);
	freopen("lcm.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n/i; ++j) 
			sum[j*i]+=(gcd(i, j) == 1);
	for(int i = 2; i <= n; ++i)
		sum[i]=sum[i]/2;
	for(int i = 1; i <= n; ++i)
		ans+=n/i*sum[i];
	write(ans, '\n');
	return 0;
}
