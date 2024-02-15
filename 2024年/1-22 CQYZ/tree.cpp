#include <bits/stdc++.h>
#define mod 1000000007
#define inv2 500000004
#define File(xxx) freopen(xxx".in", "r", stdin), freopen(xxx".out", "w", stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, m, L, R, u, v, d, w[N], rt, siz[N], mx[N], sum, vis[N], dep[N], tr[N], 
ww[N], www[N], top[N], ans, mmx, up[N], summ;
vector <int> to[N];

template <typename T> void debug(T x) { cerr<<x; }
template <typename T, typename ..._T> void debug(T x, _T ...p) { cerr<<x<<' ', debug(p...); }
template <typename T> void read(T& x) {
    x = 0; char c = getchar(); int f = 0;
    while(c < '0' || c > '9') f|=(c == '-'), c=getchar();
    while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
    x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
    if(x < 0) putchar('-'), x=-x;
    do put[++lne]=x%10, x/=10; while(x);
    while(lne) putchar(put[lne]^48), --lne;
    putchar(ch);
}
int upd(int x) {
    return (x >= mod ? x-mod : x);
}
void add(int x, int w) {
    while(x <= mmx) tr[x]+=w, x+=(x&(-x));
}
int ask(int x, int ret = 0) {
    x=min(x, mmx);
    while(x >= 1) ret+=tr[x], x-=(x&(-x));
    return ret;
}
void getrt(int x, int fa) {
    siz[x]=1, mx[x]=0;
    for(int y : to[x])
        if(y != fa && !vis[y]) 
            getrt(y, x), siz[x]+=siz[y], mx[x]=(siz[y] > mx[x] ? siz[y] : mx[x]);
    mx[x]=(sum-siz[x] > mx[x] ? sum-siz[x] : mx[x]);
    if(mx[x] <= mx[rt])
        rt=x;
}
void getdep(int x, int fa) {
    siz[x]=1;
    dep[x]=dep[fa]+1;
    mmx = max(mmx, dep[x]);
    // debug(x, dep[x], "?\n");
    for(int y : to[x])
        if(y != fa && !vis[y]) 
            getdep(y, x), siz[x]+=siz[y];
}
void get(int x, int fa) {
    add(dep[x], 1);
    // debug(x, dep[x], "?\n");
    for(int y : to[x])
        if(y != fa && !vis[y]) 
            get(y, x);
}
void clen(int x, int fa) {
    add(dep[x], -1);
    for(int y : to[x])
        if(y != fa && !vis[y]) 
            clen(y, x);
}
int upup(int x, int fa) {
    int l = L-dep[x]+1, r = R-dep[x]+1, ret = 0;
    if(r >= 1) {
        int op = ask(r)-(l-1 <= 0 ? 0 : ask(l-1));
        // debug(zhan[i], "!", x, dep[zhan[i]], l, r, op, ask(2), "!?\n");
        ret=op;
        summ=upd(summ+op);
    }
    for(int y : to[x])
        if(y != fa && !vis[y]) 
            ret=upd(ret+upup(y, x));
    www[x]=upd(www[x]+ret);
    return ret;
}
void dfs(int x) {
    // debug("rt:", x, "!?!?\n");
    vis[x]=dep[x]=1;
    mmx=1;
    for(int y : to[x])
        if(!vis[y]) 
            getdep(y, x);
    for(int y : to[x])
        if(!vis[y]) 
            get(y, x);
    summ = ask(R)-ask(L-1);
    add(1, 1);
    for(int y : to[x])
        if(!vis[y]) {
            clen(y, x);
            sum=upup(y, x);
            get(y, x);
        }
    for(int y : to[x])
        if(!vis[y]) 
            clen(y, x);
    add(1, -1);
    www[x]=upd(www[x]+1LL*summ*inv2%mod);
    // debug(summ, "az\n");
    for(int y : to[x])
        if(!vis[y]) {
            rt=0, sum=siz[y];
            getrt(y, x);
            dfs(rt);
        }
}
void dfss(int x, int fa, int ss) {
    dep[x]=dep[fa]+1;
    up[x]=fa;
    int az = upd(www[x]+ss);
    www[x]=az;
    siz[x]=1, mx[x]=0;
    for(int y : to[x])
        if(y != fa)
            dfss(y, x, az), siz[x]+=siz[y], mx[x]=(siz[y] > siz[mx[x]] ? y : mx[x]);
}
void dfsss(int x, int fa, int tp) {
    top[x]=tp;
    if(mx[x])
        dfsss(mx[x], x, tp);
    for(int y : to[x])
        if(y != fa && y != mx[x])
            dfsss(y, x, y);
}
int lca(int x, int y) {
    while(top[x]^top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x=up[top[x]];
    }
    return (dep[x] > dep[y] ? y : x);
}

signed main() {
    read(n), read(m), read(L), read(R);
    for(int i = 1; i <= n; ++i)
        read(w[i]);
    for(int i = 2; i <= n; ++i)
        read(u), to[i].push_back(u), to[u].push_back(i);
    rt=0, mx[0]=n+1, sum=n;
    getrt(1, 0);
    dfs(rt);
    // debug(ask(n), "!?\n");
    for(int i = 1; i <= n; ++i)
        /*write(www[i], ' '), */www[i]=upd(www[i]+(L == 1)), ans=upd(ans+1LL*w[i]*www[i]%mod);
    dep[0]=0;
    www[0]=0;
    siz[0]=0;
    dfss(1, 0, 0);
    dfsss(1, 0, 1);
    // write(ans, '\n');
    for(int i = 1; i <= m; ++i) {
        read(u), read(v), read(d);
        int lc = lca(u, v);
        // debug(u, v, lc, "!?\n");
        ans=upd(ans+1LL*upd(upd(upd(www[u]+www[v])-www[lc]+mod)-www[up[lc]]+mod)*d%mod);
        write(ans, '\n');
    }
    return 0;
}