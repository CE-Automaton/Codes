#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 1e5+5, B = 400;
int n, m, f[N], a[N], u, v, l[N], r[N], ans[N], dfn[N], cnt, tt[N], bl[N], ll[N], rr[N], dep[N], 
tot, ola[N], in[N], st[N][25], vis[N], now;
vector <int> to[N];
vector <pii> que[N];

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
	dfn[x]=++cnt, tt[cnt]=x;
	ola[++tot]=x, in[x]=tot, dep[x]=dep[fa]+1;
	for(int y : to[x])
		dfs(y, x), ola[++tot]=x;
	return ;
}
int mmn(int x, int y) {
	return (dep[x] < dep[y] ? x : y);
}
int ask(int x, int y) {
	if(x > y) swap(x, y);
	int lg = floor(log2(y-x+1));
	return mmn(st[x][lg], st[y-(1<<lg)+1][lg]);
}

signed main() {
	read(n), read(m);
	for(int i = 2; i <= n; ++i)
		read(f[i]), to[f[i]].push_back(i);
	for(int i = 1; i <= n; ++i)
		read(a[i]), a[i+n]=a[i], l[i]=i-1, r[i]=i+1, ++vis[a[i]];
	now=n;
	r[0]=1;
	for(int i = 1, j = 0; i <= n+n; ++i) {
		if(i%B == 1) ++j, ll[j]=i;//分块
		bl[i]=j, rr[j]=i;
	}
	dfs(1, 0);
	for(int i = 1; i < n; ++i)
		++vis[ask(in[tt[i]], in[tt[i+1]])];
	return 0;
}