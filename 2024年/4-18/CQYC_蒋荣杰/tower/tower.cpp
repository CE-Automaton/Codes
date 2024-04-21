#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, d, u, dep[N], rt, pd[N], ans, tot, zhan[N], ll[N], rr[N], ds[N];
vector <int> to[N];

struct tree {
	int tr[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k) { tr[k]=max(tr[ls], tr[rs]); }
	void down(int k) {
		if(lzy[k] != 0)
			tr[ls]+=lzy[k], tr[rs]+=lzy[k], lzy[ls]+=lzy[k], lzy[rs]+=lzy[k], lzy[k]=0;
	}
	void built(int k, int l, int r) {
		lzy[k]=0;
		if(l == r) {
			tr[k]=zhan[l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k);
	}
	void add(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			tr[k]+=w;
			lzy[k]+=w;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			add(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			add(rs, mid+1, r, lq, rq, w);
		upup(k);
	}
}A;
template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
	int pd = 1;
	for(int y : to[x])
		if(y != fa)
			pd = 0;
	if(pd) zhan[++tot]=dep[x], ll[x]=rr[x]=tot;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), ll[x]=(ll[x] == 0 ? ll[y] : min(ll[x], ll[y]));
	rr[x]=tot;
}
void ddfs(int x, int fa) {
	dep[x]=dep[fa]+1;
	if(pd[x])
		rt=(dep[rt] > dep[x] ? rt : x);
	for(int y : to[x])
		if(y != fa)
			ddfs(y, x);
}
void sol(int x, int fa) {
	if(A.tr[1] <= d) ++ans;
	A.add(1, 1, tot, 1, tot, 1);
	for(int y : to[x])
		if(y != fa) {
			A.add(1, 1, tot, ll[y], rr[y], -2);
			sol(y, x);
			A.add(1, 1, tot, ll[y], rr[y], 2);
		}
	A.add(1, 1, tot, 1, tot, -1);
}

signed main() {
	File("tower");
	read(n), read(m), read(d);
	for(int i = 2; i <= n; ++i)
		read(u), to[u].push_back(i), to[i].push_back(u), ++ds[u], ++ds[i];
	if(n <= 20) {
		for(int i = 1; i < (1<<n); ++i) {
			int gs = 0;
			for(int j = 1; j <= n; ++j)
				if((i>>(j-1))&1)
					++gs, pd[j]=1;
				else
					pd[j]=0;
			if(gs == m) {
				gs=0;
				for(int j = 1; j <= n; ++j) {
					rt=j;
					ddfs(j, 0);
					if(dep[rt]-1 <= d)
						++gs;
				}
				ans=max(ans, gs);
			}
		}
		write(ans, '\n');
		return 0;
	}
	if(m == n) {
		for(int i = 1; i <= n; ++i)
			if(ds[i] >= 2)
				rt=i;
		dep[0]=-1;
		dfs(rt, 0);
		A.built(1, 1, tot);
		sol(rt, 0);
		write(ans, '\n');
		return 0;
	}
	return 0;
}