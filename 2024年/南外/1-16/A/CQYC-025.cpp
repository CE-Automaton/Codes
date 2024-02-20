#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int s=0;
    char ch=getchar(),last=' ';
    while(ch<'0'||ch>'9')
        last=ch,ch=getchar();
    while(ch>='0'&&ch<='9')
        s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
    return last=='-'?-s:s;
}
void write(int x)
{
    if(!x)
        putchar('0');
    char F[200];
    int tmp=x>0?x:-x;
    if(x<0)
        putchar('-');
    int cnt=0;
    while(tmp>0)
        F[cnt++]=tmp%10+'0',tmp/=10;
    while(cnt>0)
        putchar(F[--cnt]);
}
const int maxn=2500010;
int ans,now;
int a[maxn],b[maxn];
int n,m,nd,md,cnt;
signed main()
{
    freopen("rabbit.in","r",stdin);
    freopen("rabbit.out","w",stdout);
    n=read(),m=read();
    a[1]=read(),nd=read();
    b[1]=read(),md=read();
    now=a[1];
    for(int i=2;i<=n;i++)
    {
        a[i]=(a[i-1]*58+nd)%(m+1);
        now+=a[i];
    }
    for(int i=2;i<=m;i++)
        b[i]=(b[i-1]*58+md)%(n+1);
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    ans=n*m;
    cnt=1;
    for(int i=n;i>=0;i--)
    {
        while(cnt<=m&&n-i>=b[cnt])
        {
            now+=b[cnt]-n+i;
            cnt++;
        }
        ans=min(ans,now);
        now+=m-cnt+1-a[i];
    }
    write(ans);
    putchar('\n');
    return 0;
}
