#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
int n, m, k, u, v, w, e, T, q, x, t, o, dp[305][10005], ans[2][305], st1, st2; 
struct qwq {
	int a, b;
	bool operator <(const qwq& A) const {
		return A.a < a; 
	}
};
vector <qwq> to[10005];
set<int> tim[10][10005];

template <typename T> void read(T& xx) {
	xx = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') xx=(xx<<1)+(xx<<3)+(c^48), c=getchar();
	xx=(f ? -xx : xx);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
void solve(int xx, int a) {
	for(int i = 0; i <= o; ++i) {
		ans[a][i]=inf;
		for(int j = 1; j <= n; ++j)
			dp[i][j]=inf;
	}
	dp[0][xx]=0;
	priority_queue <qwq> qq;
	for(int i = 0; i <= o; ++i) {
		for(int j = 1; j <= n; ++j)
			if(dp[i][j] != inf)
				qq.push(qwq{dp[i][j], j});
		while(!qq.empty()) {
			qwq it = qq.top(); qq.pop();
//			cout<<it.a<<" "<<it.b<<" "<<dp[i][it.b]<<"\n";
			if(dp[i][it.b] < it.a) continue;
			for(auto j : to[it.b]) 
				if(dp[i][j.a] > it.a+j.b)
					dp[i][j.a]=it.a+j.b, qq.push(qwq{dp[i][j.a], j.a})/*, cout<<it.b<<"->"<<j.a<<"\n"*/;
		}
//		exit(0);
		for(int j = 1; j <= n; ++j)
			for(int p = 0; p < k; ++p)
				if(((i>>p)&1)^1) {
					auto it = tim[p][j].lower_bound(dp[i][j]);
					if (it != tim[p][j].end() && dp[i|(1<<p)][j] > *it)
						dp[i|(1<<p)][j] = *it;
				}
		for(int j = 1; j <= n; ++j)
			ans[a][i]=min(ans[a][i], dp[i][j]);
	}
}

int main() {
	freopen("ghost.in", "r", stdin);
	freopen("ghost.out", "w", stdout);
	read(n), read(m), read(k);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), read(w), to[u].push_back(qwq{v, w}), to[v].push_back(qwq{u, w});
	read(e), read(T);
	for(int i = 1; i <= e; ++i)
		read(q), read(x), read(t), tim[q-1][x].insert(t);
	read(st1), read(st2);
	o = (1<<k)-1;
	solve(st1, 0);
	solve(st2, 1);
	int po = inf;
//	for(int i = 0; i < o; ++i)
//		write(ans[0][i]), putchar(' '), write(ans[1][i]), putchar('\n');
	for(int i = 0; i <= o; ++i)
		for(int j = 0; j <= o; ++j)
			if((i|j) == o)
				po=min(po, max(ans[0][i], ans[1][j]));
//	write(po), putchar('\n');
	if(po > T)
		puts("-1");
	else
		write(po);
	return 0;
}
