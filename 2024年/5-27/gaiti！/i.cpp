#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, fa[N], xx, yy, gs, zhan[N], tot;
LL ans[N], a[N], ss;
vector <int> to[N];
struct node {
	int vis[2], cnt, now;
}tr[N*60];
struct trie {
	void add(LL x, int nw) {
		int now = 0, nn = 0;
		LL sum = 0;
		for(LL i = 59; i >= 0; --i) {
			int op = ((x>>i)&1);
			int& too = tr[now].vis[op];
			if(!too) too=++gs;
			if(tr[nn].vis[op^1])
				sum+=(1LL<<i), nn=tr[nn].vis[op^1];
			else
				nn=tr[nn].vis[op];
			now=too;
		}
		++tr[now].cnt, tr[now].now=nw;
		if(sum > ss)
			ss=sum, xx=nw, yy=tr[nn].now;
	}
}A;

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
	// debug(x, "???\n");
	A.add(a[x], x);
	for(int y : to[x])
		if(y != fa)
			dfs(y, x);
}
void sol(int x) {
	for(int i = 0; i <= gs; ++i)
		tr[i].vis[0]=tr[i].vis[1]=tr[i].cnt=tr[i].now=0;
	gs=0;
	tot=0;
	for(int y = x; y; y=fa[y])
		zhan[++tot]=y, ans[y]=0;
	ss=0, xx=yy=0;
	for(int i = tot; i >= 1; --i) {
		ans[zhan[i]]=ss;
		// debug(zhan[i], ":\n");
		A.add(a[zhan[i]], zhan[i]);
		for(int y : to[zhan[i]])
			if(y != zhan[i-1])
				dfs(y, zhan[i]);
	}
	// debug('\n');
}

signed main() {
	read(n);
	for(int i = 2; i <= n; ++i)
		read(fa[i]), to[fa[i]].push_back(i);
	for(int i = 1; i <= n; ++i) 
		read(a[i]), A.add(a[i], i);
	for(int i = 1; i <= n; ++i) 
		ans[i]=ss;
	sol(xx);
	sol(yy);
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}