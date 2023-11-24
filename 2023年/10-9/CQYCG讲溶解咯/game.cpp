#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e6+5;
int t, n, m, sum[1005][1005];

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
int f(int x, int y) {
	if(x > y) swap(y, x);
	if(y%x == 0)
		return y/x;
	int lcc = gcd(x, y%x); 
	return ((y/x*x+x+(y%x))/lcc-1);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	for(int i = 1; i <= 1000; ++i)
		for(int j = 1; j <= 1000; ++j)
			sum[i][j]=upd(sum[i][j-1]+upd(sum[i-1][j]+upd(upd(f(i, j)-1+mod)+mod-sum[i-1][j-1])));
	read(t);
	while(t--) {
		read(n), read(m);
		write(sum[n][m], '\n');
	}
	return 0;
}
