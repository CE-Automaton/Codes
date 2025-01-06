#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int y, p, pp, dp[N][N];

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
	File("excrement");
	read(y), read(p);
	pp=upd(1-p+mod);
	for(int i = 1; i <= y; ++i)
		dp[i][0]=i;
	for(int i = 1; i <= y; ++i)
		for(int j = 1; j <= i; ++j) {
			int ii = i, jj = j-1;
			if(ii < jj) swap(ii, jj);
			dp[i][j]=upd(dp[i][j]+1LL*pp*dp[ii][jj]%mod);
			ii = i-1, jj = j;
			if(ii < jj) swap(ii, jj);
			dp[i][j]=upd(dp[i][j]+1LL*p*dp[ii][jj]%mod);
		}
	// for(int i = 1; i <= y; ++i, debug('\n'))
	// 	for(int j = 0; j <= i; ++j, debug(' ')) 
	// 		debug(dp[i][j]);
	for(int i = 1; i <= y; ++i)
		write(dp[y][i], ' ');
	return 0;
}