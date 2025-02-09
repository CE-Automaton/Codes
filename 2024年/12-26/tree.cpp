#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5, B = 2000;
int n, q, c, f, col[N], xx, ss, siz[N], ans[2005][35005], vis[N], tot, qu[N], hd, tl, ww[N], pp[N];
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
void solve(int x) {
	for(int i = 1; i <= n; ++i)
		ww[i]=0;
	hd=1, tl=0, qu[++tl]=x;
	ww[x]=(1<<col[x]);
	while(hd <= tl) {
		int now = qu[hd]; ++hd;
		for(int y : to[now])
			if(!ww[y]) {
				ww[y]=(ww[now]|(1<<col[y]));
				qu[++tl]=y;
			}
	}
	for(int i = 1; i <= n; ++i)
		++ans[vis[x]][ww[i]];
	for(int i = 0; i < c; ++i)
		for(int j = 1; j < (1<<c); ++j)
			if((j>>i)&1)
				ans[vis[x]][j]+=ans[vis[x]][j^(1<<i)];
}
void dfs(int x, int fa) {
	siz[x]=1;
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), siz[x]+=siz[y];
	if(siz[x] >= B)
		vis[x]=++tot, siz[x]=1, solve(x);
}

signed main() {
	File("tree");
	read(n), read(q), read(c);
	for(int i = 1; i <= n; ++i)
		read(col[i]);
	for(int i = 2; i <= n; ++i)
		read(f), to[f].push_back(i), to[i].push_back(f);
	dfs(1, 0);
	for(int i = 1; i <= q; ++i) {
		read(ss), read(xx);
		if(!((ss>>col[xx])&1)) {
			putchar('1'), putchar('\n');
			continue;
		}
		int gs = 1;
		hd=1, tl=1, qu[1]=xx;
		pp[xx]=1;
		while(hd <= tl && !vis[qu[tl]]) {
			int now = qu[hd]; ++hd;
			for(int y : to[now])
				if(!pp[y] && ((ss>>col[y])&1)) {
					pp[y]=1;
					++gs;
					qu[++tl]=y;
					if(vis[y]) break;
				}
		}
		if(vis[qu[tl]])
			write(ans[vis[qu[tl]]][ss], '\n');
		else
			write(gs, '\n');
		for(int i = 1; i <= tl; ++i)
			pp[qu[i]]=0;
	}
	FastIO::flusher.~Flusher();
	return 0;
}