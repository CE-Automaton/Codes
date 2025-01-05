#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+6;
int t, n, m, u, v, col[N], vis[N], mx, mn, gc;
vector <int> ad[N], dl[N];

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
int gcd(int x, int y) {
	if(!x || !y) return (x|y);
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}
void dfs(int x) {
	mx=max(mx, col[x]), mn=min(mn, col[x]);
	vis[x]=1;
	for(int i = 0; i < ad[x].size(); ++i)
		if(!vis[ad[x][i]])
			col[ad[x][i]]=col[x]+1, dfs(ad[x][i]);
		else {
			int now = abs(col[ad[x][i]]-col[x]-1);
			// debug(x, "->", ad[x][i], now, '\n');
			gc=gcd(gc, now);
		}
	for(int i = 0; i < dl[x].size(); ++i)
		if(!vis[dl[x][i]])
			col[dl[x][i]]=col[x]-1, dfs(dl[x][i]);
		else {
			int now = abs(col[dl[x][i]]-col[x]+1);
			// debug(dl[x][i], "->", x, now, '\n');
			gc=gcd(gc, now);
		}
}

signed main() {
	read(t);
	while(t--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i)
			ad[i].clear(), dl[i].clear(), vis[i]=col[i]=0;
		for(int i = 1; i <= m; ++i)
			read(u), read(v), ++u, ++v, ad[u].push_back(v), dl[v].push_back(u);
		int ans = 0;
		gc=0;
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
				mx=mn=0, dfs(i), ans+=mx-mn;
		if(!gc) gc=ans;
		write(n-gc, '\n');
	}
	return 0;
}