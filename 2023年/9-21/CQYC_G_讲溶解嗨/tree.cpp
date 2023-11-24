#include <bits/stdc++.h>
#define mod 998244353
#define inf 151561313
using namespace std;
const int N = 1505;
int n, m, a[N], dis[N][N], k, u, v, ans, az[N];
vector <int> to[N];
struct qwq {
	int now, st, w;
	bool operator <(const qwq& A) const {
		return A.w < w;
	}
};
priority_queue <qwq> q;

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
void dfs(int x, int fa, int gf) {
	for(int y : to[x])
		if(y != fa)
			dis[gf][y]=dis[gf][x]+1, dfs(y, x, gf);
}
int ksm(int x, int y, int ret = 1) {
	while(x) {
		if(x&1)
			ret=1LL*ret*y%mod;
		y=1LL*y*y%mod;
		x=(x>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	read(n), read(m), read(k);
	for(int i = 1; i <= m; ++i)
		read(a[i]);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	if(k == 2) {
		for(int i = 1; i <= n; ++i)
			dfs(i, 0, i);
		for(int i = 1; i <= m; ++i)
			for(int j = i+1; j <= m; ++j)
				ans=upd(ans+dis[a[i]][a[j]]);
		write(1LL*ans*ksm(mod-2, 1LL*m*(m-1)/2%mod)%mod, '\n');
	}
	else {
		if(n <= 10) {
			for(int i = 1; i <= n; ++i)
				dfs(i, 0, i);
			for(int i = 0; i <= (1<<m)-1; ++i)
				az[i]=inf;
			for(int i = 1; i <= m; ++i)
				q.push(qwq {(1<<(i-1)), i, 0}), az[(1<<(i-1))]=0;
			while(!q.empty()) {
				qwq it = q.top(); q.pop();
				if(it.w > az[it.now]) continue;
				for(int i = 0; i <= m-1; ++i) {
					if((it.now>>i)&1) continue;
					int aa = (it.now|(1<<i)), ww = it.w+dis[a[it.st]][a[i+1]];
					if(ww < az[aa])
						az[aa]=ww, q.push(qwq {aa, i+1, ww});
				}
			}
			int tot = 0;
			for(int i = 0; i <= (1<<m)-1; ++i) {
				int gs = 0;
				for(int o = 0; o <= m-1; ++o)
					if((i>>o)&1)
						++gs;
				if(gs == k) 
					++tot, ans=upd(ans+az[i]);
			}
			write(1LL*ans*ksm(mod-2, tot)%mod, '\n');
		}
	}
	return 0;
}
