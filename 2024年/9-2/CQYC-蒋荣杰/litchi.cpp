#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, a[N], b[2][2], gs[2];
LL ans, sum[2];

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
	File("litchi");
	read(n);
	b[0][0]=inf;
	b[1][1]=-inf;
	for(int i = 1; i <= n; ++i) {
		read(a[i]);
		if(a[i] < 0)
			b[1][0]=min(b[1][0], a[i]), b[1][1]=max(b[1][1], a[i]), ++gs[1], sum[1]=sum[1]+a[i];
		else
			b[0][0]=min(b[0][0], a[i]), b[0][1]=max(b[0][1], a[i]), ++gs[0], sum[0]=sum[0]+a[i];
	}
	if(!gs[1]) {
		write(1LL*b[0][0]*(sum[0]-b[0][0]), '\n');
		return 0;
	}
	if(!gs[0]) {
		write(1LL*b[1][1]*(sum[1]-b[1][1]), '\n');
		return 0;
	}
	write(min(1LL*b[1][0]*sum[0]+1LL*(sum[1]-b[1][0])*b[0][1], 1LL*b[0][1]*sum[1]+1LL*(sum[0]-b[0][1])*b[1][0]), '\n');
	// debug("!!!\n");
	return 0;
}