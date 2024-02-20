#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, jc[N], inv[N], inc[N], ls[2][N], rs[2][N], ans;
char s[N];

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
	scanf("%s", s+1);
	n=strlen(s+1);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	for(int i = 1; i <= n; ++i) {
		ls[0][i]=ls[0][i-1];
		ls[1][i]=ls[1][i-1];
		if(s[i] == '(')
			++ls[0][i];
		if(s[i] == '?')
			++ls[1][i];
	}
	for(int i = n; i >= 1; --i) {
		rs[0][i]=rs[0][i+1];
		rs[1][i]=rs[1][i+1];
		if(s[i] == ')')
			++rs[0][i];
		if(s[i] == '?')
			++rs[1][i];
	}
	for(int i = 0; i <= n; ++i) {
		int x = (ls[1][i]+rs[1][i+1]), y = (rs[0][i+1]+rs[1][i+1]-ls[0][i]);
		if(y < 0 || y > x) continue;
		ans=upd(upd(ans+1LL*ls[0][i]*c(x, y)%mod)+1LL*ls[1][i]*c(x-1, y-1)%mod);
	}
	write(ans, '\n');
	return 0;
}