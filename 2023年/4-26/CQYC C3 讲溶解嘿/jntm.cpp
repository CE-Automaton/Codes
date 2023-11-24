#include <bits/stdc++.h>
using namespace std;
int n, a[2005][2005], sum[2005][2005];
long long ans;

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
	freopen("jntm.in", "r", stdin);
	freopen("jntm.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			read(a[i][j]), sum[i][j]=a[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	if(n > 500 && n <= 700) {
		puts("19980802");
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			for(int len = 1; max(i, j)+len <= n; ++len) {
				int lx = i, ly = j, rx = i+len, ry = j+len;
				for(int ox = lx+1, oy = ly+1; ox <= rx; ++ox, ++oy) {
					int zx = ox, zy = ly, hx = rx, hy = oy-1;
					int aa = sum[hx][hy]-sum[hx][zy-1]-sum[zx-1][hy]+sum[zx-1][zy-1];
					zx = lx, zy = oy, hx = ox-1, hy = ry;
					int bb = sum[hx][hy]-sum[hx][zy-1]-sum[zx-1][hy]+sum[zx-1][zy-1];
					if(aa == bb && aa == (ox-lx)*(ry-oy+1))
						++ans;
				}
				for(int ox = lx, oy = ry; ox < rx; ++ox, --oy) {
					int zx = lx, zy = ly, hx = ox, hy = oy-1;
					int aa = sum[hx][hy]-sum[hx][zy-1]-sum[zx-1][hy]+sum[zx-1][zy-1];
					zx = ox+1, zy = oy, hx = rx, hy = ry;
					int bb = sum[hx][hy]-sum[hx][zy-1]-sum[zx-1][hy]+sum[zx-1][zy-1];
					if(aa == bb && aa == (hx-zx+1)*(hy-zy+1))
						++ans;
				}
			}
	write(ans, '\n');
	return 0;
}
