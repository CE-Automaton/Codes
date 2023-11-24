#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
long long l[8], r[8], ll[4], rr[4];
int ans = 1, f[65][2][2][2];
int upd(int x) {
	return (x < 0 ? x+mod : (x >= mod ? x-mod : x));
}
int dp(long long a, long long b, long long c) {
	if(a < 0 || b < 0 || c < 0) return 0;
	memset(f, 0, sizeof f);
	f[60][0][0][0]=1;
	for(int i = 59; i >= 0; --i) 
		for(int aa = 0; aa < 2; ++aa)
			for(int bb = 0; bb < 2; ++bb)
				for(int cc = 0; cc < 2; ++cc) {
					if(f[i+1][aa][bb][cc] == 0) continue;
					if(aa || ((a>>i)&1)) {
						if(bb || ((b>>i)&1)) 
							f[i][aa][bb][cc | ((c>>i)&1)] = upd(f[i][aa][bb][cc | ((c>>i)&1)] + f[i+1][aa][bb][cc]);
						if(cc || ((c>>i)&1)) 
							f[i][aa][bb | ((b>>i)&1)][cc] = upd(f[i][aa][bb | ((b>>i)&1)][cc] + f[i+1][aa][bb][cc]);
					}
					if(bb || ((b>>i)&1)) if(cc || ((c>>i)&1)) 
						f[i][aa | ((a>>i)&1)][bb][cc] = upd(f[i][aa | ((a>>i)&1)][bb][cc] + f[i+1][aa][bb][cc]);
					f[i][aa | ((a>>i)&1)][bb | ((b>>i)&1)][cc | ((c>>i)&1)] = upd(f[i][aa | ((a>>i)&1)][bb | ((b>>i)&1)][cc | ((c>>i)&1)] + f[i+1][aa][bb][cc]);
				}
	int sum = 0;
	for(int aa = 0; aa < 2; ++aa)
		for(int bb = 0; bb < 2; ++bb)
			for(int cc = 0; cc < 2; ++cc)
				sum=upd(sum+f[0][aa][bb][cc]);
	return sum;
}
int main() {
	freopen("qgygd.in","r",stdin);
	freopen("qgygd.out","w",stdout);
	for(int i = 1; i <= 7; ++i) scanf("%lld%lld", &l[i], &r[i]), ans=1LL*ans*((r[i]-l[i]+1)%mod)%mod;
	ll[1]=max({l[1], l[2], l[3]}), ll[2]=l[4], ll[3]=max({l[5], l[6], l[7]});
	rr[1]=min({r[1], r[2], r[3]}), rr[2]=r[4], rr[3]=min({r[5], r[6], r[7]});
	if(rr[1] < ll[1] || rr[2] < ll[2] || rr[3] < ll[3]) {
		printf("%d\n", ans);
		return 0;
	}
	int bb=dp(rr[1], rr[2], rr[3]);
	bb=upd(bb-dp(rr[1], rr[2], ll[3]-1));
	bb=upd(bb-dp(rr[1], ll[2]-1, rr[3]));
	bb=upd(bb-dp(ll[1]-1, rr[2], rr[3]));
	bb=upd(bb+dp(ll[1]-1, ll[2]-1, rr[3]));
	bb=upd(bb+dp(ll[1]-1, rr[2], ll[3]-1));
	bb=upd(bb+dp(rr[1], ll[2]-1, ll[3]-1));
	bb=upd(bb-dp(ll[1]-1, ll[2]-1, ll[3]-1));
	ans=upd(ans-bb);
	printf("%d\n", ans);
	return 0;
}
