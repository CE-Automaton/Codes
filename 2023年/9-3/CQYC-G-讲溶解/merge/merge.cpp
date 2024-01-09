#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int N = 2e5+5;
int n, k, u, v, c[N], vis[N], pd[N], zhan[N], tot, col, sum;
vector <int> to[N], tc[N];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char chh = getchar();
	while(chh < '0' || chh > '9') f |= (chh == '-'), chh=getchar();
	while(chh >= '0' && chh <= '9') x=(x<<1)+(x<<3)+(chh^48), chh=getchar();
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
	zhan[++tot]=x;
	if(c[x] == col) {
		for(int i = 1; i <= tot; ++i)
			vis[c[zhan[i]]]=1, pd[zhan[i]]=1;
		tot=0;
	}
	for(int y : to[x])
		if(y != fa)
			dfs(y, x);
	if(pd[x] == 0)
		--tot;
}

signed main() {
	freopen("merge.in", "r", stdin);
	freopen("merge.out", "w", stdout);
	read(n), read(k);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i)
		read(c[i]), tc[c[i]].push_back(i);
	sum=k;
	for(int i = 1; i <= k; ++i) {
		col=i;
		dfs(tc[i][0], 0);
		int ans = 0;
		for(int j = 1; j <= k; ++j)
			ans+=vis[j], vis[j]=0;
		for(int o = 1; o <= n; ++o)
			pd[o]=0;
//		cout<<ans-1<<" "<<i<<"\n";
		sum=min(sum, ans-1);
	}
	write(sum, '\n');
	return 0;
}
