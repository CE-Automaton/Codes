#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 305;
int n, m, l[N], r[N], fa[N], ll[N], rr[N], cc[N], vis[N], viss[N], zhan[N], ans[N], tot, op, siz[N];

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
int dfs(int x) {
	if(x == n+1) {
		int pd = 1;
		for(int i = 1; i <= m; ++i) {
			for(int j = 1; j <= n; ++j)
				viss[j]=0;
			int xx = zhan[ll[i]];
			while(xx)
				viss[xx]=1, xx=fa[xx];
			xx=zhan[rr[i]];
			while(!viss[xx])
				xx=fa[xx];
			pd&=(xx == cc[i]);
		}
		return pd;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			zhan[x]=i, vis[i]=1;
			if(dfs(x+1))
				return 1;
			vis[i]=0;
		}
	return 0;
}
void ddfs(int x) {
	siz[x]=1;
	if(!l[x]) return ;
	ddfs(l[x]);
	ddfs(r[x]);
	siz[x]+=siz[l[x]]+siz[r[x]];
}
void dddfs(int x) {
	zhan[++tot]=x;
	if(!l[x]) return ;
	dddfs(l[x]);
	dddfs(r[x]);
}

signed main() {
	File("final");
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(l[i]), read(r[i]), fa[l[i]]=i, fa[r[i]]=i;
	int xz = 1;
	for(int i = 1; i <= m; ++i)
		read(ll[i]), read(rr[i]), read(cc[i]), xz&=(cc[i] == 1);
	if(dfs(1))
		for(int i = 1; i <= n; ++i)
			write(zhan[i], ' ');
	return 0;
}