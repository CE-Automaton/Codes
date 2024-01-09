#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, q, f[N], rt[N], dfn[N], siz[N], cnt, dep[N], top[N], fa[N], haha[N];
vector <int> to[N];
struct edgeorpue {
	int u, v, w;
}b[N], pro;
struct node {
	int ls, rs, tr, pdl, pdr, lnl, lnr, inf;
};
struct tree {
	int gs;
	node tr[N*25];
	void upup(node& ret, node ls, node rs) {
		int pd = 0;
		ret.inf=(ls.inf&rs.inf);
		ret.pdl=ls.pdl, ret.pdr=rs.pdr;
		ret.lnl=ls.lnl, ret.lnr=rs.lnr;
		if(ret.inf) ret.lnl=ret.lnr=ls.lnl+rs.lnl, ret.tr=f[ret.lnl], pd=1;
		else {
			if(ls.inf && rs.pdl) ret.lnl=ls.lnl+rs.lnl, ret.tr=rs.tr-f[rs.lnl]+f[rs.lnl+ls.lnl], pd=1;
			else ret.lnl=ls.lnl;
			if(ls.pdr && rs.inf) ret.lnr=ls.lnr+rs.lnr, ret.tr=ls.tr-f[ls.lnr]+f[rs.lnr+ls.lnr], pd=1;
			else ret.lnr=rs.lnr; 
		}
		if(!pd) {
			ret.tr=ls.tr+rs.tr;
			if(ls.pdr && rs.pdl) ret.tr+=f[ls.lnr+rs.lnl]-f[ls.lnr]-f[rs.lnl];
		}
	}
	void updt(int& k, int l, int r, int to) {
		tr[++gs]=tr[k], k=gs;
		if(l == r) {
			tr[k].pdl=tr[k].pdr=tr[k].lnl=tr[k].lnr=tr[k].inf=1, tr[k].tr=f[1];
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) updt(tr[k].ls, l, mid, to);
		else updt(tr[k].rs, mid+1, r, to);
		upup(tr[k], tr[tr[k].ls], tr[tr[k].rs]);
	}
	node find(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) return tr[k];
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq) {
			node ret;
			upup(ret, find(tr[k].ls, l, mid, lq, rq), find(tr[k].rs, mid+1, r, lq, rq));
			return ret;
		}
		if(lq <= mid) return find(tr[k].ls, l, mid, lq, rq);
		if(mid+1 <= rq) return find(tr[k].rs, mid+1, r, lq, rq);
	}
}A;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
int comp(edgeorpue A, edgeorpue B) { return A.w < B.w; }
void dfs(int x, int faa) {
	dep[x]=dep[faa]+1, fa[x]=faa;
	siz[x]=1;
	for(auto y : to[x]) if(y != faa)
		dfs(y, x), siz[x]+=siz[y];
}
void dfs2(int x, int faa) {
	dfn[x]=++cnt;
	int mxson = 0;
	for(auto y : to[x]) 
		if(y != faa) if(siz[y] > siz[mxson])
			mxson=y;
	if(mxson == 0) return ;
	top[mxson]=top[x], dfs2(mxson, x);
	for(auto y : to[x]) if(y != faa && y != mxson) 
		top[y]=y, dfs2(y, x);
}
int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n), read(q);
	for(int i = 1; i <= n-1; ++i) read(f[i]);
	for(int i = 1; i <= n-1; ++i)
		read(b[i].u), read(b[i].v), read(b[i].w), 
		to[b[i].u].push_back(b[i].v), to[b[i].v].push_back(b[i].u);
	dfs(1, 1), top[1]=1, dfs2(1, 1);
	sort(b+1, b+n, comp);
	cnt = 0;
	for(int i = n-1; i >= 1; --i) {
		if(i == n-1 || b[i].w != b[i+1].w)
			haha[++cnt]=b[i].w, rt[cnt]=rt[cnt-1];
		A.updt(rt[cnt], 2, n, max(dfn[b[i].u], dfn[b[i].v]));
	}
	for(int i = 1; i <= q; ++i) {
		read(pro.u), read(pro.v), read(pro.w);
		int l = 1, r = cnt, mn = -1;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(haha[mid] >= pro.w) mn=mid, l=mid+1;
			else r=mid-1; 
		}
		if(mn == -1) {
			putchar('0'), putchar('\n');
			continue;
		}
		l=pro.u, r=pro.v;
		node ll, rr;
		int pdll, pdrr;
		pdll=pdrr=0;
		while(top[l] != top[r]) {
			if(dep[top[l]] < dep[top[r]]) {
				if(pdrr == 0) rr=A.find(rt[mn], 2, n, dfn[top[r]], dfn[r]), pdrr=1;
				else A.upup(rr, A.find(rt[mn], 2, n, dfn[top[r]], dfn[r]), rr);
				r=fa[top[r]];
			}
			else {
				if(pdll == 0) ll=A.find(rt[mn], 2, n, dfn[top[l]], dfn[l]), pdll=1;
				else A.upup(ll, A.find(rt[mn], 2, n, dfn[top[l]], dfn[l]), ll);
				l=fa[top[l]];
			}
		}
		if(l != r) 
			if(dfn[l] > dfn[r]) 
				if(pdll == 0) ll=A.find(rt[mn], 2, n, dfn[r]+1, dfn[l]), pdll=1;
				else A.upup(ll, A.find(rt[mn], 2, n, dfn[r]+1, dfn[l]), ll);
			else 
				if(pdrr == 0) rr=A.find(rt[mn], 2, n, dfn[l]+1, dfn[r]), pdrr=1;
				else A.upup(rr, A.find(rt[mn], 2, n, dfn[l]+1, dfn[r]), rr);
		if(!pdll && !pdrr) {
			putchar('0'), putchar('\n');
			continue;
		}
		if(pdll && pdrr) 
			swap(ll.lnl, ll.lnr), swap(ll.pdl, ll.pdr), A.upup(ll, ll, rr);
		else 
			if(pdrr) ll=rr;
		write(ll.tr), putchar('\n');
	}
	return 0;
}
