#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 2e5+10;
int n, m, k, opt, xx, yy, tot, b, inv[N], jc[N], inc[N], f[45][N];
struct qwq {
	int xx, yy;
}zhan[N];

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
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void genshin() {
	for(int i = 1; i <= tot; ++i)
		f[0][zhan[i].xx]=upd(f[0][zhan[i].xx]+zhan[i].yy);
	tot=0;
	for(int o = 1; o <= k; ++o)
		for(int i = 1; i <= n; ++i)
			f[o][i]=upd(f[o-1][i]+f[o][i-1]);
}

signed main() {
    read(n), read(m), read(k);
	b=(int) sqrt(n*k);
	inv[0]=inv[1]=jc[0]=jc[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n+k; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	for(int i = 1; i <= m; ++i) {
		read(opt), read(xx);
		if(opt == 0) 
			read(yy), zhan[++tot]=qwq {xx, yy};
		else {
			int ans = f[k][xx];
			for(int j = 1; j <= tot; ++j)
				if(zhan[j].xx <= xx)
					ans=upd(ans+1LL*c(xx-zhan[j].xx+k-1, k-1)*zhan[j].yy%mod);
			write(ans, '\n');
		}
		if(tot%b == 0) 
			genshin();
	}
	return 0;
}