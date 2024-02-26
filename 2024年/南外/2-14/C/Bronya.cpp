#include<bits/stdc++.h>

using namespace std;
int n;
char s[10000005];
int st[5000005],tp,id;
int d[5000005],fa[5000005];
int dep[5000005];
int Fa[5000005];
long long sum[5000005],f[5000005];
int siz[5000005],ma[5000005],se[5000005],lson[5000005];
int q[5000005],head[5000005],tail[5000005],dfn[5000005],cnt;
int topf[5000005];
int main(){
    freopen("handout.in","r",stdin);
    freopen("handout.out","w",stdout);
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=2*n;i++){
        if(s[i]=='(')st[++tp]=++id,fa[id]=st[tp-1],d[fa[id]]++;
        else tp--;
    }
    for(int i=1;i<=n;i++)dep[i]=dep[fa[i]]+1;
    for(int i=1;i<=n;i++){
        if(d[i]==1)Fa[i]=Fa[fa[i]];
        else Fa[i]=i;
    }
    for(int i=1;i<=n;i++)fa[i]=Fa[fa[i]];
    for(int i=n;i>=1;i--)
        if(d[i]!=1){
            if(d[i]==0)siz[i]=1,sum[i]=dep[i],ma[i]=dep[i],se[i]=0;
            else f[i]=1e18;
            siz[fa[i]]+=siz[i];sum[fa[i]]+=sum[i];
            if(ma[i]>ma[fa[i]]){
                se[fa[i]]=ma[fa[i]];
                ma[fa[i]]=ma[i];lson[fa[i]]=i;
            }
            else if(ma[i]>se[fa[i]])se[fa[i]]=ma[i];
        }
    lson[0]=0;
    for(int i=1;i<=n;i++){
        if(d[i]!=1){
            if(lson[fa[i]]!=i){
                int x=i;
                while(x)topf[x]=i,dfn[x]=++cnt,x=lson[x];
            }
        }
    }
    long long ans=0;
    for(int i=n;i>=1;i--){
        if(d[i]!=1){
            if(!d[i]){
                f[i]=0;
                head[i]=tail[i]=dfn[topf[i]];
                q[head[i]]=i;
            }
            else {
				while(head[i]<=tail[i]&&dep[q[tail[i]]]<=se[i]){
            		int x=q[tail[i]];
            		f[i]=min(f[i],f[x]+sum[i]-sum[x]-(siz[i]-siz[x])*1ll*dep[i]);
            		tail[i]--;
            	}
            	while(head[i]<tail[i]){
                	int x=q[tail[i]],y=q[tail[i]-1];
                    if(f[x]-sum[x]+dep[x]+1ll*siz[x]*dep[i]+dep[x]>=f[y]-sum[y]+dep[y]+1ll*siz[y]*dep[i]+dep[y])tail[i]--;
                    else break;
                }
                if(head[i]<=tail[i]){
                	int x=q[tail[i]];
            		f[i]=min(f[i],f[x]+sum[i]-sum[x]-(siz[i]-siz[x])*1ll*dep[i]+dep[x]-se[i]);
                }
                while(head[i]<tail[i]){
                	int x=q[tail[i]],y=q[tail[i]-1];
                	if((siz[i]-siz[y])*(f[x]-sum[x]-f[y]+sum[y]+dep[x]-dep[y])-(siz[x]-siz[y])*(f[i]-sum[i]-f[y]+sum[y]+dep[i]-dep[y])>=0)tail[i]--;
                	else break;
                }
                tail[i]++;q[tail[i]]=i;
            }
            if(lson[fa[i]]==i)head[fa[i]]=head[i],tail[fa[i]]=tail[i];
            else {
                int x=i;
                while(x){
                	f[fa[i]]=min(f[fa[i]],f[x]+(sum[fa[i]]-sum[x])-(siz[fa[i]]-siz[x])*1ll*dep[fa[i]]);
                	x=lson[x];
                }
            }
            if(fa[i]==0)ans=f[i]+dep[i]-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
