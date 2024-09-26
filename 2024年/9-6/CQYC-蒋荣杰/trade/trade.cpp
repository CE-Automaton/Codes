#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5, M = 1e6+5;
int n, a[N], dp[2][M], f[2][M], ans;

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
	File("trade");
	read(n);
	int pd = 1, pd2 = 0, sum = 1, mn = 100000000;
	for(int i = 1; i <= n; ++i)
		read(a[i]), pd&=(a[i] <= 1), pd2|=(a[i] == 0), sum=1LL*sum*a[i]%mod, mn=min(mn, a[i]+1);
	if(pd) {
		write((pd2 ? 0 : 2), '\n');
		return 0;
	}
	int now = 0;
	for(int i = 0; i <= a[1]; ++i)
		dp[0][i]=1, f[0][i]=mod-i;
	for(int j = 2; j <= n; ++j) {
		now^=1;
		for(int i = 0; i <= a[j]; ++i)
			dp[now][i]=f[now][i]=0;
		for(int k = 0; k <= a[j-1]; ++k)
			for(int i = 0; i <= a[j]; ++i)
				dp[now][i]=upd(1LL*dp[now^1][k]*(a[j]-i+k)%mod+dp[now][i]), 
				f[now][i]=upd(1LL*f[now^1][k]*(a[j]-i+k)%mod+f[now][i]);
	}
	for(int i = 0; i <= a[n]; ++i)
		ans=upd(ans+1LL*dp[now][i]*(a[1]+i)%mod),
		ans=upd(ans+f[now][i]);
	write(upd(ans-1LL*sum*mn%mod+mod), '\n');
	return 0;
}