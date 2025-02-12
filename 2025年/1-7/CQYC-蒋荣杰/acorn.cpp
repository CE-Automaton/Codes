#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, k, t, v, s, a[N], nb[N], b[N], vis[N], ans[N];

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
	return (x >= k ? x-k : x);
}
void genshin(int x) {
	if(a[x] < 0 && a[x] == 1-k)
		a[x]=1;
	if(a[x] > 0 && a[x] == k-1)
		a[x]=-1;
}
void sol(int j) {
	if(a[j] > 0) {
		// if(ans[(j+t-2)%n+1] != 0)
		// 	debug("???\n");
		--a[j], ++a[(j+t-1)%n+1], ans[(j+t-2)%n+1]=1;
	}
	// for(int i = 1; i <= n; ++i)
	// 	debug(a[i]), debug(' ');
	// debug('\n');
	// for(int i = 1; i <= n; ++i)
	// 	debug(ans[i]), debug(' ');
	// debug("\n--------------------\n");
}

signed main() {
	File("acorn");
	read(n), read(k), read(t);
	for(int i = 1; i <= n; ++i)
		read(b[i]);
	int pd = 1, sum = 0;
	for(int i = 1; i <= n; ++i)
		a[i]=upd((b[i]-b[(i == 1 ? n : i-1)])%k+k);
	for(int i = 1; i <= n; ++i)
		sum=upd(a[i]+sum);
	if(sum != 0) {
		puts("No");
		return 0;
	}
	for(int i = 1; i <= n; ++i) 
		if(a[i] == k-1)
			a[i]=-1;
	v=__gcd(n, t);
	// for(int i = 1; i <= n; ++i)
	// 	debug(a[i]), debug(' ');
	// debug('\n');
	for(int i = 1; i <= v; ++i) {
		sol(i);
		for(int j = (i+t-1)%n+1; j != i; j = (j+t-1)%n+1)
			sol(j);
		sol(i);
		for(int j = (i+t-1)%n+1; j != i; j = (j+t-1)%n+1)
			sol(j);
	}
	for(int i = 1; i <= n; ++i)
		if(a[i] != 0) 
			pd=0;
	// for(int i = 1; i <= n; ++i)
	// 	debug(ans[i]), debug(' ');
	// debug('\n');
	if(!pd) {
		puts("No");
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		nb[i]=nb[i-1]+ans[i];
	int nd = b[1]-(nb[t]%k);
	if(nd < 0) 
		nd+=k;
	for(int i = 1; i <= v && nd >= 1; ++i) {
		int now = (ans[i]^1);
		for(int j = (i+t-1)%n+1; j != i; j = (j+t-1)%n+1)
			now&=(ans[j]^1);
		if(now) {
			nd=upd(nd-t/v%k+k);
			ans[i]=1;
			for(int j = (i+t-1)%n+1; j != i; j = (j+t-1)%n+1)
				ans[j]=1;
		}
	}
	if(nd != 0) {
		// debug(nd, "?\n");
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i = 1; i <= n; ++i)
		write(ans[i], ' ');
	return 0;
}
