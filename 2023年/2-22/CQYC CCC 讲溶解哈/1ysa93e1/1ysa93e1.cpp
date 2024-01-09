#include <bits/stdc++.h>
using namespace std;
int n, m, lu[1005][1005], rd[1005][1005], pt[1005][1005], vis[1005][1005], az[1005][1005], cnt, ans=1000005, 
fx[4][2]={{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char s[1005][1005];
struct qwq {
	int x, y;
}sx[1000005];
int comp(qwq A, qwq B) {
	return pt[A.x][A.y] > pt[B.x][B.y];
}
void solve(int x, int y, int ss) {
	queue <qwq> t;
	vis[x][y]=ss;
	az[x][y]=(az[x][y] < ss ? ss : az[x][y]);
	t.push(qwq{x, y});
	while(!t.empty()) {
		qwq it = t.front(); t.pop();
//		cout<<it.x<<" "<<it.y<<" "<<vis[it.x][it.y]<<" "<<pt[it.x][it.y]<<"\n";
		if(vis[it.x][it.y] == 1) continue;
		for(int i = 0; i < 4; ++i) {
			int X=it.x+fx[i][0], Y=it.y+fx[i][1];
			if(s[X][Y] == '.') continue;
			if(vis[X][Y] < vis[it.x][it.y])
				vis[X][Y]=vis[it.x][it.y]-1, t.push(qwq{X, Y});
			az[X][Y]=(az[X][Y] < ss ? ss : az[X][Y]);
		}
	}
}
int main() {
	freopen("1ysa93e1.in", "r", stdin);
	freopen("1ysa93e1.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]+1);
	for(int i = 2; i <= n-1; ++i) 
		for(int j = 2; j <= m-1; ++j) {
			if(s[i][j] == '.') continue;
			lu[i][j]=min(lu[i-1][j], lu[i][j-1])+1;
		}
	for(int i = n-1; i >= 2; --i)
		for(int j = m-1; j >= 2; --j) {
			if(s[i][j] == '.') continue;
			rd[i][j]=min(rd[i+1][j], rd[i][j+1])+1;
		}
	for(int i = 1; i <= n; ++i/*, putchar('\n')*/)
		for(int j = 1; j <= m; ++j)
			pt[i][j]=min(lu[i][j], rd[i][j])/*, cout<<pt[i][j]<<" "*/;
	for(int i = 2; i <= n-1; ++i)
		for(int j = 2; j <= m-1; ++j) {
			if(s[i][j] == '.') continue; 
			sx[++cnt]=qwq{i, j};
		}
	sort(sx+1, sx+1+cnt, comp);
	for(int i = 1; i <= cnt; ++i)
		if(vis[sx[i].x][sx[i].y] < pt[sx[i].x][sx[i].y])
			solve(sx[i].x, sx[i].y, pt[sx[i].x][sx[i].y]);
//	for(int i = 1; i <= n; ++i, putchar('\n'))
//		for(int j = 1; j <= m; ++j)
//			cout<<az[i][j]<<" ";
	for(int i = 2; i <= n-1; ++i)
		for(int j = 2; j <= m-1; ++j) {
			if(s[i][j] == '.') continue; 
			ans=min(ans, az[i][j]-1);
		}
	printf("%d\n", ans);
	return 0;
}
