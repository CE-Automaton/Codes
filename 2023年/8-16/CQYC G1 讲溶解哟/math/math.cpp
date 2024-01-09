#include <bits/stdc++.h>
using namespace std;
int t, xx;
long double oa, ob, oh, ya, yb, hm;

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
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
	read(t);
	while(t--) {
		read(xx), oa=xx;
		read(xx), ya=xx;
		read(xx), ob=xx;
		read(xx), yb=xx;
		read(xx), oh=xx;
		read(xx), hm=xx;
		if(oa > ob) swap(oa, ob);
		long double b = (ob-oa)/2.0, a = (oa+b)*hm/oh, om2 = oh*oh+hm*hm, 
		x = (((long double) sqrt(4.0*a*a*oh*oh*oh*oh-4.0*hm*hm*(om2*b*b-oh*oh*a*a)))-2.0*a*oh*oh)/(2.0*hm*hm), 
		xp = oa+b-((long double) sqrt((x*x+b*b)/(hm*hm+oh*oh)))*hm, yp = xp*hm/oh;
		printf("%.7Lf %.7Lf\n", xp, yp);
	}
	return 0;
}
