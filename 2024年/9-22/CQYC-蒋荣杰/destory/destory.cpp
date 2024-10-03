#include <bits/stdc++.h>
#define inf 1000000009
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1500;
int n, m, C, u[N], v[N], w[N], vis[N], dp[N][N], ans, vv[N], ll[N];
struct qwq { int t, w; };
vector <qwq> to[N];

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
int upd(int x) {
	return (x >= inf ? x-inf : x);
}
void dfs(int x) {
	vv[x]=1;
	for(qwq y : to[x])
		if(!vis[y.w] && !vv[y.t])
			dfs(y.t);
	if(ll[x] && !vv[x%n+1])
		dfs(x%n+1);
	int lst = (x-2+n)%n+1;
	if(ll[lst] && !vv[lst])
		dfs(lst);
}

signed main() {
	File("destory");
	read(n), read(m), read(C);
	C=upd(upd(C));
	C=upd(C+C);
	for(int i = 1; i <= m; ++i)
		read(u[i]), read(v[i]), read(w[i]), to[u[i]].push_back(qwq {v[i], i}), to[v[i]].push_back(qwq {u[i], i});
	for(int i = 1; i <= n; ++i)
		ll[i]=1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) 
			dp[i][j]=inf;
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j) {
			ll[i]=ll[j]=0;
			for(int k = 0; k < (1<<m); ++k) {
				int sum = 0;
				for(int p = 0; p < m; ++p)
					vis[p+1]=((k>>p)&1), sum+=((k>>p)&1)*w[p+1];
				for(int p = 1; p <= n; ++p) {
					dfs(p);
					for(int o = 1; o <= n; ++o)
						if(!vv[o])
							dp[p][o]=min(dp[p][o], sum);
						else
							vv[o]=0;
				}
			}
			ll[i]=ll[j]=1;
		}
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j)
			dp[i][j]=min(dp[i][j], dp[j][i]), ans=upd(ans+upd(dp[i][j]+dp[i][j])), ans=upd(upd(ans+C)+C);
	write(ans, '\n');
	return 0;
}
/*
4 2 1000000000
1 3 1
1 4 2
*/