#include <bits/stdc++.h>
#define mod 998244353
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e7+5;
int n, m, k, R, C, dis[2][N], pw[N], ans, tot, zhan[N], sum, fx[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector <char> a[N];
queue <int> q[2];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	read(n), read(m), read(R), read(C);
	for(int i = 1; i <= n; ++i) {
		a[i].resize(m+4);
		for(int j = 1; j <= m; ++j)
			scanf(" %c", &a[i][j]), k+=(a[i][j] == '.');
	}
	pw[0]=1;
	for(int i = 1; i < k; ++i)
		pw[i]=2021LL*pw[i-1]%mod;
	for(int i = 1; i <= n*m; ++i)
		dis[0][i]=dis[1][i]=inf;
	for(int i = 1; i <= m; ++i)
		q[0].push(dd(n, i)), dis[1][dd(n, i)]=0;
	while(!q[0].empty() || !q[1].empty()) {
		int now = 0;
		if(q[1].empty() || (!q[0].empty() && dis[1][q[0].front()] < dis[1][q[1].front()]))
			now=q[0].front(), q[0].pop();
		else
			now=q[1].front(), q[1].pop();
		int i = (now-1)/m+1, j = (now-1)%m+1;
		// debug(i, j, dis[1][now], "?????\n");
		if(j-1 >= 1 && dis[1][now-1] > dis[1][now] && a[i][j-1] == '#' && a[i][j] == '#') 
			dis[1][now-1]=dis[1][now], q[0].push(now-1);
		if(j+1 <= m && dis[1][now+1] > dis[1][now] && a[i][j+1] == '#' && a[i][j] == '#') 
			dis[1][now+1]=dis[1][now], q[0].push(now+1);
		if(i+1 <= n && dis[1][now+m] > dis[1][now] && a[i+1][j] == '#' && a[i][j] == '#') 
			dis[1][now+m]=dis[1][now], q[0].push(now+m);
		if(i-1 >= 1 && dis[1][now-m] > dis[1][now]+(a[i][j] == '.')) 
			dis[1][now-m]=dis[1][now]+(a[i][j] == '.'), q[(a[i][j] == '.')].push(now-m);
	}
	q[0].push(dd(R, C)), dis[0][dd(R, C)]=0;
	while(!q[0].empty() || !q[1].empty()) {
		int now = 0;
		if(q[1].empty() || (!q[0].empty() && dis[0][q[0].front()] < dis[0][q[1].front()])) 
			now=q[0].front(), q[0].pop();
		else
			now=q[1].front(), q[1].pop();
		int i = (now-1)/m+1, j = (now-1)%m+1;
		if(j-1 >= 1 && dis[0][now-1] > dis[0][now] && a[i][j-1] == '#' && a[i][j] == '#') 
			dis[0][now-1]=dis[0][now], q[0].push(now-1);
		if(j+1 <= m && dis[0][now+1] > dis[0][now] && a[i][j+1] == '#' && a[i][j] == '#') 
			dis[0][now+1]=dis[0][now], q[0].push(now+1);
		if(i-1 >= 1 && dis[0][now-m] > dis[0][now] && a[i-1][j] == '#' && a[i][j] == '#') 
			dis[0][now-m]=dis[0][now], q[0].push(now-m);
		if(i+1 <= n && dis[0][now+m] > dis[0][now]+(a[i+1][j] == '.')) 
			dis[0][now+m]=dis[0][now]+(a[i+1][j] == '.'), q[(a[i+1][j] == '.')].push(now+m);
	}
	int g = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(a[i][j] == '.') {
				++g;
				ans=dis[1][dd(R, C)];
				tot=0;
				for(int o = 0; o < 4; ++o) {
					int X = i+fx[o][0], Y = j+fx[o][1];
					if(X >= 1 && X <= n && Y >= 1 && Y <= m && a[X][Y] == '#')
						zhan[++tot]=dd(X, Y);
				}
				zhan[++tot]=dd(i, j);
				for(int o = 1; o <= tot; ++o)
					for(int p = 1; p <= tot; ++p)
						ans=min(ans, dis[0][zhan[o]]+dis[1][zhan[p]]);
				if(i != 1)
					for(int o = 1; o <= tot; ++o)
						ans=min(ans, dis[1][zhan[o]]+dis[0][dd(i-1, j)]);
				// debug(i, j, ans, '\n');
				sum=upd(sum+1LL*pw[k-g]*(R+ans)%mod);
			}
	write(sum, '\n');
	return 0;
}