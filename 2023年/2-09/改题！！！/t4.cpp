#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, k, a[N], q, que, xx, yy;
namespace nqio {
	const unsigned R=4e5,W=4e5;
	char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;
	bool s;
	struct q {
		void r(char&x) {x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}
		void f() { fwrite(o,1,c-o,stdout); c=o; }
		~q() { f(); }
		void w(char x){ *c=x; if(++c==d) f(); }
		q&operator>>(char&x) { do r(x); while(x<=32); return*this; }
		q&operator>>(char*x) { do r(*x); while(*x<=32); while(*x>32) r(*++x); *x=0; return*this; }
		template<typename t>q&operator>>(t&x) {
			for(r(y),s=0;!isdigit(y);r(y))
				s|=y==45;
			if(s) for(x=0;isdigit(y);r(y))
				x=x*10-(y^48);
			else for(x=0;isdigit(y);r(y))x=x*10+(y^48);
			return*this;
		}
		q&operator<<(char x){ w(x); return*this; }
		q&operator<<(char*x){ while(*x) w(*x++); return*this; }
		q&operator<<(const char*x){ while(*x) w(*x++); return*this; }
		template<typename t>q&operator<<(t x) {
			if(!x) w(48);
			else if(x<0) for(w(45);x;x/=10) *p++=48|-(x%10);
			else for(;x;x/=10)*p++=48|x%10;
			while(p!=h)w(*--p);return*this;
		}
	}qio;
}
using nqio::qio;
struct tree1 {
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	int tr[N<<3], pro, qwq;
	void upup(int k) { tr[k]=max(tr[ls], tr[rs]); }
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=a[l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int to) {
		if(l == r) {
			tr[k]=a[l];
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) updt(ls, l, mid, to);
		else updt(rs, mid+1, r, to);
		upup(k);
	}
	int findl(int k, int l, int r) {
		if(l == r) {
			if(l != pro && (tr[k] > a[pro] || (tr[k] == a[pro] && qwq)))
				return l;
			return 0;
		}
		int mid = ((l+r)>>1), ret = 0;
		if(mid+1 <= pro && (tr[rs] > a[pro] || (tr[rs] == a[pro] && qwq)))
			ret = findl(rs, mid+1, r);
		if(ret == 0 && (tr[ls] > a[pro] || (tr[ls] == a[pro] && qwq)))
			ret = findl(ls, l, mid);
		return ret;
	}
	int findr(int k, int l, int r) {
		if(l == r) {
			if(l != pro && (tr[k] > a[pro] || (tr[k] == a[pro] && qwq)))
				return l;
			return n+1;
		}
		int mid = ((l+r)>>1), ret = n+1;
		if(pro <= mid && (tr[ls] > a[pro] || (tr[ls] == a[pro] && qwq)))
			ret = findr(ls, l, mid);
		if(ret == n+1 && (tr[rs] > a[pro] || (tr[rs] == a[pro] && qwq)))
			ret = findr(rs, mid+1, r);
		return ret;
	}
	#undef ls
	#undef rs
}A;

struct tree2 {
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	int tr[N<<3], lazy[N<<3], zf, lq, rq;
	void upup(int k) { tr[k]=tr[ls]+tr[rs]; }
	void down(int k, int l, int r) { 
		if(lazy[k] == 0) return ;
		int mid = ((l+r)>>1);
		tr[ls]+=lazy[k]*(mid-l+1), tr[rs]+=lazy[k]*(r-mid);
		lazy[ls]+=lazy[k], lazy[rs]+=lazy[k];
		lazy[k]=0;
	}
	void built(int k, int l, int r) {
		tr[k]=0;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r) {
		if(lq <= l && r <= rq) {
			tr[k]+=zf*(r-l+1);
			lazy[k]+=zf;
			return ;
		}
		down(k, l, r);
		int mid = ((l+r)>>1);
		if(lq <= mid) updt(ls, l, mid);
		if(mid+1 <= rq) updt(rs, mid+1, r);
		upup(k);
	}
	void updtt(int k, int l, int r, int to, int w) {
		if(l == r) {
			tr[k]=w;
			return ;
		}
		down(k, l, r);
		int mid = ((l+r)>>1);
		if(to <= mid) updtt(ls, l, mid, to, w);
		else updtt(rs, mid+1, r, to, w);
		upup(k);
	}
	int ask(int k, int l, int r) {
		if(lq <= l && r <= rq) 
			return tr[k];
		down(k, l, r);
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid) 
			ret+=ask(ls, l, mid);
		if(mid+1 <= rq) 
			ret+=ask(rs, mid+1, r);
		upup(k);
		return ret;
	}
	#undef ls
	#undef rs
}B;
void update(int i, int zf, int t) {
	A.pro=i; A.qwq=1, B.zf=zf;
	int l = A.findl(1, 1, n);
	if(l+1 <= i-1 && (a[l] != a[i] || t))
		B.lq=l+1, B.rq=i-1, B.updt(1, 1, n); 
	int r = A.findr(1, 1, n);
	if(i+1 <= r-1 && a[r] != a[i])
		B.lq=i+1, B.rq=r-1, B.updt(1, 1, n);
}
int pdd(int x) {
	int p = -1;
	A.pro=x; A.qwq=0;
	int l = A.findl(1, 1, n);
	if(l != 0) p=l;
	int r = A.findr(1, 1, n);
	if(r != n+1 && (p == -1 || a[r] < a[p])) p=r;
	B.lq=p, B.rq=p;
	return (p == -1 ? 0 : B.ask(1, 1, n)+1);
}
signed main() {
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	qio>>n>>k;
	for(int i = 1; i <= n; ++i)
		qio>>a[i]; 
	A.built(1, 1, n);
	B.built(1, 1, n);
	for(int i = 1; i <= n; ++i) 
		update(i, 1, 1);
	qio>>q;
	for(int i = 1; i <= q; ++i) {
		qio>>que>>xx;
		if(que == 1) {
			yy=xx+1;
			if(a[xx] != a[yy]) {
				if(a[xx] > a[yy]) swap(xx, yy);
				B.lq=yy, B.rq=yy; int haha = B.ask(1, 1, n);
				update(xx, -1, 0);
				swap(a[xx], a[yy]);
				A.updt(1, 1, n, xx); A.updt(1, 1, n, yy);
				update(yy, 1, 0);
				B.updtt(1, 1, n, xx, haha);
				B.updtt(1, 1, n, yy, pdd(yy));
			}
		}
		else 
			qio>>yy, B.lq=xx, B.rq=yy, qio<<(1LL*(n-1)*(yy-xx+1)+1LL*k*B.ask(1, 1, n))<<"\n";
	}
	return 0;
}
