#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, a[N], l, r, q;
LL sum[N];
struct qwq {
	LL a;
	int b;
	bool operator <(const qwq& A) const {
		return 1LL*a*A.b < 1LL*A.a*b;
	}
	void ccc() {
		LL op = __gcd(a, 1LL*b);
		a=a/op, b=1LL*b/op;
	}
}dp[N][20];

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
	File("value");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), sum[i]=sum[i-1]+a[i];
	for(int len = 1; len <= min(n, 50); ++len)
		for(int i = 1, j = len; j <= n; ++i, ++j) {
			dp[i][len]=qwq {1LL*(sum[j]-sum[i-1])*(sum[j]-sum[i-1]), j-i+1};
			if(len >= 2) {
				if(dp[i][len] < dp[i+1][len-1])
					dp[i][len]=dp[i+1][len-1];
				if(dp[i][len] < dp[i][len-1])
					dp[i][len]=dp[i][len-1];
			}
		}
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(l), read(r);
		qwq ans = qwq {0, 1};
		for(int o = l; o <= r; ++o)
			if(ans < dp[o][max(min(n-o+1, 50), r-o+1)])
				ans=dp[o][max(min(n-o+1, 50), r-o+1)];
		ans.ccc();
		write(ans.a, ' '), write(ans.b, '\n');
	}
	return 0;
}