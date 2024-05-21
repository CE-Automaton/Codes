#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, m, a[8][75], b[2][8][78], tot, ans, anss, fx[4][2]={{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
struct qwq {
	int x, y;
}zhan[562];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void sol() {
	int now = 0, lst = 0;
	for(int o = 1; o <= n; ++o)
		for(int p = 1; p <= m; ++p)
			b[0][o][p]=a[o][p];
	for(int pp = 1; pp <= n*m; ++pp) {
		now^=1;
		for(int o = 1; o <= n; ++o)
			for(int p = 1; p <= m; ++p) {
				int pd = 0;
				for(int op = 0; op <= 3 && !pd; ++op) {
					int X = (o+fx[op][0]), Y = (p+fx[op][1]);
					if(X <= 0 || Y <= 0 || X > n || Y > m) continue;
					pd|=(b[now^1][X][Y] == (b[now^1][o][p]+2)%3);
				}
				b[now][o][p]=(pd ? (b[now^1][o][p]+2)%3 : b[now^1][o][p]);
			}
		int oo = 1;
		for(int o = 1; o <= n; ++o)
			for(int p = 1; p <= m; ++p) 
				oo&=(b[now][o][p] == b[now][1][1]);
		if(b[now][1][1] != b[now^1][1][1])
			lst=pp;
		if(oo) {
			++ans, anss=upd(anss+lst);
			return ;
		}
	}
}
void dfs(int x) {
	if(x == tot+1) {
		sol();
		return ;
	}
	for(int i = 0; i <= 2; ++i)
		a[zhan[x].x][zhan[x].y]=i, dfs(x+1);
}

signed main() {
	File("transform");
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) 
			read(a[i][j]);
	for(int j = 1; j <= m; ++j) 
		for(int i = 1; i <= n; ++i)
			if(a[i][j] == 3)
				zhan[++tot]=qwq {i, j};
	dfs(1);
	write(ans, ' '), write(anss, '\n');
	return 0;
}