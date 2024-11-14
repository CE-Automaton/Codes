#include <bits/stdc++.h>
#define int long long
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, q, fa[N], a[N], b[N], as[N], bs[N], opt[N], xx[N], yy[N], dfn[N], tt[N], siz[N], cnt;
vector <int> to[N];

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
LL abbb(LL x) {
	return (x < 0 ? -x : x);
}
void dfs(int x) {
	as[x]=as[fa[x]]+a[x], bs[x]=bs[fa[x]]+b[x];
	dfn[x]=++cnt, tt[cnt]=x;
	siz[x]=1;
	for(int y : to[x])
		dfs(y), siz[x]+=siz[y];
}
void down(int x) {
	as[x]=as[fa[x]]+a[x];
	for(int y : to[x])
		down(y);
}
LL getans(int x) {
	LL ret = abbb(1LL*as[x]*bs[x]);
	for(int y : to[x])
		ret=max(ret, getans(y));
	return ret;
}
struct tree {
	LL tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=abbb(1LL*as[tt[l]]*bs[tt[r]]);
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=max(tr[ls], tr[rs]);
	}
	void updt(int k, int l, int r, int to) {
		if(l == r) {
			tr[k]=abbb(1LL*as[tt[l]]*bs[tt[r]]);
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to);
		else
			updt(rs, mid+1, r, to);
		tr[k]=max(tr[ls], tr[rs]);
	}
	LL ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq)
			return max(ask(ls, l, mid, lq, rq), ask(rs, mid+1, r, lq, rq));
		if(lq <= mid)
			return ask(ls, l, mid, lq, rq);
		else
			return ask(rs, mid+1, r, lq, rq);
	}
}A;
struct treee {
	LL tr[N<<2], lzy[N];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		lzy[k]=0;
		if(l == r) {
			tr[k]=as[tt[l]];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void down(int k) {
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
	}
	LL ask(int k, int l, int r, int to) {
		if(l == r) 
			return tr[k];
		down(k);
		int mid = ((l+r)>>1);
		if(to <= mid)
			return ask(ls, l, mid, to);
		else
			return ask(rs, mid+1, r, to);
	}
}B;

signed main() {
	File("tree");
	read(n), read(q);
	for(int i = 2; i <= n; ++i)
		read(fa[i]), to[fa[i]].push_back(i);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]);
	dfs(1);
	if(n <= 50000 && q <= 50000) {
		for(int i = 1; i <= q; ++i) {
			read(opt[i]), read(xx[i]);
			if(opt[i] == 1) {
				read(yy[i]);
				a[xx[i]]+=yy[i];
				down(xx[i]);
			}
			else
				write(getans(xx[i]), '\n');
		}
		return 0;
	}
	int pd = 1, ppd = 1, ddd = 1;
	for(int i = 1; i <= q; ++i) {
		read(opt[i]), read(xx[i]);
		if(opt[i] == 1)
			read(yy[i]), pd&=(siz[xx[i]] == 1), ddd&=(xx[i] == 1);
		else
			ppd&=(siz[xx[i]] == 1);
	}
	if(pd) {
		// debug("sub2!\n");
		A.built(1, 1, n);
		for(int i = 1; i <= q; ++i) {
			if(opt[i] == 1) 
				as[xx[i]]+=yy[i], A.updt(1, 1, n, dfn[xx[i]]);
			else
				write(A.ask(1, 1, n, dfn[xx[i]], dfn[xx[i]]+siz[xx[i]]-1), '\n');
		}
		return 0;
	}
	if(ppd) {
		// debug("sub4!\n");
		B.built(1, 1, n);
		for(int i = 1; i <= q; ++i) {
			if(opt[i] == 1) 
				B.updt(1, 1, n, dfn[xx[i]], dfn[xx[i]]+siz[xx[i]]-1, yy[i]);
			else
				write(abbb(1LL*B.ask(1, 1, n, dfn[xx[i]])*bs[xx[i]]), '\n');
		}
		return 0;
	}
	if(ddd) {
		// debug("sub3!\n");
		return 0;
	}
	return 0;
}