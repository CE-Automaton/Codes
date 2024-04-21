#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e5+5;
int n, k, q, a[N], tr[N];
LL gs;

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
void add(int x) {
	while(x >= 1)
		++tr[x], x-=(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x <= n)
		ret+=tr[x], x+=(x&(-x));
	return ret;
}

signed main() {
	File("random");
	read(n), read(k), read(q);
	for(int i = 1; i <= n; ++i)
		read(a[i]), gs+=1LL*ask(a[i]), add(a[i]);
	write(gs, '\n');
	return 0;
}