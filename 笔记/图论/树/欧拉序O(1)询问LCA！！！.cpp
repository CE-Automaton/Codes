//O(1)LCA!!! 
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, m, s, u, v, ola[N<<1], tot, in[N], dep[N], st[N<<1][20];
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
	ola[++tot]=x, in[x]=tot, dep[x]=dep[fa]+1;
	for(int y : to[x]) 
		if(y != fa)
			dfs(y, x), ola[++tot]=x;
	return ;
}
int mmn(int x, int y) {
	return (dep[x] < dep[y] ? x : y);
}
int ask(int x, int y) {
	if(x > y) swap(x, y);
	int lg = floor(log2(y-x+1));
	return mmn(st[x][lg], st[y-(1<<lg)+1][lg]);
}

signed main() {
	read(n), read(m), read(s);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(s, 0);
	for(int i = 1; i <= tot; ++i)
		st[i][0]=ola[i];
	for(int i = 1; i <= 19; ++i)
		for(int j = 1; j <= tot; ++j)
			if(j+(1<<(i-1)) > tot)
				st[j][i]=st[j][i-1];
			else
				st[j][i]=mmn(st[j][i-1], st[j+(1<<(i-1))][i-1]);
	for(int i = 1; i <= m; ++i) 
		read(u), read(v), write(ask(in[u], in[v]), '\n');
	return 0;
}
