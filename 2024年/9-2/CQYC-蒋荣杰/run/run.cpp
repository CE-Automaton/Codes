#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, m, q, u, v, l, r, ds[N], vis[N];
struct qwq {
	int y, w;
};
vector <qwq> to[N];
queue <int> qq;

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

signed main() {
	File("run");
	read(n), read(m), read(q);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u].push_back(qwq {v, i}), to[v].push_back(qwq {u, i});
	for(int i = 1; i <= q; ++i) {
		read(l), read(r);
		int ans = 0;
		for(int j = 1; j <= n; ++j)
			vis[j]=0, ds[j]=0;
		for(int j = 1; j <= n && !ans; ++j) 
			if(!vis[j]) {
				ds[j]=1;
				qq.push(j);
				while(!qq.empty() && !ans) {
					int it = qq.front(); qq.pop();
					for(qwq y : to[it]) {
						if(y.w >= l && y.w <= r) continue;
						if(vis[y.y] && ds[y.y] == ds[it]) {
							ans=1;
							break;
						}
						if(!vis[y.y]) {
							vis[y.y]=1;
							ds[y.y]=ds[it]^1;
							qq.push(y.y);
						}
					}
				}
				while(!qq.empty()) qq.pop();
			}
		if(ans)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}