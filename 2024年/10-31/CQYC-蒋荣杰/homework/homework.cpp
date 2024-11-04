#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+5, M = 6e2+5;
int n, T, mod, qq, xx, dp[M][M], ans[2][M];

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
	File("homework");
	read(n), read(T), read(mod);
	++T;
	for(int i = 1; i <= 600; ++i) 
		dp[i][1]=1;
	for(int j = 2; j <= 600; ++j) {
		int sum = 0;
		for(int i = 1; i+T <= 600; ++i)
			sum=upd(sum+dp[i][j-1]), 
			dp[i+T][j]=sum;
	}
	for(int i = 1; i <= 600; ++i)
		for(int j = 2; j <= 600; ++j)
			dp[i][j]=upd(dp[i][j-1]+dp[i][j]);
	int now = 0;
	ans[now][T]=1;
	for(int i = 1; i <= n; ++i) {
		read(qq), read(xx);
		now^=1;
		for(int j = 0; j <= T; ++j)
			ans[now][j]=0;
		for(int j = 0; j <= qq; ++j)
			for(int lst = max(T+j-qq, 0); lst <= T; ++lst) {
				int t = (j+1 >= T ? T : j+1);
				ans[now][t]=upd(ans[now][t]+1LL*ans[now^1][lst]*dp[lst+qq-j-T][qq-xx]%mod);
			}
		for(int j = 0; j <= T; ++j) {
			int t = (j+qq >= T ? T : j+qq);
			ans[now][t]=upd(ans[now][t]+ans[now^1][j]);
		}
		// for(int j = 0; j <= T; ++j)	
		// 	debug(ans[now][j]), debug(' ');
		// debug('\n');
	}
	int sum = 0;
	for(int j = 0; j <= T; ++j)
		sum=upd(sum+ans[now][j]);
	write(sum, '\n');
	return 0;
}
/*
3 1 998244353
4 3
2 2
2 1
15*/