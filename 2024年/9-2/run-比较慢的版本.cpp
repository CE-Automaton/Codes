#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 4e5+5;
int n, m, q, u[N], v[N], f[N], fa[N], cnt[N], zhan[N], tot;

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
int find(int x) {
	return (fa[x] == x ? x : fa[x]=find(fa[x]));
}
int add(int x) {
	int xx = find(u[x]), yy = find(v[x]+n);
	if(xx != yy) {
		if(cnt[xx] < cnt[yy]) swap(xx, yy);
		zhan[++tot]=xx, zhan[++tot]=yy;
		fa[yy]=xx, cnt[xx]+=cnt[yy];
	}
	xx = find(u[x]+n), yy = find(v[x]);
	if(xx != yy) {
		if(cnt[xx] < cnt[yy]) swap(xx, yy);
		zhan[++tot]=xx, zhan[++tot]=yy;
		fa[yy]=xx, cnt[xx]+=cnt[yy];
	}
	return (find(u[x]) == find(v[x]));
}
void dfs(int l, int r, int L, int R) {
	if(L > R || l > r) return ;
	int mid = ((l+r)>>1), to = mid;
	while(to >= L && !add(to))
		--to;
	for(int i = L; i <= to && i <= R; ++i)
		f[i]=mid;
	while(tot) fa[zhan[tot]]=zhan[tot], cnt[zhan[tot]]=1, --tot;
	dfs(l, mid-1, L, to);
	dfs(mid+1, r, to+1, R);
}

signed main() {
	read(n), read(m), read(q);
	for(int i = 1; i <= n+n; ++i)
		fa[i]=i, cnt[i]=1;
	for(int i = 1; i <= m; ++i)
		read(u[i]), read(v[i]), u[i+m]=u[i], v[i+m]=v[i];
	dfs(1, m+m, 1, m+m);
	for(int i = 1; i <= m+m; ++i)
		debug(f[i]), debug(' ');
	for(int i = 1; i <= q; ++i) {
		int l, r;
		read(l), read(r);
		if(l > r) {
			puts("NO");
			continue;
		}
		// assert(l <= r);
		l=l-1+m;
		r=r+1;
		if(!f[r] || l < f[r]) 
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}