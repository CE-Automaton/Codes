#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, u, v, zhan[N], tot, pw[N], dp[N][60004], s[60004], ans;
LL X, Y, a[N];
vector <int> to[N];

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
void dfs(int x, int fa) {
	int now = 0;
	for(int i = 1; i <= tot; ++i)
		now=now+pw[i-1]*(a[x]%zhan[i] == 0 ? 1 : 0);
	dp[x][now]=1;
	for(int y : to[x])
		if(y != fa) {
			dfs(y, x);
			for(int i = 0; i <= pw[tot]-1; ++i) 
				if(dp[x][i])
					for(int j = 0, now = 0; j <= pw[tot]-1; ++j, now = 0) 
						if(dp[y][j]) {
							for(int k = 0; k < tot; ++k)
								if(i%pw[k+1]/pw[k] == 2 || j%pw[k+1]/pw[k] == 2)
									now+=2*pw[k];
								else
									if(i%pw[k+1]/pw[k] != j%pw[k+1]/pw[k])
										now+=2*pw[k];
									else
										now+=(i%pw[k+1]/pw[k])*pw[k];
							s[now]=upd(s[now]+1LL*dp[x][i]*dp[y][j]%mod);
						}
			for(int i = 0; i <= pw[tot]-1; ++i) 
				dp[x][i]=upd(dp[x][i]+s[i]), s[i]=0;
		}
	// for(int i = 0; i <= pw[tot]-1; ++i) 
	// 	cout<<dp[x][i]<<" ";
	// puts("\n");
	ans=upd(ans+dp[x][pw[tot]-1]);
}

signed main() {
	File("B");
	read(n), read(X), read(Y);
	for(int i = 2; i <= 50; ++i) 
		if(Y%i == 0) {
			if(X%i != 0) zhan[++tot]=i;
			Y/=i;
		}
	pw[0]=1;
	for(int i = 1; i <= tot; ++i)
		pw[i]=pw[i-1]*3;
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	write(ans, '\n');
	return 0;
}