#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, a[N], st[N][21], mx, tot, zhan[N];

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
int gcd(int x, int y) {
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}
int ask(int l, int r) {
	int o = (int) log2(r-l+1);
	return gcd(st[l][o],st[r-(1<<o)+1][o]);
}

signed main() {
	 freopen("interval.in", "r", stdin);
	 freopen("interval.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), st[i][0]=a[i];
	for(int j = 1; j <= 19; ++j)
		for(int i = 1; i <= n; ++i)
			if(i+(1<<(j-1)) > n)
				st[i][j]=st[i][j-1];
			else
				st[i][j]=gcd(st[i][j-1], st[i+(1<<(j-1))][j-1]);
	for(int i = 1; i <= n; ++i) {
		int l = 1, r = i, ll = i, rr = i; 
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(ask(mid, i) == a[i])
				ll=mid, r=mid-1;
			else
				l=mid+1;
		}
		l = i, r = n; 
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(ask(i, mid) == a[i])
				rr=mid, l=mid+1;
			else
				r=mid-1;
		}
		if(rr-ll > mx)
			mx=rr-ll, tot=0;
		if(rr-ll == mx)
			zhan[++tot]=ll;
	}
	sort(zhan+1, zhan+1+tot);
	int gs = 1;
	for(int i = 2; i <= tot; ++i)
		if(zhan[i] != zhan[i-1])
			++gs;
	write(gs, ' '), write(mx, '\n');
	write(zhan[1], ' ');
	for(int i = 2; i <= tot; ++i)
		if(zhan[i] != zhan[i-1])
			write(zhan[i], ' ');
	return 0;
}
