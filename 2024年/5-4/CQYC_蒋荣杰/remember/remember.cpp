#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, q, typ, xx, ll, rr, yy, rt[15], gs;
LL a[15][N], mod, kk;

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
LL upd(LL x) {
	return (x >= mod ? x-mod :x);
}
struct node { LL w, lzy; int ls, rs; }tr[(N<<2)*11];
struct tree {
	void upup(int k) { tr[k].w=upd(tr[tr[k].ls].w+tr[tr[k].rs].w); }
	void down(int k, int l, int r) {
		if(tr[k].lzy == 0) return ;
		int mid = ((l+r)>>1);
		if(tr[k].ls)
			tr[tr[k].ls].w=upd(tr[tr[k].ls].w+1LL*tr[k].lzy*(mid-l+1)%mod), 
			tr[tr[k].ls].lzy=upd(tr[tr[k].ls].lzy+tr[k].lzy);
		if(tr[k].rs)
			tr[tr[k].rs].w=upd(tr[tr[k].rs].w+1LL*tr[k].lzy*(r-mid)%mod), 
			tr[tr[k].rs].lzy=upd(tr[tr[k].rs].lzy+tr[k].lzy);
		tr[k].lzy=0;
	}
	void built(int& k, int l, int r, int dd) {
		k=++gs;
		tr[k].w=tr[k].ls=tr[k].rs=0;
		if(l == r) {
			tr[k].w=a[dd][l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(tr[k].ls, l, mid, dd);
		built(tr[k].rs, mid+1, r, dd);
		upup(k);
	}
	void updt(int& x, int& y, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			swap(x, y);
			return ;
		}
		down(x, l, r);
		down(y, l, r);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(tr[x].ls, tr[y].ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			updt(tr[x].rs, tr[y].rs, mid+1, r, lq, rq);
		upup(x);
		upup(y);
	}
	LL ask(int x, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[x].w;
		down(x, l, r);
		int mid = ((l+r)>>1);
		LL ret = 0;
		if(lq <= mid)
			ret=ask(tr[x].ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret=upd(ret+ask(tr[x].rs, mid+1, r, lq, rq));
		return ret;
	}
	void add(int x, int l, int r, int lq, int rq, LL w) {
		if(lq <= l && r <= rq) {
			tr[x].w=upd(tr[x].w+1LL*(r-l+1)*w%mod);
			tr[x].lzy=upd(tr[x].lzy+w);
			return ;
		}
		down(x, l, r);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			add(tr[x].ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			add(tr[x].rs, mid+1, r, lq, rq, w);
		upup(x);
	}
}A;

signed main() {
	File("remember");
	read(n), read(m), read(q), read(mod);
	if(n <= 100 && q <= 100) {
		for(int i = 1; i <= m; ++i)
			for(int j = 1; j <= n; ++j)
				read(a[i][j]), a[i][j]%=mod;
		for(int i = 1; i <= q; ++i) {
			read(typ);
			if(typ == 1) {
				read(xx), read(ll), read(rr);
				LL ans = 0;
				for(int j = ll; j <= rr; ++j)
					ans=upd(ans+a[xx][j]);
				write(ans, '\n');
			}
			if(typ == 2) {
				read(xx), read(ll), read(rr), read(yy);
				int ans = 1;
				for(int j = ll+yy; j <= rr; ++j) {
					LL lst = 0;
					for(int i = j-yy; i < j; ++i)
						lst=upd(lst+a[xx][i]);
					ans&=(lst == a[xx][j]);
				}
				if(ans) 
					pc('w'), pc('h'), pc('e'), pc('r'), pc('e'), pc(' '), pc('i'), pc('s'), pc(' '), pc('s'), pc('e'), pc('l'), pc('f'), pc('?'), pc('\n');
				else 
					pc('i'), pc('n'), pc('f'), pc('i'), pc('n'), pc('i'), pc('t'), pc('y'), pc(' '), pc('l'), pc('o'), pc('o'), pc('p'), pc('!'), pc('\n');
			}
			if(typ == 3) {
				read(xx), read(ll), read(rr), read(kk);
				kk=kk%mod;
				for(int i = ll; i <= rr; ++i)
					a[xx][i]=upd(a[xx][i]+kk);
			}
			if(typ == 4) {
				read(xx), read(yy), read(ll), read(rr);
				for(int i = ll; i <= rr; ++i)
					swap(a[xx][i], a[yy][i]);
			}
		}
	}
	else {
		for(int i = 1; i <= m; ++i) {
			for(int j = 1; j <= n; ++j)
				read(a[i][j]), a[i][j]%=mod;
			A.built(rt[i], 1, n, i);
		}
		for(int i = 1; i <= q; ++i) {
			read(typ);
			if(typ == 1) {
				read(xx), read(ll), read(rr);
				write(A.ask(rt[xx], 1, n, ll, rr), '\n');
			}
			if(typ == 2) 
				exit(0);//哈哈:D
			if(typ == 3) {
				read(xx), read(ll), read(rr), read(kk);
				kk=kk%mod;
				A.add(rt[xx], 1, n, ll, rr, kk);
			}
			if(typ == 4) {
				read(xx), read(yy), read(ll), read(rr);
				A.updt(rt[xx], rt[yy], 1, n, ll, rr);
			}
		}
	}
	FastIO::flusher.~Flusher();
	return 0;
}