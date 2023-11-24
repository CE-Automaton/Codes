#include <bits/stdc++.h>
#define mod 998244353
using namespace std;

const int N = 8e5+5;
int n, m, x, y, pw[N], inv[N], inc[N], vish[N],
h[N], ansh[N], l[N], ansl[N], visl[N], ans, sum;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("assemble.in", "r", stdin);
	freopen("assemble.out", "w", stdout);
	read(n), read(m);
	pw[0]=pw[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= 2*m; ++i)
		pw[i]=1LL*pw[i-1]*i%mod, inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	for(int i = 1; i <= n; ++i) {
		read(x), read(y);
		int p = x+y+3*m;
		for(int o = p-m; o <= p+m; o+=2) {
			int qwq = abs(o-p);
			if(o) h[o-1]=0;
			h[o]=1LL*pw[m]*inc[(m-qwq)/2+qwq]%mod*inc[(m-qwq)/2]%mod;
		}
		if(i == 1)
			for(int o = p-m; o <= p+m; o+=2)
				ansh[o]=h[o], ++vish[o];
		else
			for(int o = p-m; o <= p+m; o+=2)
				ansh[o]=1LL*ansh[o]*h[o]%mod, ++vish[o];
//		for(int o = p-m; o <= p+m; ++o)
//			cout<<h[o]<<" ";puts("");
		
		p = x-y+3*m;
		for(int o = p-m; o <= p+m; o+=2) {
			int qwq = abs(o-p);
			if(o) l[o-1]=0;
			l[o]=1LL*pw[m]*inc[(m-qwq)/2+qwq]%mod*inc[(m-qwq)/2]%mod;
		}
//		for(int o = p-m; o <= p+m; ++o)
//			cout<<l[o]<<" ";puts("\n");
		if(i == 1)
			for(int o = p-m; o <= p+m; o+=2)
				ansl[o]=l[o], ++visl[o];
		else
			for(int o = p-m; o <= p+m; o+=2)
				ansl[o]=1LL*ansl[o]*l[o]%mod, ++visl[o];
	}
	for(int o = 0; o <= 8*m; ++o)
		ansl[o]=(visl[o] != n ? 0 : ansl[o]), sum=upd(sum+ansl[o]);
	for(int o = 0; o <= 8*m; ++o)
		ansh[o]=(vish[o] != n ? 0 : ansh[o]), ans=upd(ans+ansh[o]);
//	cout<<ans<<" "<<sum<<"\n";
	write(1LL*ans*sum%mod);
	return 0;
}
