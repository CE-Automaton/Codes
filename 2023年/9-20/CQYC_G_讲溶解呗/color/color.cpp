#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e3+5;
int t, n, m, k, k0, r[N][N], d[N][N], ans[N][N], u, v, uu, vv, pp, visr[N][N], visd[N][N];

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
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
    read(t);
    while(t--) {
        read(n), read(m), read(k), read(k0);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                r[i][j]=d[i][j]=-1, visr[i][j]=visd[i][j]=0;
        for(int i = 1; i <= k; ++i) {
            read(u), read(v), read(uu), read(vv), read(pp);
            if(u > uu || (u == uu && v > vv))
                swap(u, uu), swap(v, vv);
            if(u == uu)
                r[u][v]=pp;
            else
                d[u][v]=pp;
        }
        for(int i = 1; i <= n-1; ++i)
            for(int j = 1; j <= m-1; ++j)
                if(r[i][j] != -1 && r[i+1][j] != -1 && d[i][j] != -1 && d[i][j+1] != -1) {
                    int gs[2];
                    gs[0]=gs[1]=0;
                    ++gs[r[i][j]];
                    ++gs[r[i+1][j]];
                    ++gs[d[i][j]];
                    ++gs[d[i][j+1]];
                    if(gs[0] == gs[1] || gs[0] == 0 || gs[1] == 0)
                        visr[i][j]=visr[i+1][j]=visd[i][j]=visd[i][j+1]=1;
                }
        for(int i = 1; i <= n-1; ++i)
            for(int j = 1; j <= m-1; ++j)
                if(r[i][j] != -1 && r[i+1][j] != -1 && d[i][j] != -1 && d[i][j+1] != -1) {
                    int gs[2];
                    gs[0]=gs[1]=0;
                    ++gs[r[i][j]];
                    ++gs[r[i+1][j]];
                    ++gs[d[i][j]];
                    ++gs[d[i][j+1]];
                    if(gs[0]%2 || gs[1]%2) {
                        if(visr[i][j] == 2 || visr[i+1][j] == 2 || visd[i][j] == 2 || visd[i][j+1] == 2) {
                            if(visr[i][j] != 2) 
                                visr[i][j]=1;
                            if(visr[i+1][j] != 2) 
                                visr[i+1][j]=1;
                            if(visd[i][j] != 2) 
                                visd[i][j]=1;
                            if(visd[i][j+1] != 2) 
                                visd[i][j+1]=1;
                            continue;
                        }
                        if(visr[i][j] == 0) 
                            visr[i][j]=2;
                        else
                            if(visr[i+1][j] == 0) 
                                visr[i+1][j]=2;
                            else
                                if(visd[i][j] == 0) 
                                    visd[i][j]=2;
                                else
                                    if(visd[i][j+1] == 0) 
                                        visd[i][j+1]=2;
                        if(visr[i][j] != 2) 
                            visr[i][j]=1;
                        if(visr[i+1][j] != 2) 
                            visr[i+1][j]=1;
                        if(visd[i][j] != 2) 
                            visd[i][j]=1;
                        if(visd[i][j+1] != 2) 
                            visd[i][j+1]=1;
                    }
                }
        ans[1][1]=0;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                if(r[i][j] != -1) {
                    if(visr[i][j] == 2)
                        ans[i][j+1]=((ans[i][j]^r[i][j])^1);
                    else
                        ans[i][j+1]=(ans[i][j]^r[i][j]);
                }
                if(d[i][j] != -1) {
                    if(visd[i][j] == 2)
                        ans[i+1][j]=((ans[i][j]^d[i][j])^1);
                    else
                        ans[i+1][j]=(ans[i][j]^d[i][j]);
                }
            }
        for(int i = 1; i <= n; ++i, putchar('\n'))
            for(int j = 1; j <= m; ++j)
                putchar(ans[i][j]+'0');
    }
	return 0;
}