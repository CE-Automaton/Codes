#include <bits/stdc++.h>
using namespace std;
__int128 L, l, ans;

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
__int128 f(__int128 a, __int128 b) {
	if(b == 0)
		return -a;
	return (__int128) 2*b*(a/b)+f(b, a%b);
}

signed main() {
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
	read(L), read(l);
	ans=f(L-l, l)+L;
	write(ans, '\n');
	return 0;
}
