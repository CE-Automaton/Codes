//边双连通分量
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5, M = 2e6+5;
int n, m, u, v, cnt, hed[N], pd[M<<1]/*判断割边*/, nxt[M<<1], to[M<<1],
dfn[N], low[N], vis[N], op, tot;
vector <int> ans[N];

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
void add(int x, int y) {
	nxt[++cnt]=hed[x];
	to[cnt]=y, hed[x]=cnt;
	
	nxt[++cnt]=hed[y];
	to[cnt]=x, hed[y]=cnt;
}
void tarjan(int x) {
	dfn[x]=low[x]=++op;
	for(int i = hed[x]; i; i=nxt[i]) 
		if(!dfn[to[i]]) {
			tarjan(to[i]);
			low[x]=min(low[x], low[to[i]]);
			if(low[to[i]] >= dfn[x])
				pd[i^1]=pd[i]=1;
		}
		else
			low[x]=min(low[x], dfn[to[i]]);
}
void get_ans(int x) {//性质:边双连通分量内每条边都至少在一个环内,缩点后是个树 
	ans[tot].push_back(x);
	vis[x]=1;
	for(int i = hed[x]; i; i=nxt[i]) 
		if(!vis[to[i]] && !pd[i])
			get_ans(to[i]);
}

signed main() {
	cnt=1, read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), add(u, v);
	for(int i = 1; i <= n; ++i)
		if(!dfn[i]) 
			tarjan(i);
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			++tot, get_ans(i);
	write(tot, '\n');
	for(int i = 1; i <= tot; ++i) {
		write(ans[i].size(), ' ');
		for(int j : ans[i])
			write(j, ' ');
		putchar('\n');
	}
	return 0;
}
