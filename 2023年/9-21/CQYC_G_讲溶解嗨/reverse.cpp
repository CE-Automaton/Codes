#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const int N = 6e5+5;
int n, m, r, gs, rt;
char s[N];
uLL sd=1;
uLL rd() {
	return sd=sd*1145141ull*1145141ull;
}
struct node {
	int l, r, siz, lazy;
	char key;
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
int blt(char key) {
	++gs;
	tr[gs].key=key;
	tr[gs].lazy=0;
	tr[gs].l=tr[gs].r=0; tr[gs].siz=1;
	tr[gs].pri=rd();
	return gs;
}
void upup(int now) {
	tr[now].siz=tr[tr[now].l].siz+tr[tr[now].r].siz+1;
}
void down(int now) {
	if(now == 0 || tr[now].lazy == 0) return ;
	swap(tr[now].l, tr[now].r);
	tr[tr[now].l].lazy^=1;
	tr[tr[now].r].lazy^=1;
	tr[now].lazy=0;
}
void fl_siz(int now, int siz, int& x, int& y) {
	if(!now) {
		x=y=0;
		return ;
	}
	down(now);
	if(tr[tr[now].l].siz+1 <= siz) {
		x=now;
		fl_siz(tr[now].r, siz-tr[tr[now].l].siz-1, tr[now].r, y);
	}
	else {
		y=now;
		fl_siz(tr[now].l, siz, x, tr[now].l);
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
void change() {
	int x, y;
	fl_siz(rt, r, x, y);
	tr[x].lazy^=1;
	rt=merge(x, y);
}
void dfs(int now) {
	down(now); 
	if(tr[now].l != 0)
		dfs(tr[now].l);
	putchar(tr[now].key);
	if(tr[now].r != 0)
		dfs(tr[now].r);
}

signed main() {
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	read(n), read(m);
	scanf("%s", s+1);
	for(int i = 1; i <= n; ++i)
		rt=merge(rt, blt(s[i]));
	for(int i = 1; i <= m; ++i) 
		read(r), change();
	dfs(rt);putchar('\n');
	return 0;
}
