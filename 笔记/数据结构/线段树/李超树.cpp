#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5, X = 4e4+4;
const double eps=1e-10;
int n, op, k, a, b, c, d, lst, tot; 
struct qwq {
	double k, b;
}xd[N];

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
void cf1(int &x) {
	x=(x+lst-1)%39989+1;
}
void cf2(int &y) {
	y=(y+lst-1)%1000000000+1;
}
double ask(int nmb, int x) {
	return (double) xd[nmb].k*x+xd[nmb].b;
}
int pd(int nmb, int tr, int x) {
	double ww = ask(nmb, x) - ask(tr, x);
	if(ww > eps)
		return 1;
	if(-ww > eps)
		return 0;
	return (nmb < tr);
}
struct tree {//Àî³¬Ïß¶ÎÊ÷ 
	int tr[X<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int nmb) {
		if(tr[k] == 0) {
			tr[k]=nmb;
			return ;
		}
		int mid = ((l+r)>>1);
		if(pd(nmb, tr[k], mid)) 
			swap(nmb, tr[k]);
		if(l == r) return ;
		if(pd(nmb, tr[k], l))
			updt(ls, l, mid, nmb); 
		if(pd(nmb, tr[k], r))
			updt(rs, mid+1, r, nmb); 
	}
	void upd(int k, int l, int r, int lq, int rq, int nmb) {
		if(lq <= l && r <= rq) {
			updt(k, l, r, nmb);
			return ;
		}
		int mid = ((l+r)>>1);
		if(lq <= mid)
			upd(ls, l, mid, lq, rq, nmb);
		if(mid+1 <= rq)
			upd(rs, mid+1, r, lq, rq, nmb); 
	}
	int find(int k, int l, int r, int to) {
		if(l == r) 
			return tr[k];
		int mid = ((l+r)>>1), ret = 0;
		if(to <= mid)
			ret=find(ls, l, mid, to);
		else
			ret=find(rs, mid+1, r, to); 
		if(pd(tr[k], ret, to))
			ret=tr[k];
		return ret;
	}
}A;

signed main() {
	read(n);
	xd[0]=qwq {0, 0};
	A.built(1, 1, 39989); 
	for(int i = 1; i <= n; ++i) {
		read(op);
		if(op == 1) {
			read(a), read(b), read(c), read(d);
			cf1(a), cf2(b), cf1(c), cf2(d);
			if(a > c) swap(a, c), swap(b, d);
			if(a == c)
				xd[++tot]=qwq {0, (double) max(b, d)};
			else
				xd[++tot].k=1.0*(b-d)/(a-c), xd[tot].b=b-xd[tot].k*a;
//			cout<<xd[tot].k<<" "<<xd[tot].b<<"\n";
			A.upd(1, 1, 39989, a, c, tot);
		}
		else {
			read(k);
			cf1(k);
			lst=A.find(1, 1, 39989, k); 
			write(lst, '\n');
		}
	}
	return 0;
}
