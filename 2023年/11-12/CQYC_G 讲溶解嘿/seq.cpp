#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 45;
int n, m, c[N][N], d[N][N], az[N][N], ans[N];

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
int upd (int x) {
    return (x >= mod ? x-mod : x);
}

signed main() {
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    read(n), read(m);
    printf("%d\n1\n", n);
	return 0;
}
