#include <bits/stdc++.h>
#define mod 10007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, k, cc, gc, xx[10], yy[10], vis[35][35], pt[35][35], hh[35], ll[35], hs[35], ls[35], f[35][35][550][78], jc[1027], inv[1027], inc[1027], ans;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int sol(int l = 1, int r = n, int zc = 0) {
	memset(f, 0, sizeof f);
	f[0][0][0][0]=1;
	while(l < r) {
		for(int i = zc; i >= 0; --i)
			for(int j = zc; j >= 0; --j)
				for(int s = (1<<k)-1; s >= 0; --s) 
					for(int o = gc; o >= 0; --o) 
						if(f[i][j][s][o]) {
							f[i+1][j][s|hh[l]][o+hs[l]]=upd(f[i+1][j][s|hh[l]][o+hs[l]]+f[i][j][s][o]);
							f[i+1][j][s|hh[r]][o+hs[r]]=upd(f[i+1][j][s|hh[r]][o+hs[r]]+f[i][j][s][o]);
							f[i][j+1][s|ll[l]][o+ls[l]]=upd(f[i][j+1][s|ll[l]][o+ls[l]]+f[i][j][s][o]);
							f[i][j+1][s|ll[r]][o+ls[r]]=upd(f[i][j+1][s|ll[r]][o+ls[r]]+f[i][j][s][o]);

							f[i+1][j+1][s|hh[l]|ll[l]][o+hs[l]+ls[l]-pt[l][l]]=upd(f[i+1][j+1][s|hh[l]|ll[l]][o+hs[l]+ls[l]-pt[l][l]]+f[i][j][s][o]);
							f[i+1][j+1][s|hh[l]|ll[r]][o+hs[l]+ls[r]-pt[l][r]]=upd(f[i+1][j+1][s|hh[l]|ll[r]][o+hs[l]+ls[r]-pt[l][r]]+f[i][j][s][o]);
							f[i+1][j+1][s|hh[r]|ll[l]][o+hs[r]+ls[l]-pt[r][l]]=upd(f[i+1][j+1][s|hh[r]|ll[l]][o+hs[r]+ls[l]-pt[r][l]]+f[i][j][s][o]);
							f[i+1][j+1][s|hh[r]|ll[r]][o+hs[r]+ls[r]-pt[r][r]]=upd(f[i+1][j+1][s|hh[r]|ll[r]][o+hs[r]+ls[r]-pt[r][r]]+f[i][j][s][o]);

							f[i+2][j][s|hh[l]|hh[r]][o+hs[l]+hs[r]]=upd(f[i+2][j][s|hh[l]|hh[r]][o+hs[l]+hs[r]]+f[i][j][s][o]);
							f[i][j+2][s|ll[l]|ll[r]][o+ls[l]+ls[r]]=upd(f[i][j+2][s|ll[l]|ll[r]][o+ls[l]+ls[r]]+f[i][j][s][o]);

							f[i+1][j+2][s|hh[l]|ll[l]|ll[r]][o+hs[l]+ls[l]+ls[r]-pt[l][l]-pt[l][r]]=upd(f[i+1][j+2][s|hh[l]|ll[l]|ll[r]][o+hs[l]+ls[l]+ls[r]-pt[l][l]-pt[l][r]]+f[i][j][s][o]);
							f[i+1][j+2][s|hh[r]|ll[l]|ll[r]][o+hs[r]+ls[l]+ls[r]-pt[r][l]-pt[r][r]]=upd(f[i+1][j+2][s|hh[r]|ll[l]|ll[r]][o+hs[r]+ls[l]+ls[r]-pt[r][l]-pt[r][r]]+f[i][j][s][o]);
							f[i+2][j+1][s|hh[l]|hh[r]|ll[l]][o+hs[l]+hs[r]+ls[l]-pt[l][l]-pt[r][l]]=upd(f[i+2][j+1][s|hh[l]|hh[r]|ll[l]][o+hs[l]+hs[r]+ls[l]-pt[l][l]-pt[r][l]]+f[i][j][s][o]);
							f[i+2][j+1][s|hh[l]|hh[r]|ll[r]][o+hs[l]+hs[r]+ls[r]-pt[l][r]-pt[r][r]]=upd(f[i+2][j+1][s|hh[l]|hh[r]|ll[r]][o+hs[l]+hs[r]+ls[r]-pt[l][r]-pt[r][r]]+f[i][j][s][o]);

							f[i+2][j+2][s|hh[l]|hh[r]|ll[l]|ll[r]][o+hs[l]+hs[r]+ls[l]+ls[r]-pt[l][l]-pt[l][r]-pt[r][l]-pt[r][r]]=upd(f[i+2][j+2][s|hh[l]|hh[r]|ll[l]|ll[r]][o+hs[l]+hs[r]+ls[l]+ls[r]-pt[l][l]-pt[l][r]-pt[r][l]-pt[r][r]]+f[i][j][s][o]);
						}
		++l, --r;
		zc+=2;
	}
	if(l == r) 
		for(int i = zc; i >= 0; --i)
			for(int j = zc; j >= 0; --j)
				for(int s = (1<<k)-1; s >= 0; --s) 
					for(int o = gc; o >= 0; --o) {
						f[i+1][j][s|hh[l]][o+hs[l]]=upd(f[i+1][j][s|hh[l]][o+hs[l]]+f[i][j][s][o]);
						f[i][j+1][s|ll[l]][o+ls[l]]=upd(f[i][j+1][s|ll[l]][o+ls[l]]+f[i][j][s][o]);
						f[i+1][j+1][s|hh[l]|ll[l]][o+hs[l]+ls[l]-pt[l][l]]=upd(f[i+1][j+1][s|hh[l]|ll[l]][o+hs[l]+ls[l]-pt[l][l]]+f[i][j][s][o]);
					}
	int ret = 0;
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= n; ++j)
			for(int s = 0; s <= (1<<k)-1; ++s)
				for(int o = 0; o <= gc; ++o) {
					// debug(i, j, s, o, f[i][j][s][o], "!!!\n");
					int gg = 0;
					for(int p = 0; p < k; ++p)
						if((s>>p)&1)
							++gg;
					if((n-i)*(n-j)+gg+o-gc-k >= cc)
						ret=((i+j)&1 ? upd(ret-1LL*f[i][j][s][o]%mod*c((n-i)*(n-j)+gg+o-gc-k, cc)%mod+mod): upd(ret+1LL*f[i][j][s][o]%mod*c((n-i)*(n-j)+gg+o-gc-k, cc)%mod));
				}
	return ret;
}

signed main() {
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= 1024; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	read(n), read(k), read(cc);
	for(int i = 1; i <= k; ++i)
		read(xx[i]), read(yy[i]), vis[xx[i]][yy[i]]=1, hh[xx[i]]|=(1<<(i-1)),
		ll[yy[i]]|=(1<<(i-1));
	ans=upd(ans+sol());
	debug(sol(), '\n');
	for(int i = 1; i <= n; ++i)
		if(!vis[i][i])
			pt[i][i]=1, ++hs[i], ++ls[i], ++gc;
	ans=upd(ans-sol()+mod);
	debug(sol(), '\n');
	for(int i = 1; i <= n; ++i)
		if(!vis[i][n-i+1] && !pt[i][n-i+1])
			pt[i][n-i+1]=1, ++hs[i], ++ls[n-i+1], ++gc;
	ans=upd(ans+sol());
	debug(sol(), '\n');
	for(int i = 1; i <= n; ++i)
		if(!vis[i][i] && i+i != n+1)
			pt[i][i]=0, --hs[i], --ls[i], --gc;
	ans=upd(ans-sol()+mod);
	debug(sol(), '\n');
	write(ans, '\n');
	return 0;
}