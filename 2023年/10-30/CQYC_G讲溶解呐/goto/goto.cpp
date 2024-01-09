#include <bits/stdc++.h>
#define inf 1000000000000000000LL
using namespace std;
const int N = 5e6+5;
int n, k;
long long sum[N], dp[N], sdp[N], ddp[N], ans;

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

signed main() {
	freopen("goto.in", "r", stdin);
	freopen("goto.out", "w", stdout);
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(sum[i]), sum[i]+=sum[i-1];
	sdp[0]=-inf;
	for(int i = 1; i <= n; ++i) {
		if(i > k)
			dp[i]=max(dp[i-1], sum[i]+max(0LL, sdp[i-k]));
		sdp[i]=max(sdp[i-1], dp[i]-sum[i]);
		ans=max(ans, dp[i]);
	}
	write(ans, '\n');
	return 0;
}
