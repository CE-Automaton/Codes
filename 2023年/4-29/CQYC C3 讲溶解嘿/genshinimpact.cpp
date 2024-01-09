#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n, m, s, dp[7][2005][4005];
char t[2000006];

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
	freopen("genshinimpact.in", "r", stdin);
	freopen("genshinimpact.out", "w", stdout);
	read(n), read(m);
	scanf("%s", t+1);
	s=n+m;
	/*0:123  1:132  2:213  3:231  4:312  5:321*/
	dp[0][0][0]=1;
	for(int i = 1; i <= s; ++i)
		for(int j = 0; j <= i-1; ++j) {
			if(t[i] == '0' || t[i] == '?') {
				dp[0][i][j+1]=upd(dp[0][i][j+1]+dp[2][i-1][j]);
				dp[2][i][j+1]=upd(dp[2][i][j+1]+dp[0][i-1][j]);
				
				dp[1][i][j+1]=upd(dp[1][i][j+1]+dp[4][i-1][j]);
				dp[4][i][j+1]=upd(dp[4][i][j+1]+dp[1][i-1][j]);
				
				dp[3][i][j+1]=upd(dp[3][i][j+1]+dp[5][i-1][j]);
				dp[5][i][j+1]=upd(dp[5][i][j+1]+dp[3][i-1][j]);
			}
			if(t[i] == '1' || t[i] == '?') {
				dp[0][i][j]=upd(dp[0][i][j]+dp[1][i-1][j]);
				dp[1][i][j]=upd(dp[1][i][j]+dp[0][i-1][j]);
				
				dp[2][i][j]=upd(dp[2][i][j]+dp[3][i-1][j]);
				dp[3][i][j]=upd(dp[3][i][j]+dp[2][i-1][j]);
				
				dp[4][i][j]=upd(dp[4][i][j]+dp[5][i-1][j]);
				dp[5][i][j]=upd(dp[5][i][j]+dp[4][i-1][j]);
			}
		}
	write(dp[0][s][n], '\n');
	return 0;
}
