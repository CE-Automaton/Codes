#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int t, n, m, a[N], b[N], c[N], ans, vis[N];

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
int pd() {
	for(int i = 1; i <= m; ++i)
		if(c[i] < a[i])
			return 2;
		else
			if(a[i] < c[i])
				return 3;
	return 1;
}
int chck(int x, int nw, int ls) {
	if(nw == 0) {
		c[m]=ls;
		return pd();
	}
	if(x == 0)
		return 3;
	int ret = 3;
	c[nw]=b[x];
	ret&=chck(x-1, nw-1, ls);
	if(x > nw) 
		ret&=chck(x-1, nw, ls);
	return ret;
} 
void dfs(int x) {
	if(x == n+1) {
		int pd = 0;
		for(int p = m; p <= n; ++p)
			if(chck(p-1, m-1, b[p]) == 1)
				pd|=1;
		if(pd == 1)
			++ans;
		return ;
	}
	for(int i = 1; i <= n; ++i) 
		if(vis[i] == 0 && (x < m || (x >= m && (chck(x-1, m-1, i)&1)))) {
			b[x]=i;
			vis[i]=1;
			dfs(x+1);
			vis[i]=0;
		}
}

signed main() {
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
	read(t);
	while(t--) {
		read(n), read(m);
		for(int i = 1; i <= m; ++i)
			read(a[i]);
		for(int i = 1; i <= n; ++i)
			vis[i]=0;
		dfs(1);
		write(ans, '\n');
	}
	return 0;
}
