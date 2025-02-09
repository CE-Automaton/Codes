#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e5+5;
int n, k, q, a[N], tr[N], ans, dp[505][505][505], sum[505], summ[505], inv, xx, yy;

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
void add(int x) {
	while(x)
		++tr[x], x-=(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x <= n)
		ret+=tr[x], x+=(x&(-x));
	return ret;
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
void sol() {
	ans=0;
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j) {
			int aa = i, bb = j;
			if(a[i] > a[j]) swap(aa, bb);
			ans=upd(ans+dp[k][aa][bb]);
		}
	write(ans, '\n');
}

signed main() {
	File("random");
	read(n), read(k), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	if(k == 0) {
		// debug("!\n");
		for(int i = 1; i <= n; ++i)
			ans=upd(ans+ask(a[i])), add(a[i]);
		write(ans, '\n');
		return 0;
	}
	inv=ksm(1LL*n*(n-1)/2%mod, mod-2);
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j < i; ++j)
			dp[0][i][j]=1, sum[i]=upd(sum[i]+dp[0][i][j]), summ[j]=upd(summ[j]+dp[0][i][j]);
	int gss = (n <= 3 ? 0 : 1LL*(n-2)*(n-3)/2%mod);
	for(int o = 1; o <= k; ++o) {
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) 
				if(i != j) {
					dp[o][i][j]=upd(dp[o-1][j][i]+1LL*gss*dp[o-1][i][j]%mod);
					dp[o][i][j]=upd(dp[o][i][j]+upd(sum[i]-dp[o-1][i][j]+mod));
					dp[o][i][j]=upd(dp[o][i][j]+upd(summ[j]-dp[o-1][i][j]+mod));
					dp[o][i][j]=1LL*dp[o][i][j]*inv%mod;
				}
		for(int i = 1; i <= n; ++i)
			sum[i]=summ[i]=0;
		for(int i = 1; i <= n; ++i) 
			for(int j = 1; j <= n; ++j)
				sum[i]=upd(sum[i]+dp[o][i][j]), summ[j]=upd(summ[j]+dp[o][i][j]);
	}
	sol();
	// debug("???\n");
	for(int i = 1; i <= q; ++i) {
		--k;
		read(xx), read(yy);
		swap(a[xx], a[yy]);
		sol();
	}
	return 0;
}