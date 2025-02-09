#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, q, c, fa[N], col[N], gs[N], up[N], ans[N], jp[N][22], wj[N][22], dn[N][22], wd[N][22], xx, ss;
vector <int> son[N];
struct pro { int x, d; };
vector <pro> que[N];

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
void dfs(int x) {
	if(x != 1) {
		jp[x][0]=fa[x];
		wj[x][0]=((1<<col[x])|(1<<col[fa[x]]));
		for(int i = 1; i <= 20; ++i)
			jp[x][i]=jp[jp[x][i-1]][i-1], 
			wj[x][i]=(wj[x][i-1]|wj[jp[x][i-1]][i-1]);
	}
	for(int y : son[x])
		dfs(y);
	if(x != n) {
		dn[x][0]=son[x][0];
		wd[x][0]=((1<<col[x])|(1<<col[son[x][0]]));
		for(int i = 1; i <= 20; ++i)
			dn[x][i]=dn[dn[x][i-1]][i-1], 
			wd[x][i]=(wd[x][i-1]|wd[dn[x][i-1]][i-1]);
	}
}
int sol(int x, int bk) {
	int ret = 1;
	for(int y : son[x])
		if(((ss>>col[y])&1) && y != bk)
			ret+=sol(y, x);
	if(((ss>>col[fa[x]])&1) && fa[x] != bk)
		ret+=sol(fa[x], x);
	return ret;
}
void cl(int x) {
	gs[x]=((ss>>col[x])&1);
	if(!up[x] && gs[x]) up[x]=x;
	for(int y : son[x])
		if((ss>>col[y])&1)
			up[y]=up[x], cl(y), gs[x]+=gs[y];
		else
			up[y]=0, cl(y);
}

signed main() {
	File("tree");
	read(n), read(q), read(c);
	for(int i = 1; i <= n; ++i)
		read(col[i]);
	int pd = 1;
	for(int i = 2; i <= n; ++i)
		read(fa[i]), son[fa[i]].push_back(i), 
		pd&=(fa[i] == i-1);
	if(pd) {//链的情况
		// debug("!!\n");
		dfs(1);
		for(int i = 1; i <= q; ++i) {
			read(ss), read(xx);
			if((ss>>col[xx])&1) {
				int ll = xx, rr = xx;
				for(int j = 20; j >= 0; --j)
					if(jp[ll][j] && (wj[ll][j]|ss) == ss)
						ll=jp[ll][j];
				for(int j = 20; j >= 0; --j)
					if(dn[rr][j] && (wd[rr][j]|ss) == ss)
						rr=dn[rr][j];
				write(rr-ll+1, '\n');
			}
			else
				putchar('1'), putchar('\n');
		}
		FastIO::flusher.~Flusher();
		return 0;
	}
	if(n <= 5000 && q <= 5000) {
		// debug("!\n");
		for(int i = 1; i <= q; ++i) {
			read(ss), read(xx);
			if((ss>>col[xx])&1) 
				write(sol(xx, 0), '\n');
			else
				putchar('1'), putchar('\n');
		}
		FastIO::flusher.~Flusher();
		return 0;
	}
	for(int i = 1; i <= q; ++i) {
		read(ss), read(xx);
		if((ss>>col[xx])&1) 
			que[ss].push_back(pro {xx, i});
		else
			ans[i]=1;
	}
	for(ss = 0; ss < (1<<c); ++ss) {
		if(que[ss].empty()) continue;
		up[1]=0;
		cl(1);
		for(pro i : que[ss])
			ans[i.d]=gs[up[i.x]];
	}
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	FastIO::flusher.~Flusher();
	return 0;
}