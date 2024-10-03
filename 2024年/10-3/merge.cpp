#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5, M = 2e6+5;
int n, c[N], u, v, cntt=1, hed[N], pd[M<<1], nxt[M<<1], to[M<<1],
dfn[N], low[N], vis[N], op, tot, bl[N], ans, lll;
vector <int> too[N];
unordered_map<LL, int> gs;

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
void add(int x, int y) {
	nxt[++cntt]=hed[x];
	to[cntt]=y, hed[x]=cntt;
	
	nxt[++cntt]=hed[y];
	to[cntt]=x, hed[y]=cntt;
}
void tarjan(int x) {
	dfn[x]=low[x]=++op;
	for(int i = hed[x]; i; i=nxt[i]) 
		if(!dfn[to[i]]) {
			tarjan(to[i]);
			low[x]=min(low[x], low[to[i]]);
			if(low[to[i]] >= dfn[x] && gs[10000000LL*to[i]+x] == 1)
				pd[i^1]=pd[i]=1;
		}
		else
			low[x]=min(low[x], dfn[to[i]]);
}
void get_ans(int x) {
	vis[x]=0;
	bl[x]=tot;
	for(int i = hed[x]; i; i=nxt[i]) 
		if(vis[to[i]] && !pd[i])
			get_ans(to[i]);
		else {
			if(pd[i] && bl[to[i]]) 
				too[tot].push_back(bl[to[i]]), 
				too[bl[to[i]]].push_back(tot);
		}
}
int siz(int x, int fa) {
	vis[x]=1;
	int ret = 0, gss = 0;
	for(int y : too[x])
		if(!vis[y])
			ret+=siz(y, x), ++gss;
	return ret+(gss == 0 || (fa == 0 && gss == 1));
}

signed main() {
	File("merge");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(c[i]), vis[c[i]]=1;
	for(int i = 2; i <= n; ++i) {
		read(u), read(v), add(c[u], c[v]);
		if(gs.find(10000000LL*c[u]+c[v]) == gs.end())
			gs[10000000LL*c[u]+c[v]]=0, gs[10000000LL*c[v]+c[u]]=0;
		++gs[10000000LL*c[u]+c[v]], ++gs[10000000LL*c[v]+c[u]];
	}
	for(int i = 1; i <= n; ++i)
		if(vis[i] && !dfn[i]) 
			tarjan(i);
	for(int i = 1; i <= n; ++i)
		if(vis[i])
			++tot, get_ans(i);
	// debug(tot, "!\n");
	for(int i = 1; i <= tot; ++i)
		if(!vis[i]) {
			int dd = siz(i, 0);
			if(dd != 1)
				ans+=(dd+1)/2;
			++lll;
		}
	write(ans+lll-1, '\n');
	return 0;
}
