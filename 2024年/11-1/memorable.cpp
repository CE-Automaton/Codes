#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, ll[N], rr[N], dep[N], zhan[N], tot, jc[N], inc[N], inv[N];

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
int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int solve(int l, int r, int x) {
	if(l >= r) return 1;
	// debug(l, t, r, "???\n");
	return 1LL*solve(l, ll[x], ll[x])*solve(rr[x], r, rr[x])%mod*c(r-l, x-l)%mod;
}

signed main() {
	read(n);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		inc[i]=1LL*inc[i-1]*inv[i]%mod, jc[i]=1LL*i*jc[i-1]%mod;
	for(int i = 1; i <= n; ++i)
		read(ll[i]), ++dep[ll[i]+1];
	for(int i = 1; i <= n; ++i)
		read(rr[i]), --dep[rr[i]];
	for(int i = 1; i <= n; ++i)
		dep[i]+=dep[i-1];
	int xx = 1;
	for(int i = 2; i <= n; ++i)
		if(dep[i] < dep[xx])
			xx=i;
	for(int i = 1; i <= n; ++i) {
		ll[i]=0, rr[i]=n+1;
		while(tot && dep[zhan[tot]] < dep[i])
			rr[zhan[tot]]=i, --tot;
		ll[i]=zhan[tot];
		zhan[++tot]=i;
	}
	write(solve(1, n, xx), '\n');
	return 0;
}