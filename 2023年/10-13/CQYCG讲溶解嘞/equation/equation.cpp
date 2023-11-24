#include <bits/stdc++.h>
using namespace std;
const int N = 1e7+5;
int t, p, jc[N], inv[N], inc[N], a, d, n;

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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%p;
		x=1LL*x*x%p;
		y=(y>>1);
	}
	return ret;
}

signed main() {
	freopen("equation.in", "r", stdin);
	freopen("equation.out", "w", stdout);
	read(t), read(p);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= p-1; ++i)
		jc[i]=1LL*jc[i-1]*i%p, inv[i]=1LL*inv[p%i]*(p-p/i)%p, 
		inc[i]=1LL*inc[i-1]*inv[i]%p;
	while(t--) {
		read(a), read(d), read(n);
		int w = 1LL*a*inv[d]%p;
		if(w+n-1 >= p) {
			write(0, '\n');
			continue;
		}
		write(1LL*jc[w+n-1]*inc[w]%p*a%p*ksm(d, n-1)%p, '\n');
	}
	return 0;
}
