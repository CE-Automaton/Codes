#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e6+5;
int n, u, v, ans, sum, ds[N], dep[N], col[N];
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
void dfs(int x, int fa, int gfa) {
	if(col[x] == col[gfa])
		sum=max(sum, dep[x]);
	for(int y : to[x])
		if(y != fa)
			dep[y]=dep[x]+1, dfs(y, x, gfa);
}
void dfss(int x) {
	if(x == n+1) {
		sum = 0;
		for(int i = 1; i <= n; ++i)
			dep[i]=0, dfs(i, 0, i);
		ans+=sum;
		return ;
	}
	col[x]=0;
	dfss(x+1);
	col[x]=1;
	dfss(x+1);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n-1; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u), ++ds[u], ++ds[v];
	if(n <= 10) {
		dfss(1);
		write(ans, '\n');
		return 0;
	}
	if(ds[1] == n-1) {
		if(n == 2) 
			write(2, '\n');
		else
			if(n == 3) 
				write(12, '\n');
			else
				write(upd(2*ksm(2, n)), '\n');
		return 0;
	}
	return 0;
}
