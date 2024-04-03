#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, q, b, sum[N], tot, mx;
struct qwq {
	int w, s;
}tr[N];
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
int comp(qwq A, qwq B) {
	return ((long double) log2l(A.w)+1.0*A.s < (long double) log2l(B.w)+1.0*B.s);
}

signed main() {
	File("halation");
	read(n), read(q);
	int o = n;
	for(int i = 1; o && i <= n; ++i) {
		int p = min((i+1)/2, o);
		ans+=1LL*p*i;
		o-=p;
		mx=i;
	}
	write(ans, '\n');
	if(q == 0) 
		return 0;
	else {
		if(n <= 1000) {
			o = n;
			for(int i = 1; i <= n && o; ++i) 
				for(int j = 1; j <= i && o; j+=2)
					tr[++tot]=qwq {j, i-j}, --o;
			sort(tr+1, tr+1+tot, comp);
			for(int i = 1; i <= q; ++i) {
				read(b);
				write(tr[b].w+tr[b].s, '\n');
			}
			return 0;
		}
	}
	return 0;
}