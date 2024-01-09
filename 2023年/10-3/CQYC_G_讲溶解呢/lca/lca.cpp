#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, u, v, siz[N];
__int128 ans[N];
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
	siz[x]=1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y];
	for(int y : to[x])
		if(y != fa)
			ans[1]+=(__int128) x*siz[y]*(siz[x]-siz[y]-1);
	ans[1]+=(__int128) 2*x*siz[x]-x;
}
void dfs2(int x, int fa) {
	for(int y : to[x]) 
		if(y != fa) {
			ans[y]=ans[x]+((__int128) 2*(y-x)*(n-siz[y])*(siz[y]));
			dfs2(y, x);
		}
}

signed main() {
	freopen("lca.in", "r", stdin);
	freopen("lca.out", "w", stdout);
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	dfs2(1, 0);
	for(int i = 1; i <= n; ++i)
		write(ans[i], ' ');
	FastIO::flusher.~Flusher(); 
	return 0;
}
