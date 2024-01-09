#include <bits/stdc++.h>
#define mod 1000000007
#define inf 2000000003
using namespace std;
const int N = 1e5+5;
int h, w, n;
struct az {
	int a, b;
};
struct qwq {
	int u, s, l, r;
}a[N];
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
struct tree {
	int tr[N<<2];
	vector <az> pnt[N];
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k) {
		tr[k]=min(tr[ls], tr[rs]);
	}
	void built(int k, int l, int r) {
		tr[k]=h+1;
		if(l == r) {
			pnt[l].push_back(az {inf, 0});
			pnt[l].push_back(az {h+1, 1});
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int to, int x, int gs) {
		if(l == r) {
			pnt[l].push_back(az {x, gs});
			tr[k]=x;
			return ;
		}
		int mid = ((l+r)>>1);
		(to <= mid ? updt(ls, l, mid, to, x, gs) : updt(rs, mid+1, r, to, x, gs));
		upup(k);
	}
	int ask(int k, int l, int r, int lq, int rq, int oo) {
		if(tr[k] > oo) return 0;
		if(l == r) {
			int ret = 0;
			// cout<<l<<" "<<r<<" "<<oo<<" "<<pnt[l].back().a<<" "<<pnt[l].back().b<<"!!\n";
			while(pnt[l].back().a <= oo)
				ret=upd(ret+pnt[l].back().b), pnt[l].pop_back();
			tr[k]=pnt[l].back().a;
			// cout<<pnt[l].back().a<<" "<<ret<<"ahhhhh\n";
			return ret;
		}
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=ask(ls, l, mid, lq, rq, oo);
		if(mid+1 <= rq)
			ret=upd(ret+ask(rs, mid+1, r, lq, rq, oo));
		upup(k);
		// cout<<l<<" "<<r<<" "<<ret<<"???\n";
		return ret;
	}
}A;

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
int comp(qwq AA, qwq BB) {
	return AA.u > BB.u;
}

signed main() {
	read(h), read(w), read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i].u), read(a[i].l), read(a[i].r), read(a[i].s);
	A.built(1, 1, w);
	sort(a+1, a+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		int x = A.ask(1, 1, w, a[i].l, a[i].r, a[i].u+a[i].s);
		// printf("%d %d !? %d\n", a[i].l, a[i].r, x);
		if(a[i].l != 1) A.updt(1, 1, w, a[i].l-1, a[i].u, upd(x+(a[i].r == w)*x));
		if(a[i].r != w) A.updt(1, 1, w, a[i].r+1, a[i].u, upd(x+(a[i].l == 1)*x));
	}
	write(A.ask(1, 1, w, 1, w, h+1), '\n');
	return 0;
}
