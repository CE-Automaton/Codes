#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, p, q, op, x, s[N];

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

signed main() {
	File("string");
	read(n), read(q), read(p);
	for(int i = 1; i <= n; ++i)
		read(s[i]);
	while(q--) {
		read(op), read(x);
		int ans = 0;
		if(op == 1) {
			for(int b = 0; b < p; ++b) {
				for(int l = 1; l <= n; ++l)
					for(int r = l; r <= n; ++r) {
						int pd = 1;
						for(int o = 1; o*2 <= r-l+2; ++o)
							pd&=((1LL*x*s[l+o-1]%p+b)%p == s[r-o+1] && (1LL*x*s[r-o+1]%p+b)%p == s[l+o-1]);
						ans+=pd;
					}
			}
		}
		else {
			int b = x;
			for(x = 0; x < p; ++x) {
				for(int l = 1; l <= n; ++l)
					for(int r = l; r <= n; ++r) {
						int pd = 1;
						for(int o = 1; o*2 <= r-l+2; ++o)
							pd&=((1LL*x*s[l+o-1]%p+b)%p == s[r-o+1] && (1LL*x*s[r-o+1]%p+b)%p == s[l+o-1]);
						ans+=pd;
					}
			}
		}
		write(ans, '\n');
	}
	return 0;
}