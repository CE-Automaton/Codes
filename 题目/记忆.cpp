#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+5;
int n, q, a[N], opt, al, ar;
struct tree {
	struct node {
		int mn, mx, sum, lazyad, lazyfu;
	}tr[N<<2];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void upup(int k) {
		tr[k].mn=min(tr[ls].mn, tr[rs].mn);
		tr[k].mx=max(tr[ls].mx, tr[rs].mx);
		tr[k].sum=tr[ls].sum+tr[rs].sum;
	}
	void down(int k, int l, int r) {
		if(tr[k].lazyfu) {
			tr[ls].sum=-tr[ls].sum, swap(tr[ls].mn, tr[ls].mx), tr[ls].mn=-tr[ls].mn, tr[ls].mx=-tr[ls].mx;
			tr[ls].lazyad=-tr[ls].lazyad;
			tr[rs].sum=-tr[rs].sum, swap(tr[rs].mn, tr[rs].mx), tr[rs].mn=-tr[rs].mn, tr[rs].mx=-tr[rs].mx;
			tr[rs].lazyad=-tr[rs].lazyad;
			tr[ls].lazyfu^=1;
			tr[rs].lazyfu^=1;
			tr[k].lazyfu=0;
		}
		int mid = ((l+r)>>1);
		tr[ls].sum+=tr[k].lazyad*(mid-l+1);
		tr[ls].mn+=tr[k].lazyad;
		tr[ls].mx+=tr[k].lazyad;
		tr[rs].sum+=tr[k].lazyad*(r-mid);
		tr[rs].mn+=tr[k].lazyad;
		tr[rs].mx+=tr[k].lazyad;
		tr[ls].lazyad+=tr[k].lazyad;
		tr[rs].lazyad+=tr[k].lazyad;
		tr[k].lazyad=0;
	}
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=node {a[l], a[l], a[l], 0, 0};
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int az) {
		if(tr[k].mn >= az) {
			tr[k].sum-=(r-l+1)*az;
			tr[k].mn-=az;
			tr[k].mx-=az;
			tr[k].lazyad-=az;
			return ;
		}
		if(tr[k].mx < az) {
			tr[k].sum=-tr[k].sum, swap(tr[k].mn, tr[k].mx), tr[k].mn=-tr[k].mn, tr[k].mx=-tr[k].mx;
			tr[k].lazyad=-tr[k].lazyad;
			tr[k].lazyfu^=1;
			tr[k].sum+=(r-l+1)*az;
			tr[k].mn+=az;
			tr[k].mx+=az;
			tr[k].lazyad+=az;
			return ;
		}
		down(k, l, r);
		int mid = ((l+r)>>1);
		updt(ls, l, mid, az);
		updt(rs, mid+1, r, az);
		upup(k);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k].sum;
		down(k, l, r);
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret+=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret+=ask(rs, mid+1, r, lq, rq);
		upup(k);
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

signed main() {
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	A.built(1, 1, n);
	for(int i = 1; i <= q; ++i) {
		read(opt), read(al);
		if(opt == 2)
			read(ar), write(A.ask(1, 1, n, al, ar), '\n');
		else
			A.updt(1, 1, n, al);
	}
	return 0;
}
