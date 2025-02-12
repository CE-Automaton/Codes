#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, w[N], u, v, gs, tot, zhan[N], rt[N], siz[N], ans[N];
vector <int> to[N];
struct qwq { int vis[2], cnt, ww; } tr[N*30];

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
void upup(int now, int dep) {
	tr[now].ww=0;
	tr[now].cnt=0;
	if(tr[now].vis[0] && tr[now].vis[1]) {
		tr[now].ww=max(tr[tr[now].vis[0]].ww, tr[tr[now].vis[1]].ww);
		tr[now].cnt=tr[tr[now].vis[0]].cnt+tr[tr[now].vis[1]].cnt;
		// debug(dep, "!!!\n");
		if(tr[tr[now].vis[0]].cnt == 1) {
			int xx = tr[now].vis[0], yy = tr[now].vis[1], ww = (1<<dep);
			for(int i = dep-1; i >= 0; --i) {
				if(tr[xx].vis[0]) {
					xx=tr[xx].vis[0];
					if(tr[yy].vis[0])
						yy=tr[yy].vis[0];
					else
						yy=tr[yy].vis[1], ww+=(1<<i);
				}
				else {
					xx=tr[xx].vis[1];
					if(tr[yy].vis[1])
						yy=tr[yy].vis[1];
					else
						yy=tr[yy].vis[0], ww+=(1<<i);
				}
			}
			tr[now].ww=max(tr[now].ww, ww);
		}
		if(tr[tr[now].vis[1]].cnt == 1) {
			int xx = tr[now].vis[1], yy = tr[now].vis[0], ww = (1<<dep);
			for(int i = dep-1; i >= 0; --i) {
				if(tr[xx].vis[0]) {
					xx=tr[xx].vis[0];
					if(tr[yy].vis[0])
						yy=tr[yy].vis[0];
					else
						yy=tr[yy].vis[1], ww+=(1<<i);
				}
				else {
					xx=tr[xx].vis[1];
					if(tr[yy].vis[1])
						yy=tr[yy].vis[1];
					else
						yy=tr[yy].vis[0], ww+=(1<<i);
				}
			}
			tr[now].ww=max(tr[now].ww, ww);
		}
	}
	else {
		if(tr[now].vis[0])
			tr[now].ww=tr[tr[now].vis[0]].ww, tr[now].cnt=tr[tr[now].vis[0]].cnt;
		if(tr[now].vis[1])
			tr[now].ww=tr[tr[now].vis[1]].ww, tr[now].cnt=tr[tr[now].vis[1]].cnt;
	}
}
void add(int st, int x) {
	zhan[tot=1]=st;
	++tr[st].cnt;
	for(int i = 16; i >= 0; --i) {
		int &to = tr[st].vis[((x>>i)&1)];
		if(!to) to=++gs;
		++tr[to].cnt;
		st=to;
		zhan[++tot]=st;
	}
	for(int i = tot-1; i >= 1; --i)
		upup(zhan[i], tot-i-1);
}
int merge(int x, int y, int dep) {
	if(!x || !y) return (x|y);
	if(dep == -1) {
		tr[x].cnt+=tr[y].cnt;
		tr[x].ww=0;
		return x;
	}
	tr[x].vis[0]=merge(tr[x].vis[0], tr[y].vis[0], dep-1);
	tr[x].vis[1]=merge(tr[x].vis[1], tr[y].vis[1], dep-1);
	upup(x, dep);
	return x;
}
void dfs(int x, int fa) {
	siz[x]=1;
	add(rt[x], w[x]);
	for(int y : to[x])
		if(y != fa)
			dfs(y, x), rt[x]=merge(rt[x], rt[y], 16), siz[x]+=siz[y];
	if(siz[x] == 1)
		ans[x]=-1;
	else
		ans[x]=tr[rt[x]].ww;
}

signed main() {
	read(n);
	for(int i = 1; i <= n; ++i)
		read(w[i]), rt[i]=i;
	gs=n;
	for(int j = 2; j <= n; ++j)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	FastIO::flusher.~Flusher();
	return 0;
}