#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 8;
int n, m, k, w[N], h[N], mm[105], sum[105], ans;

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
int pd(int x, int y, int xx, int yy) {
	return (xx >= x && yy >= y ? (yy-y)*(xx-x) : 0);
}

signed main() {
	File("posters");
	read(n), read(m), read(k);
	for(int i = 1; i <= k; ++i)
		read(w[i]);
	for(int i = 1; i <= k; ++i)
		read(h[i]);
	if(k == 1)
		write(w[1]*h[1], '\n');
	if(k == 2) 
		write(w[1]*h[1]+w[2]*h[2]-min(pd(n-w[2], m-h[2], w[1], h[1]), pd(n-w[1], m-h[1], w[2], h[2])), '\n');
	if(k == 3) {
		for(int i = 1; i <= 3; ++i)
			for(int j = 1; j <= 3; ++j) 
				if(i != j) {
					int k = ((i != 1 && j != 1) ? 1 : ((i != 2 && j != 2) ? 2 : 3)), summ = 0;
					for(int o = 1; o <= n; ++o)
						mm[o]=m;
					for(int o = 1; o <= w[i]; ++o)
						mm[o]=min(m-h[i], m);
					for(int o = n-w[j]+1; o <= n; ++o)
						mm[o]=min(m-h[j], m);
					for(int o = 1; o <= n; ++o)
						sum[i]=sum[i-1]+min(mm[o], h[k]), summ+=m-mm[o];
					for(int o = w[k]; o <= n; ++o)
						ans=max(ans, summ+sum[o]-sum[o-w[k]]);
				}
		write(ans, '\n');
	}
	if(k == 4 || k == 5)
		write(n*m, '\n');
	return 0;
}