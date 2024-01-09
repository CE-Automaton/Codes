#include <bits/stdc++.h>
#define inf 10000000000000007LL
#define int long long
using namespace std;
const int N = 1e5+5;
int n, m, q, tot, rt[N], a[N], too[N], cnt, fa[N<<1], op, jp[N<<1][20], dep[N<<1], ww[N<<1], siz[N<<1], ll[N<<1], lst;
vector <int> to[N<<1];
struct node {
	int l, r, s;
}nd[N*20], p[N*5], pro;
struct haha {
	int s, id;
}b[N];
struct tree {
	int built(int l, int r) {
		int now = ++tot; nd[now].s=0;
		if(l == r) return now;
		int mid = (l+r)/2;
		nd[now].l=built(l, mid), nd[now].r=built(mid+1, r);
		return now;
	}
	int ctrln(int z) {
		nd[++tot]=nd[z];
		return tot;
	}
	int add(int k, int x, int l, int r) {
		int now = ctrln(k);
		++nd[now].s;
		if(l == r)
			return now;
		int mid = (l+r)/2;
		if(x <= mid) nd[now].l=add(nd[k].l, x, l, mid);
		else nd[now].r=add(nd[k].r, x, mid+1, r);
		return now;
	}
	int ask(int k, int j, int x, int l, int r) {
		if(l == r) return b[l].s;
		int mid = (l+r)/2, hh = nd[nd[j].l].s-nd[nd[k].l].s;
		if(hh < x) return ask(nd[k].r, nd[j].r, x-hh, mid+1, r);
		else return ask(nd[k].l, nd[j].l, x, l, mid);
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
int comp(haha AA, haha BB) {
	return AA.s > BB.s;
}
int comp2(node AA, node BB) {
	return AA.s < BB.s;
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void dfs(int x) {
	if(ww[x] == 0)
		siz[x]=1, too[++cnt]=x, ll[x]=cnt;
	else
		ll[x]=inf;
	for(int i = 1; i <= 19; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1];
	for(int y : to[x])
		dep[y]=dep[x]+1, jp[y][0]=x, dfs(y), siz[x]+=siz[y], ll[x]=min(ll[x], ll[y]);
}

signed main() {
	read(n), read(m), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]), b[i]={a[i],i};
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i)
		a[b[i].id]=i;
	for(int i = 1; i <= m; ++i)
		read(p[i].l), read(p[i].r), read(p[i].s);
	sort(p+1, p+1+m, comp2);
	for(int i = 1; i <= n; ++i)
		fa[i]=i;
	op=n;
	for(int i = 1; i <= m; ++i) {
		int u = find(p[i].l), v = find(p[i].r);
		if(u == v) continue;
		ww[++op]=p[i].s;
		fa[op]=op;
		fa[u]=fa[v]=op;
		to[op].push_back(u);
		to[op].push_back(v);
	}
	for(int i = 1; i <= op; ++i)
		if(fa[i] == i) 
			dep[i]=1, dfs(i);
	ww[0]=inf;
	rt[0]=A.built(1, n);
	for(int i = 1; i <= n; ++i) 
		rt[i]=A.add(rt[i-1], a[too[i]], 1, n);
	for(int i = 1; i <= q; ++i) {
		read(pro.l), read(pro.r), read(pro.s);
		pro.l=(pro.l^lst)%n+1;
		pro.s=(pro.s^lst)%n+1;
		pro.r=(pro.r^lst);
		int tp = pro.l;
		for(int i = 19; i >= 0; --i)
			if(ww[jp[tp][i]] <= pro.r)
				tp=jp[tp][i];
		if(siz[tp] < pro.s) {
			lst=0;
			puts("-1");
			continue;
		}
		write(lst=A.ask(rt[ll[tp]-1], rt[ll[tp]+siz[tp]-1], pro.s, 1, n), '\n');
	}
	return 0;
}
