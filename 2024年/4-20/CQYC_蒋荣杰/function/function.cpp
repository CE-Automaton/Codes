#include <bits/stdc++.h>
#define int long long
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e4+5;
int c, n;
LL xz, yz, xa, ya, xb, yb, xp, yp, ans;
struct qwq {
	LL x, y;
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
int comp(qwq A, qwq B) {
	if(A.x == B.x)
		return A.y < B.y;
	return A.x < B.x;
}
LL abb(LL x) {
	return (x < 0 ? -x : x);
}

signed main() {
	File("function");
	read(c), read(n);
	read(xz), read(xa), read(xb), read(xp);
	read(yz), read(ya), read(yb), read(yp);
	pnt[1]=qwq {xz, yz};
	for(int i = 2; i <= n; ++i)
		pnt[i]=qwq {(1LL*pnt[i-1].x*xa%xp+1LL*xb)%xp, (1LL*pnt[i-1].y*ya%yp+1LL*yb)%yp};
	for(int i = 1; i <= n; ++i) {
		LL gs = pnt[i].x/(2LL*c);
		pnt[i].x-=2LL*gs*c;
		pnt[i].y-=2LL*gs*c;
	}
	sort(pnt+1, pnt+1+n, comp);
	// for(int i = 1; i <= n; ++i) 
	// 	write(pnt[i].x, ' '), write(pnt[i].y, '\n');
	// debug(ans, '\n');
	for(int l = 1; l <= n; ++l) {
		int r = l;
		while(r+1 <= n && pnt[r+1].x == pnt[l].x) ++r;
		// debug(l, r);
		LL sum = 0, lsm = 0, mn = 0;
		for(int j = l; j <= r; ++j)
			sum+=pnt[j].y, mn+=abb(pnt[j].y);
		// debug(' ', mn, ' ');
		for(int j = l; j <= r; ++j) {
			lsm+=pnt[j].y;
			mn=min(mn, 1LL*(j-l+1)*pnt[j].y-lsm+(sum-lsm)-1LL*(r-j)*pnt[j].y);
			// if(j != r)
			// 	mn=min(mn, 1LL*(j-l+1)*pnt[j+1].y-lsm+(sum-lsm)-1LL*(r-j)*pnt[j+1].y);
		}
		// debug(' ', mn, "???\n");
		ans+=mn;
		l=r;
	}
	write(ans, '\n');
	return 0;
}