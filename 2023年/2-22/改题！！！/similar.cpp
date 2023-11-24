#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const int N = 1e5+5;
const uLL base = 1e5+7;
int n, q, a[N], mx, rt[N], bs[N], c, d, e, f;
struct tree {
	int gs;
	struct node {
		int s, ls, rs;
		uLL hs;
	}tr[N*23];
	uLL get(int r, int l) { return tr[r].hs-tr[l].hs; }
	void updt(int& k, int l, int r, int to) {
		tr[++gs]=tr[k];
		k=gs;
		if(l == r) {
			++tr[k].s;
			tr[k].hs+=bs[l];//n½øÖÆ! 
			return ;
		}
		int mid=((l+r)>>1);
		if(to <= mid) updt(tr[k].ls, l, mid, to);
		else updt(tr[k].rs, mid+1, r, to);
		tr[k].s=tr[tr[k].ls].s+tr[tr[k].rs].s;
		tr[k].hs=tr[tr[k].ls].hs+tr[tr[k].rs].hs;
//		cout<<l<<" "<<r<<" "<<tr[k].s<<"?\n";
	}
	int ll(int k1, int k2, int k3, int k4, int l, int r) {
		if(l == r) 
			return l;
		uLL ha = get(tr[k1].ls, tr[k2].ls), haha = get(tr[k3].ls, tr[k4].ls);
		int mid = ((l+r)>>1);
		if(ha == haha)
			return ll(tr[k1].rs, tr[k2].rs, tr[k3].rs, tr[k4].rs, mid+1, r);
		return ll(tr[k1].ls, tr[k2].ls, tr[k3].ls, tr[k4].ls, l, mid);
	}
	int rr(int k1, int k2, int k3, int k4, int l, int r) {
		if(l == r) 
			return l;
		uLL ha = get(tr[k1].rs, tr[k2].rs), haha = get(tr[k3].rs, tr[k4].rs);
		int mid = ((l+r)>>1);
		if(ha == haha)
			return rr(tr[k1].ls, tr[k2].ls, tr[k3].ls, tr[k4].ls, l, mid);
		return rr(tr[k1].rs, tr[k2].rs, tr[k3].rs, tr[k4].rs, mid+1, r);
	}
	int find(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k].s;
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid) ret+=find(tr[k].ls, l, mid, lq, rq);
		if(mid+1 <= rq) ret+=find(tr[k].rs, mid+1, r, lq, rq);
		return ret;
	}
}A;
void solve(int k1, int k2, int k3, int k4) {
	if(A.get(k1, k2) == A.get(k3, k4)) {
		puts("YES");
		return ;
	}
	int l = A.ll(k1, k2, k3, k4, 1, mx), r = A.rr(k1, k2, k3, k4, 1, mx);
	if(l+1 <= r-1) {
		if(A.find(k1, 1, mx, l+1, r-1)-A.find(k2, 1, mx, l+1, r-1) != 0) {
			puts("NO");
			return ;
		}
		if(A.find(k3, 1, mx, l+1, r-1)-A.find(k4, 1, mx, l+1, r-1) != 0) {
			puts("NO");
			return ;
		}
	}
	puts("YES");
	return ;
}
int main() {
	freopen("similar.in", "r", stdin);
	freopen("similar.out", "w", stdout);
	scanf("%d%d", &n, &q);
	A.gs=0;
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]), mx=max(a[i], mx);
	bs[0]=1;
	for(int i = 1; i <= mx; ++i)
		bs[i]=bs[i-1]*base;
	for(int i = 1; i <= n; ++i)
		rt[i]=rt[i-1], A.updt(rt[i], 1, mx, a[i]);
//	for(int i = 1; i <= n; ++i)
//		cout<<a[i]<<" "<<A.find(rt[i], 1, mx, 1, mx)<<"\n";
	for(int i = 1; i <= q; ++i) {
		scanf("%d%d%d%d", &c, &d, &e, &f);
		solve(rt[d], rt[c-1], rt[f], rt[e-1]);
	}
	return 0;
}
