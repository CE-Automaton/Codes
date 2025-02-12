#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, k, a[N], b[N];
LL ans, dp[5005][5005], mn[5005][5005];

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
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	int pd = 1;
	for(int j = 1; j <= n; ++j)
		read(b[j]), pd&=(j == 1 || b[j] >= b[j-1]);
	if(pd) {
		for(int i = 1; i <= n; ++i)
			a[i]+=b[i];
		sort(a+1, a+1+n);
		for(int i = 1; i <= k; ++i)
			ans+=a[i];
		write(ans, '\n');
		return 0;
	}
	for(int j = 1; j <= k; ++j)
		for(int p = 0; p <= n; ++p)
			dp[j][p]=mn[j][p]=inf;
	for(int i = 1; i <= n; ++i) 
		for(int j = min(i, k); j >= max(k-n+i, 1); --j) {
			for(int p = i; p <= n+j-k; ++p)
				dp[j][p]=min(dp[j][p], mn[j-1][p-1]+a[i]+b[p]), 
				mn[j][p]=min(mn[j][p-1], dp[j][p]);
		}
	for(int p = 1; p <= n; ++p)
		mn[k][p]=min(mn[k][p-1], dp[k][p]);
	write(mn[k][n], '\n');
	return 0;
}