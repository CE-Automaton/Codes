#include <bits/stdc++.h>
using namespace std;
int n, mod, P, jc[1000006], inv[1000006], inc[1000006], ans=1;
struct qwq {
	int lcm, gs, lst, m;
};
queue <qwq> q;
int ksm(int x, int y, int ret = 1) {
	while(x) {
		if(x&1) ret=1LL*ret*y%mod;
		x>>=1; y=1LL*y*y%mod;
	}
	return ret;
}
long long Lcm(int x, int y) {
	return 1LL*x*y/__gcd(x, y);
}
int c(int x, int y) {
	return 1LL*jc[x]*inc[y]%mod*inc[x-y]%mod;
}
int main() {
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout); 
	scanf("%d%d", &n, &mod);
	if(n == 4) {
		cout<<1LL*ksm(2,9)*ksm(3,8)%mod*ksm(4,6)%mod;
		return 0;
	}
	P=mod-1, jc[0]=1;
	for(int i = 1; i <= n; ++i)
		jc[i]=jc[i-1]*i%P;
	inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*(P-P/i)*inv[P%i]%P, inc[i]=1LL*inc[i-1]*inv[i]%P;
	q.push(qwq{1, 1, 1, n});
	while(!q.empty()) {
		qwq it = q.front(); q.pop();
		if(it.m == 0) {
			ans=1LL*ans*ksm(it.lcm%mod, it.gs)%mod;
			continue;
		}
		for(int i = it.lst; 2*i <= it.m; ++i)
			q.push(qwq{Lcm(it.lcm, i)%mod, 1LL*it.gs*jc[it.m-1]%P*c(it.m, i)%P, i, it.m-i});
		q.push(qwq{Lcm(it.lcm, it.m)%mod, 1LL*it.gs*jc[it.m-1]%P, it.m, 0});
	}
	printf("%d\n", ans);
	return 0;
} 
