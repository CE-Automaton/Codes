#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a1, b1, a2, b2, q, ans[1000006];

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
    freopen("snow.in", "r", stdin);
    freopen("snow.out", "w", stdout);
    read(a1), read(b1), read(a2), read(b2), read(n);
    ans[0]=0;
    int l = 0, r = 1;
    for(int i = 1; i <= 1000000; ++i) {
        if((i-1)%(a1+b1)+1 <= a1)
            ++r;
        if((i-1)%(a2+b2)+1 <= a2 && l+1 < r)
            ++l;
        ans[i]=l;
    }
    for(int i = 1; i <= n; ++i) {
        read(q);
        if(q <= 1000000)
            write(ans[q]), putchar('\n');
        else
            write(max(min(q/(a1+b1)*a1+min((q-1)%(a1+b1)+1, a1)-1, q/(a2+b2)*a2+min((q-1)%(a2+b2)+1, a2)), 0LL)), putchar('\n');
    }
	return 0;
}