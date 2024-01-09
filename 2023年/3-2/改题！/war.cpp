#include <bits/stdc++.h>
#define pi pair<int, int>
using namespace std;
int n, q, u, vv, p[50005], v[50005], len, cnt, tot[50005], vis[50005], fa[50005], lca[50005], upp[50005], rt[50005];
vector <int> to[50005];
vector <pi> que[50005];
struct az {
	int s, t;
}b[50005];
struct qwq {
	int s, t, w;
}pro[50005];
int comp(az A, az B) {
	return A.s < B.s;
} 
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
struct tree {
	int gs;
	struct node {
		int ls, rs;
		long long www;
	}tr[2000005];
	int xj(int k) {
		tr[++gs]=tr[k];
		return gs;
	}
	void uppdt(int& k, int l, int r, int to, long long w) {
		k=xj(k);
		if(l == r) {
			tr[k].www+=w;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) uppdt(tr[k].ls, l, mid, to, w);
		else uppdt(tr[k].rs, mid+1, r, to, w);
		tr[k].www=tr[tr[k].ls].www+tr[tr[k].rs].www;
	}
	int ef(int k1, int k2, int k3, int k4, int l, int r, long long w) {
		long long sf = tr[k1].www+tr[k2].www-tr[k3].www-tr[k4].www;
		if(w > sf) return -1;
		if(l == r) 
			return l;
		long long ll = tr[tr[k1].ls].www+tr[tr[k2].ls].www-tr[tr[k3].ls].www-tr[tr[k4].ls].www;
		int mid = ((l+r)>>1);
		if(ll < w)
			return ef(tr[k1].rs, tr[k2].rs, tr[k3].rs, tr[k4].rs, mid+1, r, w-ll);
		else
			return ef(tr[k1].ls, tr[k2].ls, tr[k3].ls, tr[k4].ls, l, mid, w);
	}
}A;
void Tarjan(int x, int fr) {
	upp[x]=fr;
	rt[x]=rt[fr];
	A.uppdt(rt[x], 1, cnt, p[x], v[x]);
	for(int j : to[x]) {
		if(j == fr) continue;
		Tarjan(j, x);
	}
	for(auto j : que[x]) {
		int y = j.first, z = j.second;
		if(vis[y]) lca[z]=find(y);
	}
	vis[x]=1, fa[x]=fr;
}
int main() {
//	freopen("war.in", "r", stdin); 
//	freopen("war.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		fa[i]=i;
	for(int i = 1; i <= n-1; ++i)
		scanf("%d%d", &u, &vv), to[u].push_back(vv), to[vv].push_back(u);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &p[i], &v[i]), b[i]=az{p[i], i};
	for(int i = 1; i <= q; ++i) {
		scanf("%d%d%d", &pro[i].s, &pro[i].t, &pro[i].w);
		if(pro[i].s == pro[i].t)
			lca[i]=pro[i].s;
		else
			que[pro[i].s].push_back(pi{pro[i].t, i}), que[pro[i].t].push_back(pi{pro[i].s, i});
	}
	sort(b+1, b+n+1, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || b[i].s != b[i-1].s)
			tot[++cnt]=b[i].s;
		p[b[i].t]=cnt;
	}
	Tarjan(1, 0);
	for(int i = 1; i <= q; ++i) {
		int ret = A.ef(rt[pro[i].s], rt[pro[i].t], rt[lca[i]], rt[upp[lca[i]]], 1, cnt, pro[i].w);
		if(ret == -1) {
			puts("Impossible");
			continue;
		}
		printf("%d\n", tot[ret]);
	}
	return 0;
}
