#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, tot, rr[N], bk[N], ans[N], k;
double l, r;
struct qwq {
	int l, r, d;
}a[N], zhan[N];

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

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lf %lf", &l, &r);
		int lx = l*1000000, rx = r*1000000;
		++lx;
		if(rx > rr[lx])
			rr[lx]=rx, bk[lx]=i;
	}
	if(n == 1) {
		puts("1"); puts("1");
		return 0;
	}
	for(int i = 1, ls = -1; i <= 1000000; ++i)
		if(rr[i] && rr[i] > ls)
			a[++m]=qwq {i, rr[i], bk[i]}, ls=rr[i];
	int gs = 0;
	for(int i = 1; i <= m; ++i) 
		if(gs <= 1)
			zhan[++gs]=a[i];
		else {
			if(a[i].l <= zhan[gs-1].r)
				zhan[gs]=a[i];
			else
				zhan[++gs]=a[i];
		}
	int all = zhan[1].r-zhan[1].l+1;
	for(int i = 3; i <= gs; i+=2) 
		all+=zhan[i].r-zhan[i].l+1-2*max(0, zhan[i-2].r-zhan[i].l+1);
	if(all >= 650000) {
		write((gs+1)/2, '\n');
		for(int i = 1; i <= gs; i+=2)
			write(zhan[i].d, ' ');
		return 0;
	}
	all = zhan[2].r-zhan[2].l+1;
	for(int i = 4; i <= gs; i+=2) 
		all+=zhan[i].r-zhan[i].l+1-2*max(0, zhan[i-2].r-zhan[i].l+1);
	if(all >= 650000) {
		write(gs/2, '\n');
		for(int i = 2; i <= gs; i+=2)
			write(zhan[i].d, ' ');
		return 0;
	}
	write(gs, '\n');
	for(int i = 1; i <= gs; ++i)
		write(zhan[i].d, ' ');
	return 0;
}
