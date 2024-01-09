#include <bits/stdc++.h>
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
int n, a[200005], u, v, siz[200005], mx, mxsz[200005], vis[200005], rt, sum,
ans[200005], cnt, tot, zhan[200005], ppp[200005], rtt[200005], rttt[200005];
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
	int gs;
	struct node {
		int ls, rs, mx;
	}tr[8000005];
	void updt(int& k, int l, int r, int to, int w) {
		if(k == 0)
			++gs, tr[gs]=tr[0], k=gs;
		if(l == r) {
			tr[k].mx=mxxx(tr[k].mx, w);
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) updt(tr[k].ls, l, mid, to, w);
		else updt(tr[k].rs, mid+1, r, to, w);
		tr[k].mx=mxxx(tr[tr[k].ls].mx, tr[tr[k].rs].mx);
	}
	int find(int k, int l, int r, int lq, int rq) {
		if(tr[k].mx == 0 || k == 0)
			return 0;
		if(lq <= l && r <= rq) 
			return tr[k].mx;
		int ret = 0, mid = ((l+r)>>1);
		if(lq <= mid) ret=mxxx(ret, find(tr[k].ls, l, mid, lq, rq));
		if(mid+1 <= rq) ret=mxxx(ret, find(tr[k].rs, mid+1, r, lq, rq));
		return ret;
	}
	void merge(int l, int r, int& aaa, int bbb) {
		if(!aaa || !bbb) {
			aaa=(bbb|aaa);
			return ;
		}
		if(l == r) {
			tr[aaa].mx=mxxx(tr[aaa].mx, tr[bbb].mx);
			return ;
		}
		int mid=((l+r)>>1);
		merge(l, mid, tr[aaa].ls, tr[bbb].ls);
		merge(mid+1, r, tr[aaa].rs, tr[bbb].rs);
		tr[aaa].mx=mxxx(tr[tr[aaa].ls].mx, tr[tr[aaa].rs].mx);
		return ;
	}
}A;
struct zhuxi_tree {
	int gs;
	struct node {
		int ls, rs, mx;
	}tr[8000005];
	void updt(int& k, int l, int r, int to, int w) {
		++gs;
		tr[gs]=tr[k];
		k=gs;
		if(l == r) {
			tr[k].mx=mxxx(tr[k].mx, w);
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) updt(tr[k].ls, l, mid, to, w);
		else updt(tr[k].rs, mid+1, r, to, w);
		tr[k].mx=mxxx(tr[tr[k].ls].mx, tr[tr[k].rs].mx);
	}
	int find(int k, int l, int r, int lq, int rq) {
		if(tr[k].mx == 0 || k == 0)
			return 0;
		if(lq <= l && r <= rq) 
			return tr[k].mx;
		int ret = 0, mid = ((l+r)>>1);
		if(lq <= mid) ret=mxxx(ret, find(tr[k].ls, l, mid, lq, rq));
		if(mid+1 <= rq) ret=mxxx(ret, find(tr[k].rs, mid+1, r, lq, rq));
		return ret;
	}
}B;
void solve(int x, int fa) {
	siz[x]=1;
	for(auto j : to[x]) {
		if(j == fa || vis[j]) continue;
		solve(j, x);
		siz[x]+=siz[j];
		A.merge(1, cnt, rttt[x], rttt[j]);
		rttt[j]=0;
	}
	zhan[++tot]=x;
	ppp[x] = A.find(rttt[x], 1, cnt, a[x]+1, cnt)+1;
	A.updt(rttt[x], 1, cnt, a[x], ppp[x]);
}
void get_son(int x, int fa, int grfa) {
	zhan[++tot]=x;
	rtt[x]=rtt[fa];
	int pp=mxxx(A.find(rttt[0], 1, cnt, a[x]+1, cnt), B.find(rtt[x], 1, cnt, a[x]+1, cnt))+1;
	if(a[x] < a[grfa])
		pp=mxxx(pp, ppp[grfa]+1);
	ans[x]=mxxx(ans[x], pp);
	B.updt(rtt[x], 1, cnt, a[x], pp);
	for(auto j : to[x]) {
		if(j == fa || vis[j]) continue;
		get_son(j, x, grfa);
	}
	rtt[x]=0;
}
void dfs(int x) {
	vis[x]=1;
	ans[x]=mxxx(ans[x], 1);
	for(auto j : to[x]) {
		if(vis[j]) continue;
		tot=0;
		A.gs=0;
		solve(j, x);
		rttt[j]=0;
		for(int i = 1; i <= tot; ++i)
			if(a[x] < a[zhan[i]])
				ans[x]=mxxx(ans[x], ppp[zhan[i]]+1);
	}

	A.gs=B.gs=rtt[x]=rttt[0]=0;
	ppp[x]=1;
	for(auto j : to[x]) {
		if(vis[j]) continue;
		tot=0;
		get_son(j, x, x);
		B.gs=0;
		for(int o = 1; o <= tot; ++o) {
			if(a[x] < a[zhan[o]])
				ppp[x]=mxxx(ppp[x], ppp[zhan[o]]+1);
			A.updt(rttt[0], 1, cnt, a[zhan[o]], ppp[zhan[o]]);
		}
	}

	A.gs=rttt[0]=B.gs=rtt[x]=0;
	ppp[x]=1;
	for(int i = to[x].size()-1; i >= 0; --i) {
		int j = to[x][i];
		if(vis[j]) continue;
		tot=0;
		get_son(j, x, x);
		B.gs=0;
		for(int o = 1; o <= tot; ++o) {
			if(a[x] < a[zhan[o]])
				ppp[x]=mxxx(ppp[x], ppp[zhan[o]]+1);
			A.updt(rttt[0], 1, cnt, a[zhan[o]], ppp[zhan[o]]);
		}
	}

	A.gs=rttt[0]=B.gs=rtt[x]=0;

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
	freopen("17.in", "r", stdin);
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
