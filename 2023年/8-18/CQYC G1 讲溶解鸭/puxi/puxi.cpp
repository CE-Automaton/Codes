#include <bits/stdc++.h>
using namespace std;
int n, m, q, opt, xx, k, a[55][55], dis[55][55], fx[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct qwq {
	int x, y;
}s, t;
queue <qwq> qq;

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
	freopen("puxi.in", "r", stdin);
	freopen("puxi.out", "w", stdout);
	read(n), read(m), read(q);
	for(int i = 1; i <= q; ++i) {
		read(opt);
		if(opt == 1) {
			read(xx);
			for(int j = 1; j <= m; ++j)
				a[xx][j]=i;
		}
		if(opt == 2) {
			read(xx);
			for(int j = 1; j <= n; ++j)
				a[j][xx]=i;
		}
		if(opt == 3) {
			read(s.x), read(s.y), read(t.x), read(t.y), read(k);
			if(a[s.x][s.y] < k || a[t.x][t.y] < k) {
				puts("-1");
				continue;
			}
			memset(dis, 0, sizeof dis);
			dis[s.x][s.y]=1;
			qq.push(qwq {s.x, s.y});
			while(!qq.empty()) {
				qwq it = qq.front(); qq.pop();
				for(int j = 0; j <= 3; ++j) {
					int X=it.x+fx[j][0], Y=it.y+fx[j][1];
					if(X <= 0 || X > n || Y <= 0 || Y > m || a[X][Y] < k || dis[X][Y] != 0)
						continue;
					dis[X][Y]=dis[it.x][it.y]+1;
					qq.push(qwq {X, Y});
				}
			}
			write(dis[t.x][t.y]-1, '\n');
		}
	}
	return 0;
}
