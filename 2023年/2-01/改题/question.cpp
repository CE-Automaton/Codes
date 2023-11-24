#include <bits/stdc++.h>
using namespace std;
int n, m, u, v, zhan1[100005], tot1, vis[100005], dfn[100005], low[100005], cnt;
vector <int> to[100005];
template <typename T> void read(T& x) {
	x = 0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
} 
void Tarjan(int x, int fa) {
	low[x]=dfn[x]=++cnt;
	zhan1[++tot1]=x;
	vis[x]=1;
	int son = 0;
	for(auto y : to[x]) {
		if(y == fa) continue;
		if(!dfn[y]) {
			++son;
			Tarjan(y, x);
			low[x]=min(low[x], low[y]);
			if(low[y] >= dfn[x]) {//’“µΩ∏Óµ„
				int ds = 1, bs = 0;
				while(1) {
					int w = zhan1[tot1--];
					for(auto h : to[w])
						if(vis[h]) ++bs;
					++ds;
					vis[w]=0;
					if(w == y) break;
				}
				if(ds*(ds-1)/2 != bs) {
					puts("WA");
					exit(0);
				}
			}
		}
		else
			low[x]=min(low[x], dfn[y]);
	}
	if(fa == x && son == 0) 
		return ;
}
int main() {
	freopen("question.in", "r", stdin);
    freopen("question.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= m; ++i) 
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i) 
		if(!dfn[i]) cnt=0, Tarjan(i, i);
	puts("AC");
	return 0;
} 
