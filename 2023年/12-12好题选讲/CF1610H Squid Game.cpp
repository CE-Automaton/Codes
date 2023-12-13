#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int n, m, u, dep[N], jp[N][20], dp[N], ans;
vector <int> to[N], too[N];
struct bian {
	int u, v, pd;
}a[N];

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
	dep[x]=dep[fa]+1, jp[x][0]=fa;
	for(int i = 1; i <= 19; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1];
	for(int y : to[x])
		dfs(y, x);
}
int ask(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 19; i >= 0; --i) if(dep[jp[x][i]] >= dep[y])
		x=jp[x][i];
	for(int i = 19; i >= 0; --i) if(jp[x][i] != jp[y][i])
		x=jp[x][i], y=jp[y][i];
	if(x != y)
		x=jp[x][0];
	return x;
}
int ask2(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 19; i >= 0; --i) if(dep[jp[x][i]] >= dep[y]+1)
		x=jp[x][i];
	return x;
}
void dfs2(int x) {
	dp[x]=0;
	for(int y : to[x])
		dfs2(y), dp[x]+=dp[y];
	for(int y : too[x])
		dp[x]=max(dp[x], dp[y]+1);
}

signed main() {
	read(n), read(m);
	for(int i = 2; i  <= n; ++i)
		read(u), to[u].push_back(i);
	dfs(1, 0);
	for(int i = 1; i <= m; ++i) {
		read(a[i].u), read(a[i].v);
		if(dep[a[i].u] > dep[a[i].v]) swap(a[i].u, a[i].v);
		int lca = ask(a[i].u, a[i].v);
		if(lca != a[i].u && lca != a[i].v) 
			a[i].pd=1;
		else {
			int aaa = ask2(a[i].u, a[i].v);
			if(aaa == a[i].u || aaa == a[i].v) {
				puts("-1");
				return 0;
			}
			too[aaa].push_back(a[i].v);
		}
	}
	dfs2(1);
	ans=dp[1];
	for(int i = 1; i <= m; ++i)
		if(a[i].pd)
			ans=max(ans, dp[a[i].u]+dp[a[i].v]+1);
	write(ans, '\n');
	return 0;
}
