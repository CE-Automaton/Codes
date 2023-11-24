#include <bits/stdc++.h>
using namespace std;
const int N = 2e3+5;
int n, m, qq, x, y, xx, yy, vis[N][N], fx[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char s[N][N];
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
	freopen("unicom.in", "r", stdin);
	freopen("unicom.out", "w", stdout);
	read(n), read(m), read(qq);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]+1);
	for(int i = 1; i <= qq; ++i) {
		read(x), read(y), read(xx), read(yy);
		int ans = 0;
		for(int a = x; a <= xx; ++a)
			for(int b = y; b <= yy; ++b) 
				vis[a][b]=0;
		for(int a = x; a <= xx; ++a)
			for(int b = y; b <= yy; ++b) 
				if(!vis[a][b] && s[a][b] == '1') {
					q.push(qwq {a, b});
					++ans;
					vis[a][b]=1;
					while(!q.empty()) {
						qwq it = q.front();
						q.pop();
						for(int o = 0; o <= 3; ++o) {
							int X = it.x+fx[o][0], Y = it.y+fx[o][1];
							if(X < x || X > xx || Y < y || Y > yy || s[X][Y] == '0' || vis[X][Y] == 1) continue;
							vis[X][Y]=1;
							q.push(qwq {X, Y});
						}
					}
				}
		write(ans, '\n');
	}
	return 0;
}
