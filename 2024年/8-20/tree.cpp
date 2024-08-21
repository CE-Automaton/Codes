#include <bits/stdc++.h>
#define int LL
#define inf 10000000000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 6e5+5, V = 6e5;
int n, u, v, q, ds[N], gs, siz[N], dep[N];
LL k, dp[N], mdep[N], sum[N], ans[N];
vector <int> to[N];
struct qwq {
	int w, d;
}que[N];

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
	if(ds[x] == 1)
		siz[x]=1;
	mdep[x]=dep[x]=dep[fa]+1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y], mdep[x]=max(mdep[x], mdep[y]), sum[x]+=sum[y]+siz[y];
}
void dfs2(int x, int fa, LL op) {
	if(ds[x] == 1)
		return ;
	int R = max(op, mdep[x]-dep[x]);
	dp[R]=max(dp[R], (1LL*R*gs-sum[x])/2);
	// debug(x, R, sum[x], (1LL*R*gs-sum[x])/2, "???\n");
	int mx = op, mn = fa, mxx = 0, mnn = 0;
	for(int y : to[x])
		if(y != fa)
			if(mdep[y]-dep[x] > mx)
				mxx=mx, mnn=mn, mx=mdep[y]-dep[x], mn=y;
			else 
				if(mdep[y]-dep[x] > mxx)
					mxx=mdep[y]-dep[x], mnn=y;
	for(int y : to[x])
		if(y != fa)
			sum[y]=sum[x]+(gs-2*siz[y]), dfs2(y, x, (mn == y ? mxx : mx)+1);
}
int comp(qwq A, qwq B) {
	return A.w < B.w;
}

signed main() {
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(n+i-1), to[n+i-1].push_back(u), 
		to[v].push_back(n+i-1), to[n+i-1].push_back(v), ++ds[u], ++ds[v], ds[n+i-1]=2;
	for(int i = 1; i <= V; ++i)
		if(ds[i] == 1)
			++gs;
	dep[0]=-1;
	dfs(n+1, 0);
	for(int i = 0; i <= V; ++i)
		dp[i]=-inf;
	dfs2(n+1, 0, 0);
	for(int i = 2; i <= V; ++i)
		dp[i]=max(dp[i], dp[i-2]+gs);
	read(q);
	for(int i = 1; i <= q; ++i) 
		read(que[i].w), que[i].d=i;
	sort(que+1, que+1+q, comp);
	int op = 1;
	for(int i = 1; i <= V; ++i) //必须老老实实这样找！
		while(op <= q && que[op].w <= dp[i])
			ans[que[op].d]=i, ++op;
	for(int i = op; i <= q; ++i)
		ans[que[i].d]=min((que[i].w-dp[V]+gs-1)/gs*2+V, (que[i].w-dp[V-1]+gs-1)/gs*2+V-1);
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}