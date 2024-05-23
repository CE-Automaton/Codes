#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int t, n, m, zhan[N], tot, u, v, ds[N], dep[N], ppd[N], siz[N];
vector <int> to[N];

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
void dfs(int x) {
	for(int i = 0; i < to[x].size(); ++i) {
		int y = to[x][i];
		if(!dep[y] || dep[x]+1 < dep[y])
			dep[y]=dep[x]+1, dfs(y);
	}
}
int ddfs(int x, int fa) {
	siz[x]=ppd[x];
	if(ppd[x]) {
		for(int i = 0; i < to[x].size(); ++i) {
			int y = to[x][i];
			if(dep[y] != dep[x]-1)
				return 0;
		}
		return 1;
	}
	int ret = 1;
	for(int i = 0; i < to[x].size(); ++i) {
		int y = to[x][i];
		if(y != fa && dep[y] != dep[x]+1)
			return 0;
		if(y != fa)
			ret&=ddfs(y, x), siz[x]+=siz[y];
	}
	if(siz[x] == 0)
		return 0;
	return ret;
}
int check(int xx, int yy) {
	for(int x = 1; x <= n; ++x)
		dep[x]=0;
	dep[xx]=1, dfs(xx);
	dep[yy]=1, dfs(yy);
	int qqq = 1, gs = 0;
	// debug('\n');
	for(int x = 1; x <= n; ++x) {
		int pd = 1;
		for(int i = 0; i < to[x].size(); ++i) {
			int y = to[x][i];
			if(dep[y] >= dep[x]) {
				pd=0;
				break;
			}
		}
		if(pd)
			qqq&=(ds[x] == 2), ++gs, ppd[x]=1;
		else
			ppd[x]=0;
	}
	qqq&=ddfs(xx, 0), qqq&=ddfs(yy, 0);
	// debug(xx, yy, qqq, gs, "???\n");
	return (gs && qqq);
}

signed main() {
	File("fate");
	read(t);
	while(t--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i)
			to[i].clear(), ds[i]=0;
		for(int i = 1; i <= m; ++i)
			read(u), read(v), to[u].push_back(v), to[v].push_back(u), ++ds[u], ++ds[v];
		int pd = 0;
		for(int i = 1; i <= n && !pd; ++i)
			for(int j = i+1; j <= n && !pd; ++j)
				if(ds[i] == ds[j]) 
					if(check(i, j)) {
						puts("YES");
						pd=1;
						break;
					}
		if(!pd) 
			puts("NO");
	}
	return 0;
}