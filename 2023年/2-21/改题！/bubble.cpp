#include <bits/stdc++.h>
using namespace std;
int t, n, m, a[1000005], b[1000005], len;
struct node {
	int x, y, z;
}pro[1000005];
int get(int x) {
	return lower_bound(b+1, b+1+len, x)-b;
}
int comp(node A, node B) {
	return A.y == B.y ? (A.x == B.x ? A.z < B.z : A.x < B.x) : A.y < B.y;
}
vector <node> ad[1000005];
struct tree {
	int tr[4000005], lazy[4000005];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void down(int k) {
		if(lazy[k] == 0) return ;
		tr[ls]+=lazy[k];
		tr[rs]+=lazy[k];
		lazy[ls]+=lazy[k];
		lazy[rs]+=lazy[k];
		lazy[k]=0;
	}
	void built(int k, int l, int r) {
		tr[k]=lazy[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void add(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			tr[k]+=w, lazy[k]+=w;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid) add(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq) add(rs, mid+1, r, lq, rq, w);
		tr[k]=min(tr[ls], tr[rs]);
	}
}A;
int main() {
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		len=0;
		A.built(1, 1, n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", &a[i]), b[++len]=a[i];
		for(int i = 1; i <= m; ++i) 
			scanf("%d%d%d", &pro[i].x, &pro[i].y, &pro[i].z), b[++len]=pro[i].x, b[++len]=pro[i].y;
		sort(b+1, b+1+len);
		for(int i = 1; i <= len; ++i)
			ad[i].clear(); 
		for(int i = 1; i <= m; ++i)
			pro[i].x=get(pro[i].x), pro[i].y=get(pro[i].y);
		for(int i = 1; i <= n; ++i)
			a[i]=get(a[i]);
		sort(pro+1, pro+1+m, comp);
		for(int i = 1; i <= n; ++i)
			ad[a[i]].push_back(node{1, i, 1});
		int lst = 0, ok = 1;
		for(int i = 1; i <= m; ++i) {
			for(int j = lst; j <= pro[i].y; ++j)
				for(int p = 0; p < ad[j].size(); ++p) {
					auto o = ad[j][p];
					A.add(1, 1, n, o.x, o.y, o.z);
				}
			lst=pro[i].y+1;
			if(pro[i].x <= pro[i].y) ;
			else {
				A.add(1, 1, n, 1, pro[i].z, -1);
				ad[pro[i].x].push_back(node{1, pro[i].z, 1});
			}
			ok &= (A.tr[1] >= 0);
		}
		if(ok) puts("YES");
		else puts("NO");
	}
	return 0;
}
