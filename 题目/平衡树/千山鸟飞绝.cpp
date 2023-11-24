#include <bits/stdc++.h>
#define pi pair<int, int>
#define uLL unsigned long long
#define int long long
using namespace std;
const int N = 3e4+5, M = 3e5+5;
int n, t, gs, rt[N+M], w[N], bl[N], v, xx, yy, cnt;
map <pi, int> zb;
uLL sd=1;
uLL rd() { return sd=sd*1145141ull*1145141ull; }
int comp(int A, int B) {
	return w[A] < w[B];
}
struct qwq {
	int mxd/*插入以来最大威武值*/, cmxd/*插入以来次大威武值*/, mxsz/*插入以来最大siz(不除去自己)*/;
	qwq operator +(const qwq& A) const {
		qwq ret;
		int aa[5];
		aa[0]=mxd, aa[1]=cmxd, aa[2]=A.mxd, aa[3]=A.cmxd;
		sort(aa, aa+4, comp);
		ret.mxd=aa[3];
		ret.cmxd=0;
		for(int i = 2; i >= 0; --i)
			if(aa[i] != aa[i+1]) {
				ret.cmxd=aa[i];
				break;
			}
		ret.mxsz=max(mxsz, A.mxsz);
		return ret;
	}
}ans[N];
struct node {
	int l, r, key, siz, d/*威武值*/, mxd/*节点的最大威武值*/, cmxd/*节点的次大威武值*/, pdlz;
	qwq xi, lazy; 
	uLL pri;
}tr[N+M];

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
int blt(int key) {
	++gs;
	tr[gs].l=tr[gs].r=tr[gs].pdlz=0;
	tr[gs].d=tr[gs].mxd=key;
	tr[gs].key=key;
	tr[gs].cmxd=0;
	tr[gs].siz=1;
	tr[gs].pri=rd();
	tr[gs].xi=qwq {key, 0, 1};
	tr[gs].lazy=qwq {0, 0, 1};
	return gs;
}
void upup(int now) {
	int ll = tr[now].l, rr = tr[now].r, aa[5];
	tr[now].siz=1+tr[ll].siz+tr[rr].siz;
	tr[now].mxd=tr[now].d;
	tr[now].cmxd=0;
	if(ll) {
		aa[0]=tr[now].mxd, aa[1]=tr[now].cmxd, aa[2]=tr[ll].mxd, aa[3]=tr[ll].cmxd;
		sort(aa, aa+4, comp);
		tr[now].mxd=aa[3];
		tr[now].cmxd=0;
		for(int i = 2; i >= 0; --i)
			if(aa[i] != aa[i+1]) {
				tr[now].cmxd=aa[i];
				break;
			}
	}
	if(rr) {
		aa[0]=tr[now].mxd, aa[1]=tr[now].cmxd, aa[2]=tr[rr].mxd, aa[3]=tr[rr].cmxd;
		sort(aa, aa+4, comp);
		tr[now].mxd=aa[3];
		tr[now].cmxd=0;
		for(int i = 2; i >= 0; --i)
			if(aa[i] != aa[i+1]) {
				tr[now].cmxd=aa[i];
				break;
			}
	}
}
void down(int now) {
	if(now == 0 || tr[now].pdlz == 0) return ;
	int ll = tr[now].l, rr = tr[now].r;
	if(ll)
		tr[ll].xi=(tr[ll].xi+tr[now].lazy), tr[ll].lazy=(tr[ll].lazy+tr[now].lazy), tr[ll].pdlz=1;
	if(rr)
		tr[rr].xi=(tr[rr].xi+tr[now].lazy), tr[rr].lazy=(tr[rr].lazy+tr[now].lazy), tr[rr].pdlz=1;
	tr[now].pdlz=0;
	tr[now].lazy=qwq {0, 0, 1};
}
void fl_key(int now, int key, int& x, int& y) {
	if(!now) {
		x=y=0;
		return ;
	}
	down(now);
	if(tr[now].key <= key) {
		x=now;
		fl_key(tr[now].r, key, tr[now].r, y);
	}
	else {
		y=now;
		fl_key(tr[now].l, key, x, tr[now].l);
	}
	upup(now);
}
int merge(int x, int y) {
	down(x);
	down(y);
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
void insert(int k, int key) {
	int x, y;
	fl_key(rt[k], key, x, y);
	rt[k]=merge(merge(x, blt(key)), y);
	tr[rt[k]].pdlz=1;
	tr[rt[k]].lazy=qwq {tr[rt[k]].mxd, tr[rt[k]].cmxd, tr[rt[k]].siz};
	tr[rt[k]].xi=(tr[rt[k]].xi+tr[rt[k]].lazy);
}
int fr(int x, int y) {
	if(zb.find(pi{x, y}) != zb.end())
		return zb[pi{x, y}];
	else
		return (zb[pi{x, y}] = ++cnt);
}
void delt(int k, int key) {
	int x, y, z;
	tr[rt[k]].pdlz=1;
	tr[rt[k]].lazy=qwq {tr[rt[k]].mxd, tr[rt[k]].cmxd, tr[rt[k]].siz};
	tr[rt[k]].xi=tr[rt[k]].xi+tr[rt[k]].lazy;
	fl_key(rt[k], key-1, x, y);
	fl_key(y, key, z, y);
	ans[key]=(ans[key]+tr[z].xi);
	rt[k]=merge(x, y);
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(w[i]), read(xx), read(yy);
		ans[i].mxd=i, ans[i].cmxd=0, ans[i].mxsz=1;
		int haha = fr(xx, yy);
		insert(haha, i);
		bl[i]=haha;
//		cout<<1<<" "<<tr[1].xi.mxd<<" "<<tr[1].xi.cmxd<<" "<<tr[1].xi.mxsz<<"\n";
	}
	qwq A = qwq {2, 1, 2}, B = qwq {3, 4, 2};
	A=(A+B);
	read(t);
	for(int i = 1; i <= t; ++i) {
		read(v), read(xx), read(yy);
		int haha = fr(xx, yy);
		delt(bl[v], v);
		insert(haha, v);
		bl[v]=haha;
	}
	for(int i = 1; i <= n; ++i) {
		int k = bl[i], x, y, z;
		tr[rt[k]].pdlz=1;
		tr[rt[k]].lazy=qwq {tr[rt[k]].mxd, tr[rt[k]].cmxd, tr[rt[k]].siz};
		tr[rt[k]].xi=tr[rt[k]].xi+tr[rt[k]].lazy;
		fl_key(rt[k], i-1, x, y);
		fl_key(y, i, z, y);
		ans[i]=(ans[i]+tr[z].xi);
		rt[k]=merge(merge(x, z), y);
	}
	for(int i = 1; i <= n; ++i) {
		int ww = (i == ans[i].mxd ? ans[i].cmxd : ans[i].mxd);
		write(w[ww]*(ans[i].mxsz-1), '\n');
	}
	return 0;
}
