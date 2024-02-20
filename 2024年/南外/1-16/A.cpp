#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 2.5e6+5;
int m, n, m0, md, n0, nd, mm[N], nn[N];
LL ans, now;

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
int comp(int A, int B) {
	return A > B;
}

signed main() {
	// File("rabbit");
	read(m), read(n), read(m0), read(md), read(n0), read(nd);
	now=m0, mm[1]=m0;
	for(int i = 2; i <= m; ++i)
		mm[i]=(mm[i-1]*58+md)%(n+1), 
		now+=mm[i];
	nn[1]=n0;
	for(int i = 2; i <= n; ++i)
		nn[i]=(nn[i-1]*58+nd)%(m+1);
	sort(mm+1, mm+1+m);
	sort(nn+1, nn+1+n);
	ans=1LL*n*m;
	int gs = 0;
	for(int i = m; i >= 0; --i) {
		while(gs+1 <= n && nn[gs+1] < m-i)
			++gs, now=now+nn[gs]-m+i;
		ans=min(ans, now);
		now=now+n-gs-mm[i];
	}
	write(ans, '\n');
	return 0;
}