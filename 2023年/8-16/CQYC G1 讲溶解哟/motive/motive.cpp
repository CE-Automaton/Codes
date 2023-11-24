#include <bits/stdc++.h>
using namespace std;
int n, mod, a[1005], mx[1005][1005], mn[1005][1005], sum[1005], inv[1005], ans;

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
	freopen("motive.in", "r", stdin);
	freopen("motive.out", "w", stdout);
	read(n), read(mod);
	for(int i = 1; i <= n; ++i)
		read(a[i]), mx[i][i]=mn[i][i]=a[i], sum[i]=upd(sum[i-1]+a[i]%mod);
	for(int len = 2; len <= n; ++len)
		for(int i = 1, j = len; j <= n; ++i, ++j) 
			mx[i][j]=max(mx[i][j-1], a[j]), mn[i][j]=min(mn[i][j-1], a[j]);
	inv[1]=1;
	inv[2]=1LL*inv[mod%2]*(mod-mod/2)%mod;
	for(int len = 3; len <= n; ++len) {
		inv[len]=1LL*inv[mod%len]*(mod-mod/len)%mod;
		int sm = 0;
		for(int i = 1, j = len; j <= n; ++i, ++j)
			sm=upd(sm+upd(upd(upd(sum[j]-sum[i-1]+mod)-mx[i][j]%mod+mod)-mn[i][j]%mod+mod));
		ans=upd(ans+1LL*sm*inv[len-2]%mod);
	}
	ans=1LL*ans*ksm(1LL*(n-2)*(n-1)/2%mod, mod-2)%mod;
	write(ans, '\n');
	return 0;
}
