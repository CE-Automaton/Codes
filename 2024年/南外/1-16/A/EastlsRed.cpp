#include<cstdio>
#include<algorithm>
#include<queue>
#include<functional>
int m,n,m0,md,n0,nd;
int a[2500086],b[2500086],cnt[2500086];
struct item{
    int val,cnt;
    bool operator < (const item& rhs)const
    {
        return val<rhs.val;
    }
    bool operator > (const item& rhs)const
    {
        return val>rhs.val;
    }
};
std::priority_queue<item>q1;
std::priority_queue<item,std::vector<item>,std::greater<item> >q2;
int main()
{
    freopen("rabbit.in","r",stdin);
    freopen("rabbit.out","w",stdout);
    scanf("%d%d%d%d%d%d",&m,&n,&m0,&md,&n0,&nd);
    a[0]=m0,b[0]=n0;
    for(int i=1;i<m;i++)
        a[i]=(a[i-1]*58+md)%(n+1);
    for(int i=1;i<n;i++)
        b[i]=(b[i-1]*58+nd)%(m+1);
    for(int i=0;i<n;i++)
        cnt[b[i]]++;
    int sumn=0;
    for(int i=1;i<=m;i++)
        if(cnt[i])
            q2.push((item){i,cnt[i]}),sumn+=cnt[i];
    std::sort(a,a+m,std::greater<int>());
    long long res=0;
    int ncnt=sumn,ndec=0;
    for(int i=0;i<m;i++)
    {
        while(!q1.empty()&&(q2.empty()||q1.top().val+ndec>q2.top().val))
            q2.push((item){q1.top().val+ndec,q1.top().cnt}),ncnt+=q1.top().cnt,q1.pop();
        if(q2.empty())
            break;
        while(!q2.empty()&&a[i]<=ncnt-q2.top().cnt)
        {
            ncnt-=q2.top().cnt;
            if(q2.top().val==ndec)
                q2.pop();
            else if(!q1.empty()&&q1.top().val+ndec==q2.top().val)
            {
                int val=q1.top().val,cnt=q1.top().cnt;
                cnt+=q2.top().cnt;
                q1.pop();q2.pop();
                q1.push((item){val,cnt});
            }
            else q1.push((item){q2.top().val-ndec,q2.top().cnt}),q2.pop();
        }
        if(q2.empty())
            break;
        if(a[i]<ncnt)
        {
            if(q2.top().val==ndec)
            {
                item temp(q2.top());
                temp.cnt-=(ncnt-a[i]);
                q2.pop();
                q2.push(temp);
            }
            else if(!q1.empty()&&q1.top().val+ndec==q2.top().val)
            {
                item temp1(q1.top()),temp2(q2.top());
                q1.pop(),q2.pop();
                temp2.cnt-=(ncnt-a[i]);
                temp1.cnt+=(ncnt-a[i]);
                q1.push(temp1),q2.push(temp2);
            }
            else
            {
                item temp(q2.top());
                q2.pop();
                temp.cnt-=(ncnt-a[i]);
                q1.push((item){temp.val-ndec,ncnt-a[i]});
                q2.push(temp);
            }
            ncnt=a[i];
        }
        //printf("i=%d,ncnt=%d\n",i,ncnt);
        while(!q2.empty()&&q2.top().val==ndec)
            ncnt-=q2.top().cnt,q2.pop();
        res+=ncnt;
        ndec++;
    }
    printf("%lld",res);
    return 0;
}

