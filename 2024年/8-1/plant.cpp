#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int t, n, u, v, dd, rt, dep[N], f[N];
LL mx[N];
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
void dfs(int x, int fa) {
	dep[x]=dep[fa]+1;
	f[x]=fa;
	for(int i = 0; i < to[x].size(); ++i) {
		int y = to[x][i];
		if(y != fa) 
			dfs(y, x);
	}
	if(dep[rt] < dep[x])
		rt=x;
}
void dfs2(int x, int fa) {
	dep[x]=dep[fa]+1;
	mx[dep[x]]=max((LL) to[x].size()-1, mx[dep[x]]);
	for(int i = 0; i < to[x].size(); ++i) {
		int y = to[x][i];
		if(y != fa) 
			dfs2(y, x);
	}
}
LL sol(int x, int y, int mdp) {
	for(int i = 1; i < mdp; ++i)
		mx[i]=0;
	dep[y]=0;
	dfs2(x, y);
	dep[x]=0;
	dfs2(y, x);
	LL sum = 2;
	for(int i = 1; i < mdp; ++i)
		sum*=mx[i];
	return sum;
}

signed main() {
	// File("plant");
	read(t);
	while(t--) {
		read(n);
		if(n == 0) {
			puts("0 0");
			continue;
		}
		if(n == 1) {
			puts("1 1");
			continue;
		}
		for(int i = 2; i <= n; ++i)
			read(u), read(v), to[u].push_back(v), to[v].push_back(u);
		dfs(1, 0);
		int xx = rt;
		dfs(xx, 0);
		int pp = dep[rt];
		if(pp%2 == 0) {//以一条边为中心
			// debug(xx, rt, dep[rt], "???\n");
			v=rt;
			for(int i = 1; i < pp/2; ++i)
				v=f[v];
			u=f[v];
			// debug(u, v, "???\n");
			write(pp/2, ' ');
			write(sol(u, v, pp/2), '\n');
		}
		else {//以点为中心
			write(pp/2+1, ' ');
			xx=rt;
			for(int i = 1; i*2 < pp; ++i)
				xx=f[xx];
			for(int i = 1; i < pp/2; ++i)
				mx[i]=0;
			dep[xx]=0;
			for(int i = 0; i < to[xx].size(); ++i) {
				int y = to[xx][i];
				dfs2(y, xx);
			}
			LL ans = to[xx].size();
			for(int i = 1; i < pp/2; ++i)
				ans*=mx[i];
			for(int i = 0; i < to[xx].size(); ++i) {
				int y = to[xx][i];
				ans=min(ans, sol(y, xx, pp/2+1));
			}
			write(ans, '\n');
		}
		for(int i = 1; i <= n; ++i)
			to[i].clear(), f[i]=0, dep[i]=0;
	}
	return 0;
}