#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5,maxm=3e5+5;
struct edge{
    int u,v,w;
    bool operator <(edge i)const{return w<i.w;}
}ed[maxm];
int c[maxn];
int read(){
    int x=0,y=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*y;
}
int f[maxn];
int find(int x){
    if(x==f[x])return x;
    return f[x]=find(f[x]);
}
struct Edge{
    int to,w,nxt;
}e[2*maxn];
int cnt;
int head[maxn];
int val[maxn];
void add(int u,int v,int w){
    e[cnt]=(Edge){v,w,head[u]};
    head[u]=cnt++;
    return ;
}
multiset<int>a;
multiset<int>mn[maxn];
map<int,multiset<int> >s[maxn];
void dfs(int x,int fa,int w){
    f[x]=fa;val[x]=w;
    for(int i=head[x];i!=-1;i=e[i].nxt){
        int tmp=e[i].to;
        if(tmp==fa)continue;
        if(c[x]!=c[tmp]&&s[x][c[tmp]].size())mn[x].erase(mn[x].find(*s[x][c[tmp]].begin()));
        s[x][c[tmp]].insert(e[i].w);
        if(c[x]!=c[tmp])mn[x].insert(*s[x][c[tmp]].begin());
        dfs(tmp,x,e[i].w);
    }
    if(mn[x].size())a.insert(*mn[x].begin());
    return ;
}
int main(){
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
    int n,m,k,Q;
    n=read();m=read();k=read();Q=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read();v=read();w=read();
        ed[i]=(edge){u,v,w};
    }
    sort(ed+1,ed+m+1);
    for(int i=1;i<=n;i++)f[i]=i;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=m;i++){
        int u=ed[i].u,v=ed[i].v,w=ed[i].w;
        u=find(u);v=find(v);
        if(u==v)continue;
        add(u,v,w);
        add(v,u,w);
        f[u]=v;
    }
    for(int i=1;i<=n;i++)c[i]=read();
    dfs(1,0,0);
    while(Q--){
        int x,v,p;
        x=read();v=read();p=f[x];
        if(x^1){
            if(mn[p].size())a.erase(a.find(*mn[p].begin()));
            if(c[p]!=c[x]&&s[p][c[x]].size())mn[p].erase(mn[p].find(*s[p][c[x]].begin()));
            s[p][c[x]].erase(s[p][c[x]].find(val[x]));
            if(c[p]!=c[x]&&s[p][c[x]].size())mn[p].insert(*s[p][c[x]].begin());
            if(c[p]!=v&&s[p][v].size())mn[p].erase(mn[p].find(*s[p][v].begin()));
            s[p][v].insert(val[x]);
            if(c[p]!=v&&s[p][v].size())mn[p].insert(*s[p][v].begin());
            if(mn[p].size())a.insert(*mn[p].begin());
        }
        if(mn[x].size())a.erase(a.find(*mn[x].begin()));
        if(s[x][c[x]].size())mn[x].insert(*s[x][c[x]].begin());
        if(s[x][v].size())mn[x].erase(mn[x].find(*s[x][v].begin()));
        if(mn[x].size())a.insert(*mn[x].begin());
        c[x]=v;
        printf("%d\n",*a.begin());
    }
    return 0;
}
