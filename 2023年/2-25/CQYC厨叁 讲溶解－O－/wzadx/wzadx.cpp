#include <bits/stdc++.h>
#define uLL unsigned long long
#define inf 1000000007
using namespace std;
const uLL base = 29;
const int N = 2e5+5;
int n, m, sum, a[N], len[15];
uLL hs[N], bs[N], ts[15];
char s[N], t[N];
struct tree {
	int tr[(N<<2)], lazy[(N<<2)];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void down(int k) {
		if(lazy[k] == 0) return ;
		if(lazy[k] < 0) {
			tr[ls]=tr[rs]=-inf;
			lazy[ls]=lazy[rs]=-inf;
			lazy[k]=0;
			return ;
		}
		tr[ls]+=lazy[k], lazy[ls]+=lazy[k];
		tr[rs]+=lazy[k], lazy[rs]+=lazy[k];
		lazy[k]=0;
	}
	void upup(int k) {
		tr[k]=max(tr[ls], tr[rs]);
	}
	void built(int k, int l, int r) {
		tr[k]=lazy[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			tr[k]=-inf;
			lazy[k]=-inf;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid) updt(ls, l, mid, lq, rq);
		if(mid+1 <= rq) updt(rs, mid+1, r, lq, rq);
		upup(k);
	}
	void add(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			tr[k]+=w;
			lazy[k]+=w;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid) add(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq) add(rs, mid+1, r, lq, rq, w);
		upup(k);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k];
		down(k);
		int mid = ((l+r)>>1), ret = -inf;
		if(lq <= mid) ret=max(ret, ask(ls, l, mid, lq, rq));
		if(mid+1 <= rq) ret=max(ret, ask(rs, mid+1, r, lq, rq));
		upup(k);
		return ret;
	}
}A;
int main() {
	freopen("wzadx.in", "r", stdin);
	freopen("wzadx.out", "w", stdout);
	scanf("%d%d\n%s", &n, &m, s+1);
	bs[0]=1;
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]), sum+=a[i], bs[i]=bs[i-1]*base;
	for(int i = 1; i <= m; ++i) {
		scanf("%s", t+1);
		len[i] = strlen(t+1);
		for(int j = len[i]; j >= 1; --j)
			ts[i]=ts[i]*base+t[j]-'a'+1;
	}
	for(int i = n; i >= 1; --i)
		hs[i]=hs[i+1]*base+s[i]-'a'+1;
	A.built(1, 0, n);
	for(int i = 1; i <= n; ++i) {
		int j = 0;
		for(int o = 1; o <= m; ++o) {
			if(i < len[o]) continue;
			if(hs[i-len[o]+1]-hs[i+1]*bs[len[o]] == ts[o])
				j=max(j, i-len[o]+1);
		}
		//i不保留的情况: 
		int qwq = (i == 1 ? 0 : A.ask(1, 0, n, 0, i-1));
		if(qwq > 0)
			A.add(1, 0, n, i, i, qwq);
		//i保留的情况:
		if(j <= i-1)
			A.add(1, 0, n, j, i-1, a[i]);
		if(j > 0)
			A.updt(1, 0, n, 0, j-1);
//		for(int j = 0; j <= i; ++j)
//			cout<<A.ask(1, 0, n, j, j)<<" ";puts("");
	}
	int qwq = A.ask(1, 0, n, 0, n);
	if(qwq < 0) qwq=0;
	printf("%d", sum-qwq);
	return 0;
}
