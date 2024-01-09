#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 2e3+5;
int n, u, v, dp[N][N], dpp[15][15][15][15], a[N], az[15][15][15];
vector <int> to[N];

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
void dfs1(int x, int fa) {
	if(to[x].size() == 1 && fa != 0) {
		dp[x][1]=1;
		return ;
	}
	int pd = 0;
	for(int y : to[x])
		if(y != fa) {
			dfs1(y, x);
			if(!pd) {
				for(int j = n; j >= 0; --j)
					dp[x][j]=dp[y][j];
				pd=1;
			}
			else
				for(int j = n; j >= 0; --j)
					for(int i = 0; i <= j; ++i)
						dp[x][j]=upd(dp[x][j]+1LL*dp[x][j-i]*dp[y][i]%mod);
		}
	for(int j = 0; j <= n; ++j)
		a[j]=0;
	for(int j = 0; j <= n-1; ++j)
		a[j+1]=dp[x][j];
	for(int j = 1; j <= n; ++j)
		a[j-1]=upd(a[j-1]+1LL*dp[x][j]*j%mod);
	for(int j = 0; j <= n; ++j)
		dp[x][j]=a[j];
}
void dfs2(int x, int fa) {
	if(to[x].size() == 1 && fa != 0) {
		dpp[x][1][0][0]=1;
		return ;
	}
	int pd = 0;
	for(int y : to[x])
		if(y != fa) {
			dfs2(y, x);
			if(!pd) {
				for(int j = n; j >= 0; --j)
					for(int aa = 0; aa <= n; ++aa)
						for(int bb = 0; bb <= n; ++bb)
							dpp[x][j][aa][bb]=dpp[y][j][aa][bb];
				pd=1;
			}
			else
				for(int j = n; j >= 0; --j)
					for(int aa = n; aa >= 0; --aa)
						for(int bb = n; bb >= 0; --bb)
							for(int i = 0; i <= j; ++i)
								for(int aaa = 0; aaa <= aa; ++aaa)
									for(int bbb = 0; bbb <= bb; ++bbb)
										dpp[x][j][aa][bb]=upd(dpp[x][j][aa][bb]+1LL*dpp[x][j-i][aa-aaa][bb-bbb]*dpp[y][i][aaa][bbb]%mod);
		}
	for(int j = n; j >= 0; --j)
		for(int aa = 0; aa <= n; ++aa)
			for(int bb = 0; bb <= n; ++bb)
				az[j][aa][bb]=0;
	for(int j = 0; j <= n; ++j)
		for(int aa = 0; aa <= n; ++aa)
			for(int bb = 0; bb <= n; ++bb) {
				az[j+1][aa][bb]=upd(az[j+1][aa][bb]+dpp[x][j][aa][bb]);
				if(j-1 >= 0)
					az[j-1][aa+1][bb]=upd(az[j-1][aa+1][bb]+1LL*dpp[x][j][aa][bb]*j%mod);
				if(aa-1 >= 0)
					az[j][aa-1][bb+1]=upd(az[j][aa-1][bb+1]+1LL*dpp[x][j][aa][bb]*aa%mod);
				if(bb-1 >= 0)
					az[j][aa][bb-1]=upd(az[j][aa][bb-1]+1LL*dpp[x][j][aa][bb]*bb%mod);
			}
	for(int j = 0; j <= n; ++j)
		for(int aa = 0; aa <= n; ++aa)
			for(int bb = 0; bb <= n; ++bb) 
				dpp[x][j][aa][bb]=az[j][aa][bb];
}

signed main() {
	freopen("courage.in", "r", stdin);
	freopen("courage.out", "w", stdout);
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs1(1, 0);
	write(dp[1][0], ' ');
	if(n <= 10)
		dfs2(1, 0), write(dpp[1][0][0][0], '\n');
	return 0;
}
