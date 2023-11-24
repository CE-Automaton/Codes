#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
const int N = 2e5+5;
int n, u, v, c[N], tv, m, cnt, dwn[N], dfn[N], dep[N], up[N], siz[N], mxs[N], tt[N], top[N], col[N], sum, ans;
struct qwq {
	int t, d;
};
vector <qwq> to[N];
vector <int> gs[N];
map <pii, int> as;
unordered_map <int, int> vis[N];
struct tree {
	qwq tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	qwq upup(qwq l, qwq r) {
		qwq ret = qwq{0, 0};
		ret.t=((l.t&r.t)&(l.d == r.d));
		ret.d=l.d;
		return ret;
	}
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=qwq {1, c[col[tt[l]]]};
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=upup(tr[ls], tr[rs]);
	}
	void updt(int k, int l, int r, int oo) {
		if(l == r) {
			tr[k]=qwq {1, c[col[tt[l]]]};
			return ;
		}
		int mid = ((l+r)>>1);
		if(oo <= mid)
			updt(ls, l, mid, oo);
		else
			updt(rs, mid+1, r, oo);
		tr[k]=upup(tr[ls], tr[rs]);
	}
	qwq ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq)
			return upup(ask(ls, l, mid, lq, rq), ask(rs, mid+1, r, lq, rq));
		if(lq <= mid)
			return ask(ls, l, mid, lq, rq);
		else
			return ask(rs, mid+1, r, lq, rq);
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
	dep[x]=dep[fa]+1;
	up[x]=fa;
	siz[x]=1;
	for(qwq y : to[x])
		if(y.t != fa) {
			if(dep[y.t] != 0) {
				u = y.t, v = x;
				tv=y.d;
				continue;
			}
			dfs(y.t, x);
			dwn[y.d]=y.t;
			col[y.t]=y.d;//边对应到点上 
			siz[x]+=siz[y.t];
			if(siz[y.t] > siz[mxs[x]])
				mxs[x]=y.t;
		}
}
void dfs2(int x, int tp, int fa) {
	dfn[x]=++cnt;
	tt[cnt]=x;
	top[x]=tp;
	if(mxs[x])
		dfs2(mxs[x], tp, x);
	for(qwq y : to[x])
		if(y.t != fa && y.t != mxs[x] && y.d != tv)
			dfs2(y.t, y.t , x);
}
int add() {
	int ret = 1;
	if(vis[u].find(c[tv]) != vis[u].end() && gs[u][vis[u][c[tv]]] != 0)
		--ret;
	if(vis[v].find(c[tv]) != vis[v].end() && gs[v][vis[v][c[tv]]] != 0)
		--ret;
	if(ret == -1) {
		int x = u, y = v;
		qwq now = {1, c[tv]};
		while(top[x] != top[y]) {
			if(dep[top[x]] < dep[top[y]]) swap(x, y);
			now=A.upup(now, A.ask(1, 2, n, dfn[top[x]], dfn[x]));
			x=up[top[x]];
		}
		if(x != y) {
			if(dfn[x] > dfn[y]) swap(x, y);
			now=A.upup(now, A.ask(1, 2, n, dfn[x]+1, dfn[y]));
		}
		if(now.t)
			++ret;
	}
	return ret;
}

signed main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(u), read(v), read(c[i]), as[pii{u, v}]=i, as[pii{v, u}]=i, 
		to[u].push_back(qwq {v, i}), to[v].push_back(qwq {u, i});
	dfs(1, 0);
	dfs2(1, 1, 0);
	for(int i = 1; i <= n; ++i)
		for(qwq y : to[i]) 
			if(y.d != tv) {
				if(vis[i].find(c[y.d]) == vis[i].end())
					gs[i].push_back(1), vis[i][c[y.d]]=(int) gs[i].size()-1, ++sum;
				else
					++gs[i][vis[i][c[y.d]]];
				++ans;
			}
	A.built(1, 2, n);
	for(int i = 1, x = 0, y = 0, cc = 0; i <= m; ++i) {
		read(x), read(y), read(cc);
		int cg = as[pii{x, y}];
		if(cg != tv) {
			--gs[x][vis[x][c[cg]]];
			if(gs[x][vis[x][c[cg]]] == 0)
				--sum;
			if(vis[x].find(cc) == vis[x].end())
				gs[x].push_back(1), vis[x][cc]=(int) gs[x].size()-1, ++sum;
			else {
				if(gs[x][vis[x][cc]] == 0)
					++sum;
				++gs[x][vis[x][cc]];
			}
				
			--gs[y][vis[y][c[cg]]];
			if(gs[y][vis[y][c[cg]]] == 0)
				--sum;
			if(vis[y].find(cc) == vis[y].end())
				gs[y].push_back(1), vis[y][cc]=(int) gs[y].size()-1, ++sum;
			else {
				if(gs[y][vis[y][cc]] == 0)
					++sum;
				++gs[y][vis[y][cc]];
			}
			
			c[cg]=cc;
			A.updt(1, 2, n, dfn[dwn[cg]]);
		}
		else 
			c[tv]=cc;
		write(n-1+sum-ans+add(), '\n');
	}
	return 0;
}
