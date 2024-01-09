#include <bits/stdc++.h>
#define inf 1000000000000000000LL
#define CLK (double)clock()/(double)CLOCKS_PER_SEC*1000.0
#define LL long long
using namespace std;
const int N = 1e5+5;
int n, u, v, too;
LL ans, w, dis[3][N], vis[N];
struct qwq {
	int t;
	LL w;
};
vector <qwq> to[3][N];

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
void dfs(int now, int x, int fa) {
	for(qwq y : to[now][x])
		if(y.t != fa && dis[now][y.t] == inf)
			dis[now][y.t]=dis[now][x]+y.w, 
			dfs(now, y.t, x);
}
void sol(int x) {
	for(int o = 0; o <= 2; ++o) {
		for(int i = 1; i <= n; ++i)
			dis[o][i]=inf;
		dis[o][x]=0;
		dfs(o, x, x);
	}
	return ;
}

signed main() {
	srand(149816921);
	double st = CLK;
	read(n);
	for(int o = 0; o <= 2; ++o)
		for(int i = 1; i <= n-1; ++i)
			read(u), read(v), read(w), 
			to[o][u].push_back(qwq {v, w}), 
			to[o][v].push_back(qwq {u, w});
	if(n <= 3000) 
		for(int i = 1; i <= n; ++i) {
			sol(i);
			for(int j = 1; j <= n; ++j) {
				LL sm = dis[0][j]+dis[1][j]+dis[2][j];
				ans=max(ans, sm);
			}
		}
	else {
		int rt = rand()%n+1;
		while(CLK-st <= 3300) {
			do rt=rand()%n+1; while(vis[rt]);
			for(int t = 1; t <= 10; ++t) {
				if(vis[rt]) break;
				vis[rt]=1;
				sol(rt);
				LL mx = 0;
				for(int i = 1; i <= n; ++i) {
					LL sm = dis[0][i]+dis[1][i]+dis[2][i];
					ans=max(ans, sm);
					if(sm > mx && !vis[i]) 
						mx=sm, rt=i;
				}
			}
		}
	}
	write(ans, '\n');
	return 0;
}
