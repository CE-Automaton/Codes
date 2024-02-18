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
constexpr int N{1000000};
int sa[N+5],rk[N+5],h[N+5],f[N+5];
int find(int x) {return x==f[x]?x:f[x]=find(f[x]);}
vector<int> e[N+5];
void adde(int u,int v) {
    e[v].emplace_back(u);
}
int F[21][N+5];
int Find(int z,int x) {
    return F[z][x]==x?x:F[z][x]=find(F[z][x]);
}
void add(int x,int y,int k) {
    for (int i{20};i>=0;--i)
        if (k>>i&1)
            F[i][Find(i,x)]=Find(i,y),x+=(1<<i),y+=(1<<i);
}
void addd(int k,int x,int y) {
    F[k][Find(k,x)]=Find(k,y);
}
int val[N+5];
int main() {
    freopen("hush.in","r",stdin);
    freopen("hush.out","w",stdout);
    int n;read(n);
    for (int i{1};i<=n;++i) read(sa[i]),rk[sa[i]]=i;
    iota(f,f+N,0);
    for (int i{0};i<=20;++i) iota(F[i],F[i]+n+1,0);
    for (int i{1};i<n;++i) read(h[i]);
    for (int i{1};i<n;++i)
        if (~h[i])
            add(sa[i],sa[i+1],h[i]);
    for (int i{20};i>0;--i)
        for (int j{1};j+(1<<i)-1<=n;++j) {
            addd(i-1,j,Find(i,j));
            addd(i-1,j+(1<<i-1),Find(i,j)+(1<<i-1));
        }
    for (int i{1};i<=n;++i) f[i]=Find(0,i);
    for (int i{1};i<n;++i) {
        if (~h[i]) adde(find(sa[i]+h[i]),find(sa[i+1]+h[i]));
        if (rk[sa[i]+1]>rk[sa[i+1]+1]) adde(find(sa[i]),find(sa[i+1]));
    }
    // for (int i{1};i<=n;++i)
        // if (rk[find(i)]>rk[i]) f[f[i]]=i,swap(e[i],e[f[i]]),f[i]=i;
    fill_n(val+1,n,-2);
    val[n+1]=-1;
    int now{0};
    for (int i{1};i<=n;++i) {
        int u{find(sa[i])};
        if (val[u]!=-2) continue;
        for (auto v:e[u])
            now=max(now,val[v]+1);
        val[u]=now;
    }
    for (int i{1};i<=n;++i) putchar('a'+val[find(i)]);
    return 0;
}
