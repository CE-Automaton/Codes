#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int cc, t, n, k, a[N], b;
__int128 dp[N][N], mx[N][N], vis[N];

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

signed main() {
	File("festival");
	read(cc), read(t);
	while(t--) {
		read(n), read(k);
		for(int i = 1; i <= n; ++i)
			vis[i]=0;
		for(int i = 1; i < n; ++i)
			read(a[i]);
		for(int i = 1; i <= k; ++i)
			read(b), vis[i]=vis[i]+b, vis[i+n-k+1]=vis[i+n-k+1]-b;
		for(int i = 1; i <= n; ++i)
			vis[i]+=vis[i-1];
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j <= 5000; ++j)
				dp[i][j]=mx[i][j]=0;
		for(int i = 0; i <= a[1]; ++i)
			dp[1][i]=(__int128) i*vis[1];
		for(int i = 0; i <= 5000; ++i)
			mx[1][i]=max((i == 0 ? (__int128) 0 : mx[1][i-1]), dp[1][i]);
		for(int i = 2; i <= n; ++i) {
			for(int j = 0; j <= a[i-1]; ++j)
				dp[i][j]=(__int128) vis[i]*j+mx[i-1][a[i-1]-j];
			for(int j = 0; j <= 5000; ++j)
				mx[i][j]=max((j == 0 ? (__int128) 0 : mx[i][j-1]), dp[i][j]);
		}
		write(mx[n][5000], '\n');
	}
	return 0;
}
