#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e5+5;
int n, m, typ, opt, xx, lst, pp[N], vis[N], wws[N]/*轻边儿子的贡献和*/, dfn[N], siz[N], msz[N], tt[N], up[N], top[N], cnt,
tr[N<<2], lzy[N<<2];
vector <int> to[N];
set<int> qwq;

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
#define ls (k<<1)
#define rs (ls|1)
void down(int k) {
	if(lzy[k]) {
		tr[ls]+=lzy[k], lzy[ls]+=lzy[k];
		tr[rs]+=lzy[k], lzy[rs]+=lzy[k];
		lzy[k]=0;
	}
}
void built(int k, int l, int r) {
	tr[k]=lzy[k]=0;
	if(l == r) 
		return ;
	int mid = ((l+r)>>1);
	built(ls, l, mid);
	built(rs, mid+1, r);
}
void updt(int k, int l, int r, int to) {
	if(l == r) {
		tr[k]=lzy[k]=0;
		return ;
	}
	down(k);
	int mid = ((l+r)>>1);
	if(to <= mid)
		updt(ls, l, mid, to);
	else
		updt(rs, mid+1, r, to);
	tr[k]=max(tr[ls], tr[rs]);
}
int updttt(int k, int l, int r, int to) {
	if(l == r) 
		return tr[k];
	down(k);
	int mid = ((l+r)>>1);
	if(to <= mid)
		return updttt(ls, l, mid, to);
	else
		return updttt(rs, mid+1, r, to);
}
void adddd(int k, int l, int r, int lq, int rq, int ww) {
	if(lq <= l && r <= rq) {
		tr[k]+=ww, lzy[k]+=ww;
		return ;
	}
	down(k);
	int mid = ((l+r)>>1);
	if(lq <= mid)
		adddd(ls, l, mid, lq, rq, ww);
	if(mid < rq)
		adddd(rs, mid+1, r, lq, rq, ww);
	tr[k]=max(tr[ls], tr[rs]);
}
#undef ls
#undef rs
int sol(int x) {
	vis[x]=1;
	int ret = 1;
	for(int y : to[x])
		if(!vis[y] && pp[y]) 
			ret+=sol(y);
	return ret;
}
void dfs(int x, int fa) {
	siz[x]=1, up[x]=fa;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y], msz[x]=(siz[y] > siz[msz[x]] ? y : msz[x]);
}
void ddfs(int x, int tp, int fa) {
	dfn[x]=++cnt;
	tt[cnt]=x, top[x]=tp;
	if(msz[x])
		ddfs(msz[x], tp, x);
	for(int y : to[x])
		if(y != fa && y != msz[x])
			ddfs(y, y, x);
}
int erf(int l, int r) {//找重链上的第一个未加入的点
	auto op = qwq.upper_bound(r);
	if(op != qwq.begin()) {
		--op;
		return (*op >= l ? *op : -1);
	}
	return -1;
}
void jumpjumpjump(int x, int w) {
	if(!pp[x]) return ;
	while(x) {
		int op = erf(dfn[top[x]], dfn[x]);
		if(op != -1) {
			// debug(x, w, op+1, dfn[x], "???\n");
			adddd(1, 1, n, op+1, dfn[x], w);
			return ;
		}
		// debug(x, w, dfn[top[x]], dfn[x], "???\n");
		adddd(1, 1, n, dfn[top[x]], dfn[x], w);
		wws[up[top[x]]]+=w;
		if(!pp[up[top[x]]]) 
			return ;
		x=up[top[x]];
	}
}
void add(int x) {
	if(pp[x]) return ;
	qwq.erase(dfn[x]);
	pp[x]=1;
	int now = wws[x]+1;
	if(msz[x] && pp[msz[x]])
		now+=updttt(1, 1, n, dfn[msz[x]]);
	jumpjumpjump(x, now);
}
void dlt(int x) {
	if(!pp[x]) return ;
	qwq.insert(dfn[x]);
	pp[x]=0;
	int now = updttt(1, 1, n, dfn[x]);
	updt(1, 1, n, dfn[x]);
	if(x == top[x])
		wws[up[x]]-=now;
	jumpjumpjump(up[x], -now);
}

signed main() {
	File("ctt");
	read(n), read(m), read(typ);
	for(int i = 1; i <= n; ++i)
		qwq.insert(i);
	for(int i = 2; i <= n; ++i)
		read(opt), read(xx), to[opt].push_back(xx), to[xx].push_back(opt);
	dfs(1, 0);
	ddfs(1, 1, 0);
	built(1, 1, n);
	for(int i = 1; i <= m; ++i) {
		read(opt), read(xx);
		xx^=lst;
		if(opt == 1)
			add(xx);
		else
			dlt(xx);
		// pp[xx]=(opt == 1 ? 1 : 0);
		// lst=0;
		// for(int j = 1; j <= n; ++j)
		// 	vis[j]=0;
		// for(int j = 1; j <= n; ++j)
		// 	if(!vis[j] && pp[j])
		// 		lst=max(lst, sol(j));
		lst=tr[1];
		write(lst, '\n');
		lst*=typ;
	}
	return 0;
}