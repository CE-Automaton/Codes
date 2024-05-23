#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, a[N], b[N], to[N], m, u[N], v[N];
LL ans = 1000000000000000007LL;

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

signed main() {
	File("gentle");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), read(b[i]);
	read(m);
	for(int i = 1; i <= m; ++i) 
		read(u[i]), read(v[i]);
	for(int i = 0; i < (1<<m); ++i) {
		for(int j = 1; j <= n; ++j)
			to[j]=a[j];
		for(int j = 1; j <= m; ++j)
			if((i>>(j-1))&1)
				to[u[j]]=max(to[u[j]], b[u[j]]), 
				to[v[j]]=max(to[v[j]], b[v[j]]);
			else
				to[u[j]]=max(to[u[j]], b[v[j]]), 
				to[v[j]]=max(to[v[j]], b[u[j]]);
		LL sum = 0;
		for(int j = 1; j <= n; ++j)
			sum+=to[j]-a[j];
		ans=min(ans, sum);
	}
	write(ans, '\n');
	return 0;
}