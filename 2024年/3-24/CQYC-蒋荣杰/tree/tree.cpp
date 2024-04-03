#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, q, uu, vv, tp[N], u[N], v[N], c[N], d[N], ww[N], siz[N], dfn[N], tt[N], up[N],
dep[N], cnt, mxs[N], top[N], zhan[N], tot, vis[N];
vector <int> to[N];
int upd(int x) { return (x >= mod ? x-mod : x); }
struct tree {
	int tr[N], lzyc[N<<2], lzyd[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		lzyd[k]=0; lzyc[k]=1;
		if(l == r) {
			tr[l]=ww[tt[l]];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void sol(int k, int l, int r, int cc, int dd) {
		if(l == r)
			tr[l]=upd(1LL*tr[l]*cc%mod+dd);
		else
			lzyc[k]=1LL*lzyc[k]*cc%mod, lzyd[k]=upd(1LL*lzyd[k]*cc%mod+dd);
	}
	void down(int k, int l, int r) {
		int mid = ((l+r)>>1);
		if(lzyc[k] != 1 || lzyd[k] != 0)
			sol(ls, l, mid, lzyc[k], lzyd[k]), sol(rs, mid+1, r, lzyc[k], lzyd[k]);
		lzyc[k]=1, lzyd[k]=0;
	}
	void updt(int k, int l, int r, int lq, int rq, int cc, int dd) {
		if(lq <= l && r <= rq) {
			sol(k, l, r, cc, dd);
			return ;
		}
		down(k, l, r);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, cc, dd);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, cc, dd);
	}
	void ddd(int k, int l, int r, int to) {
		if(l == r) return ;
		down(k, l, r);
		int mid = ((l+r)>>1);
		if(to <= mid) ddd(ls, l, mid, to);
		else ddd(rs, mid+1, r, to);
	}
}A;

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
void dfs(int x, int fa) {
	siz[x]=1, mxs[x]=0, up[x]=fa, dep[x]=dep[fa]+1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y], mxs[x]=(siz[mxs[x]] > siz[y] ? mxs[x] : y);
}
void dfs2(int x, int fa, int tpp) {
	dfn[x]=++cnt, top[x]=tpp, tt[cnt]=x;
	if(mxs[x]) dfs2(mxs[x], x, tpp);
	for(int y : to[x])
		if(y != fa && y != mxs[x])
			dfs2(y, x, y);
}
void dfss(int x, int fa, int k, int cc, int dd) {
	ww[x]=upd(1LL*ww[x]*cc%mod+dd);
	if(k)
		for(int y : to[x])
			if(y != fa)
				dfss(y, x, k-1, cc, dd);
}

signed main() {
	File("tree");
	read(n), read(q);
	for(int i = 2; i <= n; ++i)
		read(uu), read(vv), to[uu].push_back(vv), to[vv].push_back(uu);
	for(int i = 1; i <= n; ++i)
		read(ww[i]);
	int pd = 0;
	for(int i = 1 ; i <= q; ++i) {
		read(tp[i]), read(u[i]);
		if(tp[i] == 2)
			read(v[i]), read(c[i]), read(d[i]), pd|=1;
		if(tp[i] == 3)
			read(c[i]), read(d[i]);
		if(tp[i] == 4)
			read(v[i]), read(c[i]), read(d[i]);
	}
	if(!pd) {
		// debug("!!!\n");
		dfs(1, 0);
		dfs2(1, 0, 1);
		A.built(1, 1, n);
		for(int i = 1; i <= q; ++i) {
			if(tp[i] == 1)
				A.ddd(1, 1, n, dfn[u[i]]), write(A.tr[dfn[u[i]]], '\n');
			if(tp[i] == 3) 
				A.updt(1, 1, n, dfn[u[i]], dfn[u[i]]+siz[u[i]]-1, c[i], d[i]);
			if(tp[i] == 4) {
				int x = u[i], y = v[i];
				while(top[x] != top[y]) {
					if(dep[top[x]] < dep[top[y]]) swap(x, y);
					A.updt(1, 1, n, dfn[top[x]], dfn[x], c[i], d[i]);
					x=up[top[x]];
				}
				if(dfn[x] > dfn[y]) swap(x, y);
				A.updt(1, 1, n, dfn[x], dfn[y], c[i], d[i]);
			}
		}
		return 0;
	}
	else {
		dfs(1, 0);
		for(int i = 1; i <= q; ++i) {
			if(tp[i] == 1)
				write(ww[u[i]], '\n');
			if(tp[i] == 2) 
				dfss(u[i], 0, v[i], c[i], d[i]);
			if(tp[i] == 3) 
				dfss(u[i], up[u[i]], n, c[i], d[i]);
			if(tp[i] == 4) {
				int now = u[i];
				while(now)
					++vis[now], now=up[now];
				now=v[i];
				while(now)
					++vis[now], now=up[now];
				now=u[i];
				while(now) {
					ww[now]=upd(1LL*ww[now]*c[i]%mod+d[i]);
					if(vis[now] == 2) break;
					now=up[now];
				}
				now=v[i];
				while(now) {
					if(vis[now] == 2) break;
					ww[now]=upd(1LL*ww[now]*c[i]%mod+d[i]);
					now=up[now];
				}
				while(now)
					--vis[now], now=up[now];
				now=v[i];
				while(now)
					--vis[now], now=up[now];
				now=u[i];
			}
		}
		return 0;
	}
	return 0;
}