#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e6+5;
int n, a[N], gs[N], dp[N], sum[N][5];

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

signed main() {
	File("division");
	read(n);
	int mm = 0;
	for(int i = 1; i <= n+n; ++i)
		read(a[i]), mm = max(mm, a[i]);
	if(mm == 2) {
		dp[0]=1;
		for(int i = 1; i <= n+n; ++i)
			sum[i][1]=sum[i-1][1], 
			sum[i][2]=sum[i-1][2], 
			++sum[i][a[i]];
		if(sum[n+n][1] != sum[n+n][2]) {
			puts("0");
			return 0;
		}
		int gs = 0, ret = 1, x = 2;
		for(int i = 1; i < n+n; ++i)
			gs+=(sum[i][1] == sum[i][2]);
		while(gs) {
			if(gs&1)
				ret=1LL*ret*x%mod;
			x=1LL*x*x%mod;
			gs=(gs>>1);
		}
		write(ret, '\n');
		return 0;
	}
	dp[0]=1;
	for(int i = 1; i <= n+n; ++i) {
		int mx = a[i];
		++gs[a[i]];
		for(int j = i-1; j >= 1; --j) {
			++gs[a[j]];
			if(gs[mx] < gs[a[j]])
				mx=a[j];
			if(gs[mx]*2 <= (i-j+1) && (i-j+1)%2 == 0)
				dp[i]=upd(dp[i]+dp[j-1]);
		}
		--gs[a[i]];
		for(int j = i-1; j >= 1; --j) 
			--gs[a[j]];
	}
	write(dp[n+n], '\n');
	return 0;
}
/*
3
1 1 2 3 4 5
*/