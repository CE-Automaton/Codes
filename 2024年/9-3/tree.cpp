#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, f, f2[N], rt1, rt2, a[N], dfn[N], to[N], siz[N], msiz[N], tp[N], cnt, dep[N], ans, sizz[N];
vector <int> t1[N], t2[N];
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
struct tree {
	int tr[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=lzy[k]=0;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void down(int k, int l, int r) {
		int mid = ((l+r)>>1);
		if(lzy[k] != 0) {
			tr[ls]=upd(tr[ls]+1LL*(mid-l+1)*lzy[k]%mod);
			lzy[ls]=upd(lzy[ls]+lzy[k]);
			tr[rs]=upd(tr[rs]+1LL*(r-mid)*lzy[k]%mod);
			lzy[rs]=upd(lzy[rs]+lzy[k]);
			lzy[k]=0;
		}
	}
	void updt(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			tr[k]=upd(tr[k]+1LL*w*(r-l+1)%mod);
			lzy[k]=upd(lzy[k]+w);
			return ;
		}
		down(k, l, r);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, w);
		tr[k]=upd(tr[ls]+tr[rs]);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k];
		down(k, l, r);
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=upd(ret+ask(ls, l, mid, lq, rq));
		if(mid+1 <= rq)
			ret=upd(ret+ask(rs, mid+1, r, lq, rq));
		return ret;
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
	siz[x]=1, dep[x]=dep[fa]+1;
	for(int y : t2[x])
		if(y != fa) {
			dfs(y, x);
			siz[x]+=siz[y];
			if(siz[y] > siz[msiz[x]])
				msiz[x]=y;
		}
}
void dfs2(int x, int fa, int tpp) {
	dfn[x]=++cnt, to[cnt]=x, tp[x]=tpp;
	// debug(x, fa, tpp, msiz[x], "???\n");
	if(msiz[x])
		dfs2(msiz[x], x, tpp);
	for(int y : t2[x])
		if(y != fa && y != msiz[x])
			dfs2(y, x, y);
}
void add(int x, int w) {
	while(x) {
		A.updt(1, 1, m, dfn[tp[x]], dfn[x], w);
		x=f2[tp[x]];
	}
}
int ask(int x, int ret = 0) {
	while(x) {
		ret=upd(ret+A.ask(1, 1, m, dfn[tp[x]], dfn[x]));
		x=f2[tp[x]];
	}
	return ret;
}
void dfsss(int x, int fa) {
	sizz[x]=1;
	for(int y : t1[x])
		if(y != fa) {
			dfsss(y, x);
			sizz[x]+=sizz[y];
		}
}
void dfss(int x, int fa) {
	if(fa) 
		add(a[fa], n-sizz[x]);
	// debug(x, fa, sizz[x], ask(a[x]), '\n');
	ans=upd(ans+1LL*ask(a[x])*sizz[x]%mod);
	// debug(ans, '\n');
	for(int y : t1[x])
		if(y != fa) 
			dfss(y, x);
	add(a[x], sizz[x]);
	if(fa) 
		add(a[fa], upd(sizz[x]-n+mod));
}

signed main() {
	// File("tree");
	read(n), read(m);
	for(int i = 1; i <= n; ++i) {
		read(f);
		if(!f) rt1=i;
		t1[f].push_back(i);
	}
	for(int i = 1; i <= m; ++i) {
		read(f2[i]);
		if(!f2[i]) rt2=i;
		t2[f2[i]].push_back(i);
	}
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	dfs(rt2, 0);
	dfs2(rt2, 0, rt2);
	A.built(1, 1, m);
	dfsss(rt1, 0);
	dfss(rt1, 0);
	write(ans, '\n');
	return 0;
}