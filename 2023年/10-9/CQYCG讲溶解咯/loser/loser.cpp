#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, q, u, v, opt, up[N], tp[N], dfn[N], siz[N], dep[N], w[N], tt[N], mxs[N], cnt;
vector <int> to[N];
struct node {
	int oky/*匹配上的*/, gs[2]/*0是能向左匹配的,1是能向右匹配的*/;
};
node upup_tr(node a, node b) {
	node ret;
	int qwq = min(a.gs[1], b.gs[0]);
	ret.oky=a.oky+b.oky+qwq;
	ret.gs[0]=a.gs[0]+b.gs[0]-qwq;
	ret.gs[1]=a.gs[1]+b.gs[1]-qwq;
	return ret;
}
node upup_rt(node a, node b) {
	node ret;
	int qwq = min(b.gs[1], a.gs[0]);
	ret.oky=a.oky+b.oky+qwq;
	ret.gs[0]=a.gs[0]+b.gs[0]-qwq;
	ret.gs[1]=a.gs[1]+b.gs[1]-qwq;
	return ret;
}
struct tree {
	int lzy[N<<2];
	node tr[N<<2][2/*0是()匹配,1是)(匹配*/], rt[N<<2][2/*0是()匹配,1是)(匹配*/]/*从右到左的*/;
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void upup(int k) {
		tr[k][0]=upup_tr(tr[ls][0], tr[rs][0]);
		tr[k][1]=upup_tr(tr[ls][1], tr[rs][1]);
		rt[k][0]=upup_rt(rt[ls][0], rt[rs][0]);
		rt[k][1]=upup_rt(rt[ls][1], rt[rs][1]);
	}
	void down(int k) {
		if(lzy[k]) {
			swap(tr[ls][0], tr[ls][1]);
			swap(rt[ls][0], rt[ls][1]);
			swap(tr[rs][0], tr[rs][1]);
			swap(rt[rs][0], rt[rs][1]);
			lzy[ls]^=1;
			lzy[rs]^=1;
			lzy[k]=0;
		}
	}
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k][0].gs[w[tt[l]]^1]=1;
			tr[k][1].gs[w[tt[l]]]=1;
			rt[k][0].gs[w[tt[l]]^1]=1;
			rt[k][1].gs[w[tt[l]]]=1;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			swap(tr[k][0], tr[k][1]);
			swap(rt[k][0], rt[k][1]);
			lzy[k]^=1;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid) 
			updt(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq);
		upup(k);
	}
	node ask_tr(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k][0];
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq)
			return upup_tr(ask_tr(ls, l, mid, lq, rq), ask_tr(rs, mid+1, r, lq, rq));
		if(lq <= mid)
			return ask_tr(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			return ask_tr(rs, mid+1, r, lq, rq);
	}
	node ask_rt(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return rt[k][0];
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq)
			return upup_rt(ask_rt(ls, l, mid, lq, rq), ask_rt(rs, mid+1, r, lq, rq));
		if(lq <= mid)
			return ask_rt(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			return ask_rt(rs, mid+1, r, lq, rq);
	}
}A;

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
	up[x]=fa, dep[x]=dep[fa]+1, siz[x]=1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y], mxs[x]=(siz[y] > siz[mxs[x]] ? y : mxs[x]);
}
void dfs2(int x, int t, int fa) {
	tp[x]=t, dfn[x]=++cnt, tt[cnt]=x;
	if(mxs[x]) dfs2(mxs[x], t, x);
	for(int y : to[x])
		if(y != fa && y != mxs[x])
			dfs2(y, y, x);
}

signed main() {
	freopen("loser.in", "r", stdin);
	freopen("loser.out", "w", stdout);
	read(n), read(q);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	dfs2(1, 1, 0);
	for(int i = 1; i <= n; ++i)
		read(w[i]);
	A.built(1, 1, n);
	for(int i = 1; i <= q; ++i) {
		read(opt), read(u), read(v);
		if(opt == 1) {
			while(tp[u] != tp[v]) {
				if(dep[tp[u]] < dep[tp[v]])
					swap(u, v);
				A.updt(1, 1, n, dfn[tp[u]], dfn[u]);
				u=up[tp[u]];
			}
			if(dfn[u] > dfn[v]) swap(u, v);
			A.updt(1, 1, n, dfn[u], dfn[v]);
		}
		else {
			node ll, rr, ans;
			ans=ll=rr=node{0, {0, 0}};
			while(tp[u] != tp[v]) {
				if(dep[tp[u]] > dep[tp[v]]) 
					ll=upup_rt(A.ask_rt(1, 1, n, dfn[tp[u]], dfn[u]), ll), u=up[tp[u]];
				else
					rr=upup_tr(A.ask_tr(1, 1, n, dfn[tp[v]], dfn[v]), rr), v=up[tp[v]];
			}
			if(dfn[u] <= dfn[v])
				rr=upup_tr(A.ask_tr(1, 1, n, dfn[u], dfn[v]), rr);
			else
				ll=upup_rt(A.ask_rt(1, 1, n, dfn[v], dfn[u]), ll);
			ans=upup_tr(ll, rr);
			write(ans.oky*2, '\n');
		}
	}
	return 0;
}
