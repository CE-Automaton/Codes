#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int t, n, m, gp, dmg, k;
char ss[6];

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
void lnee() {
	putchar('+');
	for(int i = 1; i <= m; ++i)
		putchar('-');
	putchar('+');
	putchar('\n');
}

signed main() {
	read(t);
	for(int i = 0; i <= 4; ++i)
		ss[i]=(char) 'A'+i;
	while(t--) {
		read(n), read(m), read(gp), read(dmg);
		lnee();
		k=(gp+m-1)/m;
		if(k == 1) {
			for(int i = 1; i <= n; ++i) {
				putchar('|');
				for(int j = 1; j <= gp-dmg; ++j)
					putchar('A');
				for(int j = gp-dmg+1; j <= gp; ++j)
					putchar('.');
				for(int j = gp+1; j <= m; ++j)
					putchar(' ');
				putchar('|');
				putchar('\n');
			}
			lnee();
			continue;
		}
		int now = (k-1)%5, lst = gp%m;
		lst=(lst == 0 ? m : lst);
		if(dmg <= lst) {
			for(int i = 1; i <= n; ++i) {
				putchar('|');
				for(int j = 1; j <= lst-dmg; ++j)
					putchar(ss[now]);
				for(int j = lst-dmg+1; j <= lst; ++j)
					putchar('.');
				for(int j = lst+1; j <= m; ++j)
					putchar(ss[(now+4)%5]);
				putchar('|');
				putchar('\n');
			}
		}
		else {
			if(dmg >= m) {
				for(int i = 1; i <= n; ++i) {
					putchar('|');
					for(int j = 1; j <= m; ++j)
						putchar('.');
					putchar('|');
					putchar('\n');
				}
			}
			else {
				for(int i = 1; i <= n; ++i) {
					putchar('|');
					for(int j = 1; j <= lst; ++j)
						putchar('.');
					for(int j = 1; j <= m-dmg; ++j)
						putchar(ss[(now+4)%5]);
					for(int j = 1; j <= dmg-lst; ++j)
						putchar('.');
					putchar('|');
					putchar('\n');
				}
			}
		}
		lnee();
	}
	return 0;
}