#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, m, u, v, dis[2][N];
char s[2][N];
struct qwq {
	int x, y;
};
queue <qwq> q;

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
	freopen("family.in", "r", stdin);
	freopen("family.ans", "w", stdout);
	read(n), read(m);
	scanf("%s\n%s", s[0]+1, s[1]+1);
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		qwq ou = qwq {(u-1)/n, (u-1)%n+1}, ov = qwq {(v-1)/n, (v-1)%n+1};
		if(ou.y > ov.y)
			swap(ou, ov);
		memset(dis, 0, sizeof dis);
		dis[ou.x][ou.y]=1;
		q.push(qwq {ou.x, ou.y});
		while(!q.empty()) {
			qwq it = q.front(); q.pop();
			if(s[it.x][it.y] == 'X') continue;
			if(s[it.x^1][it.y] == '.' && dis[it.x^1][it.y] == 0)
				dis[it.x^1][it.y]=dis[it.x][it.y]+1, q.push(qwq {it.x^1, it.y});
			if(s[it.x][it.y+1] == '.' && it.y+1 <= n && dis[it.x][it.y+1] == 0)
				dis[it.x][it.y+1]=dis[it.x][it.y]+1, q.push(qwq {it.x, it.y+1});
			if(s[it.x][it.y-1] == '.' && it.y-1 >= 1 && dis[it.x][it.y-1] == 0)
				dis[it.x][it.y-1]=dis[it.x][it.y]+1, q.push(qwq {it.x, it.y-1});
		}
		write(dis[ov.x][ov.y]-1, '\n');
	}
	return 0;
}
