#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
const int N = 1e5+5;
int n, q, a[N], k, ql, qr;
struct node {
	int lzy, sl, sr, l[2], r[2], pd[2];
}tr[N<<2];
void swp(node& x) {
	// debug(x.sl, x.sr, x.pd[0], x.pd[1], "-> ");
	swap(x.l[0], x.l[1]);
	swap(x.r[0], x.r[1]);
	swap(x.pd[0], x.pd[1]);
	x.lzy^=1;
	// debug(x.sl, x.sr, x.pd[0], x.pd[1], x.lzy, "!\n");
}
struct tree {
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(node& ret, node ll, node rr) {
		for(int w = 0; w <= 1; ++w) {
			ret.pd[w]=(ll.pd[w]|rr.pd[w]);
			if(!ret.pd[w]) {
				ret.l[w]=ret.r[w]=0;
				continue;
			}
			if(ll.pd[w]) ret.l[w]=ll.l[w];
			else ret.l[w]=rr.l[w]+(ll.sr-ll.sl+1);
			if(rr.pd[w]) ret.r[w]=rr.r[w];
			else ret.r[w]=ll.r[w]+(rr.sr-rr.sl+1);
		}
		ret.sl=ll.sl;
		ret.sr=rr.sr;
	}
	void down(int k) {
		if(tr[k].lzy == 1) {
			swp(tr[ls]), swp(tr[rs]);
			tr[k].lzy=0;
		}
	}
	void built(int k, int l, int r) {
		tr[k].lzy=0;
		tr[k].sl=l, tr[k].sr=r;
		if(l == r) {
			tr[k].l[a[l]]=tr[k].r[a[l]]=0;
			tr[k].pd[a[l]]=1;
			tr[k].l[a[l]^1]=tr[k].r[a[l]^1]=0;
			tr[k].pd[a[l]^1]=0;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(tr[k], tr[ls], tr[rs]);
	}
	node ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		down(k);
		int mid = ((l+r)>>1);
		node ret;
		if(lq <= mid && mid+1 <= rq)
			upup(ret, ask(ls, l, mid, lq, rq), ask(rs, mid+1, r, lq, rq));
		else if(lq <= mid)
			ret=ask(ls, l, mid, lq, rq);
		else
			ret=ask(rs, mid+1, r, lq, rq);
		upup(tr[k], tr[ls], tr[rs]);
		return ret;
	}
	void updt(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			swp(tr[k]);
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq);
		upup(tr[k], tr[ls], tr[rs]);
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
	File("A");
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	A.built(1, 1, n);
	for(int i = 1; i <= q; ++i) {
		read(k);
		if(k == 1) 
			read(ql), read(qr), A.updt(1, 1, n, ql, qr);
		else {
			read(k);
			int now=0;
			for(int j = 1; j <= k; ++j) {
				read(ql), read(qr);
				node re = A.ask(1, 1, n, ql, qr);
				// debug(ql, qr, re.l[1], re.l[0], re.r[1], re.r[0], re.pd[1], re.pd[0], "!?\n");
				now^=(re.pd[1] ? (qr-ql+1)-min(re.l[1], re.r[1])*2 : 0);
			}
			if(!now)
				puts("No");
			else
				puts("Yes");
		}
	}
	return 0;
}