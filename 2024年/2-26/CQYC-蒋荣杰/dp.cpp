#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+55;
int n, k, f[N][N], c[N][N], sum[N][N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("dp");
	read(n), read(k);
	for(int i = 0; i <= n+k; ++i) {
		c[i][0]=1;
		for(int j = 1; j <= i; ++j)
			c[i][j]=upd(c[i-1][j-1]+c[i-1][j]);
	}
	sum[0][0]=1;
	for(int i = 1; i <= n+1; ++i) {
		for(int j = 0; j <= min(n, n*k); ++j)
			for(int op = 1; op <= k && j+op <= n; ++op) 
				f[i][j+op]=upd(f[i][j+op]+1LL*sum[i-1][j]*c[j+op][op]%mod);
		for(int j = 0; j <= n; ++j)
			sum[i][j]=upd(sum[i-1][j]+f[i][j]);
	}
	// for(int i = 1; i <= n+1; ++i, putchar('\n')) 
	// 	for(int j = 1; j <= n; ++j)
	// 		write(f[i][j], ' ');
	for(int i = 1; i <= n+1; ++i) 
		for(int j = 1; j <= n; ++j)
			f[i][j]=upd(f[i][j]+f[i-1][j]);
	for(int i = 1; i <= n; ++i)
		write(f[i+1][i], '\n');
	return 0;
}