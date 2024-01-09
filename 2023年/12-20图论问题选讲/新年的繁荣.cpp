#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int n, m, a[N], fa[N], cnt[N], vis[N];
long long ans;

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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
int merge(int u, int v) {
	u = find(u), v = find(v);
	if(u == v) return 0;
	if(cnt[u] > cnt[v]) swap(u, v);
	fa[u]=v, cnt[v]+=cnt[u];
	return 1;
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i]), (vis[a[i]] ? (ans+=a[i]) : (vis[a[i]]=i) ), fa[i]=i, cnt[i]=1;
	for(int i = (1<<m)-1; i >= 0; --i) {
		int &u = vis[i];
		int v = 0;
		for(int j = 0; j < m && !u; ++j)
			u=vis[i|(1<<j)];
		for(int j = 0; j < m; ++j)
			if((v = vis[i|(1<<j)]) && merge(u, v))
				ans+=i;
	}
	write(ans, '\n');
	return 0;
}
