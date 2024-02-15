#include <bits/stdc++.h>
#define mod 10000
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int k, t, n, nxt[N], a[N], vis[N], pw[N], ans;

template <typename T> inline void debug(T x) { cerr<<x<<'\n'; }
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

signed main() {
	read(k), read(t);
	pw[0]=1;
	for(int i = 1; i <= 100000; ++i)
		pw[i]=1LL*pw[i-1]*k%mod;
	while(t--) {
		read(n);
		ans=0;
		for(int i = 1; i <= n; ++i)
			read(a[i]), vis[i]=0;
		for(int i = 2, j = 0; i <= n; ++i) {
			while(j && a[j+1] != a[i]) j=nxt[j];
			if(a[j+1] == a[i]) ++j;
			nxt[i]=j;
		}
		int now = n;
		while(now) 
			ans=upd(ans+pw[now]), now=nxt[now];
		if(ans < 1000) putchar('0');
		if(ans < 100) putchar('0');
		if(ans < 10) putchar('0');
		write(ans, '\n');
	}
	return 0;
}