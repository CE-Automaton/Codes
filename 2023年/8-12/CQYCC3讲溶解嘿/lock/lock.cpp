#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int t, n, a[7][N];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}

signed main() {
	freopen("lock.in", "r", stdin);
	freopen("lock.out", "w", stdout);
	read(t), read(n);
	while(t--) {
		for(int i = 1; i <= 4; ++i)
			for(int j = 1; j <= n; ++j)
				read(a[i][j]), a[i][j+n]=a[i][j];
		int ans = 0;
		for(int i = 1; i <= n && ans == 0; ++i)
			for(int j = 1; j <= n && ans == 0; ++j)
				for(int k = 1; k <= n && ans == 0; ++k)
					for(int l = 1; l <= n && ans == 0; ++l) {
						int pd = 1;
						for(int o = 1; o <= n; ++o)
							if(a[1][i]+a[2][j]+a[3][k]+a[4][l] != a[1][i+o-1]+a[2][j+o-1]+a[3][k+o-1]+a[4][l+o-1]) {
								pd=0;
								break;
							}
						ans|=pd;
					}
		write(ans);
	}
	return 0;
}
