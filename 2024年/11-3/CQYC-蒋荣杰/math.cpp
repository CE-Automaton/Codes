#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int t, gs[15], a, b, n[N], m[N];
LL ans[N*N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}

signed main() {
	File("math");
	read(t);
	while(t--) {
		read(a), read(b);
		for(int i = 1; i <= 9; ++i)
			read(gs[i]);
		if(a < b) swap(a, b);
		int now = 9, aa = a, bb = b, op = 1;
		while(a > 0 && b > 0) {
			--b, m[b]=now;
			--gs[now], now=(!gs[now] ? now-1 : now);
			--a, n[a]=now;
			--gs[now], now=(!gs[now] ? now-1 : now);
			if(m[b] != n[a]) break;
		}
		while(a > 0 && b > 0) {
			--a, n[a]=now;
			--gs[now], now=(!gs[now] ? now-1 : now);
			--b, m[b]=now;
			--gs[now], now=(!gs[now] ? now-1 : now);
		}
		while(a > 0) {
			--a, n[a]=now;
			--gs[now], now=(!gs[now] ? now-1 : now);
		}
		// for(int i = aa-1; i >= 0; --i)
		// 	debug(n[i]);
		// debug('*');
		// for(int i = bb-1; i >= 0; --i)
		// 	debug(m[i]);
		// debug('\n');
		for(int i = 0; i < aa; ++i)
			for(int j = 0; j < bb; ++j) {
				ans[i+j+1]+=n[i]*m[j]/10;
				ans[i+j]+=n[i]*m[j]%10;
			}
		for(int i = 0; i <= aa*bb; ++i)
			ans[i+1]+=ans[i]/10, ans[i]%=10;
		aa=aa*bb+5;
		while(ans[aa] == 0)
			--aa;
		for(int i = aa; i >= 0; --i)
			write(ans[i]), ans[i]=0;
		putchar('\n');
	}
	return 0;
}