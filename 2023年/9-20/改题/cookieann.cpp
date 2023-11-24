#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int t, n, a[N], tot, pd[N][2], ans;
struct qwq {
	int w, t;
}b[N];

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
int check() {
	int l = a[1], r = a[1], ll = 2, rr = n;
	while(1) {
		int pd = 0;
		if(ll <= rr && a[ll] == l-1)
			++ll, --l, pd|=1;
		else
			if(rr >= ll && a[rr] == l-1)
				--rr, --l, pd|=1;
			else
				if(ll <= rr && a[ll] == r+1)
					++ll, ++r, pd|=1;
				else
					if(rr >= ll && a[rr] == r+1)
						--rr, ++r, pd|=1;
		if(!pd)
			return 0;
		if(ll > rr) return 1;
	}
	return 0;
}

signed main() {
//	freopen("cookieann.in", "r", stdin);
//	freopen("cookieann.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		ans=0;
		for(int i = 1; i <= n; ++i)
			read(a[i]);
		ans|=check();
		for(int i = 1; i*2 <= n; ++i)
			swap(a[i], a[n-i+1]);
		ans|=check();
		if(ans || n == 1)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}
