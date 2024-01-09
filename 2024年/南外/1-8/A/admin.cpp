#include<bits/stdc++.h>
#define debug(x) cerr<<"\tDEBUG: "<<#x<<" = "<<(x)<<endl;
using namespace std;
inline void rd(int &res){
    static char c;res=0;
    while((c=getchar())<48);
    do res=(res<<1)+(res<<3)+(c^48);
    while((c=getchar())>47);
}
const int maxn=1e5+100;
int n,m,q;
int tot=1,head[maxn],to[maxn<<1],nxt[maxn<<1];
int deg[maxn];
void add_edge(int u,int v){
    deg[u]++;
    to[++tot]=v;
    nxt[tot]=head[u];
    head[u]=tot;
}
int L[maxn];
int id,num[maxn];
bool vis[maxn];
void dfs(int x){
    if(vis[x])return;
    vis[x]=1;
    num[++id]=x;
    for(int i=head[x];i;i=nxt[i])
        dfs(to[i]);
}
int main(){
//  freopen("ex.in","r",stdin);
//  freopen("ex.out","w",stdout);
    rd(m);rd(n);
    for(int i=1,a,b;i<=n;i++){
        rd(a);rd(b);
        add_edge(a,b);
        add_edge(b,a);
    }
    for(int i=1;i<=m;i++){
        if(!vis[i]){
            id=0;
            dfs(i);
            int cnt=0;
            for(int j=1;j<=id;j++)
                cnt+=deg[num[j]];
            if(cnt/2==id-1){
                sort(num+1,num+1+id);
                L[num[id]]=num[1]+1;
            }
        }
    }
    for(int i=2;i<=m;i++)
        L[i]=max(L[i],L[i-1]);
    rd(q);
    for(int i=1,l,r;i<=q;i++){
        rd(l);rd(r);
        if(L[r]<=l)puts("Yes");
        else puts("No");
    }
     
    return 0;
}
