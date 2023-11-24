#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, pd[100005], vis[100005], s[100005][45], az[100005][45], mx[100005], cnt[45], a, ans;
vector <int> to[100005];
char pro;
void dfs(int x) {
	if(vis[x]) return ;
	for(int i = 0; i <= 40; ++i)
		cnt[i]=cnt[i]-s[x][i], s[x][i]=az[x][i]=0;
	s[x][0]=az[x][0]=vis[x]=mx[x]=1;
	for(auto y : to[x]) {
		if(pd[y]) continue;
		dfs(y);
		for(int o = mx[x]; o >= 0; --o)
			for(int k = 1; k <= min(mx[y], 41-o); ++k)
				s[x][o+k]+=az[x][o]*az[y][k-1];
		mx[x]=max(mx[x], mx[y]+1);
		for(int k = 1; k <= mx[y]+1; ++k)
			az[x][k]+=az[y][k-1];
	}
	for(int i = 0; i <= 40; ++i)
		cnt[i]+=s[x][i];
}
signed main() {
	freopen("dis.in", "r", stdin);
	freopen("dis.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	for(int i = 2; i <= n; ++i)
		to[i/2].push_back(i);
	dfs(1);
	for(int i = 1; i <= m; ++i) {
		scanf(" %c %lld", &pro, &a);
		if(pro == '-') {
			pd[a]=1;
			while(1) {
				int nxt = a/2;
				if(nxt == 0) break;
				vis[nxt]=0, a=nxt;
				if(pd[nxt]) break;
			}
			dfs(a);
		}
		else {
			ans = 0;
			for(int i = 1; i <= a; ++i)
				ans+=cnt[i];
			printf("%lld\n", ans);
		}
	}
	return 0;
}
