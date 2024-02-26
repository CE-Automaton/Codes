#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e2+5;
int n;
LL c, sum[N], d[N], mx[N], ans = 1000000000000000000LL;

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
	File("shining");
	read(n), read(c);
	for(int i = 2; i <= n; ++i)
		read(sum[i]), sum[i]+=sum[i-1];
	for(int i = 1; i <= n; ++i)
		read(d[i]), mx[i]=d[i]+sum[i];
	for(int i = n; i >= 1; --i)
		mx[i]=max(mx[i], mx[i+1]);
	for(int i = 1; i < n; ++i)
		ans=min(ans, d[i]+mx[i+1]-sum[i]);
	write(ans, '\n');
	return 0;
}