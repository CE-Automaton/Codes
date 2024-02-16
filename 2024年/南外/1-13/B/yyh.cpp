#include<bits/stdc++.h>
#define N 1010
#define LL long long 
#define mod 1000000007
#define rep(i,l,r) for(int i=l;i<=r;i++) 
#define drep(i,r,l) for(int i=r;i>=l;i--) 
using namespace std;
int rd() {
	int res=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f*=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch^48),ch=getchar();
	return res*f;
}
int n,m,K,b[10];
vector<int> nxt[130];
LL dp[2][N][10],ans;
map<LL,int> mp;int tot,bl[130];
int cnt[20];
int B[20][130]={{0},
{1,1},
{1,2,2,1},
{1,2,3,2,2,3,2,1},
{1,2,3,2,3,4,3,2,2,3,4,3,2,3,2,1},
{1,2,3,2,4,2,3,2,3,5,6,2,3,5,3,2,2,3,5,3,2,6,5,3,2,3,2,4,2,3,2,1},
{1,2,3,2,4,2,3,2,4,5,3,2,4,2,3,2,3,6,7,2,3,8,3,2,3,6,3,5,3,6,3,2,2,3,6,3,5,3,6,3,2,3,8,3,2,7,6,3,2,3,2,4,2,3,5,4,2,3,2,4,2,3,2,1},
{1,2,3,2,4,2,3,2,5,2,3,2,4,2,3,2,4,6,7,2,4,2,3,2,4,6,3,2,4,2,3,2,3,8,9,2,7,8,3,2,3,8,10,2,3,8,3,2,3,8,3,6,3,8,7,2,3,8,3,6,3,8,3,2,2,3,8,3,6,3,8,3,2,7,8,3,6,3,8,3,2,3,8,3,2,10,8,3,2,3,8,7,2,9,8,3,2,3,2,4,2,3,6,4,2,3,2,4,2,7,6,4,2,3,2,4,2,3,2,5,2,3,2,4,2,3,2,1},
};
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	n=rd(),m=rd(),K=rd();
	if(m==0||K==0) {
		LL res=1;
		rep(i,1,n) res=res*2%mod;
		printf("%lld\n",res);
		return 0;
	}
	if(n<2*K) {
		puts("0");
		return 0;
	}
	rep(S,0,(1<<K)-1) {
		rep(i,1,K) b[i]=S>>(i-1)&1;
		nxt[S].resize(K+2);
		for(int i=2,j=0;i<=K;i++) { 
			while(j&&b[i]!=b[j+1]) j=nxt[S][j];
			if(b[i]==b[j+1]) j++;
			nxt[S][i]=j;
		}
	}
	rep(S,0,(1<<K)-1) cnt[B[K][S]]++;
	int p,k_;
	rep(S,0,(1<<K)-1) if(cnt[B[K][S]]) {
		rep(i,1,K) b[i]=S>>(i-1)&1;
		memset(dp,0,sizeof(dp));
		p=1;
		dp[p][0][0]=cnt[B[K][S]],cnt[B[K][S]]=0;
		rep(i,K,n-1) {
			p^=1;
			rep(j,0,m) rep(k,0,K-1) dp[p][j][k]=0;
			rep(j,0,m) rep(k,0,K-1) if(dp[p^1][j][k]) rep(o,0,1) {
				k_=k;
				while(k_&&b[k_+1]!=o) k_=nxt[S][k_];
				if(b[k_+1]==o) k_++;
				if(k_==K) dp[p][min(m,j+1)][nxt[S][K]]=(dp[p][min(m,j+1)][nxt[S][K]]+dp[p^1][j][k])%mod;
				else dp[p][j][k_]=(dp[p][j][k_]+dp[p^1][j][k])%mod;
			}
		}
//		LL res=0;
		rep(k,0,K-1) {
			ans=(ans+dp[p][m][k])%mod;
//			res=(res+dp[p][m][k])%mod;
		}
//		if(!mp[res]) mp[res]=++tot;
//		bl[S]=mp[res];
	}
	printf("%lld",ans);
	return 0;
}
