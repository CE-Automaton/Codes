#include <bits/stdc++.h>
#define uLL unsigned long long 
using namespace std;
const int N = 2e6+5;
int n, m, to[N], rt[N], gs, ll, rr, ss, kk, ww, vis[N], zhan[N], tot;
uLL sd=1;
uLL rd() { return sd=sd*1145141ull*1145141ull; }
struct node {
	int l, r, key, siz;
	uLL pri;
}tr[N];

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
	tr[gs].l=tr[gs].r=0;
	tr[gs].key=key;
	tr[gs].siz=1;
	tr[gs].pri=rd();
	return gs;
}
void upup(int now) {
	tr[now].siz=1+tr[tr[now].l].siz+tr[tr[now].r].siz;
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
void insert(int k, int key) {
	int x, y;
	fl_key(rt[k], key, x, y);
	rt[k]=merge(merge(x, blt(key)), y);
}
void delt(int k, int key) {
	int x, y, z;
	fl_key(rt[k], key-1, x, y);
	fl_key(y, key, z, y);
	rt[k]=merge(x, y);
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(to[i]), insert(to[i], i);
	srand(1614564);
	for(int i = 1; i <= m; ++i) {
		read(ll), read(rr), read(ss), read(kk);
//		if(i == 512)
//			cout<<ll<<" "<<rr<<"\n";
		for(int j = 1; j <= 14; ++j) {
			int xx = rand()%(rr-ll+1)+ll;
			int x, y, z;
//			cout<<xx<<" ";
			xx=to[xx];
			if(vis[xx]) continue;
			vis[xx]=1, zhan[++tot]=xx;
			fl_key(rt[xx], ll-1, x, y);
			fl_key(y, rr, z, y);
			if(tr[z].siz > (rr-ll+1)/2) 
				ss=xx;
			rt[xx]=merge(merge(x, z), y);
		}
		while(tot) vis[zhan[tot]]=0, --tot;
//		puts("!!!");
		write(ss, '\n');
		for(int j = 1; j <= kk; ++j) 
			read(ww), delt(to[ww], ww), to[ww]=ss, insert(ss, ww);
	}
	ss=-1;
	for(int i = 1; i <= n; ++i) 
		if(tr[rt[to[i]]].siz > n/2)
			ss=to[i];
	write(ss, '\n');
	return 0;
}
