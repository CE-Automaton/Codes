#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, k, ans, a, aa, bb, aaa, bbb, ccc;
struct qwq {
	int x, y, z;
}pnt[N];

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
	// File("pixel");
	read(n), read(k);
	int gs = n*(n-1)*(n-2)/6;
	aaa=1, bbb=2, ccc=3;
	while(k >= 6 && gs) {
		// debug(aaa, bbb, ccc, "!!!\n");
		++ans;
		pnt[ans]=qwq {aaa, bbb, ccc};
		++ans;
		pnt[ans]=qwq {aaa, ccc, bbb};
		++ans;
		pnt[ans]=qwq {bbb, aaa, ccc};
		++ans;
		pnt[ans]=qwq {bbb, ccc, aaa};
		++ans;
		pnt[ans]=qwq {ccc, aaa, bbb};
		++ans;
		pnt[ans]=qwq {ccc, bbb, aaa};
		++ccc;
		if(ccc == n+1)
			++bbb, ccc=bbb+1;
		if(bbb == n)
			++aaa, bbb=aaa+1, ccc=bbb+1;
		k-=6;
		--gs;
	}
	gs=n*(n-1);
	aa=1, bb = 2;
	while(k >= 3 && gs) {
		++ans;
		pnt[ans]=qwq {aa, aa, bb};
		++ans;
		pnt[ans]=qwq {aa, bb, aa};
		++ans;
		pnt[ans]=qwq {bb, aa, aa};
		++bb;
		if(bb == aa)
			++bb;
		if(bb == n+1)
			++aa, bb=1;
		k-=3;
		--gs;
	}
	gs=n;
	a=1;
	while(k >= 1 && gs) {
		++ans;
		pnt[ans]=(qwq) {a, a, a};
		--gs;
		--k;
		++a;
	}
	for(int i = 1; i <= ans; ++i)
		write(pnt[i].x, ' '), write(pnt[i].y, ' '), write(pnt[i].z, '\n');
	return 0;
}