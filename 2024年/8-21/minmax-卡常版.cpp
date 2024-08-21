#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int n, a[N], b[N], dp[2][N], dpp[2][N], c[N][N], f[N], ff[N], jc[N];

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
int comp(int A, int B) {
	return A > B;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("minmax");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), b[i]=a[i];
	jc[0]=1;
	for(int i = 0; i <= n; ++i)
		c[i][0]=1;
	for(int i = 1; i <= n; ++i) {
		jc[i]=1LL*jc[i-1]*i%mod;
		for(int j = 1; j <= n; ++j)
			c[i][j]=upd(c[i-1][j]+c[i-1][j-1]);
	}
	sort(a+1, a+1+n, comp);
	dp[0][0]=1;
	int now = 0, gs = 0;
	for(int l = 1; l <= n; ++l) {
		int r = l;
		while(r+1 <= n && a[r+1] == a[l]) ++r;
		gs+=r-l+1;
		a[l]=upd(upd(a[l]+mod)+mod);
		now^=1;
		for(int j = 0; j <= gs; ++j)
			dp[now][j]=0, f[j]=0;
		for(int j = 0; j+r-l <= gs; ++j)
			f[j+r-l]=1LL*dp[now^1][j]*c[j+r-l][r-l]%mod*jc[r-l]%mod, 
			dp[now][j+r-l+1]=upd(dp[now][j+r-l+1]+1LL*dp[now^1][j]*c[j+r-l+1][r-l+1]%mod*jc[r-l+1]%mod);
		int sum = 0;
		for(int j = gs; j >= 0; --j)
			sum=upd(sum+f[j]), dp[now][j]=upd(dp[now][j]+1LL*(r-l+1)*sum%mod*a[l]%mod), sum=1LL*sum*a[l]%mod;
		l=r;
	}
	write(dp[now][0], ' ');
	sort(b+1, b+1+n);
	dpp[0][0]=1;
	now = 0;
	int gss = 0;
	for(int l = 1; l <= n; ++l) {
		int r = l;
		while(r+1 <= n && b[r+1] == b[l]) ++r;
		gss+=r-l+1;
		b[l]=upd(upd(b[l]+mod)+mod);
		now^=1;
		for(int j = 0; j <= gss; ++j)
			dpp[now][j]=0, ff[j]=0;
		for(int j = 0; j+r-l <= gss; ++j)
			ff[j+r-l]=1LL*dpp[now^1][j]*c[j+r-l][r-l]%mod*jc[r-l]%mod, 
			dpp[now][j+r-l+1]=upd(dpp[now][j+r-l+1]+1LL*dpp[now^1][j]*c[j+r-l+1][r-l+1]%mod*jc[r-l+1]%mod);
		int sum = 0;
		for(int j = gss; j >= 0; --j)
			sum=upd(sum+ff[j]), dpp[now][j]=upd(dpp[now][j]+1LL*(r-l+1)*sum%mod*b[l]%mod), sum=1LL*sum*b[l]%mod;
		l=r;
	}
	write(dpp[now][0], '\n');
	return 0;
}