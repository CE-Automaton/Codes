#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, ww[N], now, ans;
struct qwq {
	int a, b;
}mm[N];

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
	return A.b < B.b;
}

signed main() {
	File("card");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(mm[i].a), read(mm[i].b);
	sort(mm+1, mm+1+n, comp);
	ans=n;
	// debug('\n');
	// for(int i = 1; i <= n; ++i)
	// 	debug(mm[i].a, mm[i].b, '\n');
	for(int i = n; i >= 1; --i) {
		now+=ww[i];
		if(now)
			--now, --ans;
		int l = 1, r = i-1, to = 0;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(mm[mid].b < mm[i].a)
				l=mid+1, to=mid;
			else
				r=mid-1;
		}
		// debug(i, to, "?????\n");
		++ww[to];
	}
	write(ans, '\n');
	return 0;
}