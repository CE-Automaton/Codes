#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, a[N];
long double ans;
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
int comp(qwq A, qwq B) {
	if(A.x == B.x)
		return A.y < B.y;
	return A.x < B.x;
}
int compp(qwq A, qwq B) {
	if(A.y == B.y)
		return A.x < B.x;
	return A.y < B.y;
}
long double dis(int x, int y) {
	long long xx = (pt[x].x-pt[y].x), yy = (pt[x].y-pt[y].y);
	xx=xx*xx, yy=yy*yy;
	return sqrtl(xx+yy);
}

signed main() {
	File("triangle");
	srand(time(0));
    read(n);
	int pd = 1;
	for(int i = 1; i <= n; ++i)
		a[i]=i, read(pt[i].x), read(pt[i].y), pd&=(pt[i].y == 0);
	ans=(long double) 30000000000.0;
	if(n <= 100) {
		for(int i = 1; i <= n; ++i)
			for(int j = i+1; j <= n; ++j)
				for(int k = j+1; k <= n; ++k)
					ans=min(ans, dis(i,j)+dis(i,k)+dis(j,k));
		printf("%.14Lf\n", ans);
		return 0;
	}
	else {
		if(pd) {
			sort(pt+1, pt+1+n, comp);
			for(int i = 3; i <= n; ++i)
				ans=min(ans, (long double) 2.0*(pt[i].x-pt[i-2].x));
			printf("%.14Lf\n", ans);
			return 0;
		}
		else {
			sort(pt+1, pt+1+n, comp);
			pd=1;
			for(int i = 1; i <= n; i+=2)
				pd&=(pt[i].x == pt[i+1].x && pt[i].y == pt[i+1].y);
			if(pd) {
				for(int i = 3; i <= n; ++i)
					for(int j = i-2, gs=100; j >= 1 && gs >= 1; j-=2, --gs)
						ans=min(ans, (long double) 2.0*dis(i,j));
				sort(pt+1, pt+1+n, compp);
				for(int i = 3; i <= n; ++i)
					for(int j = i-2, gs=100; j >= 1 && gs >= 1; j-=2, --gs)
						ans=min(ans, (long double) 2.0*dis(i,j));
				int tot = 0;
				for(int i = 1; i <= n; i+=2)
					a[++tot]=i;
				for(int o = 1; o <= 5; ++o) {
					random_shuffle(a+1, a+1+tot);
					for(int i = 2; i <= n; ++i)
						ans=min(ans, (long double) 2.0*dis(a[i], a[i-1]));
				}
				printf("%.14Lf\n", ans);
				return 0;
			}
			else {
				// debug("?!?\n");
				for(int i = 3; i <= n; ++i)
					ans=min(ans, dis(i,i-1)+dis(i,i-2)+dis(i-1,i-2));
				sort(pt+1, pt+1+n, compp);
				for(int i = 3; i <= n; ++i)
					ans=min(ans, dis(i,i-1)+dis(i,i-2)+dis(i-1,i-2));
				for(int o = 1; o <= 200; ++o) {
					random_shuffle(a+1, a+1+n);
					for(int i = 3; i <= n; ++i)
						ans=min(ans, dis(a[i], a[i-1])+dis(a[i], a[i-2])+dis(a[i-1], a[i-2]));
				}
				printf("%.14Lf\n", ans);
				return 0;
			}
		}
	}
	return 0;
}