#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
void read(T& x) {
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
vector<int> e[N+5];
int dep[N+5],fa[N+5];
int a[N+5],upl[N+5];
tree<int,int,less<int>,rb_tree_tag,tree_order_statistics_node_update> id;
int main() {
    freopen("tournament.in","r",stdin);
    freopen("tournament.out","w",stdout);
    int n,c,r;read(n,c,r);
    a[1]=r;
    for (int i{2};i<=n;++i)
        read(a[i]);
    for (int i{1};i<=n;++i) id[i]=i;
    for (int i{1};i<=c;++i) {
        int l,r;
        read(l,r);
        auto itl{id.find_by_order(l)};
        int iakioi{itl->first};
        for (int j{l};j<=r;++j) e[i+n].push_back(itl->second),fa[itl->second]=i+n,itl=id.erase(itl);
        id[iakioi]=i+n;
    }
    for (int i{n+c};i>=1;--i) dep[i]=dep[fa[i]]+1;
    for (int i{n+1};i<=n+c;++i) {
        upl[i]=-1;
        for (auto v:e[i]) {
            a[i]=max(a[i],a[v]);
            if (upl[i]==-1) upl[i]=upl[v];
            else upl[i]=max(upl[i],a[v]);
        }
    }
    int p{1};
    while (fa[p]&&a[fa[p]]==a[1]) p=fa[p];
    int win{dep[p]},ans{dep[1]-dep[p]},P{0};
    for (int i{2};i<=n;++i) {
        int x{a[i]};
        int p{i-1},q{i},up{i};
        while (fa[p]!=fa[q]) {
            if (dep[p]>=dep[q]) {
                p=fa[p];
            } else {
                q=fa[q];
                if ((a[q]=max(r,upl[q]))==r) up=q;
            }
        }
        if (up!=q) win=dep[up];
        else win=min(win,dep[up]);
        if (dep[i]-win>ans) ans=dep[i]-win,P=i-1;
    }
    cout<<P<<endl;
    return 0;
}
