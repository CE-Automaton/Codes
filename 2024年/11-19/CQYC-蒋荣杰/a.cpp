#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, m, ans1, ans2, inv;
double pii;

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
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("a");
	read(n), read(m);
	pii=__builtin_acos(-1);
	int opp = (int) ceil((double) 2.0*m/pii);
	// debug(op, opp, "???\n");
	for(int i = 1; i <= n; ++i)	
		ans1=upd(ans1+1LL*opp*(opp-1)%mod*i%mod*i%mod), 
		ans2=upd(ans2+1LL*i*(i-1)/2%mod*(2*opp-1)%mod*2%mod*m%mod), 
		ans2=upd(upd(upd(ans2+2LL*i%mod*(2*m-2*opp+1)%mod*m%mod)+1LL*i*upd(1+1LL*(2*m-2*opp+1)*(i-1)%mod)%mod*2%mod*m%mod)
		+1LL*(2*m-2*opp+1)*(1LL*(i-1)*i/2%mod)%mod*2%mod*m%mod);
	write(ans1, ' '), write(ans2, '\n');
	// debug(clock(), '\n');
	return 0;
}