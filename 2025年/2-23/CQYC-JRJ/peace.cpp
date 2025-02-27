#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, u, v, w, jp[N][22], dep[N], dfn[N], cnt, siz[N];
LL f[N], sum[N], tr[N];
vector <int> to[N];
struct qwq { int l, r, w; };
vector <qwq> pro[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
void add(int x, LL ww) {
	while(x <= n)
		tr[x]+=ww, x+=(x&(-x));
}
LL ask(int x, LL ret = 0) {
	while(x)
		ret+=tr[x], x-=(x&(-x));
	return ret;
}
void dfs(int x, int fa) {
	jp[x][0]=fa, dep[x]=dep[fa]+1;
	dfn[x]=++cnt, siz[x]=1;
	for(int i = 1; i <= 20; ++i)
		jp[x][i]=jp[jp[x][i-1]][i-1];
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y];
}
int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; --i)
		if(jp[x][i] && dep[jp[x][i]] >= dep[y])
			x=jp[x][i];
	for(int i = 20; i >= 0; --i)
		if(jp[x][i] && jp[y][i] && jp[x][i] != jp[y][i])
			x=jp[x][i], y=jp[y][i];
	return (x == y ? x : jp[x][0]);
}
void sol(int x, int fa) {
	for(int y : to[x])
		if(y != fa) 
			sol(y, x), sum[x]+=f[y], 
			add(dfn[y], -f[y]), add(dfn[y]+siz[y], f[y]);
	for(qwq y : pro[x]) {
		LL op = ask(dfn[y.l])+ask(dfn[y.r])+sum[x];
		f[x]=max(f[x], op+y.w);
		// debug(y.l, y.r, x, op, "???\n");
	}
	add(dfn[x], sum[x]), add(dfn[x]+siz[x], -sum[x]);
	f[x]=max(f[x], sum[x]);
	// debug(x, f[x], "!!!\n");
}

signed main() {
	File("peace");
	read(n), read(m);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	for(int i = 1; i <= m; ++i) {
		read(u), read(v), read(w);
		pro[lca(u, v)].push_back(qwq {u, v, w});
	}
	sol(1, 0);
	write(f[1], '\n');
	FastIO::flusher.~Flusher();
	return 0;
}
