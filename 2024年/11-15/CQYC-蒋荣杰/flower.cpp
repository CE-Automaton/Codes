#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, a[N], vis[N], tr[N], dp[N];
LL ans;

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
LL abb(int x, int y) {
	return (x >= y ? x-y : 0);
}
void add(int x, int w) {
	while(x >= 1)
		tr[x]+=w, x-=(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x <= n)
		ret+=tr[x], x+=(x&(-x));
	return ret;
}

signed main() {
	File("flower");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), vis[a[i]]=i, ans=ans+ask(a[i]), add(a[i], 1);
	for(int i = 1; i <= n; ++i) {
		if(i+1 <= n)
			dp[i+1]=max(dp[i+1], dp[i-1]+(vis[i+1] < vis[i]));
		dp[i]=max(dp[i], dp[i-1]);
	}
	write(ans-dp[n], '\n');
	return 0;
}