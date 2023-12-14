#include <bits/stdc++.h>
using namespace std;
const int N = 3e3+5;
int n, fa[N], cnt[N], jp[N][20], mx[N][20], dep[N], bb[N], a[N][N];
struct bian {
	int t, w;
};
vector <bian> to[N];
struct qwq {
	int u, v, w;
}b[N*N];

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
	for(bian y : to[x])
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
	read(n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			read(a[i][j]);
	int pd = 1, cntt = 0;
	for(int i = 1; i <= n; ++i) {
		fa[i]=i, cnt[i]=1;
		pd&=(a[i][i] == 0);
		for(int j = i+1; j <= n; ++j) {
			pd&=(a[i][j] == a[j][i]);
			b[++cntt]=qwq {i, j, a[i][j]};
		}
	}
	if(!pd) {
		puts("NOT MAGIC");
		return 0;
	}
	sort(b+1, b+1+cntt, comp);
	for(int i = 1; i <= cntt; ++i) {
		int u = find(b[i].u), v = find(b[i].v);
		if(u != v) {
			// cout<<u<<" "<<v<<" "<<b[i].w<<"\n";
			to[b[i].u].push_back(bian {b[i].v, b[i].w});
			to[b[i].v].push_back(bian {b[i].u, b[i].w});
			if(cnt[u] > cnt[v]) swap(u, v);
			fa[u]=v;
			cnt[v]+=cnt[u];
		}
	}
	for(int i = 1; i <= n; ++i)
		if(fa[i] == i) dfs(i, 0);
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j) 
			if(find(i) == find(j)) 
				pd&=(a[i][j] <= ask(i, j));
	if(!pd) {
		puts("NOT MAGIC");
		return 0;
	}
	puts("MAGIC");
	return 0;
}
