#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, q, a[N], ll[N], rr[N], xx, yy, fa[N], cnt[N], zhan[N], tot;

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
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void merge(int x, int y) {
	x=find(x), y=find(y);
	if(x != y) {
		if(cnt[x] > cnt[y])
			swap(x, y);
		fa[x]=y, cnt[y]+=cnt[x];
	}
}
void sol() {
	for(int i = 1; i <= n; ++i)
		fa[i]=i, cnt[i]=1, ll[i]=0, rr[i]=n+1;
	// tot=0;
	// for(int i = 1; i <= n; ++i) {
	// 	while(tot && a[zhan[tot]] < a[i]) rr[zhan[tot]]=i, --tot;
	// 	zhan[++tot]=i;
	// }
	// tot=0;
	// for(int i = n; i >= 1; --i) {
	// 	while(tot && a[zhan[tot]] > a[i]) ll[zhan[tot]]=i, --tot;
	// 	zhan[++tot]=i;
	// }
	// for(int i = 1; i <= n; ++i) {
	// 	if(ll[i])
	// 		merge(ll[i], i);
	// 	if(rr[i] != n+1)
	// 		merge(i, rr[i]);
	// }
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j)
			if(a[i] < a[j])
				merge(i, j);
	int gs = 0;
	for(int i = 1; i <= n; ++i)
		if(find(i) == i)
			++gs;
	write(gs, '\n');
}

signed main() {
	File("components");
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= q; ++i) {
		read(xx), read(yy);
		a[xx]=yy;
		if(a[1] <= a[n])
			write(1, '\n');
		else
			sol();
	}
	return 0;
}