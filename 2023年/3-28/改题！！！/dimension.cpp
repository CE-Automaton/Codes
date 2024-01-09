#include<bits/stdc++.h>
#define int long long
using namespace std;
//bool st;
int n, m, p, ans, inv[20000007], inc[20000007], jc[20000007];

template <typename T> inline void read(T &x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f|=(c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x = (x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> inline void write(T x, char c) {
	lne=0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne]^48), --lne;
	putchar(c);
}
int upd(int x) {
	return (x >= p ? x-p : x);
}
int c(int nn, int mm) {
	if(mm > nn || mm < 0) return 0;
	if(nn >= p || mm >= p)
		return 1LL*c(nn/p, mm/p)*c(nn%p, mm%p)%p;
	return 1LL*jc[nn]*inc[nn-mm]%p*inc[mm]%p;
}
int g(int nn, int mm) {
	mm=min(nn, mm);
	if(mm/p <= 0) {
		int ret = 0;
		for(int i = 0; i <= min(nn%p, mm); ++i)
			ret=upd(ret+c(nn%p, i));
		return ret;
	}
	int a1 = nn%p, a2 = mm%p, b1 = 1, b2 = 1;
	for(int i = 1; i <= min(a2, a1); ++i)
		b1=upd(b1+c(a1, i));
	b2=b1;
	for(int i = a2+1; i <= min(p-1, a1); ++i)
		b1=upd(b1+c(a1, i));
	a1 = nn/p, a2 = mm/p;
	return upd(1LL*g(a1, a2-1)*b1%p+1LL*b2*c(a1, a2)%p);
}

signed main() {
//	freopen("dimension.in", "r", stdin);
//	freopen("dimension.out", "w", stdout);
	read(n), read(m), read(p);
	jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
	for(int i = 2; i <= p-1; ++i)
		inv[i]=1LL*(p-p/i)*inv[p%i]%p, inc[i]=1LL*inc[i-1]*inv[i]%p, jc[i]=1LL*jc[i-1]*i%p;
	ans=upd(ans+g(n+1, m+1));
	ans=upd(ans+p-1);
	write(ans, '\n');
	return 0;
}
