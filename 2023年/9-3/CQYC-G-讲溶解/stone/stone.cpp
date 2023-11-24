#include <bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int D = 1e4+5;
int n, d, jc[D], inv[D], inc[D], ans, a[3][3], b[3], p[3], dd[3][3], e[3][3];

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
int c(int x, int y) {
	return ((y >= 0 && x >= y) ? jc[x]*inc[x-y]%mod*inc[y]%mod : 0);
}
int ksm(int x, int y, int ret = 1) {
	while(x) {
		if(x&1)
			ret=ret*y%mod;
		y=y*y%mod;
		x=(x>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("stone.in", "r", stdin);
	freopen("stone.out", "w", stdout);
	read(n), read(d);
	jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
	for(int i = 2; i <= d; ++i)
		jc[i]=jc[i-1]*i%mod, inv[i]=inv[mod%i]*(mod-mod/i)%mod, inc[i]=inc[i-1]*inv[i]%mod;
	ans=2;
	for(int j = 1; j <= d; ++j) 
		for(int o = 0; o <= 1; ++o) {
			b[1]=0, p[1]=c(d-1, j-o);
			b[2]=0, p[2]=c(d-1, j-o-1);
			a[1][1]=c(d-1, j);
			a[1][2]=c(d-1, j-1);
			a[2][1]=c(d-1, j-1);
			a[2][2]=c(d-1, j-2);
			e[1][1]=e[2][2]=1;
			e[1][2]=e[2][1]=0;
			int gs = n-1; 
			while(gs) {
				if(gs&1) {
					for(int x = 1; x <= 2; ++x)
						for(int y = 1; y <= 2; ++y)
							dd[x][y]=e[x][y], e[x][y]=0;
					for(int z = 1; z <= 2; ++z)
						for(int x = 1; x <= 2; ++x)
							for(int y = 1; y <= 2; ++y)
								e[x][y]=upd(e[x][y]+dd[x][z]*a[z][y]%mod);
				}
				for(int x = 1; x <= 2; ++x)
					for(int y = 1; y <= 2; ++y)
						dd[x][y]=a[x][y], a[x][y]=0;
				for(int z = 1; z <= 2; ++z)
					for(int x = 1; x <= 2; ++x)
						for(int y = 1; y <= 2; ++y)
							a[x][y]=upd(a[x][y]+dd[x][z]*dd[z][y]%mod);
				gs=(gs>>1);
			}
			for(int x = 1; x <= 2; ++x)
				for(int y = 1; y <= 2; ++y)
					b[x]=upd(b[x]+e[x][y]*p[y]%mod);
			ans=upd(ans+b[o+1]);
		}
	write(ans, '\n');
	return 0;
}
