#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
// bool st;
int n, m, k;
LL r, M, dp[2][505][505];

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
LL upd(LL x) {
	return (x >= M ? x-M : x);
}
// bool fn;
signed main() {
	File("distance");
	// debug("Memory:", (double) (&st-&fn)/1024/1024, "MB\n");
	read(m), read(r), read(n), read(k), read(M);
	int sum = 0, now = 0;
	dp[0][0][0]=1;
	for(int i = 1; i <= n; ++i) {
		now^=1;
		for(int ls = 0; ls <= min(k, i-1); ++ls)
			for(int j = 0; j <= sum; ++j)
				dp[now][ls][j]=dp[now^1][ls][j];
		for(int ls = 0; ls <= min(k-1, i-1); ++ls)
			for(int j = 0; j <= sum; ++j)
				if(dp[now^1][ls][j])
					dp[now][ls+1][(j+i)%m]=upd(dp[now][ls+1][(j+i)%m]+dp[now^1][ls][j]);
		sum=min(sum+i, m-1);
	}
	if(r > sum)
		write(0, '\n');
	else
		write((__int128) dp[now][k][r]*m%M, '\n');
	return 0;
}