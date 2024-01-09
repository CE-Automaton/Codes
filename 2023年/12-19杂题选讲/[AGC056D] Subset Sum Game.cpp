#include <bits/stdc++.h>
#define inf 1000000000000000000LL
using namespace std;
const int N = 5e3+5;
int n;
long long b[N], l, r, a[N], s, ans = inf;

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
	read(n), read(l), read(r);
	for(int i = 1; i <= n; ++i)
		read(a[i]), s+=a[i];
	s-=l+r;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j)
			b[j]=a[j];
		b[i]+=s;
		sort(b+1, b+1+n);
		long long now = 0;
		for(int j = 1; j <= n; j+=2)
			now+=b[j+1]-b[j];
		ans=min(ans, now);
	}
	puts((abs(ans) <= r-l ? "Alice" : "Bob"));
	return 0;
}
