//点双连通分量
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, m, u, v, cnt, zhan[N], tot, dfn[N], low[N], op;
vector <int> to[N], ans[N];

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
void tarjan(int x, int fa, int son=0) {
	zhan[++tot]=x, dfn[x]=low[x]=(++op);
	for(int y : to[x]) 
		if(!dfn[y]) {
			tarjan(y, x);
			++son;
			low[x]=min(low[x], low[y]);
			if(low[y] >= dfn[x]) {
				++cnt;
				int z;//这里可以加入建圆方树的代码 
				do { z=zhan[tot], --tot, ans[cnt].push_back(z); } while(z != y);
				ans[cnt].push_back(x);
			} 
		}
		else
			low[x]=min(low[x], dfn[y]);
	if(son == 0 && x == fa) {//!!! 
		++cnt;
		while(tot)
			ans[cnt].push_back(zhan[tot]), --tot;
	}
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i)
		if(!dfn[i]) 
			tarjan(i, i), tot=0;
	write(cnt, '\n');
	for(int i = 1; i <= cnt; ++i) {
		write(ans[i].size(), ' ');
		for(int j : ans[i])
			write(j, ' ');
		putchar('\n');
	}
	return 0;
}
