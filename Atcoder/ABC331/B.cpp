#include <bits/stdc++.h>
using namespace std;
int n, s, l, m, dp[2005];

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
	read(n);
	read(s), read(m), read(l);
	memset(dp, 0x3f, sizeof dp);
	dp[0]=0;
	for(int i = 6; i <= 200; ++i)
		dp[i]=min(dp[i], dp[i-6]+s);
	for(int i = 8; i <= 200; ++i)
		dp[i]=min(dp[i], dp[i-8]+m);
	for(int i = 12; i <= 200; ++i)
		dp[i]=min(dp[i], dp[i-12]+l);
	int ans = 0x3f3f3f3f;
	for(int i = n; i <= 200; ++i)
		ans=min(ans, dp[i]);
	write(ans, '\n');
	return 0;
}
