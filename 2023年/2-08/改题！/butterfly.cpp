#include<bits/stdc++.h>
#define pi pair<long long, int>
using namespace std;
int n, q, k, v, dfn[1600005], id[800005], ans[800005], now; 
long long w, tot, S;
vector <int> to[800005];
vector <int> put[800005];
vector <pi> pro;
struct xds {
	int tree[12800005];
	void add(int l, int r, int k, int to) {
		++tree[k];
		if(l == r) 
			return ;
		int mid = (l+r)/2;
		if(mid >= to) add(l, mid, k*2, to);
		else add(mid+1, r, k*2+1, to);
	}
	int find(int l, int r, int k, int to) {
		if(l == r) return dfn[l];
		int mid = (l+r)/2;
		if(tree[k*2] >= to) return find(l, mid, k*2, to);
		else return find(mid+1, r, k*2+1, to-tree[k*2]);
	}
}A;
void dfs(int x, int fa) {
	if(fa) dfn[++tot]=x, put[id[x]].push_back(tot);
	int pd = 0;
	for(int o:to[x]) {
		if(pd) {
			id[o]=id[x]+1;
			dfs(o, x);
			dfn[++tot]=x;
			put[id[o]].push_back(tot);
		}
		if(o == fa) pd=1;
	}
	for(int o:to[x]) {
		if(o == fa) break;
		id[o]=id[x];
		dfs(o, x);
		dfn[++tot]=x;
		put[id[o]].push_back(tot);
	}
}
int main(){
	freopen("butterfly.in", "r", stdin);
	freopen("butterfly.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &k);
		int fst = 0; scanf("%d", &fst);
		for(int j = 2; j <= k; ++j)
			scanf("%d", &v), to[i].push_back(v); 
		to[i].push_back(fst);
	}
	id[1]=1;
	dfs(1, 0);
	for(int i = 1; i <= q; ++i)
		scanf("%lld", &w), pro.push_back(pi{w, i});
	sort(pro.begin(), pro.end());
	for(int i = 1; i <= n; ++i) {
		if(!put[i].size()) break;
		int lst = S;
		for(int j : put[i])
			A.add(1, tot, 1, j);
		S+=A.tree[1];
		while(now < q && pro[now].first <= S)
			ans[pro[now].second]=A.find(1, tot, 1, pro[now].first-lst), ++now;
	}
	while(now < q)
		ans[pro[now].second]=dfn[(pro[now].first-S-1)%(2*n-2)+1], ++now;
	for(int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
