#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e6+5;
int n, q, LCA, lcc, MN, u, v, jp[N][25], mn[N][25], dep[N];
char s[8];
vector <int> to[N];

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
void dfs(int x, int fa) {
	jp[x][0]=mn[x][0]=fa;
	for(int i = 1; i <= 20 && jp[x][i-1]; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1], 
		mn[x][i]=min(mn[x][i-1], mn[jp[x][i-1]][i-1]);
	dep[x]=dep[fa]+1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x);
}
int lca(int x, int y, int pd = 0) {
	if(dep[x] < dep[y]) swap(x, y);
	int mnn = min(x, y);
	for(int j = 20; j >= 0; --j)
		if(dep[jp[x][j]] >= dep[y])
			mnn=min(mnn, mn[x][j]), x=jp[x][j];
	for(int j = 20; j >= 0; --j)
		if(jp[x][j] != jp[y][j])
			mnn=min(mnn, min(mn[x][j], mn[y][j])), 
			x=jp[x][j], y=jp[y][j];
	if(x != y)
		x=jp[x][0], mnn=min(mnn, x);
	if(pd)
		return mnn;
	return x;
}

signed main() {
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
	read(n), read(q);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	MN=1000000009;
	dfs(1, 0);
	for(int i = 1; i <= q; ++i) {
		char gt = gc();
		while(gt < 'A' || gt > 'Z') gt = gc();
		if(gt == 'J') {
			read(u);
			if(LCA == 0) 
				LCA=MN=u;
			else {
				lcc = lca(u, LCA);
				MN=min(MN, min(lca(u, lcc, 1), lca(LCA, lcc, 1)));
				LCA=lcc;
			}
		}
		else {
			read(u);
			write(min(MN, lca(u, LCA, 1)), '\n');
		}
	}
	FastIO::flusher.~Flusher(); 
	return 0;
}
