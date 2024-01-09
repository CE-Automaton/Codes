#include <bits/stdc++.h>
using namespace std;
#define For(Ti,Ta,Tb) for(auto Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(auto Ti=(Ta);Ti>=(Tb);--Ti)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
using ll=long long;
using i128=__int128;
vector<pair<ll,int>> prime_factors(ll x){
	vector<pair<ll,int>> res;
	auto add=[&](int i){
		if(x%i==0){
			res.emplace_back(i,0);
			while(x%i==0) ++res.back().second,x/=i;
		}
	};
	add(2),add(3);
	for(int i=5;1LL*i*i<=x;i+=6) add(i),add(i+2);
	if(x>1) res.emplace_back(x,1);
	return res;
}
ll power(ll x,ll y,ll mod){
	ll r=1;
	for(;y;y>>=1,x=i128(x)*x%mod){
		if(y&1) r=i128(r)*x%mod;
	}
	return r;
}
void exgcd(ll a,ll b,ll& x,ll& y){
	if(!b){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}
ll inv(ll a,ll mod){
	ll x,y;
	exgcd(a,mod,x,y);
	return (x%mod+mod)%mod;
}
pair<ll,ll> crt(ll a1,ll m1,ll a2,ll m2){
	ll m=m1*m2;
	return {(i128(a1)*m2%m*inv(m2,m1)+i128(a2)*m1%m*inv(m1,m2))%m,m};
}
struct Prime{
	ll p,mod;
	vector<ll> val;
	Prime(ll p,ll mod):p(p),mod(mod),val(mod){
		val[0]=1;
		For(i,1,mod-1){
			val[i]=val[i-1]*(i%p?i:1)%mod;
		}
	}
	ll dfac(ll n){
		ll res=0;
		for(;n;res+=(n/=p));
		return res;
	}
	ll r(ll n){
		if(!n) return 1;
		return power(val[mod-1],n/mod,mod)*val[n%mod]%mod*r(n/p)%mod;
	}
	ll binom(ll n,ll m){
		ll cnt=dfac(n)-dfac(m)-dfac(n-m);
		ll ans=power(p,cnt,mod);
		if(!ans) return 0;
		return ans*r(n)%mod*inv(r(m),mod)%mod*inv(r(n-m),mod)%mod;
	}
};
vector<Prime> vec;
void exlucas_init(ll p){
	auto pfac=prime_factors(p);
	for(auto [p,c]:pfac){
		ll mod=1;
		For(i,1,c) mod*=p;
		vec.emplace_back(p,mod);
	}
}
ll binom(ll n,ll m){
	ll a=0,mod=1;
	for(auto& x:vec){
		tie(a,mod)=crt(a,mod,x.binom(n,m),x.mod);
	}
	return a;
}
int T;
ll mod;
int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	assert(freopen("dress.in","r",stdin));
	assert(freopen("dress.out","w",stdout));
	cin>>T>>mod;
	exlucas_init(mod);
	while(T--){
		int n,k;
		cin>>n>>k;
		ll ans=i128(binom(n+k-2,k-1)-(k>1?binom(n+k-2,k-2):0)+mod)*(k<n?power(2,n-k-1,mod):1)%mod;
		cout<<ans<<'\n';
	}
	return 0;
}
