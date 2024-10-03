#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
const int N = 5e5+5, M = 2e6+5;
int n, m, tid, q, u, v, opt, cnt, hed[N], pd[M<<1]/*判断割边*/, ppd[M<<1], nxt[M<<1], to[M<<1],
dfn[N], low[N], vis[N], op, tot, bl[N];

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
		if(!ppd[i])
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
	vis[x]=1, bl[x]=tot;
	for(int i = hed[x]; i; i=nxt[i]) 
		if(!vis[to[i]] && !pd[i] && !ppd[i])
			get_ans(to[i]);
}

signed main() {
	File("graph");
	cnt=1, read(n), read(m), read(q), read(tid);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), add(u, v);
	if(tid == 3) {
		for(int i = 1; i <= n; ++i)
			if(!dfn[i]) 
				tarjan(i);
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
				++tot, get_ans(i);
		for(int i = 1; i <= q; ++i) {
			read(opt), read(u), read(v);
			if(bl[u] == bl[v])
				puts("YES");
			else
				puts("NO");
		}
		return 0;
	}
	for(int i = 1; i <= q; ++i) {
		read(opt);
		if(opt == 1) {
			read(op);
			ppd[op*2]=1;
			ppd[op*2+1]=1;
			continue;
		}
		op=0;
		read(u), read(v);
		for(int j = 2; j <= m+m; ++j)
			pd[j]=0;
		tarjan(u);
		for(int j = 1; j <= n; ++j)
			vis[j]=0, dfn[j]=low[j]=0;
		get_ans(u);
		if(vis[v]) puts("YES");
		else puts("NO");
	}
	return 0;
}
/*
7 8 7 1
1 2
1 3
1 4
2 3
3 4
3 7
7 4
5 6
1 3
2 1 3
2 2 4
1 2
2 1 3
1 8
2 5 6
*/