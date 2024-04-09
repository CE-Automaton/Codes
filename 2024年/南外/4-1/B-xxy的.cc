#include<bits/stdc++.h>
#define lt id<<1
#define rt id<<1|1
using namespace std;
const int N=1310,M=N<<2,mod=1e9+9;
inline void mul(int &x,int y) {x=1ll*x*y%mod;}
inline void upd(int &x,int y) {x+=y;x=(x>=mod)?x-mod:x;}
struct ok{
    int num[M],tag[M];
    void inc(int id,int x) {mul(num[id],x);mul(tag[id],x);}
    void push_up(int id) {num[id]=num[lt],upd(num[id],num[rt]);}
    void push_down(int id)
    {
        if(tag[id]==1) return;
        inc(lt,tag[id]),inc(rt,tag[id]);
        tag[id]=1;
    }
    void build(int id,int l,int r)
    {
        tag[id]=1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(lt,l,mid);
        build(rt,mid+1,r);
    }
    void add(int id,int l,int r,int x,int k)
    {
        if(l==r)
            return upd(num[id],k);
        push_down(id);
        int mid=(l+r)>>1;
        x<=mid?add(lt,l,mid,x,k):add(rt,mid+1,r,x,k);
        push_up(id);
    }
    int query(int id,int l,int r,int x)
    {
        if(l==r) return num[id];
        push_down(id);
        int mid=(l+r)>>1;
        return x<=mid?query(lt,l,mid,x):query(rt,mid+1,r,x);
    }
}Tr[N];
int n,L,T,ans,col[N],ned[N],f[2][N][N];
string a,b,x;
map<string,int>S;
int check(char x) {return ('a'<=x&&x<='z')?x-'a':x-'A';}
int main()
{
    cin>>n;
    while(n--) cin>>x,a+=x;
    cin>>n;
    while(n--) cin>>x,b+=x;
    n=a.size();
    cin>>L;
    for(int i=1;i<=n;i++)
    {
        x=a[i-1],x+=b[i-1];
        if(!S[x]) S[x]=++T;
        col[i]=S[x];
    }
    for(int i=1;i<=n;i++) Tr[i].build(1,1,T);
    Tr[1].add(1,1,T,col[n],1);
    // cerr<<T<<endl;
    // f[n&1][n][1]=1;
    // cerr<<Tr[1].num[1]<<endl;
    for(int i=n-1,t,p;i;i--)
    {
        for(int k=1;k<=n;k++)
        {
            ned[k]=Tr[k-1].num[1];
            upd(ned[k],mod-Tr[k-1].query(1,1,T,col[i]));
            upd(ned[k],Tr[k].query(1,1,T,col[i]));
        }
        for(int k=1;k<=n;k++)
            mul(Tr[k].num[1],n-i),mul(Tr[k].tag[1],n-i);
        for(int k=1;k<=n;k++)
            Tr[k].add(1,1,T,col[i],ned[k]);
        // for(int k=1;k<=n;k++)
        //     cout<<ned[k]<<" \n"[k==n];
        // cerr<<"He "<<endl;
        // t=i&1,p=t^1;
        // for(int j=i+1;j<=n;j++)
        // {
        //     for(int k=1;k<=n;k++)
        //         upd(f[t][i][k+(col[i]!=col[j])],f[p][j][k]);
        //     for(int k=1;k<=n;k++)
        //         upd(f[t][j][k],1ll*f[p][j][k]*(n-i)%mod);
        // }
        // for(int k=1;k<=n;k++)
        // {
        //     int ss=0;
        //     for(int j=i;j<=n;j++)
        //         upd(ss,f[t][j][k]);
        //     cout<<ss<<" \n"[k==n];
        // }
        // memset(f[p],0,sizeof(f[p]));
    }
    // for(int i=1;i<=n;i++)
    //     upd(ans,f[1][i][L]);
    // printf("%d\n",ans);
    printf("%d\n",Tr[L].num[1]);
    return 0;
}