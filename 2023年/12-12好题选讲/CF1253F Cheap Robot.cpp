#include <bits/stdc++.h>
#define int long long
#define inf 8000000000000007LL
using namespace std;
const int N = 1e5+5, M = 3e5+5;
int n, m, k, qq, dis[N], fa[N], cnt[N], jp[N][20], mx[N][20], dep[N], bb[N], aa, cc;
struct bian {
	int t, w;
	bool operator <(const bian& A) const {
		return A.w < w;
	}
};
priority_queue <bian> q;
vector <bian> to[N], too[N];
struct qwq {
	int u, v, w;
}a[M];

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
	return A.w < B.w;
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void dfs(int x, int fa) {
	dep[x]=dep[fa]+1, jp[x][0]=fa;
	for(int i = 1; i <= 19; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1], mx[x][i]=max(mx[x][i-1], mx[jp[x][i-1]][i-1]);
	for(bian y : too[x])
		if(y.t != fa) {
			bb[y.t]=mx[y.t][0]=y.w;
			dfs(y.t, x);
		}
}
int ask(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	int ret = 0;
	for(int i = 19; i >= 0; --i)
		if(dep[jp[x][i]] >= dep[y])
			ret=max(mx[x][i], ret), x=jp[x][i];
	for(int i = 19; i >= 0; --i)
		if(jp[x][i] != jp[y][i])
			ret=max(max(mx[x][i], mx[y][i]), ret), 
			x=jp[x][i], y=jp[y][i];
	if(x != y)
		ret=max(ret, max(bb[x], bb[y])), x=jp[x][0];
	// cout<<x<<"! "<<ret<<"\n";
	return ret;
}

signed main() {
	read(n), read(m), read(k), read(qq);
	for(int i = 1; i <= m; ++i) 
		read(a[i].u), read(a[i].v), read(a[i].w), 
		to[a[i].u].push_back(bian {a[i].v, a[i].w}), 
		to[a[i].v].push_back(bian {a[i].u, a[i].w});
	for(int i = 1; i <= k; ++i)
		to[n+1].push_back(bian {i, 0}), 
		to[i].push_back(bian {n+1, 0});
	for(int i = 1; i <= n+1; ++i)
		dis[i]=inf, fa[i]=i, cnt[i]=1;
	dis[n+1]=0;
	q.push(bian {n+1, 0});
	while(!q.empty()) {
		bian it = q.top(); q.pop();
		if(it.w > dis[it.t]) continue;
		for(bian y : to[it.t])
			if(dis[it.t]+y.w < dis[y.t]) {
				dis[y.t]=y.w+dis[it.t];
				q.push(bian {y.t, dis[y.t]});
			}
	}
	for(int i = 1; i <= m; ++i)
		a[i].w+=dis[a[i].u]+dis[a[i].v];
	sort(a+1, a+1+m, comp);
	for(int i = 1; i <= m; ++i) {
		int u = find(a[i].u), v = find(a[i].v);
		if(u != v) {
			// cout<<u<<" "<<v<<" "<<a[i].w<<"\n";
			too[a[i].u].push_back(bian {a[i].v, a[i].w});
			too[a[i].v].push_back(bian {a[i].u, a[i].w});
			if(cnt[u] > cnt[v]) swap(u, v);
			fa[u]=v;
			cnt[v]+=cnt[u];
		}
	}
	dfs(1, 0);
	for(int i = 1; i <= qq; ++i) {
		read(aa), read(cc);
		write(ask(aa, cc), '\n');
	}
	return 0;
}
