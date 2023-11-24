#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 3e2+5;
int typ, t, n, l, r, dp[2][N][N];

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
	read(typ), read(t);
	while(t--) {
		read(n);
		int now = 0;
		for(int i = 0; i <= n; ++i) 
			for(int j = 0; j <= n; ++j) 
				dp[0][i][j]=0;
		dp[0][0][0]=1;
		for(int i = 1; i <= n; ++i) {
			now^=1;
			for(int j = 0; j <= n; ++j)
				for(int k = 0; k <= n; ++k)
					dp[now][j][k]=0;
			read(l), read(r);
			if(l <= 0)
				for(int j = 0; j <= n; ++j)
					for(int k = 0; k <= n; ++k)
						dp[now][j][k]=upd(upd(dp[now][j][k]+1LL*(k+1)*dp[now^1][j][k+1]%mod)+(j >= 1 ? dp[now^1][j-1][k] : 0));
			if(l <= 1 && 1 <= r)
				for(int j = 0; j <= n; ++j)
					for(int k = 0; k <= n; ++k)
						dp[now][j][k]=upd(upd(dp[now][j][k]+2LL*k*dp[now^1][j][k]%mod)+(j >= 1 && k >= 1 ? upd(dp[now^1][j-1][k-1]+dp[now^1][j-1][k-1]) : 0));
			if(2 <= r)
				for(int j = 0; j <= n; ++j)
					for(int k = 0; k <= n; ++k)
						dp[now][j][k]=upd(upd(upd(dp[now][j][k]+(k >= 1 ? upd(2LL*j*dp[now^1][j][k-1]%mod+1LL*(k-1)*dp[now^1][j][k-1]%mod) : 0))
						+(j >= 1 && k >= 2 ? dp[now^1][j-1][k-2] : 0))+2LL*j*k%mod*dp[now^1][j+1][k]%mod); 
		}
		write(dp[now][1][0], '\n'); 
	}
	return 0;
}
