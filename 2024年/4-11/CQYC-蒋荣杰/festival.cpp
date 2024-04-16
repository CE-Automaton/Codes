#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e3+5;
int n, m, mod, f[(1<<21)], ans, tot, zhan[N];

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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1) ret=1LL*x*ret%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("festival");
	read(n), read(mod);
	m=ksm(n, mod-2);
	int now = 0;
	f[0]=1;
	for(int o = 1; o <= n/2+1; ++o) {
		now^=1;
		for(int s = (1<<n)-1; s >= 0; --s) 
			if(f[s]) {
				int t = s, gs = 0;
				tot=0;
				for(int o = 0; o < n; ++o)
					if(!((s>>o)&1)) {
						int l = (o-1+n)%n, r = (o+1)%n;
						if(((s>>l)&1) || ((s>>r)&1))
							t|=(1<<o), ++gs;
						else
							zhan[++tot]=(1<<o);
					}
					else
						++gs;
				f[t]=upd(f[t]+1LL*f[s]*gs%mod*m%mod);
				for(int o = 1; o <= tot; ++o)
					f[t|zhan[o]]=upd(f[t|zhan[o]]+1LL*f[s]*m%mod);
				f[s]=0;
			}
		debug(f[(1<<n)-1], '\n');
		ans=upd(ans+1LL*o*f[(1<<n)-1]%mod);
	}
	write(ans, '\n');
	return 0;
}