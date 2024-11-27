#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e5+5;
int n, k, u, v, rt, mx[3][3005][3005], dfn[N], siz[N], cnt;
LL ans, gs[N];
vector <int> to[N][3];
bitset <3005> vis;

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
void sol(int o, int x, int fa, int w) {
	vis[x]=0;
	if(!vis[w])
		w=vis._Find_next(w);
	mx[o][rt][x]=w;
	for(int y : to[x][o])
		if(y != fa)
			sol(o, y, x, w);
	vis[x]=1;
}
void dfs(int x, int fa) {
	dfn[x]=++cnt;
	siz[x]=1;
	for(int y : to[x][0])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y];
}

signed main() {
	File("cute");
	read(n), read(k);
	for(int o = 0; o < k; ++o) 
		for(int i = 2; i <= n; ++i)
			read(u), read(v), to[u][o].push_back(v), to[v][o].push_back(u);
	if(n <= 3000) {
		for(int o = 0; o < k; ++o)
			for(int i = 0; i < n; ++i)
				vis.set(), rt=i, sol(o, i, -1, 0);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) {
				int op = 0;
				for(int o = 0; o < k; ++o)
					op=max(op, mx[o][i][j]);
				ans+=op;
			}
		write(ans, '\n');
		return 0;
	}
	if(k == 1) {
		dfs(0, -1);
		gs[0]=1LL*n*n;
		int sss = 0, now = 1, ttt = 0, now2 = -1;
		LL sum = 1;
		for(int y : to[0][0]) {
			gs[0]-=1LL*siz[y]*sum*2, gs[1]+=1LL*siz[y]*sum*2;
			sum+=siz[y];
			if(dfn[y]+siz[y]-1 >= dfn[1] && dfn[y] <= dfn[1])
				sss=siz[y], ttt=y;
		}
		// debug(to[0][0].size(), "???\n");
		--gs[0], ++gs[1];
		for(int i = 1; i < n; ++i) {
			if(now2 != -1) {
				gs[i]-=1LL*siz[now]*siz[now2]*2;
				gs[i+1]+=1LL*siz[now]*siz[now2]*2;
			}
			else {
				gs[i]-=1LL*(n-sss)*siz[now]*2;
				gs[i+1]+=1LL*(n-sss)*siz[now]*2;
			}
			if(dfn[i+1]+siz[i+1]-1 >= dfn[now] && dfn[i+1] <= dfn[now])
				continue;
			if(dfn[now]+siz[now]-1 >= dfn[i+1] && dfn[now] <= dfn[i+1]) {
				now=i+1;
				continue;
			}
			if(now2 == -1) {
				if(dfn[ttt]+siz[ttt]-1 >= dfn[i+1] && dfn[ttt] <= dfn[i+1])
					break;//不能在0节点的同一个子树下
				now2=i+1;
			}
			else {
				if(dfn[i+1]+siz[i+1]-1 >= dfn[now2] && dfn[i+1] <= dfn[now2])
					continue;
				if(dfn[now2]+siz[now2]-1 >= dfn[i+1] && dfn[now2] <= dfn[i+1]) {
					now2=i+1;
					continue;
				}
				break;
			}
		}
		for(int i = 0; i <= n; ++i)
			ans=ans+1LL*i*gs[i];
		write(ans, '\n');
	}
	return 0;
}