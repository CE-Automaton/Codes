#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, op, l, r, rt[N], up[N], rtb[N], upb[N], hd[N], gs, tot;
struct node {
	int ls, rs, pd, r;
}tr[5500005];
struct qwq {
	int l, r, w;
}az[2000005];
struct tree {
	void built(int& k, int l, int r) {
		k=++gs;
		tr[k].pd=tr[k].ls=tr[k].rs=0;
		tr[k].r=l;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(tr[k].ls, l, mid);
		built(tr[k].rs, mid+1, r);
	}
	void upup(int k) {
		tr[k].pd=(tr[tr[k].ls].pd&tr[tr[k].rs].pd);
		tr[k].r=(tr[tr[k].ls].pd ? tr[tr[k].rs].r : tr[tr[k].ls].r);
	}
	void updt(int k, int l, int r, int to) {
		if(l == r) {
			tr[k].pd=1;
			tr[k].r=l;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(tr[k].ls, l, mid, to);
		else
			updt(tr[k].rs, mid+1, r, to);
		upup(k);
	}
	int ask(int k, int l, int r, int lq) {
		if(tr[k].pd)
			return -1;
		if(l == r) 
			return l;
		int mid = ((l+r)>>1);
		if(lq <= mid && !tr[tr[k].ls].pd) {
			int ret = ask(tr[k].ls, l, mid, lq);
			if(ret != -1)
				return ret;
		}
		return ask(tr[k].rs, mid+1, r, lq);
	}
}A[N], bio[N];
void blt(int& k, int l, int r) {
	k=++tot; 
	az[tot].l=-1;
	az[tot].w=l;
	for(int o = l+1; o <= r; ++o)
		++tot, az[tot-1].r=tot, az[tot].w=o, az[tot].l=tot-1;
	az[tot].r=-1;//首尾标记一下 
}
void dlt(int to) {
	if(az[to].l != -1)
		az[az[to].l].r=az[to].r;
	if(az[to].r != -1)
		az[az[to].r].l=az[to].l;
}
struct tree2 {
	int sm[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		sm[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int to, int w) {
		if(l == r) {
			sm[k]=w;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, w);
		else
			updt(rs, mid+1, r, to, w);
		sm[k]=sm[ls]+sm[rs];
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return sm[k];
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret+=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret+=ask(rs, mid+1, r, lq, rq);
		return ret;
	}
}B;

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

signed main() {
	freopen("stella.in", "r", stdin);
	freopen("stella.out", "w", stdout);
	read(n), read(m);
	for(int o = 1; o <= n; ++o)
		up[o]=n/o+1, A[o].built(rt[o], 0, up[o]), 
		upb[o]=n/o, bio[o].built(rtb[o], 1, upb[o]), blt(hd[o], 1, upb[o]);
	int rrr = n;
	for(int i = 1; i <= m; ++i) {
		read(op), read(l);
		if(op == 1) {
			--l;
			for(int ll = 1, rr = 0; ll <= l; ++ll) {
				rr=l/(l/ll);
				int kk = l/ll, st = bio[kk].ask(rtb[kk], 1, upb[kk], ll);
//				cout<<kk<<" "<<ll<<" "<<rr<<" "<<st<<"!?\n";
				if(st != -1)
					for(int o = hd[kk]+st-1; o != -1 && az[o].w <= rr; o=az[o].r) {
						int tt = az[o].w, op = tr[rt[tt]].r;
						A[tt].updt(rt[tt], 0, up[tt], kk);
						int po = tr[rt[tt]].r;
						if(op != po)
							B.updt(1, 1, n, tt, po);
						dlt(o);
						bio[kk].updt(rtb[kk], 1, upb[kk], tt);
					}
				ll=rr;
			}
			for(int o = l+1; o <= rrr; ++o) {
				int op = tr[rt[o]].r;
				A[o].updt(rt[o], 0, up[o], 0);
				int po = tr[rt[o]].r;
				if(op != po)
					B.updt(1, 1, n, o, po);
			}
			rrr=min(rrr, l);
		}
		else {
			read(r);
			write(B.ask(1, 1, n, l, r)+r-l+1, '\n');
		}
	}
	FastIO::flusher.~Flusher();
	return 0;
}
