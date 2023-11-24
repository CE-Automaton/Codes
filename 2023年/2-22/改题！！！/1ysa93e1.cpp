#include <bits/stdc++.h>
using namespace std;
int n, m, lu[1005][1005], rd[1005][1005], pt[1005][1005], l, r, ans, vis[1005][1005], az, 
fx[4][2]={{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char s[1005][1005];
struct qwq {
	int x, y;
};
int check(int x) {
	int nd = az;
	queue <qwq> bfs;
	while(!bfs.empty()) bfs.pop();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			if(s[i][j] == '.') continue;
			vis[i][j]=0;
			if(pt[i][j] >= x) vis[i][j]=x, --nd, bfs.push(qwq{i, j});
		}
	while(!bfs.empty()) {
		qwq it = bfs.front(); bfs.pop();
		if(vis[it.x][it.y] == 1) continue;
		for(int i = 0; i < 4; ++i) {
			int X=it.x+fx[i][0], Y=it.y+fx[i][1];
			if(s[X][Y] == '.' || vis[X][Y] != 0) continue;
			--nd, bfs.push(qwq{X, Y});
			vis[X][Y]=vis[it.x][it.y]-1;
		}
	}
//	for(int i = 1; i <= n; ++i, putchar('\n'))
//		for(int j = 1; j <= m; ++j, putchar(' ')) 
//			cout<<vis[i][j];cout<<x<<" "<<nd<<"!!!\n";
	if(nd == 0) return 1;
	return 0;
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
			++az;
			lu[i][j]=min(lu[i-1][j], lu[i][j-1])+1;
		}
	for(int i = n-1; i >= 2; --i)
		for(int j = m-1; j >= 2; --j) {
			if(s[i][j] == '.') continue;
			rd[i][j]=min(rd[i+1][j], rd[i][j+1])+1;
		}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			pt[i][j]=min(lu[i][j], rd[i][j]), r=max(r, pt[i][j])+5;
	l=1;
//	cout<<check(1)<<"?\n";exit(0);
	while(l <= r) {
		int mid = ((l+r)>>1);
		if(check(mid)) 
			ans=mid, l=mid+1;
		else
			r=mid-1;
	}
	printf("%d\n", ans-1);
	return 0;
}
