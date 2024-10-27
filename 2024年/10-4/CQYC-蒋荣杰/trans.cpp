#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef __int128 LL;
const int N = 5e5+5;
int n, m, q, a[N], b[N], l, r, k;
LL st, c[N];

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
int pd(int x) {
	return (x%2 == 1 ? 1 : -1);
}
LL bbb(LL x) {
	return (x < 0 ? -x : x);
}
void getans() {
	int ans = m-n+2, ll = 1, rr = m-n+1;
	while(ll <= rr) {
		int mid = ((ll+rr)>>1);
		if(c[mid] >= st)
			ans=mid, rr=mid-1;
		else
			ll=mid+1;
	}
	if(ans != m-n+2 && ans != 1)
		write(min(bbb(st-c[ans]), bbb(st-c[ans-1])), '\n');
	else
		write((ans == 1 ? bbb(st-c[1]) : bbb(st-c[m-n+1])), '\n');
}

signed main() {
	File("trans");
	read(n), read(m), read(q);
	for(int i = 1, j = 1; i <= n; ++i, j=-j)
		read(a[i]), st+=(LL) j*a[i];
	for(int i = 1; i <= m; ++i)
		read(b[i]);
	for(int i = 1, j = 1; i <= n; ++i, j=-j)
		c[1]+=(LL) j*b[i];
	for(int i = 2; i <= m-n+1; ++i) 
		c[i]=(LL) -c[i-1]+b[i-1]+pd(n)*b[i+n-1];
	// for(int i = 1; i <= m-n+1; ++i) 
	// 	write(c[i], ' ');
	// putchar('\n');
	sort(c+1, c+1+m-n+1);
	getans();
	for(int i = 1; i <= q; ++i) {
		read(l), read(r), read(k);
		if(l > r) swap(l, r);
		if(l%2 == r%2) 
			st+=(LL) pd(l)*k;
		getans();
	}
	return 0;
}