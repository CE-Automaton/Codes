#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
bool lulalulula;
const int N = 5e4+5;
bitset <N> vis[N];
int n, u, v, dd[N], op;
LL r[N], h[N], ans[N], w;
struct qwq { int t; LL w; };
vector <qwq> to[N];

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
int comp(int A, int B) {
	return r[A] > r[B];
}
void dfs(int x, int fa, LL w) {
	w=max(w, r[x]);
	vis[op][x]=1;
	for(qwq y : to[x]) 
		if(y.t != fa && vis[op][y.t] == 0 && w >= y.w) {
			if(vis[y.t][op] == 1) 
				vis[op]|=vis[y.t];
			dfs(y.t, x, w-y.w);
		}
}

bool lululalula;
signed main() {
	File("mine");
	// debug(1.0*(&lululalula-&lulalulula)/1024/1024, '\n');
	read(n);
	for(int i = 1; i <= n; ++i)
		read(h[i]), dd[i]=i;
	for(int i = 1; i <= n; ++i)
		read(r[i]);
	for(int i = 2; i <= n; ++i) 
		read(u), read(v), read(w), 
		to[u].push_back(qwq {v, w}), to[v].push_back(qwq {u, w});
	sort(dd+1, dd+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		op = dd[i];
		dfs(dd[i], 0, 0);
		for(int j = 1; j <= n; ++j)
			if(vis[op][j] == 1)
				ans[op]+=h[j];
	}
	for(int i = 1; i <= n; ++i)
		write(ans[i], ' ');
	return 0;
}