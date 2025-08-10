#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, k, a[N], jc[N], inv[N], inc[N], zhan[N], tot, b[2][N], 
dp[2][1005][1005], tr[1005][1005], sum[1005][1005], sss[1005][1005], ans;

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
void dfs(int x) {
	if(x == k+1) {
		for(int i = 1; i <= n; ++i)
			b[0][i]=a[i];
		int now = 0;
		for(int i = 1; i <= k; ++i) {
			now^=1;
			for(int o = 1; o <= zhan[i]; ++o)
				b[now][o]=b[now^1][o];
			b[now][zhan[i]]=upd(b[now][zhan[i]]-b[now^1][zhan[i]+1]+mod);
			for(int o = zhan[i]+1; o <= n-i; ++o)
				b[now][o]=b[now^1][o+1];
		}
		for(int o = 1; o <= n-k; ++o)
			ans=upd(ans+b[now][o]);
		return ;
	}
	for(int i = 1; i <= n-x; ++i)
		zhan[++tot]=i, dfs(x+1), --tot;
}

signed main() {
	File("game");
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	if(n <= 10) {
		dfs(1);
		write(1LL*ans*inc[n-1]*jc[n-1-k]%mod, '\n');
		return 0;
	}
	dp[0][0][1]=dp[1][0][1]=1;
	for(int op = 0; op <= 1; ++op)
		for(int i = 1; i <= k; ++i) 
			for(int j = 1; j <= i+1; ++j)
				dp[op][i][j]=1LL*upd((j == 1 ? 0 : dp[op][i-1][j-1])+1LL*dp[op][i-1][j]*(n-k+i-1-j+op)%mod)*inv[n-k+i-1]%mod;
	tr[1][1]=sum[1][1]=1;
	for(int i = 1; i <= k; ++i) {
		for(int j = 1; j <= i; ++j)
			tr[i+1][j+1]=sum[i][j];
		for(int j = i+1; j >= 1; --j)
			sum[i+1][j]=upd(sum[i+1][j+1]+tr[i+1][j]);
	}
	for(int j = 1; j <= k+1; ++j)
		for(int i = j; i <= n; ++i)
			sss[j][i]=upd(sss[j][i-1]+1LL*dp[0][k][i]*tr[i][j]%mod);
	for(int i = 1; i < n; ++i) 
		for(int j = 1, op = 1; j <= i && j <= k+1; ++j, op=-op)
			ans=upd(ans+upd(1LL*a[i]*sss[j][i-1]%mod*op+mod)), 
			ans=upd(ans+upd(1LL*a[i]*tr[i][j]%mod*dp[1][k][i]%mod*op+mod));
	for(int j = 1, op = 1; j <= n && j <= k+1; ++j, op=-op)
		for(int i = j; i <= k+1; ++i)
			ans=upd(ans+upd(1LL*a[n]*dp[0][k][i]%mod*tr[i][j]%mod*op+mod));
	write(ans, '\n');
	return 0;
}
