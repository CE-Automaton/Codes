#include <bits/stdc++.h>
using namespace std;
int n, a[2005][2005];

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
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			read(a[i][j]);
	if(n <= 500) {
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				for(int k = 1; k <= n; ++k)
					if(a[a[i][j]][k] != a[i][a[j][k]]) {
						puts("NO");
						return 0;
					}
		puts("YES");
		return 0;
	}
	srand(time(0));
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			for(int o = 1; 1LL*i*j*o <= 200000000LL; ++o) {
				int k = (rand()%2 ? rand()%n : 1LL*rand()*rand()%n)+1;
				if(a[a[i][j]][k] != a[i][a[j][k]]) {
					puts("NO");
					return 0;
				}
			}
	puts("YES");
	return 0;
}
