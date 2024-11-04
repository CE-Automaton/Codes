#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int t, n, p[N], a[N], b[N], rr[N], tot, zhan[N], q;
LL ans[N], u, v, lst;

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
void cf(LL& x) {
	x=(x+lst)%(n+1)+1;
	if(x <= 0) x+=n+1;
}

signed main() {
	File("increase");
	read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			read(p[i]);
		for(int i = 1; i <= n; ++i)
			read(a[i]);
		for(int i = 1; i <= n; ++i) 
			read(b[i]);
		tot=0;
		for(int i = 1; i <= n; ++i) {
			rr[i]=n+1;
			while(tot && p[zhan[tot]] < p[i])
				rr[zhan[tot]]=i, --tot;
			zhan[++tot]=i;
		}
		lst=0;
		read(q);
		for(int i = 1; i <= q; ++i) {
			read(u), read(v);
			cf(u), cf(v);
			for(int j = u; j <= v; ++j)
				ans[j]=inf;
			ans[u]=0;
			for(int j = u; j < v; ++j) {
				if(rr[j] <= v) 
					ans[rr[j]]=min(ans[rr[j]], ans[j]+b[j]);
				ans[j+1]=min(ans[j+1], ans[j]+a[j]);
			}
			write(ans[v], '\n');
			lst=(ans[v]%(n+1));
		}
	}
	return 0;
}