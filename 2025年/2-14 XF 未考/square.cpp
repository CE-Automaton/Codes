#include <bits/stdc++.h>
#define inf 2000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, x[N], y[N], c[N], cc[N], xx[N], yy[N], cnt, cntt, to[7][5];
LL ans;
vector <int> nb[N][5];
struct qwq {
	int w, d;
}b[N];
struct bit {
	int tr[N];
	void init() {
		for(int i = 1; i <= cntt; ++i)
			tr[i]=inf;
	}
	void add(int x, int w) {
		while(x <= cntt)
			tr[x]=min(tr[x], w), x+=(x&(-x));
	}
	int ask(int x, int ret = inf) {
		while(x)
			ret=min(ret, tr[x]), x-=(x&(-x));
		return ret;
	}
}aa0, aa1;

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
int comp(qwq A, qwq B) {
	return A.w < B.w;
}
struct node { LL ww, aaa, lzy1, lzy2; } tr[N<<2];
#define ls (k<<1)
#define rs (ls|1)
void built(int k, int l, int r) {
	tr[k]=node {inf, inf, inf, inf};
	if(l == r) return ;
	int mid = ((l+r)>>1);
	built(ls, l, mid);
	built(rs, mid+1, r);
}
void updtt(int k, LL lzy1, LL lzy2, LL aaa) {
	tr[k].aaa=min(tr[k].aaa, min(tr[k].ww+lzy2, aaa));
	tr[k].ww=min(tr[k].ww, lzy1);
	tr[k].lzy1=min(tr[k].lzy1, lzy1);
	tr[k].lzy2=min(tr[k].lzy2, lzy2);
}
void down(int k) {
	updtt(ls, tr[k].lzy1, tr[k].lzy2, tr[k].aaa);
	updtt(rs, tr[k].lzy1, tr[k].lzy2, tr[k].aaa);
	tr[k].lzy1=tr[k].lzy2=tr[k].aaa=inf;
}
void addd0(int k, int l, int r, int lq, int rq, LL w) {
	if(lq <= l && r <= rq) {
		updtt(k, w, inf, inf);
		return ;
	}
	down(k);
	int mid = ((l+r)>>1);
	if(lq <= mid)
		addd0(ls, l, mid, lq, rq, w);
	if(mid < rq)
		addd0(rs, mid+1, r, lq, rq, w);
}
void addd1(int k, int l, int r, int lq, int rq, LL w) {
	if(lq <= l && r <= rq) {
		updtt(k, inf, w, inf);
		return ;
	}
	down(k);
	int mid = ((l+r)>>1);
	if(lq <= mid)
		addd1(ls, l, mid, lq, rq, w);
	if(mid < rq)
		addd1(rs, mid+1, r, lq, rq, w);
}
LL askk(int k, int l, int r, int to) {
	if(l == r)
		return tr[k].aaa;
	down(k);
	int mid = ((l+r)>>1);
	if(to <= mid)
		return askk(ls, l, mid, to);
	else
		return askk(rs, mid+1, r, to);
}
void solve() {
	//离散化
	cnt=cntt=0;
	for(int i = 1; i <= n; ++i)
		b[i]=qwq {x[i], i};
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || b[i].w != b[i-1].w)
			xx[++cnt]=b[i].w;
		x[b[i].d]=cnt;
	}
	for(int i = 1; i <= n; ++i)
		b[i]=qwq {y[i], i};
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || b[i].w != b[i-1].w)
			yy[++cntt]=b[i].w;
		y[b[i].d]=cntt;
	}
	//求两个点在边界上的情况
	for(int i = 1; i <= n; ++i)
		nb[x[i]][c[i]].push_back(i);
	aa0.init(), aa1.init();
	for(int i = 1; i <= cnt; ++i) {
		for(int j = 0; j < nb[i][0].size(); ++j)
			aa0.add(y[nb[i][0][j]], -xx[i]-yy[y[nb[i][0][j]]]);
		for(int j = 0; j < nb[i][1].size(); ++j)
			aa1.add(y[nb[i][1][j]], aa0.ask(y[nb[i][1][j]]));
		for(int j = 0; j < nb[i][2].size(); ++j)
			ans=min(ans, (LL) xx[i]+yy[y[nb[i][2][j]]]+aa1.ask(y[nb[i][2][j]]));
	}
	//求三个点分别在左下角、上边沿、右边沿的情况
	built(1, 1, cntt);
	for(int i = 1; i <= cnt; ++i) {
		for(int j = 0; j < nb[i][0].size(); ++j)
			addd0(1, 1, cntt, y[nb[i][0][j]], cntt, -xx[i]-yy[y[nb[i][0][j]]]);
		for(int j = 0; j < nb[i][1].size(); ++j)
			addd1(1, 1, cntt, 1, y[nb[i][1][j]], yy[y[nb[i][1][j]]]);
		for(int j = 0; j < nb[i][2].size(); ++j)
			ans=min(ans, (LL) xx[i]+askk(1, 1, cntt, y[nb[i][2][j]]));
	}
	//清空还原
	for(int i = 1; i <= cnt; ++i)
		nb[i][0].clear(), nb[i][1].clear(), nb[i][2].clear();
	for(int i = 1; i <= n; ++i)
		x[i]=xx[x[i]], y[i]=yy[y[i]];
}

signed main() {
	// File("square");
	to[0][0]=0, to[0][1]=1, to[0][2]=2;
	to[1][0]=1, to[1][1]=2, to[1][2]=0;
	to[2][0]=1, to[2][1]=0, to[2][2]=2;
	to[3][0]=0, to[3][1]=2, to[3][2]=1;
	to[4][0]=2, to[4][1]=1, to[4][2]=0;
	to[5][0]=2, to[5][1]=0, to[5][2]=1;
	read(n);
	for(int i = 1; i <= n; ++i)
		read(x[i]), read(y[i]), read(c[i]), cc[i]=c[i];
	ans=inf;
	for(int i = 0; i < 6; ++i) {
		for(int j = 1; j <= n; ++j)
			c[j]=to[i][cc[j]];
		solve();
		for(int j = 1; j <= n; ++j)
			x[j]=-x[j];
		solve();
		for(int j = 1; j <= n; ++j)
			y[j]=-y[j];
		solve();
		for(int j = 1; j <= n; ++j)
			x[j]=-x[j];
		solve();
		for(int j = 1; j <= n; ++j)
			y[j]=-y[j];
	}
	// debug("???\n");
	write((ans<<1), '\n');
	return 0;
}
