#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e3+5;
bitset<N> to[N], ss;
int n, m, a[N], u, v, ans;

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
//	freopen("poker.in", "r", stdin);
//	freopen("poker.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u][v]=1, to[v][u]=1;
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j) {
			ss=(to[i]&to[j]);
			int gs = ss.count();
			ans=upd(ans+1LL*gs*(gs-1)/2%mod*upd(a[i]+a[j]));
		}
	write(ans, '\n');
	return 0;
}
