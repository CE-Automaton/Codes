#include <bits/stdc++.h>
#define mod 19260817
using namespace std;
int typ, t, h, a, b, H, A, B;
long long sum, pw = 1;

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
void Read() {
    long long x=1ll*h*H, y=1ll*a*A, z=1ll*b*B;
    h=(H^(y+z))%1000+1;
    a=(A^(x+z))%1000+1;
    b=(B^(x+y))%100000+1;
}
long double f(long double x) {
	x=acos(x);
	return (long double) 1.0*a*h/sin(x)+1.0*b*x;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void sol(long double ans = 0) {
	if(!typ) read(h), read(a), read(b);
	else Read();
	if(!b) 
		ans=a*h;
	else {
		long double drt = sqrtl(1LL*a*a*h*h+4LL*b*b), 
		xx = (long double) ((long double) drt-a*h)/(2.0*b);
		ans=f(xx);
	}
	if(typ) {
		pw=11514*pw%mod;
		long long op = floorl(ans*10000);
		op%=mod;
		sum=(sum+op*pw%mod)%mod;
		return ;
	}
	printf("%.4Lf\n", ans);
}

signed main() {
	// freopen("fly.in", "r", stdin);
	// freopen("fly.out", "w", stdout);
	read(typ), read(t);
	if(typ) read(h), read(a), read(b), read(H), read(A), read(B);
	while(t--) sol();
	if(typ) write(sum, '\n');
	return 0;
}
