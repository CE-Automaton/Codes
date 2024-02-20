#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=998244353,MAXN=1e7+5;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1; a%=p,b%=p-1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
int phi[MAXN];
bool isc[MAXN];
vector <int> prs;
void solve() {
	ll m,a,b,c,d;
	scanf("%lld%lld%lld%lld%lld",&m,&a,&b,&c,&d);
	if(m==1) return puts("1"),void();
	ll L=1,R=1;
	if(a&&b) for(int i=0,v=__gcd(a,b);i<v;++i) L=L*m;
	else L=0;
	if(c&&d) for(int i=0,v=__gcd(c,d);i<v;++i) R=R*m;
	else R=0;
	if(L==R) return puts("1"),void();
	ll n=(R-L)/m,ans=0; n%=MOD-1;
	auto add=[&](int x) {
		if((m/x)%2) ans=(ans+phi[m/x]*ksm(2,x*n))%MOD;
	};
	for(int k=1;k*k<=m;++k) if(m%k==0) {
		add(k); if(k*k!=m) add(m/k);
	}
	printf("%lld\n",ans*ksm(m)%MOD);
}
signed main() {
	freopen("calculate.in","r",stdin);
	freopen("calculate.out","w",stdout);
	phi[1]=1;
	for(int i=2;i<MAXN;++i) {
		if(!isc[i]) prs.push_back(i),phi[i]=i-1;
		for(int p:prs) {
			if(i*p>=MAXN) break;
			phi[i*p]=phi[i]*(p-1),isc[i*p]=true;
			if(i%p==0) { phi[i*p]+=phi[i]; break; }
		}
	}
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
