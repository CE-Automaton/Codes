#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int T, m, n, a[N], b[N];
LL dp[2005];

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
LL abb(LL x) {
	return (x < 0 ? -x : x);
}
void dfs(int s, int now, int sum) {
	if(sum > dp[s]) return ;
	dp[s]=sum;
	if(now == n+1) return ;
	for(int i = 1; i <= n; ++i) {
		if((s>>(i-1))&1) continue;
		dfs(s|(1<<(i-1)), now+1, sum+min(abb(a[i]-b[now]), (LL) m-abb(a[i]-b[now])));
	}
}

signed main() {
	File("road");
	read(T);
	while(T--) {
		read(m), read(n);
		for(int i = 1; i <= n; ++i)
			read(a[i]);
		for(int i = 1; i <= n; ++i)
			read(b[i]);
		for(int i = 0; i < (1<<n); ++i)
			dp[i]=inf;
		dp[0]=0;
		dfs(0, 1, 0);
		write(dp[(1<<n)-1], '\n');
	}
	return 0;
}