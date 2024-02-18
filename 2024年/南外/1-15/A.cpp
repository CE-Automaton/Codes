#include <bits/stdc++.h>
#define inf 100000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e4+5;
LL n, m, p[N], dp[N], cp[N], sum[N], cc, ee, ans;

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
int comp(int A, int B) {
	return A > B;
}

signed main() {
	File("bread");
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(p[i]);
	sort(p+1, p+1+n, comp);
	for(int i = 1; i <= n+1; ++i)
		dp[i]=inf;
	for(int i = 1; i <= m; ++i) {
		read(cc), read(ee);
		for(int j = 1; j <= n+1; ++j)
			cp[j]=dp[j];
		for(int j = 0; j <= n+1; ++j)
			if(j+cc > n)
				dp[n+1]=min(dp[n+1], cp[j]+ee);
			else
				dp[j+cc]=min(dp[j+cc], cp[j]+ee);
	}
	for(int i = 1; i <= n+1; ++i)
		sum[i]=sum[i-1]+p[i], 
		ans=max(ans, sum[i]-dp[i]);
	write(ans, '\n');
	return 0;
}