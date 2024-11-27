#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, k, xx[N], yy[N], xxx[N], yyy[N], zhan[N][2], tot, vis[N];
vector <int> ad[N], dl[N];

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
struct zi {
	int tr[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=lzy[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void down(int k) {
		if(lzy[k] == 0) return ;
		tr[ls]+=lzy[k], lzy[ls]+=lzy[k];
		tr[rs]+=lzy[k], lzy[rs]+=lzy[k];
		lzy[k]=0;
	}
	void updt(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			tr[k]+=w, lzy[k]+=w;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, w);
		tr[k]=max(tr[ls], tr[rs]);
	}
	int ask(int k, int l, int r, int to) {
		if(!tr[k])
			return 0;
		if(l == r)
			return l;
		down(k);
		int mid = ((l+r)>>1), ret = 0;
		if(mid+1 <= to && tr[rs])
			ret=ask(rs, mid+1, r, to);
		if(!ret)
			ret=ask(ls, l, mid, to);
		return ret;
	}
}A;
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
struct tree {
	int tr[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=lzy[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void down(int k) {
		if(lzy[k] == 0) return ;
		tr[ls]=0, lzy[ls]=1;
		tr[rs]=0, lzy[rs]=1;
		lzy[k]=0;
	}
	void updt(int k, int l, int r, int to, int w) {
		if(l == r) {
			tr[k]=upd(tr[k]+w);
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, w);
		else
			updt(rs, mid+1, r, to, w);
		tr[k]=upd(tr[ls]+tr[rs]);
	}
	void dlt(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			tr[k]=0, lzy[k]=1;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			dlt(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			dlt(rs, mid+1, r, lq, rq);
		tr[k]=upd(tr[ls]+tr[rs]);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		down(k);
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret=upd(ret+ask(rs, mid+1, r, lq, rq));
		return ret;
	}
}B;

signed main() {
	File("douglas");
	read(n), m=n, read(k);
	for(int i = 1; i <= k; ++i)
		read(xx[i]), read(yy[i]), read(xxx[i]), read(yyy[i]),
		ad[xx[i]].push_back(i), dl[xxx[i]+1].push_back(i);
	A.built(1, 1, m);
	A.updt(1, 1, m, 2, m, 1);
	yy[k+1]=2, yyy[k+1]=m;//一开始只能在(1,1)
	dl[1].push_back(k+1);
	B.built(1, 1, m);
	B.updt(1, 1, m, 1, 1);
	for(int i = 1; i <= n; ++i) {
		for(int y : ad[i]) {
			if(yyy[y]+1 <= m && !vis[yyy[y]+1]) {
				// debug(y, A.ask(1, 1, m, yyy[y]+1), "???\n");
				int op = A.ask(1, 1, m, yyy[y]+1)+1;
				if(op <= yyy[y])
					++tot, zhan[tot][0]=yyy[y]+1, zhan[tot][1]=B.ask(1, 1, m, op, yyy[y]), vis[yyy[y]+1]=1;
			}
		}
		while(tot)
			B.updt(1, 1, m, zhan[tot][0], zhan[tot][1])/*, debug(zhan[tot][0], zhan[tot][1], "????\n")*/,
			vis[zhan[tot][0]]=0, --tot;
		for(int y : dl[i])
			A.updt(1, 1, m, yy[y], yyy[y], -1);
		for(int y : ad[i]) 
			A.updt(1, 1, m, yy[y], yyy[y], 1), B.dlt(1, 1, m, yy[y], yyy[y]);
	}
	int op = A.ask(1, 1, m, m)+1;
	write(B.ask(1, 1, m, op, m), '\n');
	return 0;
}