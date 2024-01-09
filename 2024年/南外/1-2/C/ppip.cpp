#include <bits/stdc++.h>
using namespace std;
constexpr int Spp{1<<20};
char buf[Spp],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Spp,stdin),p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x) {
    char c;int f{1};
    do x=(c=getchar())^48;
    while (!isdigit(c)&&c!='-');
    if (x==29) f=-1,x=0;
    while (isdigit(c=getchar()))
        x=(x<<3)+(x<<1)+(c^48);
    x*=f;
}
template <typename T,typename ...Args>
void read(T& x,Args&... args) {read(x);read(args...);}
const int N(2e5);
int n,m,R1,R2,dis[3][N+5],ds[N+5];
vector<int> e[N+5];
void dfs(int u,int *d,int &x,int fa=0) {
    d[u]=d[fa]+1;
    if (d[u]>d[x]) x=u;
    for (auto v:e[u])
        if (v!=fa)
            dfs(v,d,x,u);
}
int hi[N+5],SG[N+5][2];
int dep[N+5],fa[N+5],sz[N+5],son[N+5],L[N+5],R[N+5],fz[N+5],tp[N+5];
void init(int u, int fa) {
    dep[u]=dep[fa]+1;
    ::fa[u]=fa;
    sz[u]=1;
    e[u].erase(find(e[u].begin(),e[u].end(),fa));
    for (auto v:e[u]) {
        init(v,u);
        sz[u]+=sz[v];
        if (sz[v]>sz[son[u]]) son[u]=v;
    }
}
void hld(int u, int top) {
    static int lda{0};
    L[u]=++lda;
    fz[lda]=u;
    tp[u]=top;
    if (son[u]) hld(son[u],top);
    for (auto v:e[u]) if (v!=son[u]) hld(v,v);
    R[u]=lda;
}
struct info {
    int s[4];
    friend info operator+(const info &a,const info &b) {
        info c;
        for (int i:{0,1,2,3}) c.s[i]=a.s[i]^b.s[i];
        return c;
    }
    void qwq(int p) {
        for (int i:{0,1,2,3})
            if ((i^p)>i) swap(s[i],s[i^p]);
    }
};
namespace Tree {
    info T[::N<<2];
    int tg[::N<<2];
    int N;
    void upd(int p) {
        if (p<=N) (T[p]=T[p<<1]+T[p<<1|1]).qwq(tg[p]);
    }
    void init(int n) {
        for (N=1;N<=n+1;N<<=1);
        for (int i{1};i<=n;++i) T[N+i]={SG[fz[i]][1],SG[fz[i]][0],0,0};
        for (int i{N};i;--i) upd(i);
    }
    void modify(int s,int t,int tp) {
        for (s+=N-1,t+=N+1;s^t^1;s>>=1,t>>=1) {
            upd(s);upd(t);
            if (~s&1) T[s^1].qwq(tp),tg[s^1]^=tp;
            if (t&1) T[t^1].qwq(tp),tg[t^1]^=tp;
        }
        for (upd(t);s;s>>=1) upd(s);
    }
}
void modify(int x, int y, int typ, int dt=0) {
    // cerr<<x<<" "<<y<<" "<<typ<<" "<<dt<<endl;
    while (tp[x]^tp[y]) {
        if (dep[tp[x]]<dep[tp[y]]) swap(x,y);
        Tree::modify(L[tp[x]],L[x],typ);
        x=fa[tp[x]];
    }
    if (dep[x]>dep[y]) swap(x,y);
    if (L[x]+dt<=L[y]) Tree::modify(L[x]+dt,L[y],typ);
}
bool Son(int x,int y) {
    return L[x]<=L[y]&&L[y]<=R[x];
}
int main() {
    freopen("genshin.in","r",stdin);
    freopen("genshin.out","w",stdout);
    read(n,m);
    for (int i{1};i<n;++i) {
        int u,v;read(u,v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int x{0},y{0};
    dfs(1,dis[2],x);
    dfs(x,dis[1],y);
    int *nl{new int};
    *nl=0;
    dfs(y,dis[0],*nl);
    for (int i{1};i<=n;++i)
        ds[i]=max(dis[0][i],dis[1][i]);
    R1=R2=1;
    for (int i{2};i<=n;++i) {
        if (ds[i]<ds[R1]) R1=R2=i;
        else if (ds[i]==ds[R1]) R2=i;
    }
    // cerr<<R1<<" "<<R2<<endl;
    e[R1].push_back(0);
    init(R1,0);hld(R1,R1);
    for (int i{1};i<=n;++i) sort(e[i].begin(),e[i].end(),[](int x,int y){return L[x]<L[y];});
    for (int i{n};i>=1;--i) {
        int u{fz[i]};
        for (int v:e[u])
            if (v!=R2) hi[u]=max(hi[u],hi[v]+1);
    }
    // for (int i{1};i<=n;++i) cerr<<hi[i]<<" ";
    for (int i{1};i<=n;++i) {
        SG[i][1]=hi[i];
        if (Son(R2,i)) SG[i][0]=dep[i]-1+hi[R1];
        else SG[i][0]=dep[i]+hi[R2];
    }
    // for (int i{1};i<=n;++i) cerr<<SG[i][0]<<" ";
    // cerr<<endl;
    Tree::init(n);
    modify(1,Son(R2,1)?R2:R1,1);
    int root{1};
    // cerr<<Tree::T[1].s[0]<<endl;
    while (m--) {
        int op,u,v,x;
        read(op,u);
        if (op==1) {
            read(v,x);
            modify(u,v,2);
        } else {
            read(x);
            if (root==u) Tree::modify(1,n,2);
            else if (Son(u,root)) {
                int v{*prev(upper_bound(e[u].begin(),e[u].end(),root,[](int x,int y){return L[x]<L[y];}))};
                Tree::modify(1,n,2);
                Tree::modify(L[v],R[v],2);
            } else {
                Tree::modify(L[u],R[u],2);
            }
        }
        modify(root,x,1,((Son(R2,root))==(Son(R2,x))));
        root=x;
        cout<<Tree::T[1].s[0]<<'\n';
    }
    return 0;
}
