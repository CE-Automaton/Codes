#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int M = 31623;
int t, n, f[4][4]={{1,0,0,1}, {0,0,0,1}, {0,1,0,0}, {0,0,1,1}}, s[2][M+5][4][4], dp[4], ha[4], ans;
void cc(int x, int y, int a, int b, int xx, int yy) {
	for(int i = 0; i <= 3; ++i)
		for(int j = 0; j <= 3; ++j)
			s[xx][yy][i][j]=0;
	for(int k = 0; k <= 3; ++k)
		for(int i = 0; i <= 3; ++i)
			for(int j = 0; j <= 3; ++j)
				s[xx][yy][i][j]=(s[xx][yy][i][j]+1LL*s[x][y][i][k]*s[a][b][k][j]%mod)%mod;
}
void cf(int x, int y) {
	if(y == 0) return ;
	int a[4];
	for(int i = 0; i <= 3; ++i)
		a[i]=0;
	for(int k = 0; k <= 3; ++k)
		for(int j = 0; j <= 3; ++j)
			a[j]=(a[j]+1LL*ha[k]*s[x][y][k][j]%mod)%mod;
	for(int i = 0; i <= 3; ++i)
		ha[i]=a[i];
}
int main() {
	dp[0]=1, dp[1]=1, dp[2]=1, dp[3]=2;
	for(int i = 0; i <= 3; ++i)
		for(int j = 0; j <= 3; ++j)
			s[0][1][i][j]=f[i][j];
	for(int i = 2; i <= M; ++i)
		cc(0, 1, 0, i-1, 0, i);
	for(int i = 0; i <= 3; ++i)
		for(int j = 0; j <= 3; ++j)
			s[1][1][i][j]=s[0][M][i][j];
	for(int i = 2; i <= M; ++i)
		cc(1, 1, 1, i-1, 1, i);
	for(int i = 0; i <= 3; ++i)
		ha[i]=dp[i];
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i <= 3; ++i)
			ha[i]=dp[i];
		if(n <= 3) {
			ans^=ha[n];
			continue;
		}
		n-=3;
		cf(0, n%M);
		cf(1, n/M);
		ans^=ha[3];
	}
	printf("%d\n", ans);
	return 0;
} 
