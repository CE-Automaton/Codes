#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, m, c[N], u, v, up[N], in[N], gs[N], nows, nowg, rt, b[N];
vector <int> to[N];

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
	up[x]=fa;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x);
}
void clear(int x, int fa) {
	gs[c[x]]=0;
	for(int y : to[x])
		if(y != fa)
			clear(y, x);
}
void get_(int x, int fa) {
	++gs[c[x]];
	if(gs[c[x]] > nowg) 
		nows=c[x], nowg=gs[c[x]];
	if(gs[c[x]] == nowg) 
		nows=min(nows, c[x]);
	for(int y : to[x])
		if(y != fa)
			get_(y, x);
}
void sol() {
	for(int i =1 ; i <= n; ++i)
		if(in[i] == n-1)
			rt=i;
	for(int i =1 ; i <= n; ++i)
		++gs[c[i]];
	for(int i =1 ; i <= N-5; ++i) 
		if(gs[i] > nowg) {
			nowg=gs[i];
			nows=i;
		}
} 

signed main() {
	freopen("diedmd.in", "r", stdin);
	freopen("diedmd.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(c[i]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u), 
		++in[u], ++in[v];
	dfs(1, 0);
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		nows=nowg=0;
		get_(u, up[u]);
		get_(v, up[v]);
		write(nows, '\n'); 
		clear(u, up[u]);
		clear(v, up[v]);
	}
	return 0;
}
