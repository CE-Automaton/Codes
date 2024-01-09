#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, q, xx, yy, rt, gs;
long long ans;
vector<int> to[N];
struct node {
	int l, r, key, rnd, siz;
	long long sum;
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
	tr[gs].rnd=0;
	tr[gs].sum=0;
	return gs;
}
void upup(int now) {
	tr[now].siz=1+tr[tr[now].l].siz+tr[tr[now].r].siz;
	tr[now].sum=tr[tr[now].l].sum+tr[tr[now].r].sum+1LL*(tr[tr[now].l].siz+1)*(tr[tr[now].r].siz+1)*tr[now].rnd;
}
int built(int l, int r) {
	if(l > r) return 0;
	if(l == r) 
		return blt(l);
	int mid=((l+r)>>1), k = blt(mid);
	tr[k].l=built(l, mid-1), tr[k].r=built(mid+1, r);
	upup(k);
	return k;
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
	if(tr[x].rnd > tr[y].rnd) {
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
void chg(int key, int d) {
	int x, y, z;
	fl_key(rt, key-1, x, y);
	fl_key(y, key, z, y);
	tr[z].rnd=d;
//	tr[z].sum=d;
	upup(z);
	rt=merge(merge(x, z), y);
}

signed main() {
	read(n), read(m), read(q);
	for(int i = 1; i <= q; ++i) 
		read(xx), read(yy), to[xx].push_back(yy);
	rt=built(1, m);
	for(int i = 1; i <= n; ++i) {
		for(int j : to[i])
			chg(j, i);
		ans+=1LL*i*m*(m+1)/2-tr[rt].sum; 
	}
	write(1LL*n*(n+1)/2*m*(m+1)/2-ans, '\n');
	return 0;
}
