#include <bits/stdc++.h>
#define inf 2000000003
using namespace std;
const int N = 5e5+5, NN = 2e3+5;
int typ, n, m, a[N], dp[NN][NN], ans;

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
	freopen("necklace.in", "r", stdin);
	freopen("necklace.out", "w", stdout);
	read(typ), read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	if(typ <= 4) {
		ans=inf;
		for(int l = 1; l+m-1 <= n; ++l) {
			for(int r = l; r <= n; ++r)
				for(int j = 0; j <= m; ++j)
					dp[r][j]=inf;
			dp[l][1]=0;
			for(int r = l+1; r <= n; ++r)
				for(int lst = l; lst < r; ++lst)
					for(int gs = 1; gs <= m && l+gs-1 <= lst; ++gs)
						dp[r][gs+1]=min(dp[r][gs+1], max(dp[lst][gs], a[r]+a[lst]));
			for(int r = l+1; r <= n; ++r)
				dp[r][m]=max(dp[r][m], a[r]+a[l]), 
				ans=min(ans, dp[r][m]);
		}
		write(ans, '\n');
		return 0;
	} 
	if(m == 2) {
		sort(a+1, a+1+n);
		write(a[1]+a[2], '\n');
	} 
	else {
		srand(time(0));
		write(a[rand()%n+1]+a[rand()%n+1], '\n');
	}
	return 0;
}
