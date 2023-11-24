#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, m, u, v, jp[N][25], vis[N], q, a, b, c, dep[N], pd[N];
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
void dfs(int x, int fa) {
	jp[x][0]=fa;
	dep[x]=dep[fa]+1;
	for(int i = 1; i <= 20; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1];
	for(int y : to[x])
		if(y != fa)
			dfs(y, x);
}
int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; --i) 
		if(dep[jp[x][i]] >= dep[y])
			x=jp[x][i];
	for(int i = 20; i >= 0; --i)
		if(jp[x][i] != jp[y][i])
			x=jp[x][i], y=jp[y][i];
	if(x != y)
		x=jp[x][0];
	return x;
}
void ddfs(int x) {
	vis[x]=1;
	for(int y : to[x])
		if(vis[y] == 0 && pd[y] == 0)
			ddfs(y);
}

signed main() {
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	read(q);
	if(m == n-1) {
		dfs(1, 0); 
		for(int i = 1; i <= q; ++i) {
			read(a), read(b), read(c);
			int x = lca(a, b), y = lca(b, c);
			if(x == a || x == b || y == b || y == c) 
				puts("-1");
			else {
				if(dep[x] < dep[y]) swap(x, y);
				write(x, '\n');
			}
		}
	}
	else 
		if(m == 1LL*n*(n-1)/2) {
			for(int i = 1; i <= q; ++i) {
				read(a), read(b), read(c);
				if(a == b && b == c) 
					write(a, '\n');
				else
					puts("-1");
			}
		}
		else {
			for(int i = 1; i <= q; ++i) {
				read(a), read(b), read(c);
				if(a == b && b == c) {
					write(a, '\n');
					continue;
				}
				int ans = -1;
				for(int j = 1; j <= n && ans == -1; ++j) {
					int sum = 1; 
					pd[j]=1;
					if(pd[a] == 0)
						ddfs(a);
					if(vis[b] || vis[c])
						sum=0;
					else {
						if(pd[b] == 0)
							ddfs(b);
						if(vis[c])
							sum=0;
					}
					if(sum == 1)
						ans=j;
					for(int o = 1; o <= n; ++o)
						vis[o]=0;
					pd[j]=0;
				}
				write(ans, '\n');
			}
		}
	return 0;
}
