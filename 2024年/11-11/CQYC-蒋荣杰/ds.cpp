#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, q, opt, ll, rr;
LL a[N], vv;

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
	LL tr[N<<2], mn[N<<2];
	int lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=a[l];
			mn[k]=a[l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=tr[ls]+tr[rs];
		mn[k]=min(mn[ls], mn[rs]);
	}
	void down(int k, int l, int r) {
		if(lzy[k]) {
			int mid = ((l+r)>>1);
			tr[ls]=1LL*(mid-l+1)*mn[k];
			mn[ls]=mn[k];
			lzy[ls]=1;
			tr[rs]=1LL*(r-mid)*mn[k];
			mn[rs]=mn[k];
			lzy[rs]=1;
			lzy[k]=0;
		}
	}
	void updt(int k, int l, int r, LL ww) {
		if(mn[k] >= ww) {
			tr[k]=(r-l+1)*ww;
			mn[k]=ww;
			lzy[k]=1;
			return ;
		}
		if(l == r) return ;
		down(k, l, r);
		int mid = ((l+r)>>1);
		updt(ls, l, mid, ww);
		updt(rs, mid+1, r, ww);
		tr[k]=tr[ls]+tr[rs];
		mn[k]=min(mn[ls], mn[rs]);
	}
	void updtt(int k, int l, int r, int to, LL ww) {
		if(l == r) {
			tr[k]=ww;
			mn[k]=ww;
			lzy[k]=0;
			return ;
		}
		down(k, l, r);
		int mid = ((l+r)>>1);
		if(to <= mid)
			updtt(ls, l, mid, to, ww);
		else
			updtt(rs, mid+1, r, to, ww);
		tr[k]=tr[ls]+tr[rs];
		mn[k]=min(mn[ls], mn[rs]);
	}
	void updttt(int k, int l, int r, int lq, int rq, LL ww) {
		if(lq <= l && r <= rq) {
			tr[k]=1LL*(r-l+1)*ww;
			mn[k]=ww;
			lzy[k]=1;
			return ;
		}
		down(k, l, r);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updttt(ls, l, mid, lq, rq, ww);
		if(mid+1 <= rq)
			updttt(rs, mid+1, r, lq, rq, ww);
		tr[k]=tr[ls]+tr[rs];
		mn[k]=min(mn[ls], mn[rs]);
	}
	LL ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		down(k, l, r);
		int mid = ((l+r)>>1);
		LL ret = 0;
		if(lq <= mid)
			ret+=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret+=ask(rs, mid+1, r, lq, rq);
		return ret;
	}
}A;
struct treee {
	LL tr[N<<2], ww[N<<2], gs[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		if(l == r) {
			ww[k]=l;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		ww[k]=ww[ls]+ww[rs];
	}
	void down(int k) {
		if(lzy[k]) {
			tr[ls]+=1LL*lzy[k]*ww[ls];
			gs[ls]+=lzy[k];
			lzy[ls]+=lzy[k];
			tr[rs]+=1LL*lzy[k]*ww[rs];
			gs[rs]+=lzy[k];
			lzy[rs]+=lzy[k];
			lzy[k]=0;
		}
	}
	void updtt(int k, int l, int r, int lq, int rq, int ppd) {
		if(lq <= l && r <= rq) {
			if(!ppd)
				tr[k]=0, lzy[k]+=-gs[k], gs[k]=0;
			else
				tr[k]+=ww[k], ++lzy[k], ++gs[k];
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updtt(ls, l, mid, lq, rq, ppd);
		if(mid+1 <= rq)
			updtt(rs, mid+1, r, lq, rq, ppd);
		tr[k]=tr[ls]+tr[rs];
	}
	LL ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		down(k);
		int mid = ((l+r)>>1);
		LL ret = 0;
		if(lq <= mid)
			ret+=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret+=ask(rs, mid+1, r, lq, rq);
		return ret;
	}
}B;

signed main() {
	File("ds");
	read(n), read(q);
	int pd = 1;
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i < n; ++i)
		pd&=(a[i] <= a[i+1]);
	A.built(1, 1, n);
	if(pd) {
		// debug("sub!\n");
		B.built(1, 1, n);
		for(int i = 1; i <= q; ++i) {
			read(opt);
			if(opt == 1) {
				read(vv);
				ll = 1, rr = n;
				int to = n+1;
				while(ll <= rr) {
					int mid = ((ll+rr)>>1);
					if(A.ask(1, 1, n, mid, mid)+B.ask(1, 1, n, mid, mid) >= vv)
						to=mid, rr=mid-1;
					else
						ll=mid+1;
				}
				if(to != n+1)
					A.updttt(1, 1, n, to, n, vv), B.updtt(1, 1, n, to, n, 0);
			}
			if(opt == 2) {
				B.updtt(1, 1, n, 1, n, 1);
			}
			if(opt == 3) {
				read(ll), read(rr);
				write(A.ask(1, 1, n, ll, rr)+B.ask(1, 1, n, ll, rr), '\n');
			}
		}
		return 0;
	}
	for(int i = 1; i <= q; ++i) {
		read(opt);
		if(opt == 1) {
			read(vv);
			A.updt(1, 1, n, vv);
		}
		if(opt == 2) {
			for(int j = 1; j <= n; ++j)
				A.updtt(1, 1, n, j, (LL) A.ask(1, 1, n, j, j)+j);
		}
		if(opt == 3) {
			read(ll), read(rr);
			write(A.ask(1, 1, n, ll, rr), '\n');
		}
	}
	return 0;
}