#include <bits/stdc++.h>
using namespace std;
int n, f[2000005];
struct qwq {
	int b, c;
}a[2000005];
int comp(qwq A, qwq B) {
	return A.b < B.b;
}
struct tree {
	int tr1[45000005], tr2[45000005], lazy[45000005];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void built(int k, int l, int r) {
		tr1[k]=tr2[k]=0;
		if(l == r) return ;
		int mid=((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void down(int k) {
		if(lazy[k] == 0) return ;
		lazy[ls]+=lazy[k], lazy[rs]+=lazy[k];
		tr1[ls]+=lazy[k], tr2[ls]+=lazy[k];
		tr1[rs]+=lazy[k], tr2[rs]+=lazy[k];
		lazy[k]=0;
	}
	void upup(int k) {
		tr1[k]=max(tr1[ls], tr1[rs]);
		tr2[k]=min(tr2[ls], tr2[rs]);
	}
	void updt(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			if(tr1[k] < w) {
				++lazy[k], ++tr1[k], ++tr2[k];
				return ;
			}
			else
				if(tr2[k] > w) {
					--lazy[k], --tr1[k], --tr2[k];
					return ;
				}
			if(l == r) return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid) updt(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq) updt(rs, mid+1, r, lq, rq, w);
		upup(k);
	}
	int ask(int k, int l, int r, int to) {
		if(l == r) 
			return tr1[k];
		down(k);
		int mid = ((l+r)>>1);
		if(to <= mid) return ask(ls, l, mid, to);
		else return ask(rs, mid+1, r, to);
		upup(k);
	}
	#undef ls 
	#undef rs 
}A;
int main() {
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout); 
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i].b);
		a[i].c=i;
	} 
	sort(a+1, a+n+1, comp);
	if(n <= 20000) {
		for(int i = 1; i <= n; ++i)
			for(int j = a[i].c; j <= n; ++j)
				if(f[j] < a[i].b) ++f[j];
				else if(f[j] > a[i].b) --f[j];
		for(int i = 1; i <= n; ++i)
			printf("%d\n", f[i]);
		return 0;
	}
	A.built(1, 1, n);
	for(int i = 1; i <= n; ++i)
		A.updt(1, 1, n, a[i].c, n, a[i].b);
	for(int i = 1; i <= n; ++i)
		printf("%d\n", A.ask(1, 1, n, i));
	return 0;
} 
