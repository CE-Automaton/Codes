#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, q, nxt[N], fa[N], vis[N], u, v, ans[N];
char s[N];
vector <int> to[N];
struct qwq {
	int u, v;
};
vector <qwq> que[N];

template <typename T> inline void debug(T x) { cerr<<x<<'\n'; }
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
int find(int x) {
	return (fa[x] == x ? x : fa[x]=find(fa[x]));
}
void tarjan(int x, int fr) {
	for(int y : to[x])
		tarjan(y, x);
	for(qwq y : que[x])
		if(vis[y.u]) 
			ans[y.v]=find(y.u);
	vis[x]=1, fa[x]=fr;
}

signed main() {
	scanf("%s", s+1);
	n=strlen(s+1);
	to[0].push_back(1);
	for(int i = 2, j = 0; i <= n; ++i) {
		while(j && s[j+1] != s[i]) j=nxt[j];
		if(s[j+1] == s[i]) ++j;
		nxt[i]=j; to[j].push_back(i);
	}
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(u), read(v);
		u=nxt[u], v=nxt[v];
		if(u == v)
			ans[i]=u;
		else
			que[u].push_back(qwq {v, i}), que[v].push_back(qwq {u, i});
	}
	for(int i = 0; i <= n; ++i)
		fa[i]=i;
	tarjan(0, 0);
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	return 0;
}