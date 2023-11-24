#include <bits/stdc++.h>
#define int long long
using namespace std;
int q, l, r, dp[35], f[35][35][2][2][2], ff[35];
int len; char s[405];
template <typename T> 
void write(T x) {
	do {s[++len]=x%10, x/=10;} while(x);
	while(len) putchar(s[len--]^48); putchar(' ');
}
void solve(int x, int y) {
	memset(f, 0, sizeof f);
	memset(ff, 0, sizeof ff);
	if(x < 0) return ;
	f[0][30][0][0][0]=1;
	for(int i = 29; i >= 0; --i)
		for(int j = 29; j >= 0; --j)
			for(int a = 0; a <= 1; ++a)
				for(int b = 0; b <= 1; ++b) {
					if(((x>>i)&1)|a)//x这位取1,则必须y已经满足大于x 
						f[j+1][i][a][b|((y>>i)&1)][1]+=f[j][i+1][a][b][1]; 
					if(((y>>i)&1)|b)//y这位取1,则y肯定满足大于x 
						f[j+1][i][a|((x>>i)&1)][b][1]+=f[j][i+1][a][b][1]+f[j][i+1][a][b][0];
					//都取0： 
					f[j][i][((x>>i)&1)|a][b|((y>>i)&1)][0]+=f[j][i+1][a][b][0]; 
					f[j][i][((x>>i)&1)|a][b|((y>>i)&1)][1]+=f[j][i+1][a][b][1];
					//都取1： 
					if((((x>>i)&1)|a) && (((y>>i)&1)|b))
						f[j][i][a][b][0]+=f[j][i+1][a][b][0], 
						f[j][i][a][b][1]+=f[j][i+1][a][b][1]; 
				}
	for(int i = 30; i >= 0; --i)
		for(int a = 0; a <= 1; ++a)
			for(int b = 0; b <= 1; ++b)
				ff[i]+=f[i][0][a][b][1]+f[i][0][a][b][0];
}
signed main() {
	freopen("bit.in", "r", stdin);
	freopen("bit.out", "w", stdout);
	scanf("%lld", &q);
	while(q--) {
		scanf("%lld%lld", &l, &r);
		solve(r, r);
		for(int i = 30; i >= 0; --i)
			dp[i]=ff[i];//懒得先赋0 
		solve(l-1, r);
		for(int i = 30; i >= 0; --i)
			dp[i]-=ff[i];//手动容斥嘻嘻 
		for(int i = 0; i <= 30; ++i)
			write(dp[i]);
		putchar('\n');
	}
	return 0;
}
