#include <bits/stdc++.h>
using namespace std;
const int N = 5e3+5;
int n, u, v, w, m, siz[N], sum, up[N];
long long dp[100005], ans, mx;
struct qwq {
	int t, d;
};
vector <qwq> to[N];

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
void dfs(int x, int fa) {
	siz[x]=1;
	for(qwq y : to[x])
		if(y.t != fa)
			up[y.t]=y.d, dfs(y.t, x), siz[x]+=siz[y.t];
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n), read(m);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), read(w), to[u].push_back(qwq {v, w}), to[v].push_back(qwq {u, w});
	dfs(1, 0);
	for(int i = 2; i <= n; ++i)
		sum+=siz[i], ans=ans+1LL*siz[i]*(n-siz[i])*up[i];
	if(m >= sum) {
		puts("0");
		return 0;
	}
	sum=0;
	for(int i = 2; i <= n; ++i) {
		for(int j = min(sum, m-siz[i]); j >= 0; --j)
			dp[j+siz[i]]=max(dp[j+siz[i]], dp[j]+1LL*up[i]*siz[i]*(n-siz[i]));
		sum=min(m, sum+siz[i]);
	}
	for(int i = 0; i <= m; ++i) 
		mx=max(mx, dp[i]);
	write(ans-mx, '\n');
	return 0;
}
