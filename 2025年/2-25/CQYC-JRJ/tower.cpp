#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, ll[N<<1], rr[N], tt, ans;
LL k, a[N], b[N], mx[N<<1];

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
int ef(LL x) {
	int l = 1, r = tt, ret = 0;
	while(l <= r) {
		int mid = ((l+r)>>1);
		if(x <= mx[mid])
			ret=mid, l=mid+1;
		else
			r=mid-1;
	}
	return ret;
}
int sol(int rx, LL pp) {
	int l = 1, r = rx, to = 0;
	while(l <= r) {
		int mid = ((l+r)>>1);
		if(pp <= mx[mid])
			to=mid, l=mid+1;
		else
			r=mid-1;
	}
	return upd(upd(1LL*(to+1)*(pp%mod)%mod+upd(ll[rx]-ll[to]+mod))-1LL*(rx+1)*tt%mod+mod);
}

signed main() {
	File("tower");
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(a[i]), b[i]=(a[i] == -1 ? 0 : a[i]);
	if(n == 1) {
		puts("-1");
		return 0;
	}
	ll[1]=rr[n]=1;
	for(int i = 2; i <= n; ++i)
		ll[i]=(ll[i-1]&((b[i] == 0 || b[i-1] == 0) ? 1 : (b[i] <= k/b[i-1])));
	for(int i = n-1; i >= 1; --i)
		rr[i]=(rr[i+1]&((b[i] == 0 || b[i+1] == 0) ? 1 : (b[i] <= k/b[i+1])));
	if(ll[n] == 0) {
		puts("0");
		return 0;
	}
	for(int i = 1; i+2 <= n; ++i)
		if(a[i] <= 0 && a[i+1] == -1 && a[i+2] <= 0 && ll[i] && rr[i+2]) {
			puts("-1");
			return 0;
		}
	int l = 1, r = 1000000;
	while(l <= r) {
		int mid = ((l+r)>>1);
		if(1LL*mid*mid*mid <= k)
			tt=mid, l=mid+1;
		else
			r=mid-1;
	}
	mx[0]=k;
	ll[0]=1LL*k%mod;
	for(int i = 1; i <= tt; ++i)
		mx[i]=k/i/i, ll[i]=upd(ll[i-1]+(1LL*mx[i]%mod));
	ans=1;
	for(int i = 1; i <= n; ++i) 
		if(a[i] == -1) {
			if(a[i+1] == -1) {
				LL ls = (i == 1 || a[i-1] == 0 ? k : (a[i-1] > tt ? ef(a[i-1]) : k/a[i-1]/a[i-1])), 
				 rs = (i+1 == n || a[i+2] == 0 ? k : (a[i+2] > tt ? ef(a[i+2]) : k/a[i+2]/a[i+2]));
				int now = 1LL*(min(ls, (LL) tt)+1)*(min(rs, (LL) tt)+1)%mod;
				// debug(now, "?????\n");
				if(ls > tt)
					now=upd(now+sol(min(rs, (LL) tt), ls));
				if(rs > tt)
					now=upd(now+sol(min(ls, (LL) tt), rs));
				// debug(ls, rs, now, "!?!?!?!?\n");
				ans=1LL*ans*now%mod;
				++i;
				continue;
			}
			LL ls = (i == 1 || a[i-1] == 0 ? k : (a[i-1] > tt ? ef(a[i-1]) : k/a[i-1]/a[i-1])), 
			 rs = (i+1 == n || a[i+1] == 0 ? k : (a[i+1] > tt ? ef(a[i+1]) : k/a[i+1]/a[i+1]));
			ans=1LL*ans*((min(ls, rs)+1)%mod)%mod;
		}
	write(ans, '\n');
	return 0;
}
