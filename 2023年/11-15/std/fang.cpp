#include<bits/stdc++.h>
using namespace std;
int t,n,k,l[1000005];
long long ans;
int lb(int x){return x&(-x);}
void chan(int x){for(;x<=k;x+=lb(x))++l[x];}
int find(int x){int s=0;for(;x;x-=lb(x))s+=l[x];return s;}
int main(){
	freopen("fang.in","r",stdin);
	freopen("fang.out","w",stdout);
	scanf("%d",&t);
	for(int i=1;i<=t;++i){
		scanf("%d%d",&n,&k),ans=0;
		for(int b=n;b;--b){
			chan(1ll*b*b%k*b%k+1);
			int l=1ll*b*b%k+1,r=1ll*b*b%k+b;
			ans+=1ll*(r-l)/k*find(k);
			l%=k,r%=k;
			if(l<=r)ans+=find(r+1)-find(l);
			else ans+=find(k)-find(l)+find(r+1);
		}
		printf("Case %d: %lld\n",i,ans);
		for(int i=1;i<=k;++i)l[i]=0;
	}
	return 0;
}
