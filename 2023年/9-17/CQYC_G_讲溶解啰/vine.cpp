#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e5+5;
__int128 t, n, m, xx, yy;

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
int ksm(int x, int y, int ret = 1) {
    while(y) {
        if(y&1)
            ret=1LL*ret*x%mod;
        x=1LL*x*x%mod;
        y=(y>>1);
    }
    return ret;
}

signed main() {
    freopen("vine.in", "r", stdin);
    freopen("vine.out", "w", stdout);
    read(t); 
    while(t--) {
        read(n), read(m);
        for(int i = 1; i <= m; ++i)
            read(xx), read(yy);
        if(n%2 == 0) 
            write(((__int128) 1LL*n/2*(n+n/2+1)*2)%mod, '\n');
        else
            write(((__int128) n/2*(n+(n+1)/2+1)*2+n+1)%mod, '\n');
    }
	return 0;
}