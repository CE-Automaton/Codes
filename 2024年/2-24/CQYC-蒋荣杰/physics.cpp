#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
LL n, m, q, am, bm, x, y;

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
LL exgcd(LL a, LL b, LL& xx, LL& yy) {
	if(b == 0) {
		xx=1, yy=0;
		return a;
	}
	LL ret = exgcd(b, a%b, yy, xx);
	yy-=(a/b)*xx;
	return ret;
}

signed main() {
	File("physics");
	LL a = 0, b = 0;
	// debug(exgcd(3, 5, a, b), ' ');
	// debug(a, b, '\n');
	read(n), read(m), read(q);
	LL gc = exgcd(n, m, a, b);
	am=m/gc-1, bm=n/gc-1;
	while(q--) {
		read(x), read(y);
		LL ans = inf;
		for(int i = 0; i <= 1; ++i)
			for(int j = 0; j <= 1; ++j) {
				LL aa = (i ? n-x : x), bb = (j ? m-y : y), an = a, bn = b, c = bb-aa;
				if(c%gc != 0) continue;
				an*=c/gc, bn*=-c/gc;
				LL op = an/(m/gc);
				an-=op*(m/gc), bn-=op*(n/gc);
				if(an < 0)
					an+=(m/gc), bn+=(n/gc);
				if(bn < 0) {
					op=bn/(n/gc), an-=op*(m/gc), bn-=op*(n/gc);
					if(bn < 0)
						an+=(m/gc), bn+=(n/gc);
				}
				// debug(c, an, bn, m/gc, n/gc, an*n+aa, bn*m+bb, "!?\n");
				if(an > am || bn > bm) continue;
				if((an%2 != i && (m/gc)%2 == 0) || (bn%2 != j && (n/gc)%2 == 0))
					continue;
				if(an%2 != i)
					an+=(m/gc), bn+=(n/gc);
				if(bn%2 != j)
					an+=(m/gc), bn+=(n/gc);
				if(an%2 != i || an > am || bn > bm) continue;
				ans=min(ans, an*n+aa);
			}
		write((ans == inf ? -1 : ans), '\n');
	}
	return 0;
}