#include <bits/stdc++.h>
#define inf 1000000000000000000LL
using namespace std ;
const int N = 3e3+5 ;
int n, k;
int a[N], b[N];
long long f[2][N][N], ans=inf;

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
    read(n), read(k);
    for(int i = 1; i <= n; ++i)
        read(a[i]) ;
    for(int i = 1; i <= n; ++i) 
        read(b[i]);
    int now = 0;
    for(int o = 1; o <= 2*k; ++o) {
        now^=1;
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= n; ++j)
                f[now][i][j]=inf;
        for(int l = 0; l <= n; ++l)
            for(int r = 0; r <= n; ++r)
                if(now) for(int j=l+1; j <= n; ++j)
                    f[now][j][r] = min(f[now][j][r],f[now^1][l][r]+a[j]);
                else for(int j = max(r+1, l); j <= n; ++j)
                    f[now][l][j] = min(f[now][l][j],f[now^1][l][r]+b[j]);
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            ans=min(ans,f[now][i][j]);
    write(ans, '\n');
    return 0 ;
}