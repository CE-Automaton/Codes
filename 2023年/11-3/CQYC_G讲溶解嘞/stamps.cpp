#include <bits/stdc++.h>
using namespace std;
const int N = 2e3+5;
int n, m, kk, mx[N], mn[N], dp[N][N], ans;
struct qwq {
	int l, r;
}g[N];

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
	return A.l < B.l;
}

signed main() {
//	freopen("stamps.in", "r", stdin);
//	freopen("stamps.out", "w", stdout);
	read(n), read(m), read(kk);
	for(int i = 1; i <= m; ++i)
		read(g[i].l), read(g[i].r);
	sort(g+1, g+1+m, comp);
	for(int i = 1, l = 1; i <= n; ++i) {
		mx[i]=mx[i-1];
		while(l <= m && g[l].l <= i)
			mx[i]=max(mx[i], g[l].r), ++l;
	}
	for(int i = 1; i <= kk; ++i) {
		mn[1]=dp[1][i-1];
		for(int j = 2; j <= n; ++j)
			mn[j]=max(dp[j][i-1], mn[j-1]);
		for(int j = 1; j <= n; ++j)
			if(mx[j] >= j)
				dp[mx[j]+1][i]=max(dp[mx[j]+1][i], dp[j][i]+mx[j]-j+1);
	}
	for(int x = 1; x <= n+1; ++x)
		ans=max(ans, dp[x][kk]);
	write(ans, '\n');
	return 0;
}
