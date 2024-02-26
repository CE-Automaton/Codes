#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 1e7+5;
__int128 md = 1844674407370955161;
int vis[N], pri[N], tot;
LL m, n;
uLL ans, f[N], pw[N], op[N];

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
struct qwq {
	uLL a[N];
	int e[N];
	void clear() {
		for(int i = 1; i <= m; ++i)
			a[i]=0, e[i]=0;
	}
	void add(int x, uLL w) {
		e[x]=__builtin_ctzll(w);
		w>>=e[x];
		a[x]=w;
	}
}jc, cj, inv, inc;
uLL ksm(uLL x, LL y, uLL ret = 1uLL) {
	while(y) {
		if(y&1) ret=ret*x;
		x=x*x, y=(y>>1);
	}
	return ret;
}

signed main() {
	md=md*10+6;
	// write(md, '\n');
	read(m), read(n), ++m, --n;
	if(m == 1) {
		write(n+1, '\n');
		return 0;
	}
	f[0]=0, f[1]=1;
	for(int i = 2; i <= m; ++i) {
		if(!vis[i]) 
			pri[++tot]=i, f[i]=ksm(i, m-1);
		for(int j = 1; j <= tot && i <= m/pri[j]; ++j) {
			vis[i*pri[j]]=1, f[i*pri[j]]=f[i]*f[pri[j]];
			if(i%pri[j] == 0) break;
		}
	}
	pw[0]=1;
	for(int i = 1; i <= 10000000; ++i)
		pw[i]=pw[i-1]+pw[i-1];
	for(int i = 1; i <= m; ++i)
		f[i]=f[i]+f[i-1];
	if(n <= m) {
		write(f[n], '\n');
		return 0;
	}
	jc.clear(), cj.clear(), inc.clear();
	jc.add(1, n);
	op[1]=1;
	uLL sum = 1;
	for(int i = 2; i <= m; ++i) {
		// write(((__int128) md-md/i), ' ');
		jc.add(i, n-i+1), jc.a[i]*=jc.a[i-1], jc.e[i]+=jc.e[i-1];
		if(i%2 == 0)
			op[i]=op[i/2], inc.e[i]=inc.e[i/2]-1;
		else
			op[i]=i;
		sum*=op[i];
	}
	for(int i = 2; i <= m; ++i)
		inc.e[i]+=inc.e[i-1];
	inc.a[m]=ksm(sum, md/2-1);
	for(int i = m-1; i >= 1; --i)
		inc.a[i]=inc.a[i+1]*op[i+1];
	inc.a[0]=1;
	// write(inv.e[95], '\n');
	// write(inv.a[95]*95uLL, '\n');
	cj.a[m]=1;
	for(int i = m-1; i >= 1; --i)
		cj.add(i, n-i-1), cj.a[i]*=cj.a[i+1], cj.e[i]+=cj.e[i+1];
	// for(int i = 0; i <= m; ++i)
	// 	debug(jc.a[i], jc.e[i], cj.a[i], cj.e[i], inc.a[i], inc.e[i], f[i], '\n');
	for(int i = m, zf = 1; i >= 1; --i) {
		uLL lst = jc.a[i]*cj.a[i]*inc.a[i]*inc.a[m-i];
		int now = jc.e[i]+cj.e[i]+inc.e[i]+inc.e[m-i];
		lst=lst*pw[now]*f[i];
		// write(now, '\n');
		ans=(zf ? (ans+lst) : (ans-lst));
		zf^=1;
	}
	write(ans, '\n');
	return 0;
}