#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, u, v, dep[N], siz[N], mxson[N], dfn[N], top[N], don[N], cnt, opt, up[N];
vector <int> to[N];
struct pnt {
    int sum/*前缀轻儿子连续段为0的答案*/, col/*颜色*/, tt/*dfn对应的点*/;
}t[N];
struct node {
    int sum[2]/*前缀颜色均为0/1的sum+1之和*/, pd/*判断是否全颜色相等*/, col/*最左边的颜色*/, dwn[2]/*颜色为0/1时最下面的点*/;
};
struct tree {
    int lzy[N<<2];
    node tr[N<<2];
    #define ls (k<<1)
    #define rs ((k<<1)|1)
    node upup(node lss, node rss) {
        node ret;
        if(dep[lss.dwn[0]] > dep[rss.dwn[0]])
            ret.dwn[0]=lss.dwn[0];
        else
            ret.dwn[0]=rss.dwn[0];
        if(dep[lss.dwn[1]] > dep[rss.dwn[1]])
            ret.dwn[1]=lss.dwn[1];
        else
            ret.dwn[1]=rss.dwn[1];
        ret.col=lss.col;
        if(lss.pd) {
            if(rss.pd) {
                if(lss.col == rss.col)
                    ret.sum[lss.col]=lss.sum[lss.col]+rss.sum[lss.col],
                    ret.sum[lss.col^1]=0,  
                    ret.pd=1;
                else
                    ret.sum[lss.col]=lss.sum[lss.col],
                    ret.sum[lss.col^1]=0, 
                    ret.pd=0;
            }
            else 
                ret.sum[lss.col]=lss.sum[lss.col],
                ret.sum[lss.col^1]=0, ret.pd=0;
        }
        else
            ret.sum[lss.col]=lss.sum[lss.col],
            ret.sum[lss.col^1]=0, ret.pd=0;
        return ret;
    }
    void azz(int k, int l) {
        tr[k].dwn[0]=tr[k].dwn[1]=0;
        tr[k].sum[t[l].col]=t[l].sum+1;
        tr[k].sum[t[l].col^1]=0;
        tr[k].pd=1;
        tr[k].col=t[l].col;
        if(dep[tr[k].dwn[t[l].col]] < dep[t[l].tt])
            tr[k].dwn[t[l].col]=t[l].tt;
    }
    void down(int k, int l, int mid, int r) {
        if(lzy[k] == 1) {
            if(l == mid)
                t[l].col^=1, azz(ls, l);
            else {
                swap(tr[ls].sum[0], tr[ls].sum[1]);
                swap(tr[ls].dwn[0], tr[ls].dwn[1]);
                tr[ls].col^=1;
                lzy[ls]^=1;
            }
            if(mid+1 == r)
                t[r].col^=1, azz(rs, r);
            else {
                swap(tr[rs].sum[0], tr[rs].sum[1]);
                swap(tr[rs].dwn[0], tr[rs].dwn[1]);
                tr[rs].col^=1;
                lzy[rs]^=1;
            }
            tr[k]=upup(tr[ls], tr[rs]);
            lzy[k]=0;
        }
    }
    void built(int k, int l, int r) {
        tr[k].dwn[0]=tr[k].dwn[1]=0;
        if(l == r) {
            azz(k, l);
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
        down(k, l, mid, r);
        node ret;
        if(lq <= mid && mid+1 <= rq)
            ret=upup(ask(ls, l, mid, lq, rq), ask(rs, mid+1, r, lq, rq));
        else
            if(lq <= mid)
                ret=ask(ls, l, mid, lq, rq);
            else
                if(mid+1 <= rq)
                    ret=ask(rs, mid+1, r, lq, rq);
        tr[k]=upup(tr[ls], tr[rs]);
        return ret;
    }
    void updt(int k, int l, int r, int lq, int rq) {
        // cout<<l<<" "<<r<<"?\n";
        if(lq <= l && r <= rq) {
            if(l == r) 
                t[l].col^=1, azz(k, l);
            else {
                swap(tr[k].sum[0], tr[k].sum[1]);
                swap(tr[k].dwn[0], tr[k].dwn[1]);
                tr[k].col^=1;
                lzy[k]^=1;
            }
            return ;
        }
        int mid = ((l+r)>>1);
        down(k, l, mid, r);
        if(lq <= mid)
            updt(ls, l, mid, lq, rq);
        if(mid+1 <= rq)
            updt(rs, mid+1, r, lq, rq);
        tr[k]=upup(tr[ls], tr[rs]);
    }
    void updtt(int k, int l, int r, int to, int w) {
        if(l == r) {
            t[l].sum+=w, azz(k, l);
            return ;
        }
        int mid = ((l+r)>>1);
        down(k, l, mid, r);
        if(to <= mid)
            updtt(ls, l, mid, to, w);
        else
            updtt(rs, mid+1, r, to, w);
        tr[k]=upup(tr[ls], tr[rs]);
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
    up[x]=fa;
    dep[x]=dep[fa]+1;
    siz[x]=1;
    for(int y : to[x]) 
        if(y != fa) {
            dfs(y, x);
            siz[x]+=siz[y];
            if(siz[y] > siz[mxson[x]])
                mxson[x]=y;
        }
}
void dfs2(int x, int fa, int tp) {
    top[x]=tp;
    don[tp]=x;
    dfn[x]=++cnt;
    t[cnt].tt=x;
    t[cnt].sum=t[cnt].col=0;
    if(mxson[x])
        dfs2(mxson[x], x, tp);
    for(int y : to[x])
        if(y != fa && y != mxson[x])
            dfs2(y, x, y), t[dfn[x]].sum+=siz[y];
}

signed main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    read(n), read(m);
    for(int i = 2; i <= n; ++i)
        read(u), read(v), to[u].push_back(v), to[v].push_back(u);
    dfs(1, 0);
    t[0].tt=0;
    t[0].sum=t[0].col=0;
    dfs2(1, 0, 1);
    A.built(1, 1, n);
    for(int i = 1; i <= m; ++i) {
        read(opt), read(u);
        if(opt == 1) {
            read(v);
            while(u) {
                // cout<<up[top[u]]<<"-"<<A.ask(1, 1, n, dfn[top[u]], dfn[u]).sum[0]<<"+";
                if(up[top[u]] != 0) 
                    A.updtt(1, 1, n, dfn[up[top[u]]], -A.ask(1, 1, n, dfn[top[u]], dfn[don[top[u]]]).sum[0]);
                A.updt(1, 1, n, dfn[top[u]], dfn[u]);
                // cout<<A.ask(1, 1, n, dfn[top[u]], dfn[u]).sum[0]<<"!\n";
                if(up[top[u]] != 0) 
                    A.updtt(1, 1, n, dfn[up[top[u]]], A.ask(1, 1, n, dfn[top[u]], dfn[don[top[u]]]).sum[0]);
                u=up[top[u]];
            }
            u=v;
            while(u) {
                // cout<<up[top[u]]<<"-"<<A.ask(1, 1, n, dfn[top[u]], dfn[u]).sum[0]<<"+";
                if(up[top[u]] != 0) 
                    A.updtt(1, 1, n, dfn[up[top[u]]], -A.ask(1, 1, n, dfn[top[u]], dfn[don[top[u]]]).sum[0]);
                A.updt(1, 1, n, dfn[top[u]], dfn[u]);
                // cout<<A.ask(1, 1, n, dfn[top[u]], dfn[u]).sum[0]<<"!\n";
                if(up[top[u]] != 0) 
                    A.updtt(1, 1, n, dfn[up[top[u]]], A.ask(1, 1, n, dfn[top[u]], dfn[don[top[u]]]).sum[0]);
                u=up[top[u]];
            }
        }
        else {
            int ner = 0, ans = 0;
            while(u) {
                node aa = A.ask(1, 1, n, dfn[top[u]], dfn[u]);
                // cout<<aa.pd<<" "<<dfn[top[u]]<<" "<<dfn[u]<<"...\n";
                if(aa.dwn[1] != 0) {
                    ner=aa.dwn[1];
                    break;
                }
                u=up[top[u]];
                // cout<<u<<"!\n";
            }
            // cout<<ner<<"!?\n";
            if(ner == 0) {
                ans+=A.ask(1, 1, n, dfn[1], dfn[don[top[1]]]).sum[0];
            }
            else {
                // cout<<ner<<"??? "<<t[ner].sum<<"!? ";
                ans+=t[ner].sum+1;
                if(dfn[ner]+1 <= dfn[don[top[ner]]]) 
                    ans+=A.ask(1, 1, n, dfn[ner]+1, dfn[don[top[ner]]]).sum[0];
            }
            write(ans, '\n');
        }
    }
	return 0;
}