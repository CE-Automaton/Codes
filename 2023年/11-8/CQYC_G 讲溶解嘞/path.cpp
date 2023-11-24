#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 2e5+5;
int n, q, u, v, a[N], dep[N], dfn[N], tt[N], siz[N], top[N], up[N], mxs[N], cnt;
vector <int> to[N];
struct node {
    int w, mx, mn;
};
node upup(node ls, node rs) {
    node ret;
    ret.w=max(ls.mx-rs.mn, max(ls.w, rs.w));
    ret.mn=min(ls.mn, rs.mn);
    ret.mx=max(ls.mx, rs.mx);
    return ret;
}
struct tree {
    node tr[N<<2];
    #define ls (k<<1)
    #define rs (ls|1)
    void built(int k, int l, int r) {
        if(l == r) {
            tr[k].mn=tr[k].mx=a[tt[l]];
            tr[k].w=0;
            return ;
        }
        int mid = ((l+r)>>1);
        built(ls, l, mid);
        built(rs, mid+1, r);
        tr[k]=upup(tr[ls], tr[rs]);
    }
    node ask(int k, int l, int r, int lq, int rq) {
        if(lq <= l && r <= rq)
            return tr[k];
        int mid = ((l+r)>>1);
        if(lq <= mid && mid+1 <= rq)
            return upup(ask(ls, l, mid, lq, rq), ask(rs, mid+1, r, lq, rq));
        if(lq <= mid)
            return ask(ls, l, mid, lq, rq);
        return ask(rs, mid+1, r, lq, rq);
    }
}A;

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
void dfs(int x, int fa) {
    siz[x]=1;
    dep[x]=dep[fa]+1;
    up[x]=fa;
    for(int y : to[x])
        if(y != fa) {
            dfs(y, x);
            siz[x]+=siz[y];
            mxs[x]=(siz[y] > siz[mxs[x]] ? y : mxs[x]);
        }
}
void dfs2(int x, int fa, int tp) {
    dfn[x]=++cnt;
    tt[cnt]=x;
    top[x]=tp;
    if(mxs[x])
        dfs2(mxs[x], x, tp);
    for(int y : to[x])
        if(y != fa && y != mxs[x])
            dfs2(y, x, y);
}

signed main() {
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
	read(n), read(q);
    for(int i = 2; i <= n; ++i)
        read(u), read(v), to[u].push_back(v), to[v].push_back(u);
    dfs(1, 0);
    dfs2(1, 0, 1);
    for(int i = 1; i <= n; ++i)
        read(a[i]);
    A.built(1, 1, n);
    for(int i = 1; i <= q; ++i) {
        read(u), read(v);
        node ans = {0, -inf, inf};
        int gs = 0;
        while(top[u] != top[v]) 
            ans=upup(A.ask(1, 1, n, dfn[top[u]], dfn[u]), ans), u=up[top[u]];
        ans=upup(A.ask(1, 1, n, dfn[v], dfn[u]), ans);
        write(ans.w, '\n');
    }
	return 0;
}
