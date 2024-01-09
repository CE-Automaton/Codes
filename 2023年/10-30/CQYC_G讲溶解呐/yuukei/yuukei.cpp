#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 2e2+5, M = 4.1e4+5;
int n, r, g, b, gs, dp[N][M], tot, u, v, ans;
char s[N];
unordered_map <int, int> t;
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
int ask(int i, int j, int k) {
	return t[i*1000000+j*1000+k];
}
void dfs(int x, int fa) {
	if(s[x] == 'r')
		dp[x][ask(1, 0, 0)]=1;
	if(s[x] == 'b')
		dp[x][ask(0, 1, 0)]=1;
	if(s[x] == 'g')
		dp[x][ask(0, 0, 1)]=1;
	for(int y : to[x])
		if(y != fa) {
			dfs(y, x);
			for(int i = r; i >= 0; --i)
			for(int j = b; j >= 0; --j)
			for(int k = g; k >= 0; --k) {
				int tt = ask(i, j, k);
				for(int ii = 0; ii <= i; ++ii)
				for(int jj = 0; jj <= j; ++jj)
				for(int kk = 0; kk <= k; ++kk) {
					int ttt = ask(ii, jj, kk);
					if(dp[y][ttt] != 0)
						dp[x][tt]=upd(dp[x][tt]+1LL*dp[x][ask(i-ii, j-jj, k-kk)]*dp[y][ttt]%mod);
				}
			}
		}
	for(int i = r; i >= 0; --i)
	for(int j = b; j >= 0; --j)
	for(int k = g; k >= 0; --k) 
		ans=upd(ans+dp[x][ask(i, j, k)])/*, cout<<x<<"! "<<i<<" "<<j<<" "<<k<<" "<<dp[x][ask(i, j, k)]<<"\n"*/;
}

signed main() {
	freopen("yuukei.in", "r", stdin);
	freopen("yuukei.out", "w", stdout);
	read(n), read(r), read(b), read(g);
	for(int i = 0; i <= r; ++i)
		for(int j = 0; j <= b; ++j)
			for(int k = 0; k <= g; ++k)
				t[i*1000000+j*1000+k]=++tot;
	scanf("%s", s+1);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	write(ans, '\n');
	return 0;
}
