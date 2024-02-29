#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
#define int LL
int n, m, u, v, l[N], r[N], pd[N], w[N], tt[N], dis[N], pp[N], vis[N], rt, cnt, ln, zhan[N], dfn[N], sss[N], ans[N], op, aaa[N];
struct qwq {
	int t, d;
};
struct qqq {
	int t, d, p;
}aa[N];
vector <qwq> to[N], ad[N];
struct tree {
	int tr[N<<2], pdl[N<<2], pdr[N<<2], ll[N<<2], rr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=pdl[k]=pdr[k]=ll[k]=rr[k]=0;
		if(l == r)
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void upup(int k) {
		tr[k]=pdl[k]=pdr[k]=ll[k]=rr[k]=0;
		pdl[k]=pdl[ls];
		pdr[k]=pdr[ls];
		tr[k]=max(tr[k], max(tr[ls], max(tr[rs], (pdl[rs] && pdr[ls] ? ll[rs]+rr[ls] : 0))));
	}
	void updt(int k, int l, int r, int to, int ww) {
		if(l == r) {
			pdl[k]=pdr[k]=ww;
			if(ww)
				tr[k]=ll[k]=rr[k]=w[pp[aaa[l]]];
			else
				tr[k]=ll[k]=rr[k]=0;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, ww);
		else
			updt(rs, mid+1, r, to, ww);
		upup(k);
	}
}AA;

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
	vis[x]=1;
	rt=(sss[rt] < sss[x] ? x : rt);
	for(qwq y : to[x])
		if(y.t != fa && pd[y.d]) {
			sss[y.t]=sss[x]+w[y.d];
			dfs(y.t, x);
		}
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
void ddfs(int x, int fa) {
	dfn[x]=++op, aaa[op]=x;
	for(qwq y : to[x]) 
		if(y.t != fa) {
			tt[y.d]=y.t, pp[y.t]=y.d;
			ddfs(y.t, x);
		}
}

signed main() {
	File("afternoon");
	read(n), read(m);
	for(int i = 2; i <= n; ++i) {
		read(u), read(v), read(w[i]), read(l[i]), read(r[i]);
		++r[i];
		to[u].push_back(qwq {v, i}), to[v].push_back(qwq {u, i});
		aa[++ln]=qqq {l[i], i, 0};
		aa[++ln]=qqq {r[i], i, 1};
		++dis[u], ++dis[v];
	}
	sort(aa+1, aa+ln+1, comp);
	for(int i = 1; i <= ln; ++i) {
		if(i == 1 || aa[i].t != aa[i-1].t)
			zhan[++cnt]=aa[i].t;
		if(aa[i].p)
			r[aa[i].d]=cnt;
		else
			l[aa[i].d]=cnt;
	}
	++cnt;
	for(int i = 2; i <= n; ++i)
		ad[l[i]].push_back(qwq {i, 1}), ad[r[i]].push_back(qwq {i, 0});
	if(n <= 3000) {
		for(int i = 1; i <= cnt+1; ++i) {
			for(qwq it : ad[i])
				pd[it.t]=it.d;
			for(int j = 1; j <= n; ++j)
				vis[j]=0, sss[j]=0;
			for(int j = 1; j <= n; ++j)
				if(!vis[j])
					sss[j]=0, rt=j, dfs(j, 0), 
					sss[rt]=0, dfs(rt, 0), ans[i]=max(ans[i], sss[rt]);
		}
		while(m--)
			read(u), write(ans[ask(u)], '\n');
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		if(dis[i] == 1)
			rt=i;
	ddfs(rt, 0);
	for(int i = 1; i <= cnt+1; ++i) {
		for(qwq it : ad[i])
			AA.updt(1, 1, n, tt[it.t], it.d);
		ans[i]=AA.tr[1];
	}
	while(m--)
		read(u), write(ans[ask(u)], '\n');
	return 0;
}