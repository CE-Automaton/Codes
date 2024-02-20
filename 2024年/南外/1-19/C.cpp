#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, m, a[25], g[(1<<20)+5]/*求2^n-1种里每个前缀都小于等于0的排列数*/,
f[(1<<20)+5]/*求2^n-1种里每个前缀都大于0的排列数*/, su[(1<<20)+5], ans;
LL sum[(1<<20)+5];

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
	File("max");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	m=(1<<n)-1;
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j)
			if(!((i>>j)&1))
				sum[i|(1<<j)]=sum[i]+1LL*a[j+1];
	f[0]=1;
	g[0]=1;
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j) {
			int k = i|(1<<j);
			if(i != k) {
				if(sum[k] > 0 && (sum[i] > 0 || i == 0))
					f[k]=upd(f[i]+f[k]);
				su[k]=upd(su[k]+f[i]);
				if(sum[k] <= 0 && sum[i] <= 0)
					g[k]=upd(g[i]+g[k]);
			}
		}
	for(int i = 1; i <= m; ++i) {
		ans=upd(ans+1LL*upd(sum[i]%mod+mod)*su[i]%mod*g[m^i]%mod);
		// for(int j = 0; j < n; ++j)
		// 	debug((i>>j)&1);
		// debug(' ', sum[i], su[i], g[m^i], "!?\n");
	}
	write(ans, '\n');
	return 0;
}