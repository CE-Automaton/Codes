#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 105;
int n, k, dp[N][3289], dpp[N][3289], sum, ans;

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

signed main() {
	freopen("stone.in", "r", stdin);
	freopen("stone.out", "w", stdout);
	read(n), read(k);
	dpp[n+1][0]=1;
	for(int i = n; i >= 1; --i) {
		int mx = sum;
		for(int j = 0; j <= k; ++j) {
			if(j > i) {
				for(int lst = 0; lst <= sum; ++lst) 
					dp[i][lst]=upd(upd(dp[i][lst]+dp[i+1][lst])+1LL*j*dpp[i+1][lst]%mod), 
					dpp[i][lst]=upd(dpp[i][lst]+dpp[i+1][lst]);
			}
			else {
				for(int lst = 0; lst <= sum; ++lst) {
					if(lst >= i-j) {
						int gs = 1+(lst-i+j)/i;
						dp[i][lst+gs]=upd(upd(dp[i][lst+gs]+dp[i+1][lst])+1LL*upd(j-gs+mod)*dpp[i+1][lst]%mod);
						dpp[i][lst+gs]=upd(dpp[i][lst+gs]+dpp[i+1][lst]);
						mx=max(mx, lst+gs);
					}
					else
						dp[i][lst]=upd(upd(dp[i][lst]+dp[i+1][lst])+1LL*j*dpp[i+1][lst]%mod), 
						dpp[i][lst]=upd(dpp[i][lst]+dpp[i+1][lst]);
				}
			}
		}
		sum=max(sum, mx);
	} 
	for(int i = 0; i <= sum; ++i)
		ans=upd(ans+dp[1][i]);
	write(ans, '\n');
	return 0;
}
