#include <bits/stdc++.h>
using namespace std;
const int N = 5e2+5;
int n, fa[N], cnt[N], tot;
long long a[N], C, ans;
struct qwq {
	int u, v;
	long long w;
}q[N*N];

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
int comp(qwq& A, qwq& B) {
	return A.w > B.w;
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}

signed main() {
	freopen("hungry.in", "r", stdin);
	freopen("hungry.out", "w", stdout);
	read(n), read(C);
	for(int i = 1; i <= n; ++i)
		read(a[i]), fa[i]=i, cnt[i]=1;
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j)
			q[++tot]=qwq {i, j, (a[i]+a[j]+(a[i]^a[j]))%C};
	sort(q+1, q+1+tot, comp);
	for(int i = 1; i <= tot; ++i) {
		int x = find(q[i].u), y = find(q[i].v);
		if(x == y) 
			continue;
		if(cnt[y] > cnt[x]) swap(x, y);
		cnt[y]+=cnt[x];
		fa[x]=y;
		ans+=q[i].w;
	} 
	write(ans, '\n');
	return 0;
}
