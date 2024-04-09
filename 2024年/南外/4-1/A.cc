#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
#define int LL
typedef unsigned long long uLL;
const int N = 2e5+5;
int n, aa, xa, xb, xc, ya, yb, yc, xx[N], yy[N], gs, rt, sm[N], ans;
uLL sd=1;
struct aaa {
	int x, y;
}p[N];

uLL rd() {
	return sd=sd*1145141ull*1145141ull;
}
struct node {
	int l, r, siz, key;
	uLL pri;
}tr[N<<2];
int blt(int key) {
	++gs;
	tr[gs].key=key;
	tr[gs].l=tr[gs].r=0; tr[gs].siz=1;
	tr[gs].pri=rd();
	return gs;
}
void upup(int now) {
	tr[now].siz=tr[tr[now].l].siz+tr[tr[now].r].siz+1;
}
void fl_key(int now, int key, int& x, int& y) {
	if(!now) {
		x=y=0;
		return ;
	}
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
void insert(int key) {
	int x, y;
	fl_key(rt, key, x, y);
	rt=merge(merge(x, blt(key)), y);
}
int asks(int siz) {
	int o = rt;
	while(1) {
		int qwq = tr[tr[o].l].siz+1;
		if(qwq == siz) break;
		if(siz < qwq) o=tr[o].l;
		else o=tr[o].r, siz-=qwq;
	}
	return tr[o].key;
}
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
int comp(aaa A, aaa B) {
	if(A.x == B.x)
		return A.y < B.y;
	return A.x < B.x;
}

signed main() {
	read(n);
	read(aa);
	for(int i = 1; i <= aa; ++i)
		read(p[i].x);
	read(aa);
	for(int i = 1; i <= aa; ++i)
		read(p[i].y);
	read(xa), read(xb), read(xc);
	read(ya), read(yb), read(yc);
	for(int i = aa+1; i <= 2*n; ++i)
		p[i].x=(p[i-1].x*xa+xb)%xc+1, 
		p[i].y=(p[i-1].y*ya+yb)%yc+1;
	for(int i = 1; i <= n*2; ++i)
		if(p[i].x > p[i].y) swap(p[i].x, p[i].y);
	sort(p+1, p+1+n+n, comp);
	sm[1]=p[1].y;
	for(int i = 2; i <= n*2; ++i)
		sm[i]=min(sm[i-1], p[i].y);
	int mn = p[n+n].y;
	for(int i = 1; i <= n-1; ++i)
		insert(p[n+n-i+1].y), mn=min(mn, p[n+n-i+1].y);
	ans=max(ans, sm[n]*p[1].x+min(mn, p[n+1].y)*p[n+1].x);
	// write(ans, '\n');
	for(int i = n; i > 1; --i) {
		insert(p[i+1].y);
		mn=min(mn, p[i+1].y);
		int xd = asks(n-i+2), yd = asks(n);
		ans=max(ans, min(sm[i-1], mn)*p[1].x+min(xd, p[i].y)*p[i].x);
		// debug(mn, xd, yd, min(sm[i-1], mn)*p[1].x+min(xd, p[i].y)*p[i].x, ' ');
		ans=max(ans, min(sm[i-1], yd)*p[1].x+min(mn, p[i].y)*p[i].x);
		// write(min(sm[i-1], yd)*p[1].x+min(mn, p[i].y)*p[i].x, '\n');
	}
	write(ans, '\n');
	return 0;
}