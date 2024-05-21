#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int base = 131;
int n, k, tot, zhan[25], qk[45][25], gs[45], dp[45][45], dpp[45][45], ans[45], anss[45], inv[25], sum;
LL t;
unordered_map <int, int> to;

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
void dfs(int x, int nn, int lst) {
	if(x == n+1) {
		if(nn == 0) {
			++tot;
			// debug(tot, ": ");
			// for(int i = 1; i <= n; ++i)
			// 	debug(zhan[i]), debug(' ');
			for(int i = 1; i <= n; ++i)
				qk[tot][i]=zhan[i], gs[tot]+=(zhan[i] != 0);
			// debug('\n');
		}
		return ;
	}
	for(int j = lst; j <= nn; ++j)
		zhan[x]=j, dfs(x+1, nn-j, j), zhan[x]=0;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("paint");
	read(n), read(t), read(k);
	dfs(1, n, 0);
	inv[0]=inv[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
	for(int i = 1; i <= tot; ++i) {
		int hs = 0;
		for(int j = 1; j <= n; ++j)
			hs=upd(1LL*base*hs%mod+(qk[i][j]+1));
		// if(to.find(hs) != to.end())
		// 	debug("!!!\n");
		to[hs]=i;
	}
	for(int i = 1; i <= tot; ++i) 
		for(int l = n-gs[i]+1; l <= n; ++l) {
			dp[i][i]=upd(dp[i][i]+1LL*qk[i][l]*qk[i][l]%mod*inv[n]%mod*inv[n]%mod);
			for(int r =  n-gs[i]+1; r <= n; ++r) 
				if(l != r) {
					for(int j = 1; j <= n; ++j)
						zhan[j]=qk[i][j];
					--zhan[l], ++zhan[r];
					sort(zhan+1, zhan+1+n);
					int hs = 0;
					for(int j = 1; j <= n; ++j)
						hs=upd(1LL*base*hs%mod+(zhan[j]+1));
					int tt = to[hs];
					dp[i][tt]=upd(dp[i][tt]+1LL*qk[i][l]*qk[i][r]%mod*inv[n]%mod*inv[n]%mod);
				}
		}
	ans[tot]=1;
	// for(int i = 1; i <= tot; ++i)
	// 	for(int j = 1; j <= tot; ++j)
	// 		debug(i, j, dp[i][j], '\n');
	while(t) {
		if(t&1) {
			for(int i = 1; i <= tot; ++i)
				anss[i]=ans[i], ans[i]=0;
			for(int i = 1; i <= tot; ++i)
				for(int j = 1; j <= tot; ++j)
					ans[j]=upd(ans[j]+1LL*anss[i]*dp[i][j]%mod);
		}
		for(int i = 1; i <= tot; ++i)
			for(int j = 1; j <= tot; ++j)
				dpp[i][j]=dp[i][j], dp[i][j]=0;
		for(int i = 1; i <= tot; ++i)
			for(int k = 1; k <= tot; ++k)
				for(int j = 1; j <= tot; ++j)
					dp[i][j]=upd(dp[i][j]+1LL*dpp[i][k]*dpp[k][j]%mod);
		t=(t>>1);
	}
	for(int i = 1; i <= tot; ++i)
		if(gs[i] >= k)
			sum=upd(sum+ans[i]);
	write(sum, '\n');
	return 0;
}