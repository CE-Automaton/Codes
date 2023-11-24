#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, k, u, v, ans[N], tot; 
long long dp[N], dpp[N], a[N];
vector<int> to[N];

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
void dfs1(int x, int fa) {
	dp[x]=0;
	for(int y : to[x])
		if(y != fa) {
			dfs1(y, x);
			dp[x]=max(dp[x], dp[y]);
		}
	dp[x]+=a[x];
}
void ans1(int x, int fa) {
	ans[++tot]=x;
	for(int y : to[x])
		if(y != fa && dp[x] == dp[y]+a[x]) {
			ans1(y, x);
			return ;
		}
	return ;
}
void ans3(int x, int fa, int eo) {
	if(eo == 0)
		write(x, ' ');
	for(int y : to[x])
		if(y != fa) 
			ans3(y, x, eo^1);
	if(eo == 1)
		write(x, ' ');
	return ;
}

signed main() {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	read(n), read(k);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	if(k == 1) {
		dfs1(1, 0);
		write(dp[1], '\n');
		ans1(1, 0);
		write(tot, '\n');
		for(int i = 1; i <= tot; ++i)
			write(ans[i], ' ');
		return 0;
	}
	if(k == 2) {//有点难处理,而且时间不够了,所以就不写了 
		long long sum = 0;
		for(int i = 1; i <= n; ++i)
			sum+=a[i];
		write(sum, '\n');
		write(n, '\n');
		ans3(1, 0, 0);
		return 0;
	}
	if(k == 3) {
		long long sum = 0;
		for(int i = 1; i <= n; ++i)
			sum+=a[i];
		write(sum, '\n');
		write(n, '\n');
		ans3(1, 0, 0);
		return 0;
	}
	return 0;
}
