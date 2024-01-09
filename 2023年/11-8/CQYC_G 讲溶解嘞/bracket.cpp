#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 4e3+5;
int t, n, dp[N];
char s[N];

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
	freopen("bracket.in", "r", stdin);
	freopen("bracket.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= 4000; ++i)
			dp[i]=0;
		dp[0]=1;
		int tot = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%s", s+1);
			int mx = 0, gs = 0, ln = strlen(s+1);
			for(int j = 1; j <= ln; ++j)
				gs+=(s[j] == '(' ? 1 : -1), 
				mx=min(mx, gs);
			mx=-mx;
			if(gs <= 0) {
				for(int j = mx; j <= tot; ++j)
					if(j+gs >= 0)
						dp[j+gs]=upd(dp[j+gs]+dp[j]);
			}
			else {
				for(int j = tot; j >= mx; --j)
					dp[j+gs]=upd(dp[j+gs]+dp[j]);
			}
			tot+=max(0, gs);
		}
		write(dp[0], '\n');
	}
	return 0;
}
