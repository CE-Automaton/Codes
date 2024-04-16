#include <bits/stdc++.h>
#define mod 998244353
#define inv2 499122177
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, m, k, s[N], sum[N], pw[N], pw_v[N], jc[N], inv[N], inc[N], ans, sm[451][N], vis[N], tot;

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
void sol() {
	if(!vis[k]) {
		vis[k]=++tot;
		for(int i = n; i <= n+n; ++i)
			sm[tot][i]=upd(sm[tot][i-1]+1LL*jc[i-1-k]*inc[i-n]%mod*pw_v[i]%mod);
	}
}

signed main() {
	File("coin");
	read(n), read(m);
	pw[0]=pw_v[0]=jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1, pw_v[1]=inv2, pw[1]=2;
	for(int i = 2; i <= n+n; ++i)
		pw_v[i]=1LL*pw_v[i-1]*inv2%mod, inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod,
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod, pw[i]=upd(pw[i-1]+pw[i-1]);
	for(int i = n; i <= n+n; ++i)
		sum[i]=upd(sum[i-1]+1LL*jc[i-1]*inc[i-n]%mod*pw_v[i]%mod);
	while(m--) {
		read(k);
		for(int i = 1; i <= k; ++i)
			read(s[i]);
		if(k > n) {
			puts("0");
			continue;
		}
		sort(s+1, s+1+k);
		s[k+1]=n+n+1;
		ans=0;
		for(int i = 0; i <= k; ++i) {
			if(n+i >= s[i+1] || s[i]+1 == s[i+1])
				continue;
			int l = max(s[i]+1, n+i), r = s[i+1]-1;
			// debug(i, s[i], n+i, s[i+1], l, r, "!!!\n");
			l-=i, r-=i+(r == 2*n);
			ans=upd(ans+1LL*upd(sum[r]-sum[l-1]+mod)*pw_v[i]%mod);
		}
		ans=1LL*ans*inc[n-1]%mod;
		if(s[k] >= n && s[k] != 2*n)
			ans=upd(ans+1LL*c(s[k]-k, n-k)*pw_v[s[k]]%mod);
		if(k != n) {
			int l = max(s[k]+1, n), r = 2*n-1;
			sol();
			if(l <= r)
				ans=upd(ans+1LL*upd(sm[vis[k]][r]-sm[vis[k]][l-1]+mod)*inc[n-1-k]%mod);
		}
		write(upd(ans+ans), '\n');
	}
	return 0;
}