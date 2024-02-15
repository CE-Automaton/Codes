#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, m, op, q, l[N], r[N], w[N], u[N], v[N], t[N], lst, now[N], sum[N];
struct tree {
	int tr[N<<2], ww[N<<2], pd[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void down(int k) {
		if(lzy[k] != -1) {
			if(!lzy[k])
				tr[ls]=tr[rs]=0;
			else
				tr[ls]=ww[ls], tr[rs]=ww[rs];
			pd[ls]=lzy[k];
			pd[rs]=lzy[k];
			lzy[ls]=lzy[k];
			lzy[rs]=lzy[k];
			lzy[k]=-1;
		}
	}
	void upup(int k) {
		pd[k]=(pd[ls]&pd[rs]);
		tr[k]=(pd[k] ? ww[k] : tr[ls]+tr[rs]);
	}
	void built(int k, int l, int r) {
		tr[k]=pd[k]=ww[k]=0;
		lzy[k]=-1;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void add(int k, int l, int r, int lq, int w) {
		ww[k]+=w;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		if(lq <= mid)
			add(ls, l, mid, lq, w);
		else
			add(rs, mid+1, r, lq, w);
	}
	void updt(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			lzy[k]=w, pd[k]=w;
			if(w == 1) tr[k]=ww[k];
			else tr[k]=0;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, w);
		upup(k);
	}
}A;

template <typename T> inline void debug(T x) { cerr<<x<<'\n'; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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

signed main() {
	File("class");
	read(n), read(m), read(op);
	int pd1 = 1, pd2 = 1;
	for(int i = 1; i <= m; ++i) {
		read(l[i]), read(r[i]), read(w[i]);
		if(l[i] > r[i]) swap(l[i], r[i]);
		pd1&=(l[i] == r[i]);
	}
	read(q);
	for(int i = 1; i <= q; ++i) 
		read(t[i]), read(u[i]), read(v[i]), 
		pd2&=(t[i] == 1);
	if(pd1) {
		A.built(1, 1, n);
		for(int i = 1; i <= m; ++i)
			A.add(1, 1, n, l[i], w[i]);
		for(int i = 1; i <= q; ++i) {
			u[i]=(u[i]^(lst*op)), v[i]=(v[i]^(lst*op));
			if(u[i] > v[i]) swap(u[i], v[i]);
			A.updt(1, 1, n, u[i], v[i], t[i]);
			lst=A.tr[1];
			write(lst, '\n');
		}
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		now[i]=1;
	for(int i = 1; i <= q; ++i) {
		u[i]=(u[i]^(lst*op)), v[i]=(v[i]^(lst*op));
		if(u[i] > v[i]) swap(u[i], v[i]);
		t[i]=(t[i]^1);
		for(int j = u[i]; j <= v[i]; ++j)
			now[j]=t[i];
		for(int j = 1; j <= n; ++j)
			sum[j]=sum[j-1]+now[j];
		lst=0;
		for(int j = 1; j <= m; ++j)
			lst+=(sum[r[j]]-sum[l[j]-1] != r[j]-l[j]+1)*w[j];
		write(lst, '\n');
	}
	return 0;
}
