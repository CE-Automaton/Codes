#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, c[N], q, u, v, ans[N], tr[N], dep[N], lst[N];
vector <int> to[N];
struct qwq {
	int u, d;
};
vector <qwq> que[N];

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
void add(int x, int w) {
	while(x)
		tr[x]+=w, x-=(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x <= n)
		ret+=tr[x], x+=(x&(-x));
	return ret;
}
void dfs(int x, int fa) {
	dep[x]=dep[fa]+1;
	int ll = lst[c[x]];
	if(ll) add(dep[ll], -1);
	add(dep[x], 1);
	lst[c[x]]=x;
	for(qwq y : que[x])
		ans[y.d]=ask(dep[y.u]);
	for(int y : to[x])
		if(y != fa)
			dfs(y, x);
	if(ll) add(dep[ll], 1);
	add(dep[x], -1);
	lst[c[x]]=ll;
}

signed main() {
	File("necklace");
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(c[i]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= q; ++i) 
		read(u), read(v), que[v].push_back(qwq {u, i});
	dfs(1, 0);
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}