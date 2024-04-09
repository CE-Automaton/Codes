#include <bits/stdc++.h>
#define mod 1000000007
#define inv2 (mod-mod/2)
#define inf 1000000
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 155;
int t, h, w, n, u, v, pd[N][N], fx[4][2]={{-1, 0}, {1, 0}, {0, 1}, {0, -1}}, ans, dis[N][N];
struct qwq { int x, y; };
queue <qwq> q;

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

signed main() {
	File("dist");
	read(t);
	while(t--) {
		read(h), read(w), read(n);
		for(int i = 1; i <= h; ++i)
			for(int j = 1; j <= w; ++j)
				pd[i][j]=1;
		for(int i = 1; i <= n; ++i) 
			read(u), read(v), pd[u][v]=0;
		for(int i = 1; i <= h; ++i)
			for(int j = 1; j <= w; ++j) 
				if(pd[i][j]) {
					for(int ii = 1; ii <= h; ++ii)
						for(int jj = 1; jj <= w; ++jj)
							dis[ii][jj]=(pd[ii][jj] ? inf : 0);
					dis[i][j]=0;
					q.push(qwq {i, j});
					while(!q.empty()) {
						int X = q.front().x, Y = q.front().y;
						q.pop();
						for(int o = 0; o < 4; ++o) {
							int x = X+fx[o][0], y = Y+fx[o][1];
							if(x <= 0 || x > h || y <= 0 || y > w || !pd[x][y] || dis[x][y] != inf) continue;
							dis[x][y]=dis[X][Y]+1;
							q.push(qwq {x, y});
						}
					}
					for(int ii = 1; ii <= h; ++ii)
						for(int jj = 1; jj <= w; ++jj)
							ans=upd(ans+dis[ii][jj]);
				}
		write(1LL*ans*inv2%mod, '\n');
	}
	return 0;
}