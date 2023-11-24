#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e5+5;
int t, n, a[N], tr1[N], tr2[N], r[N], l[N], ans;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void add1(int x, int w) {
	while(x >= 1)
		tr1[x]=upd(tr1[x]+w), x=x-(x&(-x));
}
void add2(int x, int w) {
	while(x <= n)
		tr2[x]=upd(tr2[x]+w), x=x+(x&(-x));
}
int ask1(int x, int ret = 0) {
	while(x <= n)
		ret=upd(ret+tr1[x]), x=x+(x&(-x));
	return ret;
}
int ask2(int x, int ret = 0) {
	while(x >= 1)
		ret=upd(ret+tr2[x]), x=x-(x&(-x));
	return ret;
}

signed main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		ans=0;
		for(int i = 1; i <= n; ++i)
			read(a[i]), tr1[i]=0, tr2[i]=0;
		add1(n, 1);
		add2(1, 1);
		for(int i = n; i >= 1; --i) {
			r[i]=ask1(a[i]);
			l[i]=ask2(a[i]);
			ans=upd(ans+1LL*r[i]*l[i]%mod);
			add1(a[i], r[i]);
			add2(a[i], l[i]);
		}
		write(ans, '\n');
	}
	return 0;
}
