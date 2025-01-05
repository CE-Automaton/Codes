#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 105;
int n, a[N], b[N], c[N], as[(1<<22)], sum[(1<<22)], mg;
LL ans;

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
	File("wisdom");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), read(b[i]), read(c[i]);
	for(int i = 1; i < (1<<n); ++i) {
		for(int j = 0; j < n; ++j)
			if((i>>j)&1)
				as[i]^=a[j+1];
		sum[i]=(as[i] == 0);
	}
	for(int j = 0; j < n; ++j)
		for(int i = 1; i < (1<<n); ++i)
			if((i>>j)&1)
				sum[i]+=sum[i^(1<<j)];
	for(int i = 1; i < (1<<n); ++i)
		if(sum[i] == 0) {
			int bs = 0, cs = 0, gs = 0;
			for(int j = 0; j < n; ++j)
				if((i>>j)&1)
					++gs, bs+=b[j+1], cs+=c[j+1];
			if(gs > mg)
				mg=gs, ans=1LL*bs*cs;
			if(gs == mg)
				ans=min(ans, 1LL*bs*cs);
		}
	write(ans, '\n');
	return 0;
}