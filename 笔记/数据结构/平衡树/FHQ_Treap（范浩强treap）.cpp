#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
int n, opt, k, gs, rt;
uLL sd=1;
uLL rd() {
	return sd=sd*1145141ull*1145141ull;
}
struct node {
	int l, r, siz, key;
	uLL pri;
}tr[100005];
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
void dlt(int key) {
	int x, y, z;
	fl_key(rt, key, x, y);
	fl_key(x, key-1, z, x);
	rt=merge(merge(z, merge(tr[x].l, tr[x].r)), y);
}
int ask(int key) {
	int x, y, ret=0;
	fl_key(rt, key-1, x, y);
	ret=tr[x].siz+1;
	rt=merge(x, y);
	return ret;
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
int findl(int key) {
	int x, y, ret=0;
	fl_key(rt, key-1, x, y);
	ret=x;
	while(tr[ret].r != 0) ret=tr[ret].r;
	ret=tr[ret].key;
	rt=merge(x, y);
	return ret;
}
int findr(int key) {
	int x, y, ret=0;
	fl_key(rt, key, x, y);
	ret=y;
	while(tr[ret].l != 0) ret=tr[ret].l;
	ret=tr[ret].key;
	rt=merge(x, y);
	return ret;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &opt, &k);
		if(opt == 1) insert(k);
		else if(opt == 2) dlt(k);
		else if(opt == 3)
			printf("%d\n", ask(k));
		else if(opt == 4) 
			printf("%d\n", asks(k));
		else if(opt == 5)
			printf("%d\n", findl(k));
		else if(opt == 6)
			printf("%d\n", findr(k));
	}
	return 0;
}
