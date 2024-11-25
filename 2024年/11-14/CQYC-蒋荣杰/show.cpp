#include <bits/stdc++.h>
#define mod 325609
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, a[N], rr, vvv[N][2];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
struct tree {
	int tr[N<<2], trr[N<<1][2], mn[N<<1][2], lzy[N<<1][2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=trr[k][0]=trr[k][1]=0;
		mn[k][0]=mn[k][1]=0, lzy[k][0]=lzy[k][1]=0;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void chng(int k, int now, int w) {
		mn[k][now]+=w;
		lzy[k][now]+=w;
	}
	void down(int k, int now) {
		if(lzy[k][now] == 0) return ;
		chng(ls, now, lzy[k][now]);
		chng(rs, now, lzy[k][now]);
		lzy[k][now]=0;
	}
	void upup(int k) {
		tr[k]=upd(tr[ls]+tr[rs]);
		mn[k][0]=min(mn[ls][0], mn[rs][0]);
		trr[k][0]=upd((mn[ls][0] == mn[k][0] ? trr[ls][0] : 0)+(mn[rs][0] == mn[k][0] ? trr[rs][0] : 0));
		mn[k][1]=min(mn[ls][1], mn[rs][1]);
		trr[k][1]=upd((mn[ls][1] == mn[k][1] ? trr[ls][1] : 0)+(mn[rs][1] == mn[k][1] ? trr[rs][1] : 0));
	}
	void updt(int k, int l, int r, int to, int w) {
		if(l == r) {
			tr[k]=w;
			trr[k][0]=tr[k];
			trr[k][1]=tr[k];
			return ;
		}
		down(k, 0), down(k, 1);
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, w);
		else
			updt(rs, mid+1, r, to, w);
		upup(k);
	}
	void updtt(int k, int l, int r, int lq, int rq, int now, int w) {
		if(lq <= l && r <= rq) {
			chng(k, now, w);
			return ;
		}
		down(k, 0), down(k, 1);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updtt(ls, l, mid, lq, rq, now, w);
		if(mid+1 <= rq)
			updtt(rs, mid+1, r, lq, rq, now, w);
		upup(k);
	}
	int ask(int k, int l, int r, int lq, int rq, int now) {
		// debug(now, "!!!", l, r, mn[k][now], trr[k][now], "?\n");
		if(lq <= l && r <= rq)
			return (mn[k][now] == 0 ? trr[k][now] : 0);
		down(k, 0), down(k, 1);
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=ask(ls, l, mid, lq, rq, now);
		if(mid+1 <= rq)
			ret=upd(ret+ask(rs, mid+1, r, lq, rq, now));
		upup(k);
		return ret;
	}
	int askk(int k, int l, int r, int to) {
		if(l == r)
			return tr[k];
		down(k, 0), down(k, 1);
		int mid = ((l+r)>>1);
		if(to <= mid)
			return askk(ls, l, mid, to);
		else
			return askk(rs, mid+1, r, to);
	}
}A;
struct qwq {
	int op, vis[N][2]/*每个数字最近两次出现的位置*/, mx;
	void init(int x) {
		op=x, mx=0;
		for(int i = 1; i <= n; ++i)
			vis[i][0]=vis[i][1]=0;
	}
	void add(int x, int y) {
		if(vis[x][0] != 0)
			A.updtt(1, 0, n, vis[x][1], vis[x][0]-1, op, -1);
		vis[x][1]=vis[x][0];
		vis[x][0]=y;
		A.updtt(1, 0, n, vis[x][1], vis[x][0]-1, op, 1);
		mx=max(mx, vis[x][1]);
	}
}B[2];

signed main() {
	File("show");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	A.built(1, 0, n);
	A.updt(1, 0, n, 0, 1);
	B[0].init(0), B[1].init(1);
	rr=0;
	for(int i = 1; i <= n; ++i) {
		int now = i%2, sum = 0;
		B[now].add(a[i], i);
		vvv[a[i]][now]=i;
		if(vvv[a[i]][0] && vvv[a[i]][1])
			rr=min(vvv[a[i]][0], vvv[a[i]][1]);
		int qvq = max(B[now^1].mx, rr);
		sum=A.ask(1, 0, n, qvq, i-1, now);
		// debug(qvq, i-1, A.ask(1, 0, n, qvq, i-1, now), "???\n");
		qvq = max(B[now].mx, rr);
		sum=upd(A.ask(1, 0, n, qvq, i-1, now^1)+sum);
		// debug(qvq, i-1, A.ask(1, 0, n, qvq, i-1, now^1), "!???\n");
		A.updt(1, 0, n, i, sum);
	}
	write(A.askk(1, 0, n, n), '\n');
	// debug(clock(), '\n');
	return 0;
}