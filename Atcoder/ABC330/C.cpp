#include <bits/stdc++.h>
using namespace std;
long long n, ans;

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
long long abssss(long long x) {
	return (x < 0 ? -x : x);
}

signed main() {
	read(n);
	ans=n;
	for(int i = 0; i <= 2000002; ++i) {
		int l = 1, r = 2000002, ll = 0;
		long long op = 1LL*i*i;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(op+1LL*mid*mid <= n)
				l=mid+1, ll=mid;
			else
				r=mid-1;
		}
		ans=min(ans, abssss(n-op-1LL*ll*ll));
		++ll;
		ans=min(ans, abssss(n-op-1LL*ll*ll));
		--ll, --ll;
		if(ll >= 0)
			ans=min(ans, abssss(n-op-1LL*ll*ll));
	}
	write(ans, '\n');
	return 0;
}
