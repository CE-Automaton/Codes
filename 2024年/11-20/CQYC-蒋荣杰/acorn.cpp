#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, a[N];
LL dp[N];

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
	File("acorn");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), dp[i]=inf;
	sort(a+1, a+1+n);
	for(int i = 2; i <= n; ++i) {
		if(i >= 3)
			dp[i]=min(dp[i], dp[i-3]-a[i-2]+a[i]);
		dp[i]=min(dp[i], dp[i-2]+a[i]-a[i-1]);
	}
	write(dp[n], '\n');
	return 0;
}