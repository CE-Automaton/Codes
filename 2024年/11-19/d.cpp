#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 105;
int n, m, s[N], dp[(1<<17)], jc[(1<<17)], inv[(1<<17)], inc[(1<<17)], ans;

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
int c(int x, int y) {
	return (x < y || x < 0 ? 0 : 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod);
}

signed main() {
	read(n), read(m);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= (1<<16); ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	// if(m == 0) {
	// 	write(jc[(1<<n)], '\n');
	// 	return 0;
	// }
	for(int i = 1; i <= m; ++i)
		read(s[i]);
	dp[0]=1;
	for(int j = m; j >= 1; --j) 
		for(int i = (1<<n)-1; i >= 0; --i) 
			for(int op = 0; op < n; ++op)
				if(!((i>>op)&1)) 
					dp[i|(1<<op)]=upd(dp[i|(1<<op)]+1LL*dp[i]*c((1<<n)-i-s[j], (1<<op)-1)%mod*jc[(1<<op)]%mod);
	for(int i = 0; i < (1<<n); ++i) {
		int op = 0;
		for(int j = 0; j < n; ++j)
			if((i>>j)&1)
				++op;
		// debug(op, dp[i], jc[(1<<n)-i-1], "???\n");
		if(op%2 == 0)
			ans=upd(ans+1LL*dp[i]*jc[(1<<n)-i-1]%mod);
		else
			ans=upd(ans-1LL*dp[i]*jc[(1<<n)-i-1]%mod+mod);
	}
	// debug(ans, "???\n");
	write(1LL*ans*(1<<n)%mod, '\n');
	return 0;
}