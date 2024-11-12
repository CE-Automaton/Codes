#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, q, a[N], xx, yy, gss[N];

template <typename T> inline void debug(T x) { cerr<<x; }
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
struct tree {
	int mn[N<<2], gs[N<<2], ww[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k) {
		mn[k]=min(mn[ls], mn[rs]);
		gs[k]=(mn[k] == mn[ls] ? gs[ls] : 0)+(mn[k] == mn[rs] ? gs[rs] : 0);
	}
	void down(int k) {
		if(lzy[k] == 0) return ;
		mn[ls]+=lzy[k], ww[ls]+=lzy[k], lzy[ls]+=lzy[k];
		mn[rs]+=lzy[k], ww[rs]+=lzy[k], lzy[rs]+=lzy[k];
		lzy[k]=0;
	}
	void built(int k, int l, int r) {
		mn[k]=inf, gs[k]=1, ww[k]=lzy[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int to, int w) {
		if(l == r) {
			mn[k]=ww[k]+w;
			gs[k]=1;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, w);
		else
			updt(rs, mid+1, r, to, w);
		upup(k);
	}
	void updtt(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			mn[k]+=w, ww[k]+=w, lzy[k]+=w;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updtt(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			updtt(rs, mid+1, r, lq, rq, w);
		upup(k);
	}
}A;
void add(int l, int r, int w) {
	if(a[l] == a[r]) return ;
	A.updtt(1, 0, 1000000, min(a[l], a[r]), max(a[l], a[r])-1, w);
}
void pd(int x, int w) {
	if(gss[x] == 0)
		A.updt(1, 0, 1000000, x, 0);
	gss[x]+=w;
	if(gss[x] == 0)
		A.updt(1, 0, 1000000, x, inf);
}

signed main() {
	read(n), read(q);
	A.built(1, 0, 1000000);
	a[0]=1000001;
	for(int i = 1; i <= n; ++i)
		read(a[i]), pd(a[i], 1);
	for(int i = 0; i <= n; ++i)
		add(i, i+1, 1);
	for(int i = 1; i <= q; ++i) {
		read(xx), read(yy);
		add(xx-1, xx, -1);
		add(xx, xx+1, -1);
		pd(a[xx], -1);
		a[xx]=yy;
		add(xx-1, xx, 1);
		add(xx, xx+1, 1);
		pd(a[xx], 1);
		// write(A.mn[1], '\n');
		write(A.gs[1], '\n');
	}
	return 0;
}