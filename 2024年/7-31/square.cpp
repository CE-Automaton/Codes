#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e4+5, V = 2e6, base=2000003, mod=1e9+7;
int n, q, a, b, pri[V+5], cnt, vis[V+5], tot, bl[N], jp[N][20], dep[N];
vector <int> to[N], pp[V+5];
unordered_map <int, int> viss[25];
bitset <N> nw[N], ss;

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
	nw[x][bl[x]]=(nw[x][bl[x]]^1);
    dep[x]=dep[fa]+1;
    jp[x][0]=fa;
    for(int i = 1; i <= 16; ++i)
        jp[x][i]=jp[jp[x][i-1]][i-1];
    for(int y : to[x])
        if(y != fa) 
            nw[y]=nw[x], dfs(y, x);
}
int lca(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 16; i >= 0; --i)
        if(dep[jp[x][i]] >= dep[y])
            x=jp[x][i];
    for(int i = 16; i >= 0; --i)
        if(jp[x][i] != jp[y][i])
            x=jp[x][i], y=jp[y][i];
    return (x == y ? x : jp[x][0]);
}

signed main() {
	// File("square");
	for(int i = 2; i <= V; ++i) {
		if(!vis[i])
			pri[++cnt]=i, pp[i].push_back(i);
		for(int j = 1; j <= cnt && V/pri[j] >= i; ++j) {
			vis[i*pri[j]]=1;
			pp[i*pri[j]]=pp[i]; pp[i*pri[j]].push_back(pri[j]);
			if(i%pri[j] == 0) break;
		}
	}
	cnt=0;
	read(n), read(q);
	for(int i = 1; i <= n; ++i) {
		read(a);
		int hs = 0;
		tot=0;
		for(int j = 0; j < pp[a].size(); ++j) {
			int r = j;
			while(r+1 < pp[a].size() && pp[a][r+1] == pp[a][j])
				++r;
			if((r-j+1)%2)
				++tot, hs=(1LL*hs*base%mod+pp[a][j])%mod;
			j=r;
		}
		// cout<<hs<<"\n";
		if(viss[tot].find(hs) == viss[tot].end())
			viss[tot][hs]=++cnt;
		bl[i]=viss[tot][hs];
		// debug(i, bl[i],"!\n");
	}
	for(int i = 2; i <= n; ++i)
		read(a), read(b), to[a].push_back(b), to[b].push_back(a);
	dfs(1, 0);
	for(int i = 1; i <= q; ++i) {
		read(a), read(b);
		int op = lca(a, b);
		ss.reset();
		ss=((nw[a])^(nw[b]));
		ss[bl[op]]=(ss[bl[op]]^1);
		// for(int j = 1; j <= n; ++j)
		// 	debug(nw[a][j]);
		// debug('\n');
		// for(int j = 1; j <= n; ++j)
		// 	debug(nw[b][j]);
		// debug('\n');
		if(ss.count() == dep[a]+dep[b]-dep[op]-dep[jp[op][0]])
			puts("No");
		else
			puts("Yes");
	}
	return 0;
}