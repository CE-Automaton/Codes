#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, q, opt, tt, ll, rr, xx;
struct qwq {
	int p, a, b;
}a[N];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int comp2(qwq A, qwq B) {
	return A.p < B.p;
}
int comp3(qwq A, qwq B) {
	return A.p > B.p;
}
struct hs {
	int kk, b;
	int ww(int x) {
		return upd(1LL*kk*x%mod+b);
	}
}tr[N<<3];
hs merge(hs A, hs B) {
	return hs {(int) (1LL*A.kk*B.kk%mod), B.ww(A.b)};
}
#define ls (k<<1)
#define rs (ls|1)
void built(int k, int l, int r) {
	if(l == r) {
		tr[k]=hs {a[l].a, a[l].b};
		return ;
	}
	int mid = ((l+r)>>1);
	built(ls, l, mid);
	built(rs, mid+1, r);
	tr[k]=merge(tr[ls], tr[rs]);
}
void updt(int k, int l, int r, int to) {
	if(l == r) {
		tr[k]=hs {a[l].a, a[l].b};
		return ;
	}
	int mid = ((l+r)>>1);
	if(to <= mid)
		updt(ls, l, mid, to);
	else
		updt(rs, mid+1, r, to);
	tr[k]=merge(tr[ls], tr[rs]);
}
hs ask(int k, int l, int r, int lq, int rq) {
	if(lq <= l && r <= rq)
		return tr[k];
	int mid = ((l+r)>>1);
	if(lq <= mid && mid < rq)
		return merge(ask(ls, l, mid, lq, rq), ask(rs, mid+1, r, lq, rq));
	if(lq <= mid)
		return ask(ls, l, mid, lq, rq);
	else
		return ask(rs, mid+1, r, lq, rq);
}

signed main() {
	File("stibium");
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i].p), read(a[i].a), read(a[i].b);
	if(n <= 2000 && q <= 2000) {//sub1
		for(int i = 1; i <= q; ++i) {
			read(opt);
			if(opt == 0) {
				read(tt), read(ll), read(rr), read(xx);
				a[tt+1]=qwq {ll, rr, xx};
			}
			else 
				if(opt == 1) {
					read(ll), read(rr), read(xx);
					for(int i = ll+1; i <= rr; ++i)
						xx=upd(1LL*xx*a[i].a%mod+a[i].b);
					write(xx, '\n');
				}
				else 
					if(opt == 2) {
						read(ll), read(rr);
						sort(a+1+ll, a+1+rr, comp2);
					}
					else {
						read(ll), read(rr);
						sort(a+1+ll, a+1+rr, comp3);
					}
		}
		return 0;
	}
	built(1, 1, n);
	for(int i = 1; i <= q; ++i) {
		read(opt);
		if(opt == 0) {
			read(tt), read(ll), read(rr), read(xx);
			a[tt+1]=qwq {ll, rr, xx};
			updt(1, 1, n, tt+1);
		}
		else {
			read(ll), read(rr), read(xx);
			write(ask(1, 1, n, ll+1, rr).ww(xx), '\n');
		}
	}
	return 0;
}