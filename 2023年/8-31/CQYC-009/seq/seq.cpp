#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e5+5;
int n, m, f, a[N], xx, yy, opt, l, r, lstans;

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
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	read(n), read(m), read(f);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int j = 1; j <= m; ++j) {
		read(opt);
		if(opt == 1) {
			read(l), read(r), read(xx);
			if(f)
				l^=lstans, r^=lstans, xx^=lstans;
			for(int i = l; i <= r; ++i)
				a[i]=xx;
		}
		else {
			read(xx), read(yy);
			if(f)
				xx^=lstans, yy^=lstans;
			int lsx = 0, lsy = 0, ans = mod;
			for(int i = 1; i <= n; ++i) {
				if(a[i] == xx) {
					if(lsy)
						ans=min(ans, i-lsy);
					lsx=i;
				}
				if(a[i] == yy) {
					if(lsx)
						ans=min(ans, i-lsx);
					lsy=i;
				}
			}
			if(ans != mod)
				write(ans, '\n'), lstans = ans;
			else
				puts("-1"), lstans = 0;
		}
	}
	return 0;
}
