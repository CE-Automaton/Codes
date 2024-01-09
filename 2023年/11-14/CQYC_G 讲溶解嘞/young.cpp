#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e5+5;
int n, u, v, c[N], e[N], tot, zhan[N];
long long sum[N];
vector <int> to[N];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs(int x, int fa) {
	zhan[++tot]=x;
	int st = tot;
	for(int y : to[x])
		if(y != fa) {
			int lst = tot;
			dfs(y, x);
			sum[x]=upd(sum[x]+sum[y]);
			for(int i = st; i <= lst; ++i)
				for(int j = lst+1; j <= tot; ++j)
					sum[x]=upd(sum[x]+upd(2*min(abs(e[zhan[i]]-e[zhan[j]]), abs(c[zhan[i]]-c[zhan[j]]))));
		}
}

signed main() {
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i)
		read(c[i]), read(e[i]);
	dfs(1, 0);
	for(int i = 1; i <= n; ++i)
		write(sum[i], '\n');
	return 0 ;
}
