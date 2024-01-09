#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, k, f[3][N];

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
void cf(int y, int x, int to) {
	for(int i = 1; i <= n; ++i)
		f[to][f[x][i]]=f[y][i];
}

signed main() {
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(f[0][i]);
	for(int i = 1; i <= n; ++i)
		read(f[1][i]);
	for(int i = 2; i <= k; ++i)
		if(i%3 == 0)
			cf(2, 1, 0);
		else
			if(i%3 == 1)
				cf(0, 2, 1);
			else
				cf(1, 0, 2);
	for(int i = 1; i <= n; ++i)
		write(f[k%3][i], ' ');
	return 0;
}
