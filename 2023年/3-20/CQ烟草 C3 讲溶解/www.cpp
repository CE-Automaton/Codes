#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int n, a[N], u, v, tot, zhan[N], gs[N], ans;
vector <int> to[N];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
void dfs(int x, int fa) {
	zhan[tot++]=a[x];
	++gs[a[x]];
	int pd = 0;
	for(int i = 0; i < tot; ++i)
		if(gs[i] != zhan[i] || zhan[i] >= tot)
			pd|=1;
	ans+=(pd == 0);
	for(auto i : to[x])
		if(i != fa)
			dfs(i, x);
	--tot;
	--gs[a[x]];
}

signed main() {
	freopen("www.in", "r", stdin);
	freopen("www.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i)
		dfs(i, i);
	write(ans);
	return 0;
}
