#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 5e5+5;
int n, m, k, ll, rr, ii, jj, tt, opt, gs, rt[N];
uLL sd=1;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
uLL rd() {
	return sd=sd*1145141ull*1145141ull;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
struct node {
	int l, r, siz, len, w, ws, lzy;
	uLL pri;
}tr[N<<2];
struct tree {
	int wls[N<<2], ws[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k) {
		wls[k]=upd(wls[ls]+wls[rs]);
		ws[k]=upd(ws[ls]+ws[rs]);
	}
	void down(int k) {
		if(!lzy[k]) return ;
		ws[ls]=upd(ws[ls]+1LL*wls[ls]*lzy[k]%mod);
		lzy[ls]=upd(lzy[ls]+lzy[k]);
		ws[rs]=upd(ws[rs]+1LL*wls[rs]*lzy[k]%mod);
		lzy[rs]=upd(lzy[rs]+lzy[k]);
		lzy[k]=0;
	}
	void built(int k, int l, int r) {
		lzy[k]=0;
		if(l == r) {
			wls[k]=n;
			ws[k]=0;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		built(ls, l, mid), built(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int to) {//更新序列总和、总长度
		if(l == r) {
			wls[k]=tr[rt[l]].siz;
			ws[k]=tr[rt[l]].ws;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(to <= mid) updt(ls, l, mid, to);
		else updt(rs, mid+1, r, to);
		upup(k);
	}
	void updtt(int k, int l, int r, int lq, int rq, int w) {//序列总加
		if(l == r) {
			lzy[k]=upd(lzy[k]+w);
			tr[rt[l]].lzy=upd(tr[rt[l]].lzy+lzy[k]);
			tr[rt[l]].w=upd(tr[rt[l]].w+lzy[k]);
			tr[rt[l]].ws=upd(tr[rt[l]].ws+1LL*tr[rt[l]].siz*lzy[k]%mod);
			wls[k]=tr[rt[l]].siz;
			ws[k]=tr[rt[l]].ws;
			lzy[k]=0;
			return ;
		}
		if(lq <= l && r <= rq) {
			ws[k]=upd(ws[k]+1LL*wls[k]*w%mod);
			lzy[k]=upd(lzy[k]+w);
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
	int ask(int k, int l, int r, int lq, int rq) {//询问序列总和
		if(lq <= l && r <= rq) 
			return ws[k];
		down(k);
		int mid = ((l+r)>>1), ww = 0;
		if(lq <= mid)
			ww=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ww=upd(ww+ask(rs, mid+1, r, lq, rq));
		upup(k);
		return ww;
	}
	void dfs(int k, int l, int r, int to) {//序列下传标记
		if(l == r) {
			tr[rt[l]].lzy=upd(tr[rt[l]].lzy+lzy[k]);
			tr[rt[l]].w=upd(tr[rt[l]].w+lzy[k]);
			tr[rt[l]].ws=upd(tr[rt[l]].ws+1LL*tr[rt[l]].siz*lzy[k]%mod);
			wls[k]=tr[rt[l]].siz;
			ws[k]=tr[rt[l]].ws;
			// if(wls[k] != tr[rt[l]].siz)
			// 	debug("!!!\n");
			// if(ws[k] != tr[rt[l]].ws)
			// 	debug("!!!\n");
			lzy[k]=0;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(to <= mid) dfs(ls, l, mid, to);
		else dfs(rs, mid+1, r, to);
		upup(k);
	}
}A;
int blt(int len, int w) {
	++gs;
	tr[gs].len=tr[gs].siz=len;
	tr[gs].l=tr[gs].r=0;
	tr[gs].w=w;
	tr[gs].ws=1LL*len*w%mod;
	tr[gs].pri=rd();
	return gs;
}
void upup(int now) {
	tr[now].siz=tr[tr[now].l].siz+tr[tr[now].r].siz+tr[now].len;
	tr[now].ws=upd(1LL*tr[now].w*tr[now].len%mod+upd(tr[tr[now].l].ws+tr[tr[now].r].ws));
}
void down(int now) {
	if(!now || !tr[now].lzy) return ;
	if(tr[now].l)
		tr[tr[now].l].w=upd(tr[tr[now].l].w+tr[now].lzy), 
		tr[tr[now].l].ws=upd(tr[tr[now].l].ws+1LL*tr[now].lzy*tr[tr[now].l].siz%mod), 
		tr[tr[now].l].lzy=upd(tr[tr[now].l].lzy+tr[now].lzy);
	if(tr[now].r)
		tr[tr[now].r].w=upd(tr[tr[now].r].w+tr[now].lzy), 
		tr[tr[now].r].ws=upd(tr[tr[now].r].ws+1LL*tr[now].lzy*tr[tr[now].r].siz%mod), 
		tr[tr[now].r].lzy=upd(tr[tr[now].r].lzy+tr[now].lzy);
	tr[now].lzy=0;
}
int merge(int x, int y) {
	down(x), down(y);
	if(x == 0 || y == 0) return x+y;
	if(tr[x].pri < tr[y].pri) {
		tr[x].r=merge(tr[x].r, y);
		upup(x);
		return x;
	}
	else {
		tr[y].l=merge(x, tr[y].l);
		upup(y);
		return y;
	}
}
void fl_siz(int now, int sizz, int& x, int& y) {
	if(!now) {
		x=y=0;
		return ;
	}
	down(now);
	int ll = tr[now].len+tr[tr[now].l].siz;
	if(ll <= sizz) {
		x=now;
		fl_siz(tr[now].r, sizz-ll, tr[now].r, y);
	}
	else 
		if(tr[tr[now].l].siz < sizz) {
			int ln = tr[now].len-(sizz-tr[tr[now].l].siz);
			tr[now].len=sizz-tr[tr[now].l].siz;
			x=now;
			y=merge(blt(ln, tr[now].w), tr[now].r);
			tr[now].r=0;
		}
		else {
			y=now;
			fl_siz(tr[now].l, sizz, x, tr[now].l);
		}
	upup(now);
}
void dfss(int now) {
	down(now); 
	if(tr[now].l != 0)
		dfss(tr[now].l);
	debug(tr[now].len, tr[now].w, "!\n");
	if(tr[now].r != 0)
		dfss(tr[now].r);
}
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
	File("sequence");
	read(n), read(m), read(k);
	for(int i = 1; i <= m; ++i)
		rt[i]=blt(n, 0);
	A.built(1, 1, m);
	for(int i = 1; i <= k; ++i) {
		read(opt);
		if(opt == 1) {
			read(ii), read(ll), read(rr), read(tt);
			A.dfs(1, 1, m, ii);
			int x=0, y=0, z=0, f=0;
			fl_siz(rt[ii], rr, f, z);
			fl_siz(f, ll-1, x, y);
			tr[y].w=upd(tr[y].w+tt), 
			tr[y].ws=upd(tr[y].ws+1LL*tt*tr[y].siz%mod), 
			tr[y].lzy=upd(tr[y].lzy+tt);
			rt[ii]=merge(merge(x, y), z);
			A.updt(1, 1, m, ii);
		}
		else if(opt == 2) {
			read(ii), read(ll), read(rr);
			A.dfs(1, 1, m, ii);
			int x=0, y=0, z=0, f=0;
			fl_siz(rt[ii], rr, f, z);
			fl_siz(f, ll-1, x, y);
			write(tr[y].ws, '\n');
			rt[ii]=merge(merge(x, y), z);
			A.updt(1, 1, m, ii);
			// debug("...\n");
		}
		else if(opt == 3) {
			read(ll), read(rr);
			write(A.ask(1, 1, m, ll, rr), '\n');
			// debug("...\n");
		}
		else if(opt == 4) {
			read(ll), read(rr), read(tt);
			A.updtt(1, 1, m, ll, rr, tt);
		}
		else {
			read(ii), read(ll), read(rr), read(jj), read(tt);
			A.dfs(1, 1, m, ii);
			A.dfs(1, 1, m, jj);
			int x=0, y=0, z=0, f=0;
			fl_siz(rt[ii], rr, f, z);
			fl_siz(f, ll-1, x, y);
			rt[ii]=merge(x, z);
			x=0, z=0;
			fl_siz(rt[jj], tt, x, z);
			rt[jj]=merge(merge(x, y), z);
			A.updt(1, 1, m, ii);
			A.updt(1, 1, m, jj);
		}
		// for(int j = 1; j <= m; ++j)
		// 	A.dfs(1, 1, m, j), debug(j, "!!!:\n"), dfss(rt[j]);
	}
	return 0;
}