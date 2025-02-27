#include <bits/stdc++.h>
#define inf 1000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n;
LL dp[N], ans;
struct qwq {
	int a, b;
}aa[N];

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
int comp(qwq A, qwq B) {
	return A.b < B.b;
}

signed main() {
	File("cooking");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(aa[i].a);
	for(int i = 1; i <= n; ++i)
		read(aa[i].b), dp[i]=inf;
	sort(aa+1, aa+1+n, comp);
	int st = 0;
	for(int i = 1; i <= n; ++i) {
		while(st+1 < i && dp[st+1] <= aa[i].b)
			++st;
		for(int j = i-1; j >= st; --j)
			dp[j+1]=min(dp[j+1], (LL) max(dp[j], (LL) aa[i].b)+aa[i].a);
	}
	for(int i = 1; i <= n; ++i)
		ans^=dp[i]/*, debug(dp[i]), debug(' ')*/;
	write(ans, '\n');
	return 0;
}
