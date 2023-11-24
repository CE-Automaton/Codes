#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int a, b, f[2], d[2][2], c[2][2], az[2][2], ans[2];
long long n;

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
	while(x) {
		if(x&1)
			ret=1LL*ret*y%mod;
		y=1LL*y*y%mod;
		x=(x>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("poly.in", "r", stdin);
	freopen("poly.out", "w", stdout);
	read(a), read(b), read(n);
	f[0]=2, f[1]=a;
	d[0][0]=0;
	d[0][1]=mod-b;
	d[1][0]=1;
	d[1][1]=a;
	az[0][0]=az[1][1]=1;
	--n;
	while(n) {
		if(n&1) {
			for(int i = 0; i <= 1; ++i)
				for(int j = 0; j <= 1; ++j)
					c[i][j]=az[i][j], az[i][j]=0;
			for(int k = 0; k <= 1; ++k)
				for(int i = 0; i <= 1; ++i)
					for(int j = 0; j <= 1; ++j)
						az[i][j]=upd(az[i][j]+1LL*c[i][k]*d[k][j]%mod);
		}
		n=(n>>1);
		for(int i = 0; i <= 1; ++i)
			for(int j = 0; j <= 1; ++j)
				c[i][j]=d[i][j], d[i][j]=0;
		for(int k = 0; k <= 1; ++k)
			for(int i = 0; i <= 1; ++i)
				for(int j = 0; j <= 1; ++j)
					d[i][j]=upd(d[i][j]+1LL*c[i][k]*c[k][j]%mod);
	}
	for(int i = 0; i <= 1; ++i)
		for(int j = 0; j <= 1; ++j)
			ans[i]=upd(ans[i]+1LL*f[j]*az[j][i]%mod);
	write(ans[1], '\n'); 
	return 0;
}
