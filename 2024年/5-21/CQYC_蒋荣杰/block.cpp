#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, q, l[N], r[N], mn[N];

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
	File("block");
	read(n), read(q);
	for(int i = 1; i <= q; ++i)
		read(l[i]), read(r[i]);
	for(int i = 1; i <= n; ++i) 
		mn[i]=inf;
	mn[1]=0;
	for(int i = 1; i <= n; ++i)
		for(int rr = i+1; rr <= n; ++rr) {
			int nd = 0;
			for(int p = 1; p <= q; ++p) {
				if(l[p] >= rr || r[p] <= i) continue;
				if(l[p] == i && r[p] == rr)
					++nd;
				else
					if(l[p] >= i && r[p] <= rr)
						nd+=l[p]-i+rr-r[p];
					else 
						if(l[p] <= i && rr <= r[p])
							++nd;
						else
							if(l[p] < i)
								nd+=min(r[p]-i, rr-r[p]);
							else
								nd+=min(rr-l[p], l[p]-i);
			}
			mn[rr]=min(mn[rr], mn[i]+nd);
		}
	write(mn[n], '\n');
	return 0;
}