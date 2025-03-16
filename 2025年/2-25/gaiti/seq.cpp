#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 7e5+5;
int n, m, q, u, v, pp;
struct qwq {
	int cc, oo, vv[23];
}a[N];

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
inline int upd(int x) {
	return (x >= mod ? x-mod : x);
}
inline void merge(qwq &A, qwq &B) {
	int va = A.oo, vb = B.oo, vc = 0;
	A.cc^=B.cc;
	for(int i = 0; i <= pp; ++i)
		va=upd(va+1LL*A.vv[i]*(1<<i)%mod), 
		vb=upd(vb+1LL*B.vv[i]*(1<<i)%mod);
	for(int i = pp; i >= 0; --i) {
		va=upd(va-1LL*A.vv[i]*(1<<i)%mod+mod), 
		vb=upd(vb-1LL*B.vv[i]*(1<<i)%mod+mod);
		int ll = A.vv[i];
		A.vv[i]=upd(vc+upd(1LL*ll*vb%mod+1LL*va*B.vv[i]%mod));
		vc=upd(vc+1LL*ll*B.vv[i]%mod*(1<<i)%mod);
	}
	A.oo=upd(vc+1LL*A.oo*B.oo%mod);
}

signed main() {
	File("seq");
	read(n), read(m), read(q);
	while((1<<pp) < m) ++pp;
	for(int i = 1; i <= n; ++i) {
		read(u), read(v);
		a[i].cc=u;
		while(u)
			a[i].vv[__builtin_ctz(u&(-u))]=1LL*u*(u^v)%mod, u-=(u&(-u));
	}
	// for(int o = 1; o <= n; ++o) {
	// 	debug(a[o].cc, a[o].oo, " ");
	// 	for(int p = 0; p <= pp; ++p)
	// 		debug(a[o].vv[p], "");
	// 	debug("\n");
	// }
	// debug("\n");
	for(int i = 2; i <= n; ++i) {
		merge(a[i], a[i-1]);
		// for(int o = 1; o <= n; ++o) {
		// 	debug(a[o].cc, a[o].oo, " ");
		// 	for(int p = 0; p <= pp; ++p)
		// 		debug(a[o].vv[p], "");
		// 	debug("\n");
		// }
		// debug("\n");
	}
	for(int i = 1; i <= q; ++i)
		read(u), read(v), v^=a[u].cc/*, debug(v, __lg(v), u, a[u].cc, "!?\n")*/,
		write((v == 0 ? a[u].oo : a[u].vv[__lg(v)]), '\n');
	return 0;
}
