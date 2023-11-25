#include <bits/stdc++.h>
using namespace std;
int t, dd, l, r;

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
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    read(dd), read(t);
    while(t--) {
        read(l), read(r);
        if(dd == 1) {
            if(l == r) {
                int o = (int) sqrt(l);
                if(o*o == l) {
                    puts("1");
                    continue;
                }
            }
            puts("2");
            continue;
        }
    }
	return 0;
}