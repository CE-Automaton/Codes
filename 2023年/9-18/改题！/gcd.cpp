#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+5, M = 1e6+5;
int n, k, a[N], pd[M], zhan[N], tot, to[N], ans;

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
void dfs1(int x, int s) {
    pd[s]=1;
    if(x == tot+1)
        return ;
    dfs1(x+1, s);
    for(int i = 1; i <= zhan[x]; ++i)
        s*=to[x], dfs1(x+1, s);
}
void dfs2(int x, int s) {
    if(pd[s])
        ans=max(ans, s);
    if(x == tot+1)
        return ;
    dfs2(x+1, s);
    for(int i = 1; i <= zhan[x]; ++i)
        s*=to[x], dfs2(x+1, s);
}

signed main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
	read(n), read(k);
    ans=1;
    for(int i = 1; i <= n; ++i)
        read(a[i]);
    for(int i = k+1; i <= n; ++i) {
        tot=0;
        for(int j = 2; 1LL*j*j <= a[i-k]; ++j)
            if(a[i-k]%j == 0) {
                to[++tot]=j;
                zhan[tot]=0;
                while(a[i-k]%j == 0) 
                    ++zhan[tot], a[i-k]/=j;
            }
        if(a[i-k] != 1)
			to[++tot]=a[i-k], zhan[tot]=1;
        dfs1(1, 1);
        tot=0;
        int now = a[i];
        for(int j = 2; 1LL*j*j <= now; ++j)
            if(now%j == 0) {
                to[++tot]=j;
                zhan[tot]=0;
                while(now%j == 0) 
                    ++zhan[tot], now/=j;
            }
        if(now != 1)
			to[++tot]=now, zhan[tot]=1;
        dfs2(1, 1);
    }
    write(ans, '\n');
	return 0;
}
