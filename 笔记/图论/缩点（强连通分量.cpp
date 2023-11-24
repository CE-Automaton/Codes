//缩点(强连通分量) 
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5, M = 2e6+5;
int n, m, u, v, w[N], cnt, hed[N], nxt[M<<1], to[M<<1], ww[N], dfn[N],
low[N], op, zhan[N], tot, bl[N], in[N], dis[N], vis[N], ans;
vector <int> too[N];
queue <int> q;

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
}
void tarjan(int x) {
	zhan[++tot]=x, dfn[x]=low[x]=++op;
	vis[x]=1;
	for(int i = hed[x]; i; i=nxt[i])
		if(!dfn[to[i]])
			tarjan(to[i]), low[x]=min(low[x], low[to[i]]);
		else
			if(vis[to[i]])//判断是否已经被缩!!! 
				low[x]=min(low[x], dfn[to[i]]);
	if(dfn[x] == low[x]) {
		int z; ++cnt;
		do {
			z=zhan[tot--];//缩点~ 
			bl[z]=cnt;
			vis[z]=0;
			ww[cnt]+=w[z];
		} while(z != x);
	}
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(w[i]);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), add(u, v);
	cnt=0;
	for(int i = 1; i <= n; ++i)
		if(!dfn[i])
			tarjan(i);
	for(int x = 1; x <= n; ++x)
		for(int i = hed[x]; i; i=nxt[i])
			if(bl[x] != bl[to[i]])//重新建边 
				too[bl[x]].push_back(bl[to[i]]), ++in[bl[to[i]]];
	for(int x = 1; x <= cnt; ++x) {
		dis[x]=ww[x];
		if(!in[x])
			q.push(x);
	}
	while(!q.empty()) {
		int it = q.front(); q.pop();
		for(int y : too[it]) {
			if(ww[y]+dis[it] > dis[y])
				dis[y]=ww[y]+dis[it];
			if(!(--in[y])) 
				q.push(y);
		}
	}
	for(int x = 1; x <= cnt; ++x)
		ans=max(ans, dis[x]);
	write(ans, '\n');
	return 0;
}
