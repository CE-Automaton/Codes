#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 5e5+5;
int n, m, p[N], b[N], t[N], xx[N], yy[N], cc[N], a[N], sum[N], ans = inf;
struct qwq {
	int x, s;
};
vector <qwq> az[N];

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
void dfs(int x) {
	if(x == n+1) {
		int summ = 0;
		for(int i = 1; i <= n; ++i)
			if(sum[p[i]]-sum[i-1] < b[i])
				summ+=t[i];
		ans=min(ans, summ);
		return ;
	}
	for(int i = 0; i <= b[i]; ++i) {
		a[x]=i, sum[x]=sum[x-1]+a[x];
		for(qwq j : az[x])
			if(sum[x]-sum[j.x-1] > j.s)
				return ;
		dfs(x+1);
	}
}

signed main() {
	freopen("envelope.in", "r", stdin);
	freopen("envelope.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(p[i]), read(b[i]), read(t[i]);
	for(int i = 1; i <= m; ++i)
		read(xx[i]), read(yy[i]), read(cc[i]), az[yy[i]].push_back(qwq {xx[i], cc[i]});
	dfs(1);
	write(ans, '\n');
	return 0;
}
