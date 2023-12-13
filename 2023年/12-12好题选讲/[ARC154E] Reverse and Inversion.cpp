#include <bits/stdc++.h>
#define mod 998244353
#define inv2 499122177
using namespace std;
const int N = 2e5+5;
int n, m, p[N], to[N], ans;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
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

signed main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(p[i]), to[p[i]]=i;
	int invn = ksm(1LL*n*(n+1)%mod, mod-2);
	for(int i = 1, q = 0; i <= n; ++i)
		q=ksm(upd(1+mod-2LL*i%mod*(n-i+1)%mod*invn%mod), m), ans=upd(upd(ans+1LL*i*i%mod)
		-1LL*upd(1LL*q*i%mod+1LL*upd(1-q+mod)*(n+1)%mod*inv2%mod)*p[i]%mod+mod);
	write(1LL*ans*ksm(1LL*n*(n+1)/2%mod, m)%mod, '\n');
	return 0;
}
