#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, u, v, rt, dep[N], op[N], ans[N];
vector <int> to[N];

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
	op[x]=max(op[x], dep[x]);
	if(dep[x] > dep[rt])
		rt=x;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x);
}
void sol(int x, int fa) {
	++ans[op[x]+1];
	for(int y : to[x])
		if(y != fa)
			sol(y, x);
}

signed main() {
	File("tree");
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dep[0]=-1;
	dfs(1, 0);
	int now = rt;
	rt=0;
	dfs(now, 0);
	dfs(rt, 0);
	sol(now, 0);
	for(int i = 1; i <= n; ++i)
		ans[i]+=ans[i-1], write(min(ans[i]+1, n), ' ');
	return 0;
}