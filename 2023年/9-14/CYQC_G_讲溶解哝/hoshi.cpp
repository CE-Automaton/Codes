#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5, M = 3e5+5, K = 1e4+5;
int n, m, k, ans[M];
struct qwq {
	int u, v, w, dd;
}edge[M]; 
struct op {
	int fa[N], cnt[N];
	int find(int x) {
		return (x == fa[x] ? x : fa[x]=find(fa[x]));
	}
	void merge(int x, int y) {
		x=find(x), y=find(y);
		if(cnt[x] < cnt[y]) swap(x, y);
		cnt[x]+=cnt[y];
		fa[y]=x;
	}
}A[K];

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
int comp(qwq aa, qwq bb) {
	return aa.w > bb.w;
}

signed main() {
	freopen("hoshi.in", "r", stdin);
	freopen("hoshi.out", "w", stdout);
	read(n), read(m), read(k);
	for(int i = 1; i <= m; ++i)
		read(edge[i].u), read(edge[i].v), read(edge[i].w), edge[i].dd=i;
	sort(edge+1, edge+1+m, comp);
	for(int i = 1; i <= k; ++i) 
		for(int j = 1; j <= n; ++j)
			A[i].fa[j]=j, A[i].cnt[j]=1;
	for(int j = 1; j <= m; ++j) {
		int l = 1, r = k, to = 0;
		while(l <= r) {
			int i = ((l+r)>>1), x = A[i].find(edge[j].u), y = A[i].find(edge[j].v);
			if(x == y) 
				l=i+1;
			else
				r=i-1, to=i;
		}
		A[to].merge(edge[j].u, edge[j].v);
		ans[edge[j].dd]=to;
	}
	for(int i = 1; i <= m; ++i)
		write(ans[i], '\n');
	return 0;
}
