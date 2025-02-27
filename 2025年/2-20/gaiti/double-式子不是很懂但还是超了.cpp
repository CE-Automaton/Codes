#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, jc[N], inv[N], inc[N], g[N], ans[N];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("double");
	read(n), read(m);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= m; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		inc[i]=1LL*inc[i-1]*inv[i]%mod, jc[i]=1LL*jc[i-1]*i%mod;
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; i*(j-1)+n <= m; ++j)
			g[i]=upd(g[i]+c(m-i*(j-1), n));
	for(int i = 1; i <= n; ++i)
		for(int j = i, op = 1; j <= n; ++j, op=-op)
			ans[n-i+1]=upd(upd(ans[n-i+1]+1LL*op*c(j-1, i-1)*c(n, j)%mod*g[j]%mod)+mod);
	int cc = 1LL*inc[m]*jc[m-n]%mod*jc[n]%mod;
	for(int i = 1; i <= n; ++i)
		ans[i]=upd(ans[i-1]+ans[i]), 
		write(1LL*ans[i]*cc%mod, '\n');
	return 0;
}
