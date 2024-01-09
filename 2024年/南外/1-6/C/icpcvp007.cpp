# include <bits/stdc++.h>
# define N 100005
# define B 1600
using namespace std;
int n,m,p;
bitset<N> b[6][65];
bitset<N> get(int l,int r)
{
    int k=log2(r-l+1);
    return b[k][l]|b[k][r-(1<<k)+1];
}
int tot;
bitset<N> tmp;
int a[N];
bool mark[65];
int lstans;
int main()
{
    freopen("account.in","r",stdin);
    freopen("account.out","w",stdout);
    cin>>n>>m>>p;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),assert(a[i]!=0);
    for(int i=1;i<=n;i++)
    {
        if((i-1)%B==0)
            tot++;
        b[0][tot][a[i]]=1;
    }
    for(int i=1;(1<<i)<=tot;i++)
        for(int j=1;j<=tot;j++)
            b[i][j]=b[i-1][j]|b[i-1][j+(1<<(i-1))];
    for(int mm=1;mm<=m;mm++)
    {
        tmp.reset();
        int k;
        scanf("%d",&k);
        memset(mark,0,sizeof mark);
        while(k--)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            if(mm!=1 && p)
            {
                l^=lstans,r^=lstans;
                l=l%n+1,r=r%n+1;
            }
            if(l>r)
                swap(l,r);
            int idl=(l-1)/B+1,idr=(r-1)/B+1;
            if(idl+1>=idr)
                for(int i=l;i<=r;i++)
                    tmp[a[i]]=1;
            else
            {
                for(int i=l;i<=idl*B;i++)
                    tmp[a[i]]=1;
                for(int i=(idr-1)*B+1;i<=r;i++)
                    tmp[a[i]]=1;
                for(int i=idl+1;i<=idr-1;i++)
                    mark[i]=1;
            }
        }
        int nowl=-1;
        for(int i=1;i<=tot;i++)
            if(!mark[i] && nowl!=-1)
                tmp|=get(nowl,i-1),nowl=-1;
            else if(mark[i] && nowl==-1)
                nowl=i;
        lstans=tmp.count();
        printf("%lld\n",lstans);
    }
    return 0;
}
