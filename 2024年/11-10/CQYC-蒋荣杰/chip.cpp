#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int t, n, m, c[N], gs[N], ll[N];
LL op;
struct qwq {
	int bl;
	LL w;
}b[N];

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
int comp(qwq A, qwq B) {
	return A.w < B.w;
}

signed main() {
	File("chip");
	read(t);
	while(t--) {
		read(n);
		m=0;
		for(int i = 1; i <= n; ++i) {
			read(c[i]);
			for(int j = 1; j <= c[i]; ++j)
				read(op), b[++m]=qwq {i, op};
			gs[i]=c[i], ll[i]=0;
		}
		sort(b+1, b+1+m, comp);
		int rr = m;
		LL ans = inf;
		while(rr >= 1 && gs[b[rr].bl] > 1)
			--gs[b[rr].bl], --rr;
		for(int i = 1; i <= m; ++i) {
			ans=min(ans, b[rr].w-b[i].w);
			++ll[b[i].bl], --gs[b[i].bl];
			if(ll[b[i].bl] == c[b[i].bl])
				break;
			while(gs[b[i].bl] == 0)
				++rr, ++gs[b[rr].bl];
		}
		write(ans, '\n');
	}
	return 0;
}