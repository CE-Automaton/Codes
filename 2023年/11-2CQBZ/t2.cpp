#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 4e6+5;
int t, A, B, C, D, jc[N], inv[N], inc[N], ans;

template<typename T> void read(T& x) {
	x=0; int f=0; char c=getchar();
	while(c < '0' || c > '9') f|=(c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template<typename T> void write(T x, char ch) {
	if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne]^48), --lne;
	putchar(ch);
}
int cc(int y, int x) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int sol(int d, int c, int b, int op) {
	if(d < 0 || c < 0 || b < 0) return 0;
	if(2*d+c-b != op || b > d-b) return 0;
	return 1LL*cc(b, d-b)*cc(d-b, c+d-b)%mod;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= 4000000; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	read(t);
	while(t--) {
		read(A), read(B), read(C), read(D);
		int sm = 2*D+C-B-2*A;
		if(sm == 0) {
			puts("0");//无解 
			continue;
		}
		if(sm < 0) swap(A, D), swap(B, C), sm=-sm;//全乘-1 
		int gs = A-D;
		if(gs >= 1) {
			puts("0");//无解 
			continue;
		}
		ans=0;
//		cout<<A<<" "<<B<<" "<<C<<" "<<D<<" "<<sm<<"\n"; 
		if(A != 0) {
			ans=upd(upd(upd(sol(D-A, C-1, B, sm-1)+sol(D-A-1, C, B-1, sm-1))
			+sol(D-A-1, C, B-1, sm-1))+sol(D-A, C-1, B, sm-1));
			ans=upd(ans+1LL*(A+1)*sol(D-A-2, C, B-2, sm-2)%mod);
			ans=upd(ans+1LL*A*sol(D-A-1, C-1, B-1, sm-2)%mod);
			ans=upd(ans+1LL*A*sol(D-A-1, C-1, B-1, sm-2)%mod);
			ans=upd(ans+1LL*(A-1)*sol(D-A, C-2, B, sm-2)%mod);
		}
		else
			ans=upd(upd(upd(upd(ans+sol(D, C, B, sm))+sol(D-1, C, B-1, sm-1))
			+sol(D-1, C, B-1, sm-1))+sol(D-2, C, B-2, sm-2));//单独的左边BD、右边DB的情况要考虑! 
		write(ans, '\n');
	}
	return 0;
}
