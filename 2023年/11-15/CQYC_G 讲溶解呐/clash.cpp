#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, p, q, col[15][N], now[15][N], ans[N], op[N], u, v, w;
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

signed main() {
	freopen("clash.in", "r", stdin);
	freopen("clash.out", "w", stdout);
	read(n), read(m), read(p), read(q);
	for(int i = 1; i <= m; ++i) 
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= q; ++i)
		read(u), read(v), read(w), 
		col[w][v]=u, now[w][v]=i, ans[v]=u, op[v]=i;
	for(int i = 10; i >= 1; --i) 
		for(int x = 1; x <= n; ++x) {
			if(now[i][x] == 0) continue;
			if(now[i][x] > op[x])
				op[x]=now[i][x], ans[x]=col[i][x];
			for(int y : to[x]) {
				if(now[i][x] > now[i-1][y]) 
					now[i-1][y]=now[i][x], col[i-1][y]=col[i][x];
				if(now[i][x] > op[y])
					op[y]=now[i][x], ans[y]=col[i][x];
			}
		}
	for(int x = 1; x <= n; ++x) 
		if(now[0][x] > op[x])
			op[x]=now[0][x], ans[x]=col[0][x];
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}
