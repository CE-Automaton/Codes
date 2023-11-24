#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k, a[1000005];

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
    freopen("qwq.in", "r", stdin);
    freopen("qwq.out", "w", stdout);
    read(n), read(k);
    a[1]=1;
    int l = 2, r = n;
    while(l <= r) {
        a[l]=a[r]=a[l-1]+k;
        ++l, --r;
    }
    for(int i = 1; i <= n; ++i)
        write(a[i]), putchar(' ');
	return 0;
}