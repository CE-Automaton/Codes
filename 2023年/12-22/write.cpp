#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, u, v, fa[N<<2], cnt[N<<2], gs, az;
long double ans;
struct qwq {
	int x, y;
}a[N];
vector <qwq> to[N];
struct edge {
	int u, v;
	long double w;
}b[N<<4];

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
long double len(int x, int y) {
	long long xx = a[x].x-a[y].x, yy = a[x].y-a[y].y;
	return sqrtl((xx*xx+yy*yy));
}
long double calc(int x, int y, int z) {
	long double b = len(x, y), a = len(x, z), c = len(y, z);
	return acos((long double) -(b*b+c*c-a*a)/b/c/2.00);
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
int merge(int x, int y) {
	x=find(x), y=find(y);
	if(x == y) return 0;
	if(cnt[y] > cnt[x]) swap(x, y);
	fa[y]=x, cnt[x]+=cnt[y];
	return 1;
}
int comp(edge A, edge B) {
	return A.w < B.w;
}

signed main() {
	// freopen("write.in", "r", stdin);
	// freopen("write.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i].x), read(a[i].y);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), fa[i]=i, cnt[i]=1, 
		to[u].push_back(qwq {v, i}), to[v].push_back(qwq {u, i});
	for(int i = 1; i <= n; ++i) 
		if(to[i].size() == 2) 
			ans+=calc(to[i][0].x, i, to[i][1].x), 
			az=merge(to[i][0].y, to[i][1].y);//判断边是否联通即方案合不合法
		else {
			long double mn1 = calc(to[i][0].x, i, to[i][1].x)+calc(to[i][2].x, i, to[i][3].x), 
			mn2 = calc(to[i][0].x, i, to[i][2].x)+calc(to[i][1].x, i, to[i][3].x), 
			mn3 = calc(to[i][0].x, i, to[i][3].x)+calc(to[i][1].x, i, to[i][2].x), 
			mn = min({mn1, mn2, mn3});
			if(mn1 == mn)
				az=merge(to[i][0].y, to[i][1].y), az=merge(to[i][2].y, to[i][3].y);
			else if(mn2 == mn)
				az=merge(to[i][0].y, to[i][2].y), az=merge(to[i][1].y, to[i][3].y);
			else 
				az=merge(to[i][0].y, to[i][3].y), az=merge(to[i][1].y, to[i][2].y);
			b[++gs]=edge {to[i][0].y, to[i][1].y, mn1-mn};
			b[++gs]=edge {to[i][2].y, to[i][3].y, mn1-mn};
			b[++gs]=edge {to[i][0].y, to[i][2].y, mn2-mn};
			b[++gs]=edge {to[i][1].y, to[i][3].y, mn2-mn};
			b[++gs]=edge {to[i][0].y, to[i][3].y, mn3-mn};
			b[++gs]=edge {to[i][1].y, to[i][2].y, mn3-mn};
			ans+=mn;
		}
	sort(b+1, b+1+gs, comp);
	for(int i = 1; i <= gs; ++i)
		if(merge(b[i].u, b[i].v))
			ans+=b[i].w;
	printf("%.6Lf\n", ans);
	return 0;
}
