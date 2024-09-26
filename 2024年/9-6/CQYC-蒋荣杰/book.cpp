#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 85, V = 1.5e4+5;
int n, m, mx=10000;
LL ans, sum, val[V];
struct qwq {
	int c, t, w;
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
bool comp(qwq A, qwq B) {
	return 1LL*A.w*B.t < 1LL*B.w*A.t;
}

signed main() {
	File("book");
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i].c);
	for(int i = 1; i <= n; ++i) read(a[i].t);
	for(int i = 1; i <= n; ++i) read(a[i].w);
	read(m), mx=min(mx, m);
	sort(a+1, a+1+n, comp);
	for(int i = 1; i <= n && m-mx >= 81; ++i) {
		int gs = min((m-mx)/a[i].t, a[i].c);
		m-=gs*a[i].t;
		a[i].c-=gs;
		ans+=1LL*gs*a[i].w;
	}
	for(int i = 1; i <= n; ++i) {
		if(!a[i].c) continue;
		for(int j = 0; (1<<j) <= a[i].c; ++j) {
			for(int k = m; k/a[i].t >= (1<<j); --k)
				val[k]=max(val[k], val[k-a[i].t*(1<<j)]+1LL*(1<<j)*a[i].w);
			a[i].c-=(1<<j);
		}
		if(a[i].c) 
			for(int k = m; k/a[i].t >= a[i].c; --k)
				val[k]=max(val[k], val[k-a[i].t*a[i].c]+1LL*a[i].w*a[i].c);
	}
	for(int k = 0; k <= m; ++k)
		sum=max(sum, val[k]);
	write(sum+ans, '\n');
	return 0;
}