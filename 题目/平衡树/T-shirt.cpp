#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const int N = 2e5+5;
int n, m, q, gs, ans[N], rt;
uLL sd=1;
uLL rd() {
	return sd=sd*1145141ull*1145141ull;
}
struct node {
	int l, r, key, id, g, lazy, lazg;
	uLL pri;
}tr[N];
struct qwq {
	int c, q;
}T[N];

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
int blt(int key, int d) {
	++gs;
	tr[gs].key=key;
	tr[gs].id=d;
	tr[gs].l=tr[gs].r=tr[gs].g=tr[gs].lazy=tr[gs].lazg=0;
	tr[gs].pri=rd();
	return gs;
}
void down(int k) {
	if(tr[k].lazg == 0) return ;
	if(tr[k].l)
		tr[tr[k].l].key-=tr[k].lazy, tr[tr[k].l].g+=tr[k].lazg, tr[tr[k].l].lazg+=tr[k].lazg, tr[tr[k].l].lazy+=tr[k].lazy;
	if(tr[k].r)
		tr[tr[k].r].key-=tr[k].lazy, tr[tr[k].r].g+=tr[k].lazg, tr[tr[k].r].lazg+=tr[k].lazg, tr[tr[k].r].lazy+=tr[k].lazy;
	tr[k].lazg=0;
	tr[k].lazy=0;
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
}
int merge(int x, int y) {
	if(x == 0 || y == 0) return x+y;
	down(x);
	down(y);
	if(tr[x].pri < tr[y].pri) {
		tr[x].r=merge(tr[x].r, y);
		return x;
	}
	else {
		tr[y].l=merge(x, tr[y].l);
		return y;
	}
}
void insert(int key, int d) {
	int x, y;
	fl_key(rt, key-1, x, y);
	rt=merge(merge(x, blt(key, d)), y);
}
int comp(qwq A, qwq B) {
	if(A.q == B.q)
		return A.c < B.c;
	return A.q > B.q;
}
void dfs(int k) {
	down(k);
	if(tr[k].l)
		dfs(tr[k].l);
	if(tr[k].r)
		dfs(tr[k].r);
	tr[k].l=tr[k].r=0;
	tr[k].pri=rd();
	int x, y, key = tr[k].key;
	fl_key(rt, key-1, x, y);
	rt=merge(merge(x, k), y);
}
void dfs2(int k) {
	ans[tr[k].id]=tr[k].g;
	down(k);
	if(tr[k].l)
		dfs2(tr[k].l);
//	cout<<k<<": "<<tr[k].id<<" "<<tr[k].key<<"\n";
	if(tr[k].r)
		dfs2(tr[k].r);
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		read(T[i].c), read(T[i].q);
	read(m);
	for(int i = 1; i <= m; ++i)
		read(q), insert(q, i);
	sort(T+1, T+1+n, comp);
	for(int i = 1; i <= n; ++i) {
//		cout<<T[i].c<<" "<<T[i].q<<"\n";
		int x, y, z;
		fl_key(rt, T[i].c-1, x, y);
		fl_key(y, T[i].c*2-1, y, z);
		if(z)
			++tr[z].g, ++tr[z].lazg, tr[z].lazy+=T[i].c, tr[z].key-=T[i].c;
		rt=merge(x, z);
		if(y) {
			++tr[y].g, ++tr[y].lazg, tr[y].lazy+=T[i].c, tr[y].key-=T[i].c;
			dfs(y);
		}
	}
	dfs2(rt);
	for(int i = 1; i <= m; ++i)
		write(ans[i], ' ');
	return 0;
}
