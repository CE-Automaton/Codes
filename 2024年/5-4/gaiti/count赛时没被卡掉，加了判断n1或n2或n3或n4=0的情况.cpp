#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5;
int a, b, c, d, sum[405], dp[405][405/*+1个数*/][405/*-1个数*/], ans, jc[N+5], inv[N+5], inc[N+5], pw[N+5];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
int cc(int x, int y) {
	return (x < y ? 0 : 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod);
}

signed main() {
	// File("count");
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=1;
	pw[0]=1, pw[1]=2;
	for(int i = 2; i <= N; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, pw[i]=upd(pw[i-1]+pw[i-1]), 
		jc[i]=1LL*jc[i-1]*i%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	read(a), read(b), read(c), read(d);
	if(a == 0 && b == 0) {
		write((c == d-1 || c == d || c == d+1)+(c != 0 && c == d), '\n');
		return 0;
	}
	if(c == 0 && d == 0) {
		write((a == b-1 || a == b || a == b+1)+(a != 0 && a == b), '\n');
		return 0;
	}
	int mx = a+b+1;
	if(a > b) swap(a, b);
	if(c > d) swap(c, d);
	b-=a, d-=c;//+1个数 - -1个数 应该达到的值
	dp[0][0][0]=1;
	for(int i = 1; i <= mx; ++i) {//段数 
		for(int l = 0; l < i; ++l)
			for(int r = 0; r+l < i; ++r) 
				dp[i][l][r]=upd(dp[i][l][r]+dp[i-1][l][r]),
				dp[i][l+1][r]=upd(dp[i][l+1][r]+dp[i-1][l][r]),
				dp[i][l][r+1]=upd(dp[i][l][r+1]+dp[i-1][l][r]);
		for(int l = b; l <= i; ++l) {
			int r = l-b, pp = i-l-r;
			if(l+r <= i) { //计算第一组答案
				int op = a-r-pp;
				if(op >= 0) 
					sum[i]=upd(sum[i]+1LL*dp[i][l][r]*cc(op+i-1, i-1)%mod*pw[pp]%mod);
			}
		}
	}
	for(int i = 1; i <= mx; ++i) //段数 
		for(int l = d; l <= i; ++l) {
			int r = l-d, pp = i-l-r;
			if(l+r <= i) { //计算最终的答案
				int op = c-r-pp;
				if(op >= 0) {
					int ww = 1LL*dp[i][l][r]*cc(op+i-1, i-1)%mod*pw[pp]%mod;
					ans=upd(ans+2LL*sum[i]%mod*ww%mod), 
					ans=upd(ans+1LL*sum[i-1]%mod*ww%mod), 
					ans=upd(ans+1LL*sum[i+1]%mod*ww%mod);
				}
			}
		}
	write(ans, '\n');
	return 0;
}