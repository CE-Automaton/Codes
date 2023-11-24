#include <bits/stdc++.h>
#define inf 10000007
using namespace std;
const int N = 5e5+5;
int n, q, h[N], ls, rs, ll[N], zhan[N], tot, cnt, ans[N];
struct az {
	int l, id;
};
struct qwq {
	int l, r, v;
}duan[N];
vector <az> pro[N][2];
struct qq {
	int tree[N<<2], lazy[N<<2];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void upup(int k) { tree[k]=max(tree[ls], tree[rs]); }
	void down(int k) {
		if(!lazy[k]) return ;
		tree[ls]+=lazy[k], tree[rs]+=lazy[k];
		lazy[ls]+=lazy[k], lazy[rs]+=lazy[k];
		lazy[k]=0;
	}
	void built(int k, int l, int r) {
		tree[k]=0, lazy[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int L, int R, int upd) {
		if(L <= l && r <= R) {
			tree[k]+=upd, lazy[k]+=upd;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(L <= mid)
			updt(ls, l, mid, L, R, upd);
		if(mid+1 <= R)
			updt(rs, mid+1, r, L, R, upd);
		upup(k);
	}
	int ask(int k, int l, int r, int L, int R) {
		if(L <= l && r <= R) 
			return tree[k];
		down(k);
		int mid = ((l+r)>>1), ret = -inf;
		if(L <= mid)
			ret=max(ret, ask(ls, l, mid, L, R));
		if(mid+1 <= R)
			ret=max(ret, ask(rs, mid+1, r, L, R));
		upup(k);
		return ret;
	}
	#undef ls
	#undef rs
}A, B;
void solve(int lx) {
	memset(ll, 0, sizeof ll);
	tot=cnt=0;
	for(int i = n; i >= 1; --i) {
		while(tot && h[zhan[tot]] < h[i]) ll[zhan[tot--]]=i;
		zhan[++tot]=i;
	}
	tot=0;
	A.built(1, 1, n), B.built(1, 1, n);
	for(int i = 1; i <= n; ++i) {
		while(tot && h[zhan[tot]] > h[i]) {
			int it = zhan[tot--];
			B.updt(1, 1, n, it, it, A.ask(1, 1, n, it, it));
			A.updt(1, 1, n, it, it, -inf);
		}
		zhan[++tot]=i;
		int lll = i;
		A.updt(1, 1, n, i, i, 1);
		while(cnt && duan[cnt].r >= ll[i]) {
			int lx = duan[cnt].l, rx = duan[cnt].r, vvv = duan[cnt].v;
			--cnt;
			if(lx <= ll[i]) {
				duan[++cnt]=qwq{lx, ll[i], vvv};
				A.updt(1, 1, n, ll[i]+1, rx, i-vvv);
				lll=ll[i]+1;
				break;
			}
			else
				A.updt(1, 1, n, lx, rx, i-vvv), lll=lx;
		}
		duan[++cnt]=qwq{lll, i, i};
		for(auto j:pro[i][lx])
			ans[j.id]=max(ans[j.id], max(A.ask(1, 1, n, j.l, i), B.ask(1, 1, n, j.l, i)));
	}
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &h[i]);
	for(int i = 1; i <= q; ++i)
		scanf("%d%d", &ls, &rs),
		pro[rs][0].push_back(az{ls, i}), pro[n-ls+1][1].push_back(az{n-rs+1, i});
	solve(0);
	for(int i = 1; i*2 <= n; ++i)
		swap(h[i], h[n-i+1]);
	solve(1);
	for(int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
