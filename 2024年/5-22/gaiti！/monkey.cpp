#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, k, mod, f[N][N][2], F[N][N][2], c[N][N];

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
	File("monkey");
	read(n), read(k), read(mod);
	if(k > 10) {
		puts("0");
		return 0;
	}
	c[0][0]=1;
	for(int i = 1; i <= n; ++i) {
		c[i][0]=1;
		for(int j = 1; j <= i; ++j)
			c[i][j]=upd(c[i-1][j]+c[i-1][j-1]);
	}
	f[0][0][1]=f[0][0][0]=1;
	f[1][1][1]=f[1][1][0]=1;
	for(int i = 0; i <= n; ++i)
		F[0][i][0]=F[0][i][1]=1;
	for(int i = 1; i <= n; ++i)
		F[1][i][0]=F[1][i][1]=1;
	for(int i = 2; i < n; ++i) {
		for(int j = 1; j <= 10; ++j)
			for(int x = 0; x < i; ++x) {
				f[i][j][0]=upd(f[i][j][0]+1LL*f[x][j-1][0]*f[i-x-1][j-1][0]%mod*c[i-1][x]%mod), 
				f[i][j][0]=upd(f[i][j][0]+2LL*f[x][j][0]%mod*F[i-x-1][j-1][0]%mod*c[i-1][x]%mod), 
				f[i][j][1]=upd(f[i][j][1]+1LL*F[x][j-1][1]*f[i-x-1][j-1][0]%mod*c[i-1][x]%mod), 
				f[i][j][1]=upd(f[i][j][1]+1LL*f[x][j][1]%mod*F[i-x-1][j-1][0]%mod*c[i-1][x]%mod);
			}
		for(int j = 1; j <= 10; ++j)
			F[i][j][0]=upd(F[i][j-1][0]+f[i][j][0]), 
			F[i][j][1]=upd(F[i][j-1][1]+f[i][j][1]);
	}
	int ans = 0;
	for(int x = 0; x < n; ++x) 
		ans=upd(ans+1LL*upd(1LL*F[x][k][1]*F[n-x-1][k][1]%mod-1LL*F[x][k-1][1]*F[n-x-1][k-1][1]%mod+mod)*c[n-1][x]%mod);
	write(ans, '\n');
	return 0;
}