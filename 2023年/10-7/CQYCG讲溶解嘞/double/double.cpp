#include <bits/stdc++.h>
#define inf 100000000000000000LL
using namespace std;
const int N = 2e3+5;
int n, q, u, v;
long long w, dis[N][N];
struct qwq {
	int a;
	long long b;
	bool operator <(const qwq& A) const {
		return A.b < b;
	}
};
vector <qwq> to[N];
priority_queue <qwq> qq;

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
void solve(int x) {
	for(int i = 1; i <= n+n; ++i)
		dis[x][i]=inf;
	dis[x][x]=0;
	qq.push(qwq {x, 0});
	while(!qq.empty()) {
		qwq it = qq.top(); qq.pop();
		if(it.b != dis[x][it.a])
			continue;
		for(qwq y : to[it.a])
			if(y.b+it.b < dis[x][y.a]) {
				dis[x][y.a]=y.b+it.b;
				qq.push(qwq {y.a, y.b+it.b});
			}
	}
}

signed main() {
	freopen("double.in", "r", stdin);
	freopen("double.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(w), to[2*i-1].push_back(qwq {2*i, w}), to[2*i].push_back(qwq {2*i-1, w});
	for(int i = 2; i <= n; ++i) {
		read(u), read(v);
		read(w);
		to[2*u-1].push_back(qwq {2*v-1, w}), to[2*v-1].push_back(qwq {2*u-1, w});
		read(w);
		to[2*u].push_back(qwq {2*v, w}), to[2*v].push_back(qwq {2*u, w});
	}
	for(int i = 1; i <= n+n; ++i)
		solve(i);
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(u), read(v);
		write(dis[u][v], '\n');
	}
	return 0;
}
