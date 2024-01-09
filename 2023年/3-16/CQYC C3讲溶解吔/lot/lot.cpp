#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
int n, a[100005], u, v, siz[100005], mx, mxsz[100005], vis[100005], rt, sum,
ans[100005], cnt, tot, zhan[100005], ppp[100005], rtt[100005], w[100005];
struct qwq {
	int w, id;
}b[100005];
vector <int> to[100005];
uLL sd=1;
uLL rd() {
	return sd=sd*1145141ull*1145141ull;
}

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
void get_siz(int x, int fa) {
	siz[x]=1;
	for(auto i : to[x])
		if(i != fa && !vis[i])
			get_siz(i, x), siz[x]+=siz[i];
}
void get_rt(int x, int fa) {
	siz[x]=mxsz[x]=1;
	for(auto i : to[x])
		if(i != fa && !vis[i])
			get_rt(i, x), siz[x]+=siz[i], mxsz[x]=max(mxsz[x], siz[i]);
	mxsz[x]=max(mxsz[x], sum-siz[x]);
	rt=(mxsz[x] < mxsz[rt] ? x : rt);
}
struct tree {
	int gs, rtt;
	struct node {
		int l, r, key, key2, mx;
		uLL pri;
	}tr[400005];
	int blt(int key, int pp) {
		++gs;
		tr[gs].key=key;
		tr[gs].key2=tr[gs].mx=pp;
		tr[gs].l=tr[gs].r=0;
		tr[gs].pri=rd();
		return gs;
	}
	void upup(int now) {
		tr[now].mx=max(max(tr[tr[now].l].mx, tr[tr[now].r].mx), tr[now].key2);
	}
	void fl_key(int now, int key, int& x, int& y) {
		if(!now) {
			x=y=0;
			return ;
		}
		if(tr[now].key <= key) {
			x=now;
			fl_key(tr[now].r, key, tr[now].r, y);
		}
		else {
			y=now;
			fl_key(tr[now].l, key, x, tr[now].l);
		}
		upup(now);
	}
	int merge(int x, int y) {
		if(x == 0 || y == 0) return x+y;
		if(tr[x].pri < tr[y].pri) {
			tr[x].r=merge(tr[x].r, y);
			upup(x);
			return x;
		}
		else {
			tr[y].l=merge(x, tr[y].l);
			upup(y);
			return y;
		}
	}
	int find(int key) {
		int x, y, ret=0;
		fl_key(rtt, key, x, y);
		ret=tr[y].mx;
		rtt=merge(x, y);
		return ret;
	}
	void insert(int key, int pp) {
		int x, y;
		fl_key(rtt, key, x, y);
		rtt=merge(merge(x, blt(key, pp)), y);
	}
}A;
struct zhuxi_tree {
	int gs;
	struct node {
		int ls, rs, mx;
	}tr[2000005];
	void updt(int& k, int l, int r, int to, int w) {
		++gs;
		tr[gs]=tr[k];
		k=gs;
		if(l == r) {
			tr[k].mx=w;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) updt(tr[k].ls, l, mid, to, w);
		else updt(tr[k].rs, mid+1, r, to, w);
		tr[k].mx=max(tr[tr[k].ls].mx, tr[tr[k].rs].mx);
	}
	int find(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k].mx;
		int ret = 0, mid = ((l+r)>>1);
		if(lq <= mid) ret=max(ret, find(tr[k].ls, l, mid, lq, rq));
		if(mid+1 <= rq) ret=max(ret, find(tr[k].rs, mid+1, r, lq, rq));
		return ret;
	}
}B;
void solve(int x, int fa) {
	for(auto j : to[x]) {
		if(j == fa || vis[j]) continue;
		solve(j, x);
	}
	zhan[++tot]=x;
	ppp[x] = A.find(a[x])+1;
	A.insert(a[x], ppp[x]);
}
void get_son(int x, int fa) {
	zhan[++tot]=x;
	rtt[x]=rtt[fa];
	int pp=max(A.find(a[x]), B.find(rtt[x], 1, cnt, a[x]+1, cnt))+1;
	ans[x]=max(ans[x], pp);
	B.updt(rtt[x], 1, cnt, a[x], pp);
	for(auto j : to[x]) {
		if(j == fa || vis[j]) continue;
		get_son(j, x);
	}
	rtt[x]=0;
}
void dfs(int x) {
	get_siz(x, x);//!!!!!!!!
	vis[x]=1;
	ans[x]=max(ans[x], 1);
	for(auto j : to[x]) {
		if(vis[j]) continue;
		tot=0;
		A.gs=A.rtt=0;
		A.tr[0].key2=A.tr[0].key=A.tr[0].l=A.tr[0].mx=A.tr[0].r=A.tr[0].pri=0;
		solve(j, x);
		for(int i = 1; i <= tot; ++i)
			if(a[x] < a[zhan[i]])
				ans[x]=max(ans[x], ppp[zhan[i]]+1);
	}

	A.gs=A.rtt=B.gs=0;
	rtt[x]=0;
	A.tr[0].key2=A.tr[0].key=A.tr[0].l=A.tr[0].mx=A.tr[0].r=A.tr[0].pri=0;
	B.tr[0].ls=B.tr[0].rs=B.tr[0].mx=0;
	ppp[x]=1;
	A.insert(a[x], ppp[x]);
	for(auto j : to[x]) {
		if(vis[j]) continue;
		tot=0;
		get_son(j, x);
		for(int o = 1; o <= tot; ++o) {
			if(a[x] < a[zhan[o]])
				ppp[x]=max(ppp[x], ppp[zhan[o]]+1);
			A.insert(a[zhan[o]], ppp[zhan[o]]);
		}
		A.insert(a[x], ppp[x]);
	}

	A.gs=A.rtt=B.gs=0;
	rtt[x]=0;
	A.tr[0].key2=A.tr[0].key=A.tr[0].l=A.tr[0].mx=A.tr[0].r=A.tr[0].pri=0;
	B.tr[0].ls=B.tr[0].rs=B.tr[0].mx=0;
	ppp[x]=1;
	A.insert(a[x], ppp[x]);
	for(int i = to[x].size()-1; i >= 0; --i) {
		int j = to[x][i];
		if(vis[j]) continue;
		tot=0;
		get_son(j, x);
		for(int o = 1; o <= tot; ++o) {
			if(a[x] < a[zhan[o]])
				ppp[x]=max(ppp[x], ppp[zhan[o]]+1);
			A.insert(a[zhan[o]], ppp[zhan[o]]);
		}
		A.insert(a[x], ppp[x]);
	}

	A.gs=A.rtt=B.gs=0;
	rtt[x]=0;
	A.tr[0].key2=A.tr[0].key=A.tr[0].l=A.tr[0].mx=A.tr[0].r=A.tr[0].pri=0;
	B.tr[0].ls=B.tr[0].rs=B.tr[0].mx=0;

	for(auto j : to[x]) {
		if(vis[j]) continue;
		rt=0, sum=siz[j];
		get_rt(j, j);
		dfs(rt);
	}
}
int comp(qwq A, qwq B) {
	return A.w < B.w;
}
void dfs2(int x, int fa) {
	w[x]=1;
	zhan[++tot]=x;
	for(auto j : to[x]) {
		if(j == fa) continue;
		int p = tot;
		dfs2(j, x);
		for(int o = p+1; o <= tot; ++o)
			if(a[x] < a[zhan[o]])
				w[x]=max(w[x], w[zhan[o]]+1);
	}
	ans[x]=max(ans[x], w[x]);
}

int main() {
	freopen("lot.in", "r", stdin);
	freopen("lot.out", "w", stdout);
    read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), b[i]=qwq{a[i], i};
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || b[i].w != b[i-1].w)
			++cnt;
		a[b[i].id]=cnt;
	}
	for(int i = 2; i <= n; ++i) 
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	if(n <= 50000) {
		for(int i = 1; i <= n; ++i)
			dfs2(i, i);
		for(int i = 1; i <= n; ++i)
			write(ans[i]), putchar('\n');
		return 0;
	}
	rt=0, mxsz[0]=1000000;
	sum=n;
	get_rt(1, 1);
	dfs(rt);
	for(int i = 1; i <= n; ++i)
		write(ans[i]), putchar('\n');
	return 0;
}