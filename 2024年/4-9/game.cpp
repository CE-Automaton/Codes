#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e4+5;
int n, a[N], mx, jc[N<<1], inv[N<<1], inc[N<<1], ans;
bitset<N> val, now;

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
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), mx=max(mx, a[i]), val[a[i]]=1;
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n+n; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	for(int i = 0, j = 0; i <= n; ++i) 
		ans=upd(ans+(i <= 1 ? 0 : 1LL*c(n, i)*j%mod)), j=upd(j+c(n, i));
	for(int i = 1; i <= mx; ++i) {
		now=val;
		for(int j = i; j <= mx; j+=i) 
			if(val[j]) {
				now&=(now<<i);
				int gs = now.count();
				if(!gs)
					break;
				ans=upd(ans-gs+mod);
			}
			else break;
	}
	for(int i = 1; i <= mx; ++i) {
		now=val;
		int pd = 1, cc = 0, ls = 0, cs = 0;
		for(int j = i; j <= mx; j+=i) {
			if(val[j]) ++cc, ++ls;
			else pd=0, ls=0;
			cs+=pd;
			if(j+i <= mx && val[j] && val[j+i]) {
				ans=upd(ans-c(cc+cc-1, cc-1)+mod);
				if(cc > 1)
					ans=upd(ans+c(cc+cc-1, cc-2));
				ans=upd(ans+min(ls, cs));
			}
		}
	}
	write(ans, '\n');
	return 0;
}