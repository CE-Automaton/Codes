#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e5+5;
int n, a[N];

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
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    read(n);
    for(int i = 1; i <= n; ++i)
        read(a[i]);
    sort(a+1, a+1+n);
    for(int r = n; r >= 1; --r) {
        int gs = 1, rr = r;
        while(r-1 >= 1 && a[r-1] == a[rr]) --r, gs^=1;
        if(r == 1 && gs == 0) {
            puts("Bob");
            return 0;
        }
        if(gs == 1) {
            puts("Alice");
            return 0;
        }
    }
	return 0;
}