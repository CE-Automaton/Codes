#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
// bool st;
int p, q, a[N], xx, k, l;
LL ans[105][N<<1];

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
// bool fn;
signed main() {
	File("sing");
	// debug((double) (&fn-&st)*1.0/1024/1024, "\n");
	read(p), read(q);
	int pd = 1;
	for(int i = 1; i <= p; ++i)
		read(a[i]), pd&=(a[i] == i);
	if(p <= 1000 && q <= 1000) {
		for(int i = 1; i <= q; ++i) {
			read(xx), read(k), read(l);
			xx=(xx+k-2)%p+1;
			LL sum = 0;
			for(int j = xx, o = 1; o <= l; ++o, j=(j+k-1)%p+1)
				sum=sum+a[j];
			write(sum, '\n');
		}
		return 0;
	}
	// for(int i = 1; i <= 100; ++i) {
	// 	LL sum = 0;
	// 	for(int j = xx, o = 1; o <= l; ++o, j=(j+k-1)%p+1)
	// 		sum=sum+a[j];
	// }
	if(pd) {
		for(int i = 1; i <= q; ++i) {
			read(xx), read(k), read(l);
			xx=(xx+k-2)%p+1;
			write(xx, '\n');
		}
		return 0;
	}
	return 0;
}