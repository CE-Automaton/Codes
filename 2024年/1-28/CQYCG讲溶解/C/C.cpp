#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e3+5;
int n, m, q, dp[N][N], mx[N], l, r, ll, rr;
char s[N], t[N];

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
	File("C");
	read(n), read(m), read(q);
	scanf("%s%s", s+1, t+1);
	for(int i = 1; i <= q; ++i) {
		read(l), read(r), read(ll), read(rr);
		for(int o = 0; o <= r-l+1; ++o)
			for(int p = 0; p <= rr-ll+1; ++p)
				dp[o][p]=0;
		for(int p = 0; p <= rr-ll+1; ++p)
			mx[p]=0;
		for(int o = l; o <= r; ++o) {
			for(int p = 0; p <= rr-ll; ++p)
				if(s[o] == t[p+ll])
					dp[o-l+1][p+1]=max(dp[o-l+1][p+1], dp[o-l][p]+1);
			for(int p = 1; p <= rr-ll+1; ++p)
				mx[p]=max(mx[p], dp[o-l+1][p]);
			for(int p = 1; p <= rr-ll+1; ++p)
				dp[o-l+1][p]=max(dp[o-l+1][p], mx[p]);
		}
		int mxx = 0;
		for(int p = 0; p <= rr-ll+1; ++p)
			mxx=max(mxx, mx[p]);
		write(mxx, '\n');
	}
	return 0;
}