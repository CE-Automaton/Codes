#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 15, M = 3e5+5;
int n, m, u[N], v[N], w[N], ds[N], mx[(1<<13)], fa[M], ww[M], cnt[M], dd[M], ggg;
struct qwq {
	int y, d;
};
vector <qwq> to[M];

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
void sol(int now) {
	for(int i = 1; i <= n; ++i)
		ds[i]=0;
	int mxx = 0, pd = 1;
	for(int j = 0; j < m; ++j)
		if((now>>j)&1)
			++ds[u[j]], ++ds[v[j]], mxx=max(mxx, w[j]);
	// for(int j = 0; j < m; ++j)
	// 	debug((now>>j)&1);
	for(int i = 1; i <= n; ++i)
		pd&=(ds[i]%2 == 1);
	// debug(' ', pd, "???\n");
	if(pd)
		mx[now]=mxx;
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}

signed main() {
	File("graph");
	read(n), read(m);
	if(n <= 10 && m <= 10) {
		for(int j = 0; j < (1<<m); ++j)
			mx[j]=inf;
		int ans = inf;
		for(int i = 0; i < m; ++i) {
			read(u[i]), read(v[i]), read(w[i]);
			for(int j = 0; j < (1<<i); ++j) 
				sol(j|(1<<i)), ans=min(ans, mx[j|(1<<i)]);
			if(ans == inf)
				puts("-1");
			else
				write(ans, '\n');
		}
		return 0;
	}
	// debug("sub2!\n");
	int l = 0, r = 0;
	for(int i = 1; i <= n; ++i)
		fa[i]=i, ww[i]=1, cnt[i]=1;
	int pdd = 0, tot = n;
	for(int i = 1; i <= m; ++i) {
		read(l), read(r), read(w[0]);
		if(pdd) {
			puts("1");
			continue;
		}
		int xx = find(l), yy = find(r);
		if(xx != yy) {
			if(ww[xx]%2 == 0)
				--ggg;
			if(ww[yy]%2 == 0)
				--ggg;
		}
		else {
			if(ww[xx]%2 == 0)
				--ggg;
		}
		if(dd[l]%2) --ww[xx];
		else ++ww[xx];
		if(dd[r]%2) --ww[yy];
		else ++ww[yy];
		++dd[l], ++dd[r];
		if(xx != yy) {
			if(cnt[xx] > cnt[yy]) swap(xx, yy);
			fa[xx]=yy, cnt[yy]+=cnt[xx], ww[yy]+=ww[xx];
			if(ww[yy]%2 == 0)
				++ggg;
			--tot;
		}
		else {
			if(ww[xx]%2 == 0)
				++ggg;
		}
		if(ggg == tot) 
			pdd|=1;
		if(pdd) 
			puts("1");
		else
			puts("-1");
	}
	return 0;
}