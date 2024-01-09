#include <bits/stdc++.h>
#define mod 4294967296LL
using namespace std;
int n, m, a[1005], b[1005], c[1005], l, r;
long long sum[1005][1005], sm[1005][1005], ans;

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
	freopen("de.in", "r", stdin);
	freopen("de.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]);
	for(int i = 1; i <= n; ++i)
		read(c[i]);
	for(int i = 1; i <= n; ++i)
		for(int j = i, aa = a[i], bb = b[i], cc = c[i]; j <= n; ++j)
			aa&=a[j], bb|=b[j], cc=gcd(cc, c[j]), sum[i][j]=1LL*aa*bb*cc%mod;
	for(int len = 1; len <= n; ++len)
		for(int i = 1; len+i-1 <= n; ++i) {
			int j = i+len-1;
			sm[i][j]=(sm[i+1][j]+sm[i][j-1]-sm[i+1][j-1]+mod+sum[i][j])%mod;
		}
	for(int i = 1; i <= m; ++i) {
		read(l), read(r);
		ans^=sm[l][r];
		ans%=mod;
	}
	write(ans, '\n');
	return 0;
}
