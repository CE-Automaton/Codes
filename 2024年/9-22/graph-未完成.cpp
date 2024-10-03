#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5, M = 2e6+5;
int n, m, tid, q, u[M], v[M], dl[M], opt[M], ll[M], rr[M], cnt, hed[N], pd[M<<1]/*判断割边*/, nxt[M<<1], to[M<<1],
dfn[N], low[N], vis[N], tot, op, zhan[N], bl[N], fa[N], cnt[N], fa2[N], cnt2[N];

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
	nxt[++cnt]=hed[x];
	to[cnt]=y, hed[x]=cnt;
	
	nxt[++cnt]=hed[y];
	to[cnt]=x, hed[y]=cnt;
}
void tarjan(int x) {
	dfn[x]=low[x]=++op;
	for(int i = hed[x]; i; i=nxt[i]) 
		if(!dfn[to[i]]) {
			tarjan(to[i]);
			low[x]=min(low[x], low[to[i]]);
			if(low[to[i]] >= dfn[x])
				pd[i^1]=pd[i]=1;
		}
		else
			low[x]=min(low[x], dfn[to[i]]);
}
void get_ans(int x) {//性质:边双连通分量内每条边都至少在一个环内,缩点后是个树 
	vis[x]=1, zhan[++tot]=x, bl[x]=op;
	for(int i = hed[x]; i; i=nxt[i]) 
		if(!vis[to[i]] && !pd[i])
			get_ans(to[i]);
}

signed main() {
	read(n), read(m), read(q), read(tid);
	for(int i = 1; i <= m; ++i)
		read(u[i]), read(v[i]), add(u[i], v[i]);
	return 0;
}