#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int n, k, a[N][N], sum[N][N];

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
	File("b");
	read(n), read(k);
	if(k == 1) {
		write(1, '\n');
		return 0;
	}
	for(int i = 1; i <= k; ++i)
		a[1][i]=1;
	for(int j = 1; j <= n; ++j)
		sum[1][j]=upd(sum[1][j-1]+a[1][j]);
	for(int i = 2; i <= n; ++i) 
		for(int j = i; j <= n; ++j)
			a[i][j]=upd(1LL*a[i-1][j]*(j-i+1)%mod+upd(sum[i-1][j-1]-(j > k ? sum[i-1][j-k-1] : 0)+mod)), 
			sum[i][j]=upd(sum[i][j-1]+a[i][j]);
	write(sum[n][n], '\n');
	return 0;
}