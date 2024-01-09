#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 5e7+5;
int r, n, m, inv[N], jcc, jcc2n, now, sum, win, ans;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int c(int x, int y) {
	while(now <= x)
		jcc=1LL*jcc*now%mod, ++now;
	return 1LL*jcc*inv[x-y]%mod*inv[y]%mod;
}
int f(int k) {
	return 1LL*jcc2n*inv[n+n-k]%mod*inv[k]%mod*c(n*m+2*n-1-k*(m+1), 2*n-1)%mod;
}

signed main() {
	freopen("dice.in", "r", stdin);
	freopen("dice.out", "w", stdout);
	read(n), read(m), read(r);
	--m;
	inv[0]=inv[1]=1;
	for(int i = 2; i <= n*m; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod;
	int inv2 = inv[2];
	for(int i = 2; i <= n*m; ++i)
		inv[i]=1LL*inv[i-1]*inv[i]%mod;
	jcc2n=now=jcc=1;
	for(int i = 1; i <= n+n; ++i)
		jcc2n=1LL*jcc2n*i%mod;
	for(int i = m*n/(m+1), j=(i&1 ? -1 : 1); i >= 0; --i)
		sum=upd(sum+upd(j*f(i)+mod)), j=-j;
	sum=1LL*sum*ksm(ksm(m+1, n+n), mod-2)%mod;
	win=1LL*(1-sum+mod)*inv2%mod;
	for(int i = 1, qvq = 1; i <= r; ++i)
		ans=upd(ans+1LL*win*qvq%mod), qvq=1LL*qvq*sum%mod;
	write(ans, '\n');
	return 0;
}
