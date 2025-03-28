#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 4e5+5;
int n, a[N], b[N], zhan[N], tot;
long long inf=3000000000000000000LL;
struct qwq {
	int x, y;
}pt[N];

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
long long dis(int x, int y) {
	long long xx = (pt[x].x-pt[y].x), yy = (pt[x].y-pt[y].y);
	return xx*xx+yy*yy;
}
int comp(qwq A, qwq B) {
	if(A.x == B.x)
		return A.y < B.y;
	return A.x < B.x;
}
long long solve(int l, int r) {
	if(l >= r) return inf;
	if(l+1 == r) {
		b[l]=(pt[a[l]].y < pt[a[r]].y ? a[l] : a[r]);
		b[r]=(pt[a[l]].y < pt[a[r]].y ? a[r] : a[l]);
		a[l]=b[l], a[r]=b[r];
		return dis(a[l], a[r]);
	}
	int mid = ((l+r)>>1), xx = pt[a[mid]].x, lx = l, rx = mid+1, pp = l-1;
	long long d = min(solve(l, mid), solve(mid+1, r));
	for(int i = l; i <= r; ++i) 
		if(lx <= mid && rx <= r) {
			if(pt[a[lx]].y < pt[a[rx]].y)
				b[++pp]=a[lx], ++lx;
			else
				b[++pp]=a[rx], ++rx;
		}
		else {
			if(lx <= mid)
				b[++pp]=a[lx], ++lx;
			else
				b[++pp]=a[rx], ++rx;
		}
	for(int i = l; i <= r; ++i) 
		a[i]=b[i];
	tot=0;
	for(int i = l; i <= r; ++i)
		if(1LL*abs(pt[a[i]].x-xx)*abs(pt[a[i]].x-xx) <= d)
			zhan[++tot]=a[i];
	for(int i = 1; i <= tot; ++i)
		for(int j = i+1; j <= tot && 1LL*(pt[zhan[j]].y-pt[zhan[i]].y)*(pt[zhan[j]].y-pt[zhan[i]].y) <= d; ++j)
			d=min(d, dis(zhan[i], zhan[j]));
	return d;
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		read(pt[i].x), read(pt[i].y), a[i]=i;
	sort(pt+1, pt+1+n, comp);
	printf("%lld\n", solve(1, n));
	return 0;
}