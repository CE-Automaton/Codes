#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 1e6+5, M = 2e6+5;
int n, m, q, u, v, w, ans[M], dij[N];
struct qwq {
	int t, v;
};
vector <qwq> to[N];
struct que {
	int x, l, r, id;
}pro[M];

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
int comp1(que A, que B) {
	return A.l > B.l;
}
int comp2(qwq A, qwq B) {
	return A.v > B.v;
}
void dfs(int x, int ss) {
//	cout<<x<<" "<<ss<<"!?\n";
	for(auto y : to[x]) 
		if(y.v > ss && y.v < dij[y.t])
			dij[y.t]=y.v, dfs(y.t, y.v);
} 

signed main() {
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
	read(n), read(m), read(q);
	for(int i = 1; i <= m; ++i) 
		read(u), read(v), read(w), to[v].push_back(qwq{u, w});
	for(int i = 1; i <= q; ++i)
		read(pro[i].x), read(pro[i].l), read(pro[i].r), pro[i].id=i;
	sort(pro+1, pro+1+q, comp1);
	sort(to[1].begin(), to[1].end(), comp2);
	for(int i = 1; i <= n; ++i)
		dij[i]=inf;
	int st = 0;
	for(int i = 1; i <= q; ++i) {
//		cout<<pro[i].id<<" "<<pro[i].l<<"! :";
		while(st < to[1].size() && to[1][st].v >= pro[i].l) {
			if(to[1][st].v < dij[to[1][st].t])
				dij[to[1][st].t]=to[1][st].v, dfs(to[1][st].t, to[1][st].v)/*, cout<<to[1][st].t<<" "*/;
			++st;
		}
		if(dij[pro[i].x] <= pro[i].r)
			ans[pro[i].id]=1;
	}
	for(int i = 1; i <= q; ++i)
		if(ans[i])
			puts("Yes");
		else
			puts("No");
	return 0;
}
