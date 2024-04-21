#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, q, z, dp[(1<<18)+5][19], tot, zhan[19];

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
	File("cry");
	read(n), read(q);
	for(int i = 0; i <= n+n; ++i)
		dp[(1<<(n+n+1))-1-(1<<i)][i]=1;
	for(int i = (1<<(n+n+1))-1; i >= 3; --i) {
		tot=0;
		for(int j = 0; j <= n+n; ++j)
			if((i>>j)&1)
				zhan[++tot]=j;
		for(int k = 0; k <= n+n; ++k) 
			for(int o = 1; o <= tot; ++o)
				for(int p = o+1; p <= tot; ++p) {
					int tt = (i^(1<<zhan[o])^(1<<zhan[p])), to = min(max(k, zhan[o]), zhan[p]);
					dp[tt][to]=upd(dp[tt][to]+dp[i][k]);
				}
	}
	for(int i = 1; i <= q; ++i)
		read(z), write(dp[0][z], '\n');
	return 0;
}