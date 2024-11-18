#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+5;
int n, m, jc[N], inv[N], inc[N], a[2][N/*填了总共i个了*/][N/*填了j组*/], ans;

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
void addd(int &x, int y) {
	x+=y, x=(x >= mod ? x-mod : x);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int ccc(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod, y=(y>>1);
	}
	return ret;
}

signed main() {
	File("battle");
	read(n), read(m);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	int now = 0;
	a[0][0][0]=1;
	for(int i = 1; i <= n; ++i) {//这次填i个
		now^=1;
		for(int k = 0; k <= n; ++k)
			for(int o = 0; o <= k; ++o)
				a[now][k][o]=0;
		for(int k = 0; k <= n-i; ++k)
			for(int o = 0; o <= k; ++o)
				if(a[now^1][k][o])
					for(int j = 1, sum = 1; k+i*j <= n; ++j) //填j组
						sum=1LL*sum*ccc(k+i*j, i)%mod, addd(a[now][k+i*j][o+j], 1LL*a[now^1][k][o]*sum%mod*inc[j]%mod);
		for(int o = 1, sum = 1; o <= n; ++o)
			sum=1LL*sum*(m-o+1)%mod, addd(ans, 1LL*a[now][n][o]*sum%mod*i%mod);
		for(int k = 0; k <= n; ++k)
			for(int o = 0; o <= k; ++o)
				addd(a[now][k][o], a[now^1][k][o]);
	}
	write(1LL*ans*ksm(ksm(m, n), mod-2)%mod, '\n');
	// debug(clock(), '\n');
	return 0;
}