#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e6+5;
int n, k, a[N], cnt, tot, gs, zhan[N*26], rt[N], siz[N], u, v, ansx, ansy;
vector <int> to[N];
struct qwq {
	int w, t;
}b[N];
struct node {
	int ls, rs, w;
}tr[N*30];//空间是log的! 
struct tree {//线段树合并板子 
	#define ls(x) tr[x].ls
	#define rs(x) tr[x].rs
	#define w(x) tr[x].w
	void upup(int k) {
		w(k)=w(ls(k))+w(rs(k));
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
			w(x)|=w(y);
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
			w(k)|=1;
			return ;
		} 
		int mid = ((l+r)>>1);
		if(tt <= mid)
			updt(ls(k), l, mid, tt);
		else
			updt(rs(k), mid+1, r, tt);
		upup(k);
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
int comp(qwq AA, qwq BB) {
	return AA.w < BB.w;
}
void dfs(int x) {
	siz[x]=1;
	for(int y : to[x])
		dfs(y), rt[x]=A.merge(rt[x], rt[y], 1, cnt), siz[x]+=siz[y];
	A.updt(rt[x], 1, cnt, a[x]);
	u = tr[rt[x]].w, v = siz[x];
	if(!ansy || 1LL*ansx*v > 1LL*u*ansy)
		ansx=u, ansy=v;
} 
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1) ret=1LL*ret*x%mod;
		y=(y>>1), x=1LL*x*x%mod;
	}
	return ret;
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(a[i]), b[i]=qwq{a[i], i};
	for(int i = 2; i <= n; ++i)
		read(u), to[u].push_back(i);
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || b[i].w != b[i-1].w) 
			++cnt;
		a[b[i].t]=cnt;
	}
	dfs(1);
	write(1LL*ansx*ksm(ansy, mod-2)%mod, '\n');
	return 0;
}
