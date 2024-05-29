#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5, V = 1e5+5;
int n, m, a, b, c, d, p, w[N][N], lst, fa[N*2], cnt[N*2], tot;
LL ans;
struct qwq {
	int x, y;
};
vector <qwq> to[V];

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
int f(int x) {
	return 1LL*(1LL*x*x*b+1LL*x*c+d)%p;
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}

signed main() {
	File("chess");
	read(n), read(m), read(a), read(b), read(c), read(d), read(p);
	lst=f(a);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			w[i][j]=lst, lst=f(w[i][j]), to[w[i][j]].push_back(qwq {i, j+n});
	for(int i = 1; i <= n+m; ++i)
		fa[i]=i, cnt[i]=1;
	for(int i = 0; i <= V-5; ++i)
		for(qwq uu : to[i]) {
			int x = find(uu.x), y = find(uu.y);
			if(x != y) {
				if(cnt[x] < cnt[y]) swap(x, y);
				fa[y]=x, cnt[x]+=cnt[y];
				ans+=i, ++tot;
				if(tot == n+m-1) {
					write(ans, '\n');
					debug(clock(), '\n');
					return 0;
				}
			}
		}
	return 0;
}