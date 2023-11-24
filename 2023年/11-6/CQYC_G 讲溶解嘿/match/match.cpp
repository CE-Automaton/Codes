#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int t, n, m, u, v, ds[N], ans, up[N], dep[N], vis[N];
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
void dfs(int x) {
	for(int o = 0; o < ds[x]; ++o) {
		int y = to[x][o];
		if(!dep[y]) {
			dep[y]=dep[x]+1;
			vis[y]=vis[x];
			up[y]=x;
			dfs(y);
		}
	}
}
int pd() {
	for(int x = 1; x <= n; ++x) 
		if(!dep[x])
			dep[x]=1, vis[x]=x, dfs(x);
	for(int x = 1; x <= n; ++x) 
		for(int o = 0; o < ds[x]; ++o) {
			int y = to[x][o];
			if((dep[x] == dep[y]+2 || dep[y] == dep[x]+2) && vis[x] == vis[y])
				return 1;
			if(up[x] != 0 && up[x] == up[y] && dep[x] == dep[y] && vis[x] == vis[y])
				return 1;
		}
	return 0;
}

signed main() {
	freopen("match.in", "r", stdin);
	freopen("match.out", "w", stdout);
	read(t);
	while(t--) {
		read(n), read(m);
		ans=0;
		for(int i = 1; i <= m; ++i)
			read(u), read(v), ++ds[u], ++ds[v], 
			to[u].push_back(v), to[v].push_back(u);
		if(pd())
			ans=3;
		for(int i = 1; i <= n; ++i)
			ans=max(ans, ds[i]), ds[i]=dep[i]=up[i]=vis[i]=0, to[i].clear();
		write(ans, '\n');
	}
	return 0;
}
