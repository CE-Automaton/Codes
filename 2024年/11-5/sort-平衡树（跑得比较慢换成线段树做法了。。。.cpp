#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 5e5+5;
int n, a[N], q, gs, rt, xx, yy;
uLL sd=1;
uLL rd() {
	return sd=sd*1145141ull*1145141ull;
}
struct node {
	LL key;
	int w, mn, l, r, siz, lzy;
	uLL pri;
}tr[N<<1];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
void upup(int x) {
	tr[x].mn=tr[x].w;
	tr[x].siz=1;
	if(tr[x].l)
		tr[x].mn=min(tr[x].mn, tr[tr[x].l].mn), tr[x].siz+=tr[tr[x].l].siz;
	if(tr[x].r)
		tr[x].mn=min(tr[x].mn, tr[tr[x].r].mn), tr[x].siz+=tr[tr[x].r].siz;
}
void down(int x) {
	if(!x || tr[x].lzy == 0) return ;
	if(tr[x].l)
		tr[tr[x].l].w+=tr[x].lzy, tr[tr[x].l].mn+=tr[x].lzy, tr[tr[x].l].lzy+=tr[x].lzy;
	if(tr[x].r)
		tr[tr[x].r].w+=tr[x].lzy, tr[tr[x].r].mn+=tr[x].lzy, tr[tr[x].r].lzy+=tr[x].lzy;
	tr[x].lzy=0;
}
void fl_key(int now, LL key, int& x, int& y) {
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
void add(int xxx) {
	int x = 0, y = 0;
	fl_key(rt, a[xxx]*1000000LL+xxx, x, y);
	++gs;
	tr[gs].key=a[xxx]*1000000LL+xxx;
	tr[gs].pri=rd();
	tr[gs].siz=1;
	tr[gs].l=tr[gs].r=tr[gs].lzy=0;
	tr[gs].w=tr[gs].mn=(x ? tr[x].siz : 0)+1-xxx;
	if(y) ++tr[y].lzy, ++tr[y].w, ++tr[y].mn;
	rt=merge(x, merge(gs, y));
}
void dlt(int xxx) {
	int x = 0, y = 0, z = 0;
	fl_key(rt, a[xxx]*1000000LL+xxx, x, z);
	fl_key(x, a[xxx]*1000000LL+xxx-1, x, y);
	if(z) --tr[z].lzy, --tr[z].w, --tr[z].mn;
	rt=merge(x, z);
}

signed main() {
	File("sort");
	read(n), read(q);
	for(int i = 1; i <= n; ++i) 
		read(a[i]), add(i);
	for(int i = 1; i <= q; ++i) {
		read(xx), read(yy);
		dlt(xx);
		a[xx]=yy;
		add(xx);
		write(-tr[rt].mn, '\n');
	}
	// write(clock(), '\n');
	FastIO::flusher.~Flusher();
	return 0;
}
