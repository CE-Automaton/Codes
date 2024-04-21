#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e2+5;
int n, k, typ, dp[N][N], sum[N][N], c[N][N];

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
	read(n), read(k), read(typ);
	if(typ == 1) {
		dp[n][0]=1;
		for(int i = n-1; i >= 1; --i)
			for(int j = 0; j <= n; ++j)
				dp[i][j]=upd(dp[i][j]+dp[i+1][j]), 
				dp[i][j+1]=upd(dp[i][j+1]+1LL*dp[i+1][j]*(n-i)%mod);
		write(dp[1][k], '\n');
		return 0;
	}
	else {
		// debug("???\n");
		for(int i = 0; i <= n; ++i)
			c[i][0]=1;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= i; ++j)
				c[i][j]=upd(c[i-1][j]+c[i-1][j-1]);
		for(int i = 1; i <= n; ++i)
			sum[0][i]=sum[1][i]=1;
		dp[1][1]=1;
		sum[0][0]=1;
		dp[0][0]=1;
		for(int i = 2; i <= n; ++i) {
			for(int j = 0; j < i; ++j) 
				for(int p = 0; p <= i; ++p)
					sum[i][p+1]=upd(sum[i][p+1]+1LL*c[i-1][j]*sum[j][p+1]%mod*sum[i-j-1][p]%mod);
			for(int p = 1; p <= i; ++p)
				dp[i][p]=upd(sum[i][p]-sum[i][p-1]+mod);
			for(int p = i+1; p <= n; ++p)
				sum[i][p]=sum[i][p-1];
		}
		write((n-k-1 < 0 ? 0 : dp[n-1][n-k-1]), '\n');
		return 0;
	}
	return 0;
}