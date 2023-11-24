#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, m, x, q, a, b, fa[N], cnt[N], vis[N], to[N], ha[N], qwq, nd, en;
vector <int> son[N];
struct edge {
	int u, v;
}ans[N];
int find(int x) { return (x == fa[x] ? x : fa[x] = find(fa[x])); } 
int comp(int A, int B) {
	return cnt[A] > cnt[B];
}
int main() {
	freopen("city.in", "r", stdin);
	freopen("city.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &x, &q);
	for(int i = 1; i <= n; ++i)
		fa[i]=i, cnt[i]=1;
	for(int i = 1; i <= q; ++i) {
		scanf("%d%d", &a, &b);
		a=find(a), b=find(b);
		if(a == b) continue;
		if(cnt[a] > cnt[b]) swap(a, b);
		fa[a]=b, cnt[b]+=cnt[a];
	} 
	for(int i = 1; i <= n; ++i) 
		if(i == fa[i])
			to[++nd]=i, qwq+=(cnt[i] == 1 ? 0 : cnt[i]);
//	cout<<nd<<" "<<qwq<<"\n";
	if(x > nd || qwq > m) {
		printf("-1\n");
		return 0;
	}
//	puts("???");
	sort(to+1, to+1+nd, comp);
	for(int i = 1; i < nd-x+1; ++i) 
		ha[to[i]]=nd-x+1, cnt[to[nd-x+1]]+=cnt[to[i]], fa[to[i]]=to[nd-x+1];
	for(int i = nd-x+1; i <= nd; ++i) 
		ha[to[i]]=i;
	for(int i = 1; i <= n; ++i) {
		int u = find(i);
		son[ha[u]].push_back(i);
	}
	for(int i = nd-x+1; i <= nd; ++i) {
		if(cnt[to[i]] == 1) break;
		for(int j = 1; j < cnt[to[i]]; ++j) {
			int now = son[i][j-1], nxt = son[i][j];
			ans[++en]=edge{now, nxt};
		}
		ans[++en]=edge{son[i][cnt[to[i]]-1], son[i][0]};
		m-=cnt[to[i]];
	}
	if(m >= 1) {
		for(int o = nd-x+1; m >= 1 && o <= nd; ++o)
			for(int i = nd-x+1; m >= 1 && i < o; ++i) 
				for(int j = 0; m >= 1 && j < cnt[to[i]]; ++j)
					for(int k = 0; m >= 1 && k < cnt[to[o]]; ++k) {
						--m;
						ans[++en]=edge{son[o][k], son[i][j]};
					}
		if(m >= 1) {
			for(int i = nd-x+1; m >= 1 && i <= nd; ++i) {
				if(cnt[to[i]] == 1) continue;
				for(int j = 0; m >= 1 && j < cnt[to[i]]; ++j)
					for(int k = 0; m >= 1 && k < cnt[to[i]]; ++k) {
						if(j == cnt[to[i]]-1 && k == 0) continue;
						if(j+1 == k || j == k) continue;
						--m;
						ans[++en]=edge{son[i][j], son[i][k]};
					}
			}
			if(m >= 1) {
				puts("-1");
				exit(0);
			}
		}
	}
	for(int i = 1; i <= en; ++i) 
		printf("%d %d\n", ans[i].u, ans[i].v);
	return 0;
} 
