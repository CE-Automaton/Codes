#include <bits/stdc++.h>
#define TPLT template <typename T>
#define mod 998244353
using namespace std;
//bool st;
int n, a[200005], sum, tot, ans, dp[2][1050][1050], vis[1050][1050];
struct qwq {
	int x, y, pdx, pdy;
}zhan[1500005][2];

TPLT void read(T& x) {
	x=0; char c=getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
int len; char put[105];
TPLT void write(T x) {
	if(x < 0) putchar('-'), x=-x;
	do { put[++len]=x%10, x/=10; }while(x);
	while(len) putchar(put[len--]^48);
}
//bool fn;
int main() {
//	cerr<<(double) ((&st-&fn)*1.0/1024/1024)<<"\n";
	freopen("or.in", "r", stdin);
	freopen("or.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	if(n <= 20) {
		sort(a+1, a+1+n);
		int now = 1;
		zhan[++tot][0]=qwq{0, 0, 0, 0};
		for(int i = 1; i <= n; ++i) {
			now^=1;
			int ttt = tot;
			tot=0;
			for(int o = 1; o <= ttt; ++o) {
				zhan[++tot][now]=qwq{(zhan[o][now^1].x|a[i]), zhan[o][now^1].y, 
				(zhan[o][now^1].pdx|1), zhan[o][now^1].pdy};
				zhan[++tot][now]=qwq{zhan[o][now^1].x, (zhan[o][now^1].y|a[i]), 
				zhan[o][now^1].pdx, (zhan[o][now^1].pdy|1)};
			}
		}
		for(int i = 1; i <= tot; ++i) 
			if(zhan[i][now].x == zhan[i][now].y && zhan[i][now].pdx && zhan[i][now].pdy)
				ans=(ans+1)%mod;
		write(ans);
		return 0;
	}
	int now = 0;
	for(int i = 1; i <= n; ++i)
		sum|=a[i]; 
	dp[0][0][0]=1;
	zhan[0][++tot]=qwq{0, 0};
	for(int k = 1; k <= n; ++k) {
		now^=1;
		memset(dp[now], 0, sizeof dp[now]);
		int ttt = tot;
		for(int o = 1; o <= ttt; ++o)
			vis[zhan[o][now^1].x][zhan[o][now^1].y]=0;
		tot=0;
		for(int o = 1; o <= ttt; ++o) {
			int i = zhan[o][now^1].x, j = zhan[o][now^1].y;
//			cout<<i<<"-"<<j<<" "<<(i|a[k])<<"-"<<j<<" "<<i<<"-"<<(j|a[k])<<"\n";
			(dp[now][i|a[k]][j]+=dp[now^1][i][j])%=mod;
			if(!vis[i|a[k]][j])
				zhan[++tot][now]=qwq{(i|a[k]), j}, vis[i|a[k]][j]=1;
				
			(dp[now][i][j|a[k]]+=dp[now^1][i][j])%=mod;
			if(!vis[i][j|a[k]])
				zhan[++tot][now]=qwq{i, (j|a[k])}, vis[i][j|a[k]]=1;
		}
//		cout<<tot<<"\n";
	}
	write(dp[now][sum][sum]);
	return 0;
}
