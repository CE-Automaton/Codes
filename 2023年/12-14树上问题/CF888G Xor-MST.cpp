#include <bits/stdc++.h>
#define inf (1LL<<30)
using namespace std;
const int N = 2e5+5;
int n, a[N], to[2][N<<5], L[2][N<<5], R[2][N<<5], gs;

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
void add(int x, int dd) {
	int now = 1;
	for(int i = 30; i >= 0; --i) {
		int too = ((x>>i)&1);
		if(!to[too][now])
			to[too][now]=++gs;
		if(!L[too][now])
			L[too][now]=dd;
		R[too][now]=dd;
		now=to[too][now];
	}
}
int ask(int x, int k, int dep) {
	if(dep < 0) return 0;
	int too = ((x>>dep)&1);
	if(to[too][k])
		return ask(x, to[too][k], dep-1);
	return ask(x, to[too^1][k], dep-1)+(1<<dep);
}
long long dfs(int x, int dep) {
	if(dep < 0) return 0;
	if(to[0][x] && to[1][x]) {
		int ans = inf;
		for(int i = L[0][x]; i <= R[0][x]; ++i) 
			ans=min(ans, ask(a[i], to[1][x], dep-1)+(1<<dep));
		return dfs(to[0][x], dep-1)+dfs(to[1][x], dep-1)+ans;
	}
	else if(to[0][x])
		return dfs(to[0][x], dep-1);
	else if(to[1][x])
		return dfs(to[1][x], dep-1);
	return 0;
}

signed main() {
	read(n);
	gs=1;
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	sort(a+1, a+1+n);
	for(int i = 1; i <= n; ++i)
		add(a[i], i);
	write(dfs(1, 30), '\n');
	return 0;
}
