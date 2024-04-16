#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, a[15], s, dp[2][1405][1405], ans;

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
void dfs(int now, int l, int r) {
	int& ret = dp[now][l][r];
	if(ret != -1) return ;
	if(now) {
		dp[now][l][r]=0;
		for(int j = 1; j <= 10; ++j)
			if((r>>(j-1))&1)
				for(int k = j+1; k <= 10; ++k)
					if(((r>>(k-1))&1) && !((l>>(k-j-1))&1)) {
						dfs(now^1, l|(1<<(k-j-1)), r);
						dp[now][l][r]|=(dp[now^1][l|(1<<(k-j-1))][r]^1);
					}
	}
	else {
		dp[now][l][r]=0;
		for(int j = 1; j <= 10; ++j)
			if((l>>(j-1))&1)
				for(int k = j+1; k <= 10; ++k)
					if(((l>>(k-1))&1) && !((r>>(k-j-1))&1)) {
						dfs(now^1, l, r|(1<<(k-j-1)));
						dp[now][l][r]|=(dp[now^1][l][r|(1<<(k-j-1))]^1);
					}
	}
}

signed main() {
	File("game");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), s|=(1<<(a[i]-1));
	for(int i = 0; i < (1<<10); ++i)
		for(int j = 0; j < (1<<10); ++j) 
			dp[0][i][j]=-1, dp[1][i][j]=-1;
	for(int i = 0; i < (1<<10); ++i)
		for(int j = 0; j < (1<<10); ++j) {
			int pd = 1;
			for(int o = 1; o <= 10 && pd; ++o)
				if((i>>(o-1))&1)
					for(int p = o+1; p <= 10 && pd; ++p)
						if(((i>>(p-1))&1) && !((j>>(p-o-1))&1)) 
							pd=0;
			if(pd)
				dp[0][i][j]=0, dp[1][j][i]=0;//先手必输
		}
	for(int i = 0; i < (1<<10); ++i)
		for(int j = 0; j < (1<<10); ++j) {
			if(dp[0][i][j] == -1)
				dfs(0, i, j);
			if(dp[1][i][j] == -1)
				dfs(1, i, j);
		}
	for(int o = s; o; o=((o-1)&s)) {
		if((o&(-o)) != o)
			++ans;
		for(int p = s; p; p=((p-1)&s)) 
			ans+=(dp[0][o][p] == 1);
	}
	write(ans, '\n');
	return 0;
}