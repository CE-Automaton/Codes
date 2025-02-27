#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, m, s[N][N], pd[N][N], t[N][N], fx[4][2]={{-1, 0}, {0, 1}, {1, 0}, {0, -1}}, vis[N][N][4], hd, tl,
dp[N][N][2];
struct qwq { int x, y, ww, nw; } zhan[N*N];
struct qvq { int a, b, s; } ls[N][N][2];

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

signed main() {
	File("prism");
	read(n), read(m);
	int oooo = 1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			read(s[i][j]), oooo&=((s[i][j]&1)^1);
	if(oooo) {
		for(int i = 1; i <= n; ++i, putchar('\n'))
			for(int j = 1; j <= m; ++j)
				putchar('0');
		return 0;
	}
	if(n <= 4 && m <= 4) {
		for(int i = 0; i < (1<<(n*m)); ++i) {
			for(int j = 0; j < n*m; ++j)
				if((i>>j)&1)
					t[j/m+1][j%m+1]=1;
			for(int xx = 1; xx <= n; ++xx)
				for(int yy = 1; yy <= m; ++yy) 
					for(int st = 0; st < 4; ++st) {
						// debug(xx, yy, st, ":???\n");
						vis[xx][yy][st]=1;
						zhan[hd=tl=1]=qwq {xx, yy, s[xx][yy], st};
						while(hd <= tl) {
							qwq it = zhan[hd]; ++hd;
							int X = it.x+fx[it.nw][0], Y = it.y+fx[it.nw][1];
							// debug(it.x, it.y, it.ww, it.nw, "!!!\n");
							if(X >= 1 && X <= n && Y >= 1 && Y <= m && !vis[X][Y][(it.nw+t[X][Y])%4]) {
								vis[X][Y][(it.nw+t[X][Y])%4]=1;
								pd[X][Y]^=(max(s[X][Y]-it.ww, 0)&1);
								zhan[++tl]=qwq {X, Y, max(s[X][Y], it.ww), (it.nw+t[X][Y])%4};
							}
						}
						for(int j = 1; j <= tl; ++j)
							vis[zhan[j].x][zhan[j].y][zhan[j].nw]=0;
					}
			int ppp = 1;
			for(int ii = 1; ii <= n; ++ii)
				for(int jj = 1; jj <= m; ++jj)
					ppp&=(t[ii][jj] == pd[ii][jj]);
			if(ppp) {
				for(int ii = 1; ii <= n; ++ii, putchar('\n'))
					for(int jj = 1; jj <= m; ++jj)
						putchar((char) '0'+t[ii][jj]);
				exit(0);
			}
			// for(int ii = 1; ii <= n; ++ii, debug('\n'))
			// 	for(int jj = 1; jj <= m; ++jj)
			// 		debug(t[ii][jj], "");
			// for(int ii = 1; ii <= n; ++ii, debug('\n'))
			// 	for(int jj = 1; jj <= m; ++jj)
			// 		debug(pd[ii][jj], "");
			// debug("------------\n");
			for(int ii = 1; ii <= n; ++ii)
				for(int jj = 1; jj <= m; ++jj)
					t[ii][jj]=pd[ii][jj]=0;
		}
		return 0;
	}
	dp[1][1][s[1][1]&1]=1;
	putchar('0');
	int j = 1;
	for(int i = 2; i <= m; ++i) {
		if(dp[i-1][j][0]) {
			if((j&(s[1][i]&1)) == 0)
				dp[i][j+1][((j+1)&(s[1][i]&1))]=1, 
				putchar('0'), ++j;
			else
				dp[i][1][s[1][i]&1]=1, 
				putchar('1'), j=1;
		}
		else
			if(dp[i-1][j][1]) {
				if((j&(s[1][i]&1)) == 1)
					dp[i][j+1][((j+1)&(s[1][i]&1))]=1, 
					putchar('0'), ++j;
				else
					dp[i][1][s[1][i]&1]=1, 
					putchar('1'), j=1;
			}
	}
	return 0;
}
