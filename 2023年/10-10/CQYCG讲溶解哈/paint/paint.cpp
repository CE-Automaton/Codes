#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e3+5;
int t, n, m, u, v, ans[N], tot, vis[N], zhan[N], siz[N][2];
vector <int> to[N];

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
void ddfs(int x, int fa, int p) {
	siz[x][p]=1;
	for(int o = 0, y = 0; o < to[x].size(); ++o) {
		y=to[x][o];
		if(y != fa)
			ddfs(y, x, p^1), siz[x][p]+=siz[y][p^1];
	}
}
void getans(int x, int fa, int p) {
	ans[x]=p;
	for(int o = 0, y = 0; o < to[x].size(); ++o) {
		y=to[x][o];
		if(y != fa)
			getans(y, x, p^1);
	}
} 
void soltree() {
	ddfs(1, 0, 0);
	if(siz[1][0] >= siz[1][1])
		getans(1, 0, 0);
	else
		getans(1, 0, 1);
}
int check(int x) {
	int siz = 1;
	vis[x]=1;
	for(int o = 0, y = 0; o < to[x].size(); ++o) {
		y=to[x][o];
		if(!vis[y] && ans[x] != ans[y])
			siz+=check(y);
	}
	return siz;
}
int dfs(int x) {
	if(x == n+1) {
		for(int i = 1; i <= n; ++i)
			vis[i]=0;
		return (check(1) == n);
	}
	ans[x]=0;
	if(dfs(x+1))
		return 1;
	ans[x]=1;
	if(dfs(x+1))
		return 1;
	ans[x]=2;
	if(dfs(x+1))
		return 1;
	return 0; 
}
void getans(int x, int p) {
	ans[x]=p;
	vis[x]=1;
	for(int o = 0, y = 0; o < to[x].size(); ++o) {
		y=to[x][o];
		if(!vis[y])
			getans(y, x, p^1);
	}
} 

signed main() {
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
	read(t);
	while(t--) {
		read(n), read(m);
		for(int i = 1; i <= m; ++i)
			read(u), read(v), to[u].push_back(v), to[v].push_back(u);
		int pd = 1;
		if(m == n-1) 
			soltree();
		else
			if(n <= 10) {
				if(!dfs(1))
					pd=0;
			}
			else
				getans(1, 0); 
		if(!pd) {
			putchar('-'), putchar('1'), putchar('\n');
			continue;
		}
		for(int i = 1; i <= n; ++i)
			putchar((ans[i] == 0 ? 'R' : (ans[i] == 1 ? 'G' : 'B')));
		putchar('\n');
	}
	return 0;
}
