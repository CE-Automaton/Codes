#include <bits/stdc++.h>
using namespace std;
int t, k, c[45][45], ans[45][45], n, m; 

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
int dfs(int now, int lst, int kk) {
	if(kk == 0) 
		return 1;
	if(now > n || lst == 1)
		return 0;
	if(dfs(now+1, lst, kk)) return 1;
	for(int i = min(lst-1, m); i >= 1; --i) {
		if(now == 1 && i == 1) return 0;
		ans[now][i]=1;
		long long qwq = 1LL*c[now+i-2][i-1]*c[n-now+m-i][m-i];
		if(qwq <= (long long) kk) 
			if(dfs(now+1, i, kk-qwq))
				return 1;
		ans[now][i]=0;
	}
	return 0;
}

signed main() {
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w", stdout);
	read(t);
	for(int i = 0; i <= 40; ++i)
		c[i][0]=1;
	for(int i = 1; i <= 40; ++i)
		for(int j = 1; j <= i; ++j)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	while(t--) {
		read(k);
		for(int i = 1; i <= 18; ++i)
			for(int j = 1; j <= 18; ++j)
				ans[i][j]=0;
		int pd = 1;
		ans[1][1]=1;
		for(n = 1; n <= 18; ++n) {
			for(m = 18; m >= 1; --m) {
				if(c[n+m-2][n-1] < k) 
					continue;
				if(dfs(1, 18, k)) {
					pd=0;
					break;
				}
			}
			if(pd == 0)
				break;
		}
		write(n, ' '), write(m, '\n');
		for(int i = 1; i <= n; ++i, putchar('\n'))
			for(int j = 1; j <= m; ++j)
				write(ans[i][j], ' ');
	}
	return 0;
}
