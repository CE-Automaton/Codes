#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 2e3+4;
int n, m, dp[N][N][2], ans[N][N];
char s[N][N];

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
void dfs(int x, int y) {
	if(x == n+1) {
		puts("Yes");
		for(int i = 1; i <= n; ++i, putchar('\n'))
			for(int j = 1; j <= m; ++j)
				putchar(ans[i][j]+'0');
		exit(0);
	} 
	if(x >= 2 && y >= 2) {
		int pd1 = dp[x][y][0], pd2 = dp[x][y][1];
		if(ans[x-1][y-1] == 0 && ans[x-1][y] == 1 && ans[x][y-1] == 1)
			pd1=0;
		if(ans[x-1][y-1] == 1 && ans[x-1][y] == 0 && ans[x][y-1] == 0)
			pd2=0;
		if(pd1)
			ans[x][y]=0, dfs(x+y/m, y%m+1);
		if(pd2)
			ans[x][y]=1, dfs(x+y/m, y%m+1);
	}
	else {
		if(dp[x][y][0])
			ans[x][y]=0, dfs(x+y/m, y%m+1);
		if(dp[x][y][1])
			ans[x][y]=1, dfs(x+y/m, y%m+1);
	}
	return ;
} 

signed main() {
	freopen("chessboard.in", "r", stdin);
	freopen("chessboard.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]+1);
	for(int j = 1; j <= m; ++j) 
		if(s[1][j] == '?')
			dp[1][j][0]=dp[1][j][1]=1;
		else
			dp[1][j][s[1][j]-'0']=1;
	for(int i = 2; i <= n; ++i) {
		if(s[i][1] == '?')
			dp[i][1][0]=dp[i][1][1]=1;
		else
			dp[i][1][s[i][1]-'0']=1;
		for(int j = 2; j <= m; ++j) {
			dp[i][j][0]|=(dp[i-1][j-1][0]/*左上*/&dp[i-1][j][0]/*上*/&dp[i][j-1][0]/*左*/);
			dp[i][j][0]|=(dp[i-1][j-1][0]/*左上*/&dp[i-1][j][1]/*上*/&dp[i][j-1][0]/*左*/);
			dp[i][j][0]|=(dp[i-1][j-1][0]/*左上*/&dp[i-1][j][0]/*上*/&dp[i][j-1][1]/*左*/);
			dp[i][j][0]|=(dp[i-1][j-1][1]/*左上*/&dp[i-1][j][0]/*上*/&dp[i][j-1][0]/*左*/);
			dp[i][j][0]|=(dp[i-1][j-1][1]/*左上*/&dp[i-1][j][1]/*上*/&dp[i][j-1][0]/*左*/);
			dp[i][j][0]|=(dp[i-1][j-1][1]/*左上*/&dp[i-1][j][0]/*上*/&dp[i][j-1][1]/*左*/);
			dp[i][j][0]|=(dp[i-1][j-1][1]/*左上*/&dp[i-1][j][1]/*上*/&dp[i][j-1][1]/*左*/);
			
			dp[i][j][1]|=(dp[i-1][j-1][1]/*左上*/&dp[i-1][j][1]/*上*/&dp[i][j-1][1]/*左*/);
			dp[i][j][1]|=(dp[i-1][j-1][1]/*左上*/&dp[i-1][j][0]/*上*/&dp[i][j-1][1]/*左*/);
			dp[i][j][1]|=(dp[i-1][j-1][1]/*左上*/&dp[i-1][j][1]/*上*/&dp[i][j-1][0]/*左*/);
			dp[i][j][1]|=(dp[i-1][j-1][0]/*左上*/&dp[i-1][j][1]/*上*/&dp[i][j-1][1]/*左*/);
			dp[i][j][1]|=(dp[i-1][j-1][0]/*左上*/&dp[i-1][j][0]/*上*/&dp[i][j-1][1]/*左*/);
			dp[i][j][1]|=(dp[i-1][j-1][0]/*左上*/&dp[i-1][j][1]/*上*/&dp[i][j-1][0]/*左*/);
			dp[i][j][1]|=(dp[i-1][j-1][0]/*左上*/&dp[i-1][j][0]/*上*/&dp[i][j-1][0]/*左*/);
			
			if(s[i][j] != '?')
				dp[i][j][(s[i][j]-'0')^1]=0;
			if(dp[i][j][0] == 0 && dp[i][j][1] == 0) {
				puts("No");
				return 0;
			}
		}
	}
	dfs(1, 1);
	puts("No");
	return 0;
}
