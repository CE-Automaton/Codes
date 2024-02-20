#include <bits/stdc++.h>
#define mod 1000000007
#define inv2 (mod-mod/2)
#define inf 0x3f3f3f3f
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2.5e3+5;
int n, m, t, dp[N][N], u, v, w, tot;
LL ans;
struct qwq {
    int u, v;
};
vector <qwq> to[N];
struct az {
    int a, b, l, r;
}zhan[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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

signed main() {
    File("a");
    read(n), read(m), read(t);
    for(int i = 1; i <= m; ++i)
        read(u), read(v), read(w), to[u].push_back(qwq {v, w}), to[v].push_back(qwq {u, w});
    memset(dp, 0x3f, sizeof dp);
    // debug(dp[0][0], "!!!\n");
    dp[0][1]=0;
    for(int i = 0; i < n; ++i) 
        for(int j = 1; j <= n; ++j)
            if(dp[i][j] != inf)
                for(qwq k : to[j])
                    if(dp[i][j]+k.v < dp[i+1][k.u])
                        dp[i+1][k.u]=dp[i][j]+k.v;
    for(int i = 2; i <= n; ++i) {
        tot=0;
        // debug(i, ":\n");
        for(int j = n; j >= 1; --j) 
            if(dp[j][i] != inf) {
                // debug(j, dp[j][i], "\n");
                while(tot && ceil(1.0*(dp[j][i]-zhan[tot].b)/(zhan[tot].a-j)) <= zhan[tot].l) --tot;
                if(tot) {
                    int xx = (dp[j][i]-zhan[tot].b)/(zhan[tot].a-j);
                    if(xx >= t) {
                        zhan[tot].r=t;
                        continue;
                    }
                    ++tot, zhan[tot]=az {j, dp[j][i], xx+1, t}, zhan[tot-1].r=xx;
                }
                else
                    zhan[++tot]=az {j, dp[j][i], 0, t};
            }
        // debug("end:\n");
        // for(int j = 1; j <= tot; ++j)
        //     debug(zhan[j].a, zhan[j].b, zhan[j].l, zhan[j].r, "!?!?\n");
        for(int j = 1; j <= tot; ++j)
            ans=upd(ans+upd(1LL*zhan[j].b*(zhan[j].r-zhan[j].l+1)%mod+1LL*zhan[j].a*upd(zhan[j].r+zhan[j].l)%mod*(zhan[j].r-zhan[j].l+1)%mod*inv2%mod));
    }
    write(ans, '\n');
	return 0;
}