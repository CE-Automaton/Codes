#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const signed N = 5e3+5;
int n, m, k, p[N], s[N], dp[2][(1<<20)+5];

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
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("childhood.in", "r", stdin);
	freopen("childhood.out", "w", stdout);
	read(n), read(m);
	int now = 0;
	dp[now][0]=1; 
	for(int i = 1; i <= n; ++i) {
		now^=1;
		for(int j = 0; j <= (1<<m)-1; ++j)
			dp[now][j]=0;
		read(k);
		int sm = 0;
		for(int j = 1; j <= k; ++j)
			read(s[j]), read(p[j]), sm+=p[j];
		sm=ksm(sm, mod-2);
		for(int j = 0; j <= (1<<m)-1; ++j)
			for(int o = 1; o <= k; ++o)
				dp[now][j|s[o]]=upd(dp[now][j|s[o]]+1LL*dp[now^1][j]*sm%mod*p[o]%mod);
	}
	for(int j = 0; j <= (1<<m)-1; ++j)
		write(dp[now][j], ' ');
	return 0;
}
