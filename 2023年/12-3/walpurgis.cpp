#include <bits/stdc++.h>
using namespace std;
const int N = 4e5;
int typ, n, m, ww, gsx, gsy, ans[N+5];
long long xx, yy;
struct qwq {
	long long y;
	int w;
};
struct trrx{
	int to[2];
	vector <qwq> pd[2];//1是修改, 0是查询 
}trrx[N*80+5];
struct trry {
	int to[2], w;
}trry[N*80+5];

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
void add(long long x, qwq ad, int ppd) {
	int now = 0;
	for(int i = 0; i <= 59 && (1LL<<(i+ppd/*修改操作的最高位不加进去,查询的时候只查0~最高位-1就行*/)) <= x; ++i) {
		int xs = ((x>>i)&1);
		if(!trrx[now].to[xs]) trrx[now].to[xs]=++gsx;
		now=trrx[now].to[xs];
	}
	trrx[now].pd[ppd].push_back(ad);
}
void addy(long long x, int w) {
	int now = 0;
	for(int i = 0; i <= 59 && (1LL<<(i+1)) <= x; ++i) {
		int xs = ((x>>i)&1);
		if(!trry[now].to[xs]) trry[now].to[xs]=++gsy;
		now=trry[now].to[xs];
	}
	trry[now].w+=w;
}
int ask(long long x, int ret = 0) {
	int now = 0;
	for(int i = 0; i <= 59 && (1LL<<i) <= x; ++i) {
		ret+=trry[now].w;
		int xs = ((x>>i)&1);
		if(!trry[now].to[xs]) break;
		now=trry[now].to[xs];
	}
	return ret;
}
void sol(int x) {
	for(qwq o : trrx[x].pd[0])
		ans[o.w]=ask(o.y);
	for(qwq o : trrx[x].pd[1])
		addy(o.y, o.w);
	for(int o = 0; o <= 1; ++o)
		if(trrx[x].to[o])
			sol(trrx[x].to[o]);
	for(qwq o : trrx[x].pd[1])
		addy(o.y, -o.w);
}

signed main() {
//	freopen("walpurgis.in", "r", stdin);
//	freopen("walpurgis.out", "w", stdout);
	read(typ);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(xx), read(yy), read(ww), add(xx, qwq {yy, ww}, 1);
	for(int i = 1; i <= m; ++i)
		read(xx), read(yy), add(xx, qwq {yy, i}, 0);
	sol(0);
	for(int i = 1; i <= m; ++i)
		write(ans[i], '\n');
	return 0;
}
