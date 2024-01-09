#include <bits/stdc++.h>
#define inf 998244353
using namespace std;
const int N = 1e6+5;
int t, n, a, b, ans;

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
	freopen("op.in", "r", stdin);
	freopen("op.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		if(n == 1) {
			read(a), read(b);
			ans=inf;
			int gs = 0;
			while(a) {
				ans=min(ans, abs(b-a)+gs);
				a/=2;
				++gs;
			}
			write(ans, '\n');
		}
		else
			puts("0");
	}
	return 0;
}

