#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, qq, u, v, w, k, vis[N], to[N];
struct qwq {
	int to, w, idd;
};
vector <qwq> az[N];

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
int gcd(int x, int y) {
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}
int dfs(int x, int fa, int ww) {
	int ret = (ww == 1);
	for(qwq y : az[x])
		if(vis[y.idd] == 0 && y.to != fa)
			ret+=dfs(y.to, x, (ww == -1 ? y.w : (ww == 1 ? 1 : gcd(ww, y.w))));
	return ret;
}
void sol() {
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		ans+=dfs(i, 0, -1);
	write(ans/2, '\n');
}

signed main() {
	freopen("lct.in", "r", stdin);
	freopen("lct.out", "w", stdout);
	read(n), read(qq);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), read(w), az[u].push_back(qwq {v, w, i}), az[v].push_back(qwq {u, w, i}), to[i]=i;
	sol();
	for(int i = 1; i <= qq; ++i) {
		read(k), read(u), read(v), read(w);
		++k;
		int ppd = k;
		k=to[k];
		vis[k]=1;
		az[u].push_back(qwq {v, w, i+n}), az[v].push_back(qwq {u, w, i+n});
		to[ppd]=i+n;
		sol();
	}
	return 0;
}
