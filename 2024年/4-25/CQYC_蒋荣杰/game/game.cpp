#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, m, u, v, col[N];
vector <int> to[N];

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
int pdd(int w) {
	for(int i = 1; i <= n+n; ++i)
		for(int j : to[i])
			if(((w>>(i-1))&1) && !((w>>(j-1))&1))
				return 1;
	return 0;
}
int dfs(int x, int w) {
	if(x == n+1)
		return (pdd(w)^(n%2 == 1 ? 0 : 1));
	int ret = ((dfs(x+1, w|(1<<(2*x-2)))^1)|(dfs(x+1, w|(1<<(2*x-1)))^1));
	return ret;
}

signed main() {
	File("game");
	read(n), read(m);
	if(n <= 5) {
		for(int i = 1; i <= m; ++i)
			read(u), read(v), to[u].push_back(v);
		int pd = dfs(1, 0);
		if(pd)
			puts("Alice");
		else
			puts("Bob");
		return 0;
	}
	int pd = 1, sfy = 0;
	for(int i = 1; i <= m; ++i)
		read(u), read(v), pd&=(v == u+1 && u%2 == 1), sfy|=(v == u+1 && u%2 == 1 && v/2%2 == 0), 
		to[u].push_back(v);
	if(pd) {
		if(sfy)
			puts("Bob");
		else
			puts("Alice");
		return 0;
	}
	return 0;
}