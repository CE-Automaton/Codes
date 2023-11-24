#include <bits/stdc++.h>
using namespace std;
int n, dp[2005], zhan[2005], tot;

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
	freopen("atom.in", "r", stdin);
	freopen("atom.out", "w", stdout);
	read(n);
	dp[2]=1;
	for(int i = 3; i <= n; ++i) 
		dp[i]=dp[i-1]+i/2;
//	write(n, '\n');
	write(dp[n], '\n');
//	for(int i = 1; i <= n-1; ++i) 
//		dp[0]+=min(i, n-i);
//	write(dp[0], '\n');
	for(int i = 1; i <= n-1; ++i) {
		int r = min(i, n-i);
		for(int l = 1; l <= r; ++l) {
			int now = l;
			tot=0;
			if(l != 1)
				zhan[++tot]=l-1;
			for(int j = 1; j <= (n-l)/i; ++j)
				zhan[++tot]=i, now+=i;
			if(now != n)
				zhan[++tot]=n-now;
			write(tot, ' ');
			for(int i = 1; i <= tot; ++i)
				write(zhan[i], ' ');
			putchar('\n');
		}
	} 
	return 0;
}
