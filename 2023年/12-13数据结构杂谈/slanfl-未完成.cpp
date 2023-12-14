#include <bits/stdc++.h>
using namespace std;
const int N = 5e2+5, LN = 1e3+5;
bitset <LN> dis[N], ww, up[N], huan[LN<<1], ku[LN], ans[LN];
int n, m, q, fa[N], cnt[N], u, v, op[LN], tot, zhann[LN], totz, totzz, gs;
char ssss[15];
struct qwq {
	int t, w, p, s;
}zhan[N<<3];
struct bian {
	int t, tt, ll, rr;
	bitset<1005> az;
}edge[LN];

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
int find(int x) {
	if(x == fa[x])
		return x;
	int op = find(fa[x]);
	dis[x]=(up[x]^dis[op]);
	return op;
}
void add(int x, int pd) {
	for(int j = 1000; j >= 0; --j)
		if(huan[x][j])
			if(ku[j].none()) { if(pd) zhann[++totz]=j; ku[j]=huan[x]; break; }
			else huan[x]^=ku[j];
}
bitset<1005> query() {
	bitset<1005> ret(0);
	for(int j = 1000; j >= 0; --j)
		if(!ret[j] && ku[j].any())
			ret^=ku[j];
	return ret;
}
void merge(int x, int y, int pd=1/*表示要不要撤销*/) {
	x = find(x), y = find(y);
	if(x == y) 
		huan[++tot]=(dis[x]^dis[y]^ww), add(tot, pd);
	else {
		if(cnt[x] > cnt[y]) swap(x, y);
		if(pd)
			zhan[++totzz]=qwq {x, fa[x], y, cnt[y]};
		fa[x]=y, up[x]=ww, cnt[y]+=cnt[x];
	}
}
struct tree {
	vector <int> tr[LN<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void add(int k, int l, int r, int kk) {
		if(edge[kk].ll <= l && r <= edge[kk].rr) {
			tr[k].push_back(kk);
			return ;
		}
		int mid = ((l+r)>>1);
		if(edge[kk].ll <= mid)
			add(ls, l, mid, kk);
		if(mid+1 <= edge[kk].rr)
			add(rs, mid+1, r, kk);
	}
	void dfs(int k, int l, int r) {
		int now1 = totz, now2 = totzz;
		for(int y : tr[k]) 
			merge(edge[y].t, edge[y].tt);
		if(l == r) {
			ans[l]=query();
			return ;
		}
		int mid = ((l+r)>>1);
		dfs(ls, l, mid);
		while(totz > now1)
			fa[zhan[totz].t]=zhan[totz].w, up[zhan[totz].t].reset(), 
			cnt[zhan[totz].p]=zhan[totz].s, --totz;
		while(totzz > now2)
			ku[zhann[totzz]].reset();
		dfs(rs, mid+1, r);
		while(totz > now1)
			fa[zhan[totz].t]=zhan[totz].w, up[zhan[totz].t].reset(), 
			cnt[zhan[totz].p]=zhan[totz].s, --totz;
		while(totzz > now2)
			ku[zhann[totzz]].reset();
	}
};

signed main() {
	read(n), read(m), read(q);
	for(int i = 1; i <= n; ++i)
		fa[i]=i, cnt[i]=1;
	for(int i = 1; i <= m; ++i) {
		ww=0;
		read(u), read(v), cin>>ww;
		merge(u, v, 0);
	}
	for(int i = 1; i <= q; ++i) {
		scanf("%s", ssss+1);
		if(ssss[1] == 'A') {
			read(u), read(v), cin>>ww;
			edge[++gs]=bian {u, v, i, q, ww};
			op[gs]=gs;
		}
		else {
			u=op[u];
			if(ssss[1] == 'C' && ssss[2] == 'a') 
				read(u), edge[u].rr=i-1;
			if(ssss[1] == 'C' && ssss[2] == 'h') {
				read(u);
				edge[u].rr=i-1;
				edge[++gs]=edge[u];
				edge[gs].ll=i, edge[gs].rr=q;
				op[u]=gs;
			}
		}
	}
	for(int i = 1; i <= q; ++i) {
		for(int op)
	}
	return 0;
}
