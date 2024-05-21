#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 6e5+5;
int n, q, a[N], r[N], lst[N], cnt, ans, u, v;
unordered_map <int, int> to;

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
void afaa(int x) {
	if(to.find(x) == to.end()) to[x]=++cnt;
}
void sol() {
	for(int i = 1; i <= cnt; ++i)
		lst[i]=0;
	for(int i = 1; i <= n; ++i) {
		int tt = to[a[i]];
		if(lst[tt] && lst[tt] == i-1)
			++ans;
		lst[tt]=r[i];
	}
}

signed main() {
	File("tower");
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i) {
		afaa(a[i]), r[i]=i;
		while(r[i]+1 <= n && a[r[i]+1] < a[i]) ++r[i];
	}
	sol();
	write(ans, '\n');
	for(int i = 1; i <= q; ++i) {
		read(u), read(v);
		afaa(v);
		a[u]=v, r[u]=u;
		while(r[u]+1 <= n && a[r[u]+1] < a[u]) ++r[u];
		for(int j = 1; j < u; ++j) {
			if(r[j] == u-1 && a[j] > v) {
				r[j]=r[u];
				while(r[j]+1 <= n && a[r[j]+1] < a[j]) ++r[j];
			}
			if(r[j] >= u && a[j] < v)
				r[j]=u-1;
		}
		ans=0;
		sol();
		write(ans, '\n');
	}
	return 0;
}