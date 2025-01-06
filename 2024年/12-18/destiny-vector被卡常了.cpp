#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, u, v, mdep[N], son[N], dep[N], nb[N], tot, ans;
vector <int> to[N];
struct qwq { int f, g, h; };
vector <qwq> op[N];

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
inline int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs(int x, int fa) {
	mdep[x]=dep[x]=dep[fa]+1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), son[x]=(mdep[y] > mdep[son[x]] ? y : son[x]), mdep[x]=max(mdep[x], mdep[y]);
}
void sol(int x, int fa) {
	if(son[x]) 
		sol(son[x], x), nb[x]=nb[son[x]];
	else {
		nb[x]=++tot;
		op[tot].push_back(qwq {1, 0, 0});
		return ;
	}
	int now = nb[x], noww = 0;
	if(op[now].size() >= 2)
		ans=upd(ans+op[now][op[now].size()-2].h);
	op[now].push_back(qwq {1, 0, 0});
	for(int i = op[now].size()-1; i >= 0; --i)//找到原因了,这个的时间复杂度为O(n^2)的......
		op[now][i].g=(i >= 1 ? op[now][i-1].g : 0),
		op[now][i].h=(i >= 2 ? op[now][i-2].h : 0);
	for(int y : to[x]) 
		if(y != fa && y != son[x]) {
			sol(y, x);
			noww = nb[y];
			if(op[noww].size() >= 2)
				ans=upd(ans+1LL*op[noww][op[noww].size()-2].h*op[now][op[now].size()-1].f%mod);
			for(int i = op[noww].size()-1, j = op[now].size()-2; ~i; --i, --j)
				ans=upd(ans+upd(upd(1LL*op[now][j].h*op[noww][i].f%mod+(i >= 2 ? 1LL*op[noww][i-2].h*op[now][j].f%mod : 0))+(!i ? 0 : 1LL*op[now][j].g*op[noww][i-1].g%mod))), 
				op[now][j].h=upd(op[now][j].h+(i >= 2 ? op[noww][i-2].h : 0)), 
				op[now][j].h=upd(op[now][j].h+upd((!i ? 0 : 1LL*op[now][j].f*op[noww][i-1].g%mod)+1LL*op[now][j].g*op[noww][i].f%mod)), 
				op[now][j].g=upd(upd(op[now][j].g+1LL*op[now][j].f*op[noww][i].f%mod)+(!i ? 0 : op[noww][i-1].g)), 
				op[now][j].f=upd(op[now][j].f+op[noww][i].f);
			// debug(x, y, nb[x], "??? :\n");
			// for(int i = op[nb[x]].size()-1; i >= 0; --i)
			// 	debug(op[nb[x]][i].f, op[nb[x]][i].g, op[nb[x]][i].h, "?\n");
		}
}

signed main() {
	File("destiny");
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	sol(1, 0);
	write(ans, '\n');
	FastIO::flusher.~Flusher();
	return 0;
}
/*
7
1 2
1 3
1 5
4 6
7 6
6 1
*/