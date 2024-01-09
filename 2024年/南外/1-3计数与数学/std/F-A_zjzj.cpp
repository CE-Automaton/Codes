#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define all(a) (a).begin(),(a).end()
#ifdef DEBUG
template<class T>
ostream& operator << (ostream &out,vector<T> a){
	out<<'[';
	for(T x:a)out<<x<<',';
	return out<<']';
}
template<class T>
vector<T> ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
template<class T>
void debug(T x){
	cerr<<x<<endl;
}
template<class T,class...S>
void debug(T x,S...y){
	cerr<<x<<' ',debug(y...);
}
#else
#define debug(...) void()
#endif
const int mod=19491001,N=4e3+10;
int n,k,d,w;
ll qpow(ll x,ll y=mod-2,ll ans=1){
	for(;y;(x*=x)%=mod,y>>=1)if(y&1)(ans*=x)%=mod;
	return ans;
}
int fac[N],ifac[N],inv[N];
int C(int n,int m){
	if(0>m||m>n)return 0;
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
void init(int n=N-1){
	for(int i=fac[0]=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n]);
	for(int i=n;i>=1;i--)ifac[i-1]=1ll*ifac[i]*i%mod;
	for(int i=1;i<=n;i++)inv[i]=1ll*ifac[i]*fac[i-1]%mod;
}
int g[N][N];
namespace Solve4{
	void solve(){
		for(int n=-k;n<=k;n++){
			for(int m=-k;m<=k;m++){
				int i=n+k,j=m+k;
				if(!i){
					g[i][j]=!m;
					continue;
				}
				ll sum=0;
				if(i>1)sum+=(k-n+2ll)*g[i-2][j];
				if(i&&j)sum-=(n-1ll)*g[i-1][j-1];
				if(i)sum-=(n-1ll)*g[i-1][j+1];
				g[i][j]=(sum%mod+mod)*inv[n+k]%mod;
			}
		}
	}
}
namespace Solve6{
	void solve(){
		for(int n=-k;n<=k;n++){
			for(int m=-k;m<=k;m++){
				int i=n+k,j=m+k;
				if(!i){
					g[i][j]=C(k,m);
					continue;
				}
				ll sum=0;
				if(i>1)sum+=(k-n+2ll)*(g[i-2][j]+g[i-2][j+1]);
				if(i&&j)sum-=(n-1ll)*g[i-1][j-1];
				if(i)sum-=(n-1ll)*g[i-1][j+1];
				if(j)sum-=1ll*(n+k)*g[i][j-1];
				g[i][j]=(sum%mod+mod)*inv[n+k]%mod;
			}
		}
	}
}
int main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	init();
	cin>>n>>k>>d;
	w=qpow(7,(mod-1)/d);
	if(d==4)Solve4::solve();
	else Solve6::solve();
	int ans=0;
	vector<pair<int,int>>t;
	for(int n=-k;n<=k;n++){
		for(int m=-k;m<=k;m++){
			int i=n+k,j=m+k;
			if(!g[i][j])continue;
			// debug(n,m,g[i][j]);
			ans=(ans+g[i][j]*qpow((n+mod+1ll*(m+mod)*w)%mod,::n))%mod;
		}
	}
	ans=ans*qpow(qpow(d,k))%mod;
	cout<<ans<<endl;
	return 0;
}
