#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e5+5;
#define int LL
int n, m, u[N], v[N], ll[N], rr[N], w, cnt, ln, zhan[N], fa[N], siz[N], ds[N][2], tot, st[N<<1][25], dfs[N], op, in[N], hah;
LL dep[N], ww[N], ans[N<<2], out[N];
struct qwq {
	int t, d;
};
vector <qwq> to[N];
struct qqq {
	int t, d, p;
}aa[N];
struct aaa {
	int s, f, si, d[2];
	LL w;
}bb[N<<2];

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
int comp(qqq A, qqq B) {
	return A.t < B.t;
}
int ask(int x) {
	int ll = 1, rr = cnt, al = 0;
	while(ll <= rr) {
		int mid = ((ll+rr)>>1);
		if(zhan[mid] <= x)
			al=mid, ll=mid+1;
		else
			rr=mid-1;
	}
	return al;
}
void dfss(int x, int fa) {
	dfs[++op]=x;
	in[x]=op;
	for(qwq y : to[x])
		if(y.t != fa)
			dep[y.t]=dep[x]+y.d, dfss(y.t, x), dfs[++op]=x;
}
LL lca(int x, int y) {
	if(x > y) swap(x, y);
	int lg = log2(y-x+1);
	return dep[(dep[st[x][lg]] < dep[st[y-(1<<lg)+1][lg]] ? st[x][lg] : st[y-(1<<lg)+1][lg])];
}
LL dis(int x, int y) {
	return (x && y ? dep[x]+dep[y]-2LL*lca(in[x], in[y]) : 0);
}
struct tree {//线段树分治
	vector <int> tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	int find(int x) { return (fa[x] == x ? x : find(fa[x])); }
	void merge(int x, int y) {
		x=find(x), y=find(y);
		if(siz[x] < siz[y]) swap(x, y);
		bb[++tot]=aaa {x, fa[x], siz[x], {ds[x][0], ds[x][1]}, ww[x]};
		bb[++tot]=aaa {y, fa[y], siz[y], {ds[y][0], ds[y][1]}, ww[y]};
		fa[y]=x, siz[x]+=siz[y];
		int a = ds[x][0], b = ds[x][1], c = ds[y][0], d=ds[y][1];
		LL ab=ww[x], ac=dis(a, c), ad=dis(a, d), bc=dis(b, c), bd=dis(b, d), cd=ww[y], 
		mx=max({ab, ac, ad, bc, bd, cd});
		if(ab == mx)
			ds[x][0]=a, ds[x][1]=b;
		else if(ac == mx)
			ds[x][0]=a, ds[x][1]=c;
		else if(ad == mx)
			ds[x][0]=a, ds[x][1]=d;
		else if(bc == mx)
			ds[x][0]=b, ds[x][1]=c;
		else if(bd == mx)
			ds[x][0]=b, ds[x][1]=d;
		else if(cd == mx)
			ds[x][0]=c, ds[x][1]=d;
		ww[x]=mx;
		++hah;
		ans[hah]=max(ans[hah-1], ww[x]);
	}
	void dlt() {
		int x = bb[tot].s;
		fa[x]=bb[tot].f, siz[x]=bb[tot].si, ds[x][0]=bb[tot].d[0], ds[x][1]=bb[tot].d[1], ww[x]=bb[tot].w;
		--tot;
	}
	void updt(int k, int l, int r, int dd) {
		if(ll[dd] <= l && r <= rr[dd]) {
			tr[k].push_back(dd);
			return ;
		}
		int mid = ((l+r)>>1);
		if(ll[dd] <= mid)
			updt(ls, l, mid, dd);
		if(mid+1 <= rr[dd])
			updt(rs, mid+1, r, dd);
	}
	void ddd(int k) {
		for(int y : tr[k])
			dlt(), dlt(), --hah;
	}
	void dfs(int k, int l, int r) {
		for(int y : tr[k])
			merge(u[y], v[y]);
		if(l == r) {
			out[l]=ans[hah];
			ddd(k);
			return ;
		}
		int mid = ((l+r)>>1);
		dfs(ls, l, mid);
		dfs(rs, mid+1, r);
		ddd(k);
	}
}AA;

signed main() {
	File("afternoon");
	read(n), read(m);
	for(int i = 2; i <= n; ++i) 
		read(u[i]), read(v[i]), read(w), read(ll[i]), read(rr[i]), 
		to[u[i]].push_back(qwq {v[i], w}), to[v[i]].push_back(qwq {u[i], w}), 
		aa[++ln]=qqq {ll[i], i, 0}, aa[++ln]=qqq {rr[i], i, 1}, aa[++ln]=qqq {rr[i]+1, 0, 0};
	sort(aa+1, aa+ln+1, comp);
	for(int i = 1; i <= ln; ++i) {
		if(i == 1 || aa[i].t != aa[i-1].t)
			zhan[++cnt]=aa[i].t;
		if(aa[i].p)
			rr[aa[i].d]=cnt;
		else
			ll[aa[i].d]=cnt;
	}
	// zhan[cnt+1]=zhan[cnt]+1, ++cnt;
	for(int i = 2; i <= n; ++i)
		AA.updt(1, 1, cnt, i);
	dfss(1, 0);
	for(int i = 1; i <= op; ++i) 
		st[i][0]=dfs[i];
	for(int i = 1; i <= 18; ++i)
		for(int j = 1; j+(1<<i)-1 <= op; ++j)
			st[j][i]=(dep[st[j][i-1]] < dep[st[j+(1<<(i-1))][i-1]] ? st[j][i-1] : st[j+(1<<(i-1))][i-1]);
	for(int i = 1; i <= n; ++i)
		ww[i]=0, fa[i]=i, siz[i]=1, ds[i][0]=i, ds[i][1]=0;
	debug("!?\n");
	AA.dfs(1, 1, cnt);
	debug("!??\n");
	while(m--)
		read(w), write(out[ask(w)], '\n');
	return 0;
}