#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5, M = 3e3+5;
int t, n, u, v, w, q;
LL dis1[N], dis2[N];
struct qwq {
	int t, d;
};
vector <qwq> t1[N], t2[N];

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
void dfs1(int x, int fa) {
	for(qwq y : t1[x])
		if(y.t != fa)
			dis1[y.t]=dis1[x]+y.d, dfs1(y.t, x);
}
void dfs2(int x, int fa) {
	for(qwq y : t2[x])
		if(y.t != fa)
			dis2[y.t]=dis2[x]+y.d, dfs2(y.t, x);
}
void sub1() {
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(u), read(v);
		dis1[u]=0, dis2[v]=0;
		dfs1(u, 0);
		dfs2(v, 0);
		LL ans = 0;
		for(int j = 1; j <= n; ++j)
			ans=max(ans, dis1[j]+dis2[j]);
		write(ans, '\n');
	}
}
void sub2() {
}

signed main() {
	File("move");
	read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			t1[i].clear(), t2[i].clear();
		for(int i = 2; i <= n; ++i)
			read(u), read(v), read(w), 
			t1[u].push_back(qwq {v, w}), 
			t1[v].push_back(qwq {u, w});
		for(int i = 2; i <= n; ++i)
			read(u), read(v), read(w), 
			t2[u].push_back(qwq {v, w}), 
			t2[v].push_back(qwq {u, w});
		// if(n <= 3000)
			sub1();
		// else
		// 	sub2();
	}
	return 0;
}