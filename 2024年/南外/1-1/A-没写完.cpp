#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, u, v, w[N], fa[N], cnt[N], tot, siz[N], mn[N], mx[N], out[N], tt;
long long ans;
vector <int> to[N];
struct edge {
	int u, v, w, xx;
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
	siz[x]=1;
	mn[x]=n+1, mx[x]=0;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), mn[x]=min(mn[x], mn[y]), mx[x]=max(mx[x], mx[y]), siz[x]+=siz[y];
	if(siz[x] == 1)
		mn[x]=mx[x]=++tot;
	a[x]=edge {mn[x], mx[x]+1, w[x], x};
	// cout<<x<<" "<<mn[x]<<" "<<mx[x]<<w[x]<<"!?\n";
}
int comp(edge A, edge B) {
	return A.w < B.w;
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
int merge(int x, int y) {
	x=find(x), y=find(y);
	if(x == y) return 0;
	if(cnt[x] > cnt[y]) swap(x, y);
	fa[x]=y, cnt[y]+=cnt[x];
	return 1;
}

signed main() {
    read(n);
	for(int i = 1; i <= n; ++i)
		read(w[i]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	sort(a+1, a+1+n, comp);
	for(int i = 1; i <= tot+1; ++i)
		fa[i]=i, cnt[i]=1;
	for(int i = 1; i <= n; ++i)
		if(merge(a[i].u, a[i].v)) 
			out[++tt]=a[i].xx, ans+=a[i].w;
	write(tt, '\n');
	for(int i = 1; i <= tt; ++i)
		write(out[i], ' '), write(i, '\n');
	return 0;
}