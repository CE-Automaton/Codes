#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
// bool st;
int n, m, ans[N], jc[N], inv[N], inc[N], 
dp[51][2001][2001], ss[51][2001];

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
inline int upd(int x) {
	return (x >= mod ? x-mod : x);
}
inline int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
inline int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
// bool fn;
signed main() {
	File("double");
	// debug((double) 1.0*(&st-&fn)/1024/1024, "MB!\n");
	read(n), read(m);
	inv[0]=inv[1]=inc[0]=inc[1]=jc[0]=jc[1]=1;
	for(int i = 2; i <= m; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
		inc[i]=1LL*inc[i-1]*inv[i]%mod, jc[i]=1LL*jc[i-1]*i%mod;
	if(n == 1) {
		write((m+1)/2, '\n');
		return 0;
	}
	if(n == 2) {
		for(int i = 1; i*2 <= m; ++i)
			ans[1]=upd(ans[1]+1LL*i*inv[2]%mod), 
			ans[2]=upd(ans[2]+1LL*i*inv[2]%mod);
		for(int i = 1; i*2 <= m; ++i) {
			int r = m-i*2;
			ans[1]=upd(ans[1]+1LL*i*r%mod);
		}
		for(int i = 1; i <= m; ++i) {
			int l = min(i-1, m-i);
			ans[2]=upd(ans[2]+1LL*i*l%mod);
		}
		int cc = ksm(c(m,n), mod-2);
		write(1LL*ans[1]*jc[n]%mod*cc%mod, '\n'),
		write(1LL*upd(ans[1]+ans[2])*jc[n]%mod*cc%mod, '\n');
		return 0;
	}
	if(n <= 50 && m <= 2000) {
		dp[0][m-n+2][0]=1;
		for(int i = 0; i <= n; ++i) {
			for(int j = m-n+1; j >= 2; --j)
				for(int ls = 0; ls <= m; ++ls)
					dp[i][j][ls]=upd(dp[i][j][ls]+dp[i][j+1][ls]);
			for(int j = 2; j <= m-n+1; ++j)
				for(int ls = 0; ls+j <= m; ++ls)
					if(dp[i][j+1][ls])
						for(int p = 1; j*p+ls <= m && i+p <= n; ++p) 
							dp[i+p][j][ls+j*p]=upd(dp[i+p][j][ls+j*p]+1LL*dp[i][j+1][ls]*inc[p]%mod);
		}
		for(int i = 0; i <= n; ++i) 
			for(int j = m-n+1; j >= 2; --j)
				for(int ls = 1; ls <= m; ++ls)
					dp[i][j][ls]=upd(dp[i][j][ls-1]+dp[i][j][ls]);
		ss[0][0]=1;
		for(int i = 1; i <= m-n+1; ++i)
			for(int j = n-1; j >= 0; --j)
				for(int ls = m-i; ls >= 0; --ls)
					if(ss[j][ls])
						for(int p = 1; i*p+ls <= m && j+p <= n; ++p) {
							int rr = 1LL*ss[j][ls]*inc[p]%mod;
							ss[j+p][ls+i*p]=upd(ss[j+p][ls+i*p]+rr);
							rr=1LL*rr*i%mod*dp[n-j-p][i+1][m-ls-i*p]%mod;
							ans[j+1]=upd(ans[j+1]+rr);
							ans[j+p+1]=upd(ans[j+p+1]-rr+mod);
						}
		for(int i = 1; i <= n; ++i)
			ans[i]=upd(ans[i-1]+ans[i]);
		for(int i = 1; i <= n; ++i)
			ans[i]=upd(ans[i-1]+ans[i]);
		int cc = ksm(c(m, n), mod-2)%mod;
		for(int i = 1; i <= n; ++i)
			write(1LL*ans[i]*jc[n]%mod*cc%mod, '\n');
		// debug(clock(), "?\n");
		return 0;
	}
	return 0;
}
