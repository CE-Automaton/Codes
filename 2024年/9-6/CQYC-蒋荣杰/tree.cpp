#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e3+5;
int n, mod, jc[N], inc[N], gs[N], az[N], dp[N], ans, sum[N][N];

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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}

signed main() {
	File("tree");
	read(n), read(mod);
	if(mod == 2) {
		puts("1");
		return 0;
	}
	jc[0]=inc[0]=1;
	for(int i = 1; i <= n; ++i) 
		jc[i]=1LL*jc[i-1]*i%mod;
	inc[n]=ksm(jc[n], mod-2);
	for(int i = n-1; i >= 1; --i)
		inc[i]=1LL*inc[i+1]*(i+1)%mod;
	for(int i = 1; i <= n; ++i)
		gs[i]=ksm(upd(i+i), i-1);
	dp[0]=1;
	for(int op = 1; op <= n; ++op)
		for(int j = 1; j <= op; ++j)
			dp[op]=upd(dp[op]+1LL*dp[op-j]*inc[j]%mod*gs[j]%mod);
	write(1LL*dp[n]*jc[n]%mod, '\n');
	return 0;
}