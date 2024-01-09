#include <bits/stdc++.h>
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
int n, a[200005], u, v, siz[200005], mx, mxsz[200005], vis[200005], rt, sum,
ans[200005], cnt, tot, zhan[200005], ppp[200005], rtt[200005], dfn[200005];
struct qwq {
	int w, id;
}b[200005];
vector <int> to[200005];

inline void read(int& s) {
	s=0; char ch = getchar(); while(ch<'0' || ch > '9') ch=getchar();
	while(ch >= '0'&& ch <= '9') s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
}
int lne; char put[105];
inline void write(int x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
inline int mxxx(int x, int y) {
	return (x > y ? x : y);
}
void get_rt(int x, int fa) {
//	cout<<x<<" "<<fa<<"\n";
	siz[x]=mxsz[x]=1;
	for(auto i : to[x])
		if(i != fa && !vis[i])
			get_rt(i, x), siz[x]+=siz[i], mxsz[x]=mxxx(mxsz[x], siz[i]);
	mxsz[x]=mxxx(mxsz[x], sum-siz[x]);
	rt=(mxsz[x] < mxsz[rt] ? x : rt);
}
struct tree {
	int tr[1000005];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int to, int w) {
		if(l == r) {
			tr[k]=mxxx(tr[k], w);
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) updt(ls, l, mid, to, w);
		else updt(rs, mid+1, r, to, w);
		tr[k]=mxxx(tr[ls], tr[rs]);
	}
	int find(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k];
		int ret = 0, mid = ((l+r)>>1);
		if(lq <= mid) ret=mxxx(ret, find(ls, l, mid, lq, rq));
		if(mid+1 <= rq) ret=mxxx(ret, find(rs, mid+1, r, lq, rq));
		return ret;
	}
	#undef ls
	#undef rs
}A;
struct shuz {
	int gs, tr[200005];
	qwq bck[8000005];
	void add(int x, int w) {
		while(x >= 1) {
			bck[++gs]=qwq{tr[x], x};
			tr[x]=max(tr[x], w);
			x=x-(x&(-x));
		}
	}
	int find(int x, int ret=0) {
		while(x <= cnt) 
			ret=max(ret, tr[x]), x=x+(x&(-x));
		return ret;
	}
	void back(int op) {
		while(gs > op)
			tr[bck[gs].id]=bck[gs].w, --gs;
	}
}B, C;
void solve(int x, int fa) {
	siz[x]=1;
	zhan[++tot]=x;
	dfn[x]=tot;
	for(auto j : to[x]) {
		if(j == fa || vis[j]) continue;
		solve(j, x);
		siz[x]+=siz[j];
	}
}
void get_son(int x, int fa, int grfa) {
	zhan[++tot]=x;
	int pp=mxxx(C.find(a[x]+1), B.find(a[x]+1))+1;
	if(a[x] < a[grfa]) pp=mxxx(pp, ppp[grfa]+1);
	ans[x]=mxxx(ans[x], pp);
	int cc = B.gs;
	B.add(a[x], pp);
	for(auto j : to[x]) {
		if(j == fa || vis[j]) continue;
		get_son(j, x, grfa);
	}
	B.back(cc);
}
void dfs(int x) {
	vis[x]=1;
	ans[x]=mxxx(ans[x], 1);
	tot=0;
	for(auto j : to[x]) {
		if(vis[j]) continue;
		solve(j, x);
	}
	if(tot) {
		sort(zhan+1, zhan+1+tot, [](const int A, const int B) {
			return a[A] > a[B];
		});
		int l = 1;
		for(int i = 1; i <= tot; ++i) {
			while(l <= tot && a[zhan[l]] > a[zhan[i]])
				A.updt(1, 1, tot, dfn[zhan[l]], ppp[zhan[l]]), ++l;
			ppp[zhan[i]]=A.find(1, 1, tot, dfn[zhan[i]], dfn[zhan[i]]+siz[zhan[i]]-1)+1;
		}
		for(int i = 1; i <= tot; ++i)
			if(a[x] < a[zhan[i]])
				ans[x]=mxxx(ans[x], ppp[zhan[i]]+1);
		A.built(1, 1, tot);
	}

	B.back(0);
	C.back(0);
	ppp[x]=1;
	for(auto j : to[x]) {
		if(vis[j]) continue;
		tot=0;
		get_son(j, x, x);
		for(int o = 1; o <= tot; ++o) {
			if(a[x] < a[zhan[o]])
				ppp[x]=mxxx(ppp[x], ppp[zhan[o]]+1);
			C.add(a[zhan[o]], ppp[zhan[o]]);
		}
	}

	B.back(0);
	C.back(0);
	ppp[x]=1;
	for(int i = to[x].size()-1; i >= 0; --i) {
		int j = to[x][i];
		if(vis[j]) continue;
		tot=0;
		get_son(j, x, x);
		for(int o = 1; o <= tot; ++o) {
			if(a[x] < a[zhan[o]])
				ppp[x]=mxxx(ppp[x], ppp[zhan[o]]+1);
			C.add(a[zhan[o]], ppp[zhan[o]]);
		}
	}

	B.back(0);
	C.back(0);

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
	rt=0, mxsz[0]=1000000;
	sum=n;
	get_rt(1, 1);
	dfs(rt);
	for(int i = 1; i <= n; ++i)
		write(ans[i]), putchar('\n');
	return 0;
}
