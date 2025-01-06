#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, u, v, mdep[N], son[N], dd[N<<4], *ppp=dd, tot, ans, *f[N], *g[N], *h[N];
vector <int> to[N];

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
	mdep[x]=1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), son[x]=(mdep[y] > mdep[son[x]] ? y : son[x]), mdep[x]=max(mdep[x], mdep[y]+1);
}
void sol(int x, int fa) {
	if(son[x]) 
		f[son[x]]=f[x]+1, g[son[x]]=g[x], h[son[x]]=h[x]-1, sol(son[x], x);
	ans=upd(ans+h[x][0]);
	f[x][0]=1;
	for(int y : to[x]) 
		if(y != fa && y != son[x]) {
			f[y]=ppp, ppp+=2*mdep[y], g[y]=ppp, ppp+=2*mdep[y], h[y]=ppp, ppp+=2*mdep[y];
			sol(y, x);
			ans=upd(ans+1LL*h[y][1]*f[x][0]%mod), h[x][0]=upd(h[x][0]+h[y][1]);
			for(int i = 1; i <= mdep[y]; ++i)
				ans=upd(ans+upd(1LL*h[x][i]*f[y][i-1]%mod+upd(1LL*f[x][i]*h[y][i+1]%mod+1LL*g[x][i]*g[y][i]%mod))), h[x][i]=upd(h[x][i]+h[y][i+1]), h[x][i]=upd(h[x][i]+upd(1LL*g[x][i]*f[y][i-1]%mod+1LL*f[x][i]*g[y][i]%mod)), g[x][i]=upd(upd(g[x][i]+1LL*f[x][i]*f[y][i-1]%mod)+g[y][i]), f[x][i]+=f[y][i-1];
		}
}

signed main() {
	File("destiny");
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	f[1]=ppp, ppp+=2*mdep[1], g[1]=ppp, ppp+=2*mdep[1], h[1]=ppp, ppp+=2*mdep[1];
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