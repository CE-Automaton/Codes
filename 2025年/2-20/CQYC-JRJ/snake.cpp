#include <bits/stdc++.h>
#define inf 100000000000000000LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3.5e4+5;
int n, q, a[N], l, r, k;
LL sum[N], mx[3005][3005][2];

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
	File("snake");
	read(n), read(q);
	int pd = 1;
	for(int i = 1; i <= n; ++i)
		read(a[i]), pd&=(a[i] >= 0);
	if(pd) {
		for(int i = 1; i <= n; ++i)
			sum[i]=sum[i-1]+a[i];
		for(int i = 1; i <= q; ++i)
			read(l), read(r), read(k), write(sum[r]-sum[l-1], '\n');
		return 0;
	}
	for(int i = 1; i <= q; ++i) {
		read(l), read(r), read(k);
		for(int j = l; j <= r; ++j)
			for(int kk = 0; kk <= k; ++kk)
				mx[j][kk][0]=mx[j][kk][1]=-inf;
		mx[l][1][0]=a[l], mx[l][1][1]=a[l], mx[l][0][0]=-inf;
		for(int j = l+1; j <= r; ++j) {
			mx[j][1][0]=a[j], mx[j][1][1]=a[j];
			for(int kk = 0; kk <= k; ++kk)
				mx[j][kk+1][1]=max(mx[j][kk+1][1], mx[j-1][kk][0]+a[j]), 
				mx[j][kk][0]=max(mx[j][kk][0], mx[j-1][kk][0]), 
				mx[j][kk][1]=max(mx[j][kk][1], mx[j-1][kk][1]+a[j]), 
				mx[j][kk][0]=max(mx[j][kk][0], mx[j][kk][1]);
		}
		write(mx[r][k][0], '\n');
	}
	return 0;
}
