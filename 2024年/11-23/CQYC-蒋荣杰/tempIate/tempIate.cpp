#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, m, opt, p, ll, rr, xx, cnt, vis[35], pri[15], gs[35][12], ww[12], ret[12];

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
struct tree {
	int tr[2][N<<2][12]/*亮着的/没亮的灯泡的gcd*/, lzy[N<<2][12], ppd[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		// ppd[k]=0;
		for(int i = 1; i <= 10; ++i)
			tr[0][k][i]=inf, tr[1][k][i]=lzy[k][i]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void upup(int k) {
		for(int i = 1; i <= 10; ++i)
			tr[0][k][i]=min(tr[0][ls][i], tr[0][rs][i]), 
			tr[1][k][i]=min(tr[1][ls][i], tr[1][rs][i]);
	}
	void down(int k) {
		// if(ppd[k]) {
		// 	for(int i = 1; i <= 10; ++i)
		// 		swap(tr[0][ls][i], tr[1][ls][i]), swap(tr[0][rs][i], tr[1][rs][i]), 
		// 		ppd[ls]^=1, ppd[rs]^=1;
		// 	ppd[k]=0;
		// }
		for(int i = 1; i <= 10; ++i) 
			if(lzy[k][i] != 0) {
				tr[1][ls][i]+=lzy[k][i], lzy[ls][i]+=lzy[k][i];
				tr[1][rs][i]+=lzy[k][i], lzy[rs][i]+=lzy[k][i];
				lzy[k][i]=0;
			}
	}
	void upd(int k, int l, int r, int to) {
		if(l == r) {
			for(int i = 1; i <= 10; ++i)
				swap(tr[0][k][i], tr[1][k][i]);
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(to <= mid)
			upd(ls, l, mid, to);
		else
			upd(rs, mid+1, r, to);
		upup(k);
	}
	// void updt(int k, int l, int r, int lq, int rq) {呃呃，怎么是单点改
	// 	if(lq <= l && r <= rq) {
	// 		for(int i = 1; i <= 10; ++i)
	// 			swap(tr[0][k][i], tr[1][k][i]);
	// 		ppd[k]^=1;
	// 		return ;
	// 	}
	// 	down(k);
	// 	int mid = ((l+r)>>1);
	// 	if(lq <= mid)
	// 		updt(ls, l, mid, lq, rq);
	// 	if(mid+1 <= rq)
	// 		updt(rs, mid+1, r, lq, rq);
	// 	upup(k);
	// }
	void updtt(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			for(int i = 1; i <= 10; ++i)
				tr[1][k][i]+=ww[i], lzy[k][i]+=ww[i];
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updtt(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			updtt(rs, mid+1, r, lq, rq);
		upup(k);
	}
	void ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			for(int i = 1; i <= 10; ++i)
				ret[i]=min(ret[i], min(tr[0][k][i], tr[1][k][i]));
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ask(rs, mid+1, r, lq, rq);
	}
	#undef rs
	#undef ls
}A;

signed main() {
	File("tempIate");
	for(int i = 2; i <= 30; ++i) {
		if(!vis[i])
			pri[++cnt]=i, gs[i][cnt]=1;
		for(int j = 1; j <= cnt && pri[j] <= 30/i; ++j) {
			for(int op = 1; op <= cnt; ++op)
				gs[i*pri[j]][op]=gs[i][op]+gs[pri[j]][op];
			vis[i*pri[j]]=1;
			if(i%pri[j] == 0) break;
		}
	}
	read(n), read(m);
	A.built(1, 1, n);
	for(int i = 1; i <= m; ++i) {
		read(opt);
		if(opt == 1) {
			read(p);
			A.upd(1, 1, n, p);
		}
		if(opt == 2) {
			read(ll), read(rr), read(xx);
			for(int i = 1; i <= 10; ++i)
				ww[i]=gs[xx][i];
			A.updtt(1, 1, n, ll, rr);
		}
		if(opt == 3) {
			read(ll), read(rr), read(xx);
			for(int i = 1; i <= 10; ++i)
				ret[i]=inf;
			A.ask(1, 1, n, ll, rr);
			int pd = 1;
			for(int i = 1; i <= 10; ++i)
				pd&=(gs[xx][i] <= ret[i]);
			if(pd) {
				putchar('Y'), putchar('E'), putchar('S'), putchar('\n');
				for(int i = 1; i <= 10; ++i)
					ww[i]=-gs[xx][i];
				A.updtt(1, 1, n, ll, rr);
			}
			else
				putchar('N'), putchar('O'), putchar('\n');
		}
	}
	// debug(clock(), '\n');
	return 0;
}