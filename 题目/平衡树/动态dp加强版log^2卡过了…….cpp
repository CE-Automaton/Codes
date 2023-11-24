#include <bits/stdc++.h>
//#define int long long
#define inf 1000000007
#define max(x, y) (x > y ? x : y)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
using namespace std;
const int N = 1e6+5;
int n, m, f[N], u, v, dfn[N], cnt, dep[N], siz[N], ft[N], top[N], az[N], down[N],
per_g[N][2], per_f[N][2], lst, head[N], to[N<<1], nxt[N<<1], tot, rt[N];
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
struct ggg {
	int g[2][2];
	ggg operator * (const ggg& A) const {
		ggg ret;
		ret.g[0][0]=max(g[0][0]+A.g[0][0], g[0][1]+A.g[1][0]);
		ret.g[1][0]=max(g[1][0]+A.g[0][0], g[1][1]+A.g[1][0]);
		ret.g[0][1]=max(g[0][0]+A.g[0][1], g[0][1]+A.g[1][1]);
		ret.g[1][1]=max(g[1][0]+A.g[0][1], g[1][1]+A.g[1][1]);
		return ret;
	}
};
struct tree {
	int gs;
	ggg tr[N<<2];
	int ls[N<<2], rs[N<<2];
	void built(int& k, int l, int r) {
		++gs, k=gs;
		if(l == r) {
			tr[k].g[0][0]=tr[k].g[0][1]=per_g[l][0];
			tr[k].g[1][0]=per_g[l][1], tr[k].g[1][1]=-inf;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls[k], l, mid);
		built(rs[k], mid+1, r);
		tr[k]=(tr[ls[k]]*tr[rs[k]]);
	}
	void updtt(int k, int l, int r, int to, int w1, int w2) {
		if(l == r) {
			tr[k].g[0][0]+=w1;
			tr[k].g[0][1]+=w1;
			tr[k].g[1][0]+=w2;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updtt(ls[k], l, mid, to, w1, w2);
		else
			updtt(rs[k], mid+1, r, to, w1, w2);
		tr[k]=(tr[ls[k]]*tr[rs[k]]);
	}
	ggg ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k];
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq) {
			ggg a = ask(ls[k], l, mid, lq, rq), b = ask(rs[k], mid+1, r, lq, rq);
			return (a*b);
		}
		if(lq <= mid)
			return ask(ls[k], l, mid, lq, rq);
		if(mid+1 <= rq)
			return ask(rs[k], mid+1, r, lq, rq);
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
void edge(int x, int y) {
	nxt[++tot]=head[x];
	to[tot]=y;
	head[x]=tot;
}
void dfs1(int x, int fa) {
	dep[x]=dep[fa]+1, siz[x]=1, ft[x]=fa;
	for(int i = head[x]; i; i=nxt[i]) {
		int y = to[i]; 
		if(y != fa)
			dfs1(y, x), siz[x]+=y;
	}
}
void dfs2(int x, int fa) {
	down[top[x]]=x;
	dfn[x]=++cnt;
	per_g[cnt][0]=0;
	per_g[cnt][1]=f[x];
	int hson = 0;
	for(int i = head[x]; i; i=nxt[i]) {
		int y = to[i]; 
		if(y != fa)
			if(siz[y] > siz[hson])
				hson=y;
	}
	if(hson) {
		top[hson]=top[x];
		dfs2(hson, x);
	}
	for(int i = head[x]; i; i=nxt[i]) {
		int y = to[i]; 
		if(y != fa && y != hson)
			top[y]=y, dfs2(y, x),
			per_g[dfn[x]][0]+=max(per_f[dfn[y]][0], per_f[dfn[y]][1]), 
			per_g[dfn[x]][1]+=per_f[dfn[y]][0];
	}
	down[x]=down[top[x]];
	per_f[dfn[x]][0]=per_g[dfn[x]][0]+max(per_f[dfn[hson]][0], per_f[dfn[hson]][1]);
	per_f[dfn[x]][1]=per_g[dfn[x]][1]+per_f[dfn[hson]][0];
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(f[i]);
	for(int i = 1; i <= n-1; ++i) 
		read(u), read(v), edge(u, v), edge(v, u);
	dfs1(1, 0);
	top[1]=1;
	dfs2(1, 0);
	for(int i = 1; i <= n; ++i)
		if(i == top[i])
			A.built(rt[i], dfn[i], dfn[down[i]]);
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		u^=lst;
		A.updtt(rt[top[u]], dfn[top[u]], dfn[down[top[u]]], dfn[u], 0, v-f[u]);
		f[u]=v;
		while(u) {
			ggg qwq = /*A.ask(1, 1, n, dfn[top[u]], dfn[down[top[u]]])*/A.tr[rt[top[u]]];
			int haha = ft[top[u]];
			if(ft[top[u]] != 0)
				A.updtt(rt[top[haha]], dfn[top[haha]], dfn[down[top[haha]]], dfn[haha], 
				max(qwq.g[0][0], qwq.g[1][0])-max(per_f[dfn[top[u]]][0], per_f[dfn[top[u]]][1]), 
				qwq.g[0][0]-per_f[dfn[top[u]]][0]);
			per_f[dfn[top[u]]][0]=qwq.g[0][0];
			per_f[dfn[top[u]]][1]=qwq.g[1][0];
			u=ft[top[u]];
		}
//		ggg qwq = A.ask(1, 1, n, dfn[1], dfn[down[1]]);
		lst=max(per_f[1][0], per_f[1][1]);
		write(lst, '\n');
	}
	return 0;
}
