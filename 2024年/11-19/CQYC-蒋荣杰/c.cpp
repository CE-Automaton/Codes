#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 105;
int n, m, p[N], vis[N], dp[N][N][N], ans;

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
	File("c");
	read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(p[i]), vis[p[i]]=i;
	if(n == m) {
		puts("1");
		return 0;
	}
	int to = n-1;
	for(int i = 0; i < n; ++i)
		if(!vis[i])
			to=i;
	if(vis[0])
		dp[0][vis[0]-1][vis[0]-1]=1;
	else
		for(int i = 0; i <= m; ++i)
			dp[0][i][i]=1;
	for(int i = 1; i <= to; ++i) {
		if(vis[i]) {
			for(int l = 0; l <= m; ++l)
				for(int r = l; r <= m; ++r) 
					if(vis[i] <= l || vis[i] > r)
						dp[i][min(vis[i]-1, l)][max(vis[i]-1, r)]=upd(dp[i][min(vis[i]-1, l)][max(vis[i]-1, r)]+dp[i-1][l][r]);
			continue;
		}
		for(int l = 0; l <= m; ++l)
			for(int r = l; r <= m; ++r) {
				for(int now = 0; now <= l; ++now)
					dp[i][now][r]=upd(dp[i][now][r]+dp[i-1][l][r]);
				for(int now = r; now <= m; ++now)
					dp[i][l][now]=upd(dp[i][l][now]+dp[i-1][l][r]);
			}
	}
	for(int i = 0; i <= m; ++i)
		for(int j = i; j <= m; ++j)
			ans=upd(ans+dp[to][i][j]);
	write(ans, '\n');
	return 0;
}