#include <bits/stdc++.h>
#define mod 41719
using namespace std;
const int N = 1e7+5;
int n, a[N], to[N], ans=1;

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

signed main() {
	freopen("arena.in", "r", stdin);
	freopen("arena.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) 
		read(a[i]), to[a[i]]=i;
	for(int i = 0, l = to[0], r = to[0]; i <= n-2; ++i) {
		l=min(l, to[i]);
		r=max(r, to[i]);
		int nxt = to[i+1];
		if(r-l+1 > 2*i+2 || l <= nxt && nxt <= r) continue;
		if(nxt <= l) {
			int w = l+2*i+2-r;
			if(r+w-1 <= n)
				ans=(ans+(1LL*w*(w+1)/2-(l-w+1 > nxt ? 0 : 1LL*(w-l+nxt)*(w-l+nxt+1)/2))%mod)%mod;
			else {
				int ww=n-r+1;
				ans=(ans+1LL*(w-ww)*ww%mod)%mod;
				ans=(ans+1LL*ww*(ww+1)/2%mod)%mod;
				if(l-w+1 <= nxt) {
					w=w-l+nxt;
					if(w > ww) 
						ans=(ans-1LL*(w-ww)*ww%mod+mod)%mod;
					ans=(ans-1LL*min(ww, w)*(min(ww, w)+1)/2%mod+mod)%mod;
				}
			}
		}
		if(nxt >= r) {
			int w = l+2*i+2-r;
			if(r+w-1 < nxt)
				ans=(ans+(1LL*w*(w+1)/2-(l-w+1 > 0 ? 0 : 1LL*(w-l)*(w-l+1)/2))%mod)%mod;
			else {
				int ww=nxt-r;
				ans=(ans+1LL*(w-ww)*ww%mod)%mod;
				ans=(ans+1LL*ww*(ww+1)/2%mod)%mod;
				if(l-w+1 <= 0) {
					w=w-l;
					if(w > ww) 
						ans=(ans-1LL*(w-ww)*ww%mod+mod)%mod;
					ans=(ans-1LL*min(ww, w)*(min(ww, w)+1)/2%mod+mod)%mod;
				}
			}
		}
//		cout<<i<<" "<<ans<<"!!!\n";
	}
	write((1LL*n*(n+1)/2-ans)%mod, '\n');
	return 0;
}
