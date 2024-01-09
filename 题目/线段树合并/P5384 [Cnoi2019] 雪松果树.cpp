#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int rt[N], gs, tot, zhan[N<<1], n, q, u, v[N], fa[N], cnt, dep[N], siz[N], mxdp, ans[N];
vector <int> to[N], pro[N];
struct qwq { int d, w; };
struct node {
	int ls, rs, ss;
}tr[N<<1];//空间是log的!
struct tree {//线段树合并板子 
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
	#define ss(x) tr[x].ss
	void upup(int k) {
		ss(k)=ss(ls(k))+ss(rs(k));
	}
	void dlt(int k) { zhan[++tot]=k; }
	void cnw(int& ret) {
		if(tot) ret=zhan[tot], --tot;//回收空间,用处不是很大,兴许什么时候要卡空间了就用上看能不能过吧 
		else ret=(++gs); 
		tr[ret]=node {0, 0, 0};
	}
	int merge(int x, int y, int l, int r) {
		if(!x || !y) return (x|y);
		if(l == r) {//注意线段树叶子结点也要合并!!! 
			ss(x)+=ss(y), dlt(y);
			return x;
		}
		int mid = ((l+r)>>1); 
		ls(x)=merge(ls(x), ls(y), l, mid); 
		rs(x)=merge(rs(x), rs(y), mid+1, r); 
		upup(x), dlt(y);
		return x;
	}
	void updt(int& k, int l, int r, int tt) {
		if(!k) cnw(k);
		if(l == r) {
			++ss(k);
			return ;
		} 
		int mid = ((l+r)>>1);
		if(tt <= mid)
			updt(ls(k), l, mid, tt);
		else
			updt(rs(k), mid+1, r, tt);
		upup(k);
	}
	int ask(int k, int l, int r, int tt) {
		if(!k) return 0;
		if(l == r) 
			return ss(k);
		int mid = ((l+r)>>1);
		if(tt <= mid)
			return ask(ls(k), l, mid, tt);
		else
			return ask(rs(k), mid+1, r, tt);
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
void get(int x) {
	siz[x]=1, dep[x]=dep[fa[cnt]]+1, fa[++cnt]=x, mxdp=max(mxdp, dep[x]);
	for(int y : pro[x])
		if(v[y] >= cnt) ans[y]=1;
		else pro[fa[cnt-v[y]]].push_back(y), v[y]=dep[x];
	pro[x].clear();
	for(int y : to[x]) get(y), siz[x]+=siz[y];
	--cnt;
}
void dfs(int x) {
	int mxs = 0;
	for(int y : to[x]) 
		mxs=(siz[mxs] < siz[y] ? y : mxs);
	if(mxs)
		dfs(mxs), rt[x]=rt[mxs];
	for(int y : to[x]) 
		if(y != mxs)
			dfs(y), rt[x]=A.merge(rt[x], rt[y], 1, mxdp);
	A.updt(rt[x], 1, mxdp, dep[x]);
	for(int i = 0; i < pro[x].size(); ++i) {
		int y = pro[x][i];
		ans[y]=A.ask(rt[x], 1, mxdp, v[y]);
	}
}

signed main() {
	read(n), read(q);
	for(int i = 2; i <= n; ++i)
		read(u), to[u].push_back(i);
	for(int i = 1; i <= q; ++i) {
		read(u), read(v[i]);
		if(v[i] == 0) ans[u]=0;
		else pro[u].push_back(i);
	} 
	get(1), dfs(1);
	for(int i = 1; i <= q; ++i) 
		write(ans[i]-1, ' ');
	return 0;
}
