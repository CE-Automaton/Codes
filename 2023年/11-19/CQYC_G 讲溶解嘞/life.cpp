#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int M = 1e6+5, N = 3e2+5;
int n, m, jc[M], inv[M], inc[M], dp[2][N][N], sm[N], ans;

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
int upd(int x) {
    return (x >= mod ? x-mod : x);
}
int A(int x, int y) {
    return 1LL*jc[x]*inc[x-y]%mod;
}

signed main() {
	freopen("life.in", "r", stdin);
	freopen("life.out", "w", stdout);
	read(n), read(m);
    dp[0][0][0]=1;
    int now = 0;
    for(int i = 1; i <= n; ++i) {
        now^=1;
        for(int j = 0; j <= min(m, n); ++j) {
            dp[now][j][0]=0;
            for(int l = 1; l <= n; ++l)
                dp[now][j][l]=dp[now^1][j][l-1];//加入i
        }
        for(int j = min(m, n)-1; j >= 0; --j) {
            sm[n+1]=0;
            for(int l = n; l >= 1; --l) 
                sm[l]=upd(sm[l+1]+dp[now][j][l]);
            for(int l = 0; l <= n; ++l)
                dp[now][j+1][l]=upd(dp[now][j+1][l]+sm[l+1]);
        }
    }
    jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
    for(int i = 2; i <= m; ++i)
        inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
        jc[i]=1LL*i*jc[i-1]%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
    for(int i = 1; i <= min(m, n); ++i)
        ans=upd(ans+1LL*dp[now][i][0]*A(m, i)%mod);
    write(ans, '\n');
	return 0;
}