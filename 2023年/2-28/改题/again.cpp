#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
using i64 = long long;
#define int i64
int t, op, n, k, inv2, inv3, ddd[5][5];
i64 ans, sum;

template<typename T> void read(T& x) {
	x = 0; char ch = getchar(); while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = (x<<1) + (x<<3) + ch - '0', ch = getchar();
}
int __stk[100], __tp;
template<typename T> void put(T x) {
	if (x < 0) putchar('-'), x = -x;
	do { __stk[++__tp] = x % 10, x /= 10; } while (x);
	while (__tp) putchar(__stk[__tp--] + '0');
}
i64 ksm(int x, int y, int ret = 1) { while(y) {if(y&1) ret=1LL*ret*x%mod; x=1LL*x*x%mod, y=(y>>1); } return ret; }
i64 inv(int x) { return ksm(x, mod-2); }

signed main() {
	freopen("again.in", "r", stdin);
	freopen("again.out", "w", stdout);
	read(t);
	inv2=inv(2), inv3=inv(3);
	while(t--) {
		read(n), read(op), read(k);
		ans=0;
		if(n <= 2) {//特判,反正都这么少 
			ddd[1][1]=1, ddd[1][2]=4;
			ddd[2][1]=2, ddd[2][2]=3;
			for(int i = k; i <= n; ++i)
				ans=(ans+(op == 1 ? ddd[i][i-k+1] : ddd[i-k+1][i]))%mod;
			sum^=ans;
			continue;
		}
		if(op == 2 && k == 1) op=1;//特殊转换 
		if(op == 1) {
			i64 az = (n-k+2)/2, a1 = 2*(n-1+n-2)%mod, 
			a=mod-4*inv3%mod, b = (4+1*a1*inv2)%mod, c = (mod-8*inv3%mod+mod-1*a1*inv2%mod)%mod, d = ((long long) mod+mod+mod-a-b-c)%mod;
			ans=2*((((1*n*az%mod+1*az*az%mod*az%mod*a%mod)%mod+1*az*az%mod*b%mod)%mod+1*az*c%mod)%mod+d)%mod;
			if((n-k+1)%2 == 1) {
				i64 aaz=(n+2*((n+n-1-2*(az-1))%mod)%mod*(az-1)%mod)%mod;
				ans=(ans-aaz+mod)%mod;
			}
//			put(ans), putchar('\n');
		}
		else {
			i64 az = (n-k+2)/2, aa=(3*n%mod+mod-2)%mod, a1 = 2*(n-2+n-3)%mod, 
			a=mod-4*inv3%mod, b = (4+1*a1*inv2)%mod, c = (mod-8*inv3%mod+mod-1*a1*inv2%mod)%mod, d = ((long long) mod+mod+mod-a-b-c)%mod;
			ans=2*((((1*aa*az%mod+1*az*az%mod*az%mod*a%mod)%mod+1*az*az%mod*b%mod)%mod+1*az*c%mod)%mod+d)%mod;
			if((n-k+1)%2 == 1) {
				i64 aaz=(aa+2*((n+n-3-2*(az-1))%mod)%mod*(az-1)%mod)%mod;
				ans=(ans-aaz+mod)%mod;
			}
//			put(ans), putchar('\n');
		}
		sum^=ans;
	}
	put(sum);
	return 0;
}
