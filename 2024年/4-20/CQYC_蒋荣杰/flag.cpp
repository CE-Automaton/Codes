#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, m, q, l, r, c[N][N], fa[N*N], cnt[N*N], ans[N][N];

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
int dd(int x, int y) {
	return (x-1)*m+y;
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
int merge(int x, int y) {
	x=find(x), y=find(y);
	if(x == y) return 0;
	if(cnt[x] > cnt[y]) swap(x, y);
	fa[y]=x, cnt[x]+=cnt[y];
	return 1;
}

signed main() {
	File("flag");
	read(n), read(m), read(q);
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= m; ++j)
			read(c[i][j]);
	for(int i = 1; i <= m; ++i) {
		for(int j = i; j <= m; ++j) {
			ans[i][j]=ans[i][j-1];
			for(int k = 1; k <= n; ++k)
				fa[dd(k, j)]=dd(k, j);
			for(int k = 1; k < n; ++k)
				if(c[k][j] == c[k+1][j])
					fa[dd(k+1, j)]=fa[dd(k, j)], ++cnt[fa[dd(k, j)]], ++ans[i][j];
			if(j != i)
				for(int k = 1; k <= n; ++k)
					if(c[k][j] == c[k][j-1])
						ans[i][j]+=merge(dd(k, j-1), dd(k, j));
		}
	}
	for(int i = 1; i <= q; ++i) {
		read(l), read(r);
		write((r-l+1)*n-ans[l][r], '\n');
	}
	return 0;
}